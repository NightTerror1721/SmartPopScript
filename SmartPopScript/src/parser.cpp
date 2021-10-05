#include "parser.h"

namespace parser
{
	CodeReader::CodeReader(std::istream* input) :
		_in{ input },
		_cache{},
		_buffer(buffer_len),
		_bufferCount{ 0 },
		_bufferOff{ 0 },
		_row{ 0 },
		_col{ 0 }
	{}

	CodeReader::CodeReader(const Path& path) :
		CodeReader{ new std::ifstream{ path, std::ios::in } }
	{}

	CodeReader::CodeReader(const std::string& code) :
		CodeReader{ new std::istringstream{ code } }
	{}

	CodeReaderElement CodeReader::next()
	{
		if (!_cache.empty())
		{
			CodeReaderElement elem = _cache.front();
			_cache.pop_front();
			return elem;
		}

		if (_bufferOff >= _bufferCount)
		{
			_in->read(_buffer.data(), buffer_len);
			std::streamsize count = _in->gcount();
			if (count < 1)
			{
				_bufferCount = static_cast<Size>(count);
				_bufferOff = _bufferCount = 0;
				return {};
			}
			else _bufferOff = 0;
		}

		CodeReaderElement elem{
			.character = _buffer[_bufferOff++],
			.position = { .row = _row, .column = _col++ }
		};
		if (elem.character == '\n')
		{
			_row++;
			_col = 0;
		}

		return elem;
	}

	CodeReaderElement CodeReader::peekNext(Size extra_displ)
	{
		if (extra_displ == 0)
		{
			if (!_cache.empty())
				return _cache.front();

			CodeReaderElement elem = next();
			if (elem)
				_cache.push_back(elem);
			return elem;
		}
		else
		{
			extra_displ++;
			if (_cache.size() == extra_displ)
				return _cache.back();
			if (_cache.size() < extra_displ)
				extra_displ -= _cache.size();

			CodeReaderElement elem = {};
			for (; extra_displ > 0; --extra_displ)
			{
				elem = next();
				if (elem)
					_cache.push_back(elem);
				else break;
			}
			return elem;
		}
	}
}




namespace parser
{
	Token::Token(const Token& right) :
		_type{ right._type },
		_data{},
		position{ right.position }
	{
		switch (_type)
		{
			using enum TokenType;

			case Identifier:
				_data.identifier = new std::string{ *right._data.identifier };
				break;

			case DataType:
				_data.type = new ::DataType{ *right._data.type };
				break;

			case Command:
				_data.command = right._data.command;
				break;

			case LiteralString:
				_data.literalString = new std::string{ *right._data.literalString };
				break;

			case LiteralInteger:
				_data.literalInteger = right._data.literalInteger;
				break;

			case LiteralData:
				_data.literalData = right._data.literalData;
				break;

			case LiteralInternal:
				_data.literalInternal = right._data.literalInternal;
				break;

			case Operator:
				_data.oper = right._data.oper;
				break;
		}
	}

	Token::Token(Token&& right) noexcept :
		_type{ right._type },
		_data{ right._data },
		position{ right.position }
	{
		right._type = TokenType::Invalid;
		right._data = {};
		right.position = {};
	}

	Token::~Token()
	{
		switch (_type)
		{
			using enum TokenType;

			case Identifier:
				if (_data.identifier)
					delete _data.identifier;
				break;

			case DataType:
				if (_data.type)
					delete _data.type;
				break;

			case LiteralString:
				if (_data.literalString)
					delete _data.literalString;
				break;
		}
	}
}
