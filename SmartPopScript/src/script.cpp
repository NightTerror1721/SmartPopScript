#include "script.h"

void ScriptField::validate()
{
	switch (_type)
	{
		using enum Type;

		case Constant:
			break;

		case User:
			if (_data.variable_index < 0 || _data.variable_index >= utils::ScriptMaxVariableCount)
			{
				_type = Type::Invalid;
				_data = {};
			}
			break;

		case Internal:
			if (!codes::is_valid(_data.internal_index))
			{
				_type = Type::Invalid;
				_data = {};
			}
			break;

		case Invalid:
			break;

		default:
			_type = Type::Invalid;
			_data = {};
			break;
	}
}

void ScriptField::write(std::ostream& output) const
{
	static constexpr Type invalid_type = Type::Invalid;
	static constexpr decltype(_data) invalid_data = { .constant_value = 0 };

	switch (_type)
	{
		using enum Type;

		case Constant:
		case User:
		case Internal:
			output.write(reinterpret_cast<const char*>(&_type), sizeof(_type));
			output.write(reinterpret_cast<const char*>(&_data), sizeof(_data));
			break;

		case Invalid:
			break;

		default:
			output.write(reinterpret_cast<const char*>(&invalid_type), sizeof(invalid_type));
			output.write(reinterpret_cast<const char*>(&invalid_data), sizeof(invalid_data));
			break;
	}
}

void ScriptField::read_fields(void* ptr)
{
	ScriptField* const nextLastField = reinterpret_cast<ScriptField*>(ptr) + utils::ScriptFieldCount;
	for (ScriptField* field = reinterpret_cast<ScriptField*>(ptr); field < nextLastField; ++field)
		field->validate();
}



void Script::insert_codes(Offset index, const ScriptCode* codes, Size len)
{
	check_code_bounds((index + len) - 1);
	std::memcpy(_code.data() + index, codes, sizeof(ScriptCode) * len);
}

void Script::insert_fields(Offset index, const ScriptField* fields, Size len)
{
	check_field_bounds((index + len) - 1);
	std::memcpy(_fields.data() + index, fields, sizeof(ScriptField) * len);
}

bool Script::check_version(std::istream& input)
{
	ScriptVersionType version;
	if (!utils::read_fully(&version, input, utils::ScriptVersionSize))
		return false;

	return version.code == utils::ScriptVersion.code;
}

bool Script::read(std::istream& input)
{
	if (!check_version(input))
		return false;

	if (!utils::read_fully(_code.data(), input, utils::ScriptCodeSize))
		return false;

	if (!utils::read_fully(_fields.data(), input, utils::ScriptFieldsSize))
		return false;
	ScriptField::read_fields(_fields.data());

	return utils::skip(input, utils::ScriptPaddingSize);
}

bool Script::read(const Path& path)
{
	bool result = false;
	std::ifstream f{ path, std::ios::in | std::ios::binary };
	if (f.good())
		result = read(f);
	f.close();
	return result;
}

bool Script::write(std::ostream& output) const
{
	output.write(reinterpret_cast<const char*>(&utils::ScriptVersion), utils::ScriptVersionSize);
	output.write(reinterpret_cast<const char*>(_code.data()), utils::ScriptCodeSize);

	for (int i = 0; i < utils::ScriptFieldCount; ++i)
		_fields[i].write(output);

	static char padding[utils::ScriptPaddingSize] = { 1 };
	if (padding[0] == 1)
		std::memset(padding, 0, sizeof(padding));
	
	output.write(padding, utils::ScriptPaddingSize);

	return output.good();
}

bool Script::write(const Path& path) const
{
	bool result = false;
	std::ofstream f{ path, std::ios::out | std::ios::binary };
	if (f.good())
		result = write(f);
	f.close();
	return result;
}

std::ostream& operator<< (std::ostream& left, const Script& right)
{
	return right.write(left), left;
}

std::istream& operator>> (std::istream& left, Script& right)
{
	return right.read(left), left;
}
