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

	void CodeReader::setCache(const CodeReaderElement& elem)
	{
		_cache.push_back(elem);
	}
}




namespace parser
{
	Token::Token(const Token& right) :
		_type{ right._type },
		_data{},
		start_position{ right.start_position },
		end_position{ right.end_position }
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
		start_position{ std::move(right.start_position) },
		end_position{ std::move(right.end_position) }
	{
		right._type = TokenType::Invalid;
		right._data = {};
		right.start_position = {};
		right.end_position = {};
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



namespace parser
{
	namespace
	{
		std::unordered_map<std::string, Token> builtin_tokens;
	}

	void init_builtin_tokens()
	{
		#define increase_enum(_Value, _EnumType, _Type) static_cast<_EnumType>(static_cast<_Type>(_Value) + 1)
		if (builtin_tokens.empty())
		{
			for (Command cmd = Command::If; cmd <= Command::Yield; cmd = increase_enum(cmd, Command, int))
				builtin_tokens.insert({ lang::get_name(cmd), Token::command(cmd) });

			for (RawType type = RawType::Int; type <= RawType::Vehicle; type = increase_enum(type, RawType, int))
				builtin_tokens.insert({ DataType::get_type_langname(type), Token::type(type) });

			for (TypeModifier mod = TypeModifier::Var; mod <= TypeModifier::Internal; mod = increase_enum(mod, TypeModifier, int))
				builtin_tokens.insert({ DataType::get_modifier_langname(mod), Token::type(mod) });

			for(ScriptInternal internal = ScriptInternal::GameTurn; internal <= ScriptInternal::GreenMana; internal = increase_enum(internal, ScriptInternal, ScriptCode))
				builtin_tokens.insert({ lang::get_name(internal), Token::literalInternal(internal) });

			for (ScriptInternal internal = ScriptInternal::AttrExpansion; internal <= ScriptInternal::Bloodlust; internal = increase_enum(internal, ScriptInternal, ScriptCode))
				builtin_tokens.insert({ lang::get_name(internal), Token::literalInternal(internal) });

			for (ScriptToken token = ScriptToken::ConstructBuilding; token <= ScriptToken::IsPrisonOnLevel; token = increase_enum(token, ScriptToken, ScriptCode))
				builtin_tokens.insert({ lang::get_name(token), Token::literalData(token) });

			builtin_tokens.insert({ lang::get_name(ScriptToken::On), Token::literalData(ScriptToken::On) });
			builtin_tokens.insert({ lang::get_name(ScriptToken::Off), Token::literalData(ScriptToken::Off) });

			builtin_tokens.insert({ "yield", Token::yield() });
		}
		#undef increase_enum
	}

	Token get_builtin_token(const std::string& identifier)
	{
		const auto it = builtin_tokens.find(identifier);
		return it == builtin_tokens.end() ? Token() : it->second;
	}
}



void ErrorManager::registerError(const SourcePosition& begin, const parser::CodeReaderElement& elem, const std::string& message)
{
	registerError(begin, elem.position + utils::column_value(1), message);
}




namespace parser
{
	bool is_valid_identifier(const std::string& str)
	{
		static const std::regex pattern("[_a-zA-Z][_a-zA-Z0-9]*");
		return std::regex_match(str, pattern);
	}

	namespace
	{
		static inline bool is_valid_literal_integer(const std::string& str)
		{
			static const std::regex pattern("[+-]?[0-9]+");
			return std::regex_match(str, pattern);
		}

		static inline Int32 parse_integer(const std::string& str)
		{
			return static_cast<Int32>(std::stol(str));
		}

		static Token parse_token_identifier(const std::string& identifier, const SourcePosition& pbegin, const SourcePosition& pend, ErrorManager& errors)
		{
			Token token = get_builtin_token(identifier);
			if (!token.isInvalid())
				return token.injectPosition(pbegin, pend);

			if (is_valid_literal_integer(identifier))
				return Token::literalInteger(parse_integer(identifier), pbegin, pend);

			if (is_valid_identifier(identifier))
				return Token::identifier(identifier, pbegin, pend);

			errors.registerError(pbegin, pend, std::format("Unknown identifier: '{}'", identifier));
			return Token::invalid(pbegin, pend);
		}

		static Token parse_token(CodeReader& input, ErrorManager& errors)
		{
			#define ss_flush(_Ss, _Elem, _PBegin) if(ss.tellp() > 0) \
					return input.setCache((_Elem)), parse_token_identifier((_Ss).str(), (_PBegin), (_Elem).position, errors)

			std::ostringstream ss;
			CodeReaderElement elem;
			SourcePosition pbegin;
			bool first = true;

			while (elem = input.next())
			{
				if (first)
				{
					first = false;
					pbegin = elem.position;
				}

				switch (elem.character)
				{
					case '\n':
					case '\t':
					case '\r':
					case ' ':
						if (ss.tellp() > 0)
							return parse_token_identifier(ss.str(), pbegin, elem.position, errors);
						break;

					case ';':
						ss_flush(ss, elem, pbegin);
						return Token::statementEnd(elem.position);

					case '(':
						ss_flush(ss, elem, pbegin);
						return Token::parenthesisOpen(elem.position);

					case ')':
						ss_flush(ss, elem, pbegin);
						return Token::parenthesisClose(elem.position);

					case '{':
						ss_flush(ss, elem, pbegin);
						return Token::blockOpen(elem.position);

					case '}':
						ss_flush(ss, elem, pbegin);
						return Token::blockClose(elem.position);

					case '\"':
					case '\'': {
						ss_flush(ss, elem, pbegin);

						const char cend = elem.character;
						while (input.hasMoreData())
						{
							if (!(elem = input.next()))
							{
								errors.registerError(pbegin, elem, "Invalid token within a string.");
								return Token::invalid(pbegin, elem.position);
							}

							//if(elem.)
						}
						
					} break;
				}
			}

			return Token::invalid(pbegin, elem.position);
			#undef ss_flush
		}
	}

	std::vector<Token> parse(CodeReader& input, ErrorManager& errors)
	{
		std::vector<Token> tokens;
		tokens.reserve(utils::ScriptCodeCount + 1);

		while (input.hasMoreData())
		{
			Token token = parse_token(input, errors);
			if (!token.isInvalid())
				tokens.push_back(std::move(token));
		}

		return tokens;
	}
}
