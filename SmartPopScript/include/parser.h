#pragma once

#include "common.h"
#include "script.h"
#include "langdata.h"
#include "errors.h"

namespace parser
{
	struct CodeReaderElement
	{
		char character;
		SourcePosition position;

		inline operator bool() const { return character || position.row || position.column; }
		inline bool operator! () const { return !character && !position.row && !position.column; }

		inline bool isInvalid() const { return !(*this); }
	};

	class CodeReader
	{
	private:
		static constexpr Size buffer_len = 8192;

	private:
		std::unique_ptr<std::istream> _in;
		std::deque<CodeReaderElement> _cache;
		utils::DynamicArray<char> _buffer;
		Size _bufferCount;
		Offset _bufferOff;
		Offset _row;
		Offset _col;

	public:
		CodeReader() = default;
		CodeReader(const CodeReader&) = delete;
		CodeReader(CodeReader&& right) noexcept = default;
		~CodeReader() = default;

		CodeReader& operator= (const CodeReader&) = delete;
		CodeReader& operator= (CodeReader&& right) noexcept = default;

	public:
		CodeReader(std::istream* input);
		CodeReader(const Path& path);
		CodeReader(const std::string& code);

		CodeReaderElement next();

		CodeReaderElement peekNext(Size extra_displ = 0);

		void setCache(const CodeReaderElement& elem);

	public:
		inline bool hasNext(Size extra_displ = 0) { return peekNext(extra_displ); }

		inline bool hasMoreData() { return _in && *_in && !_in->eof(); }
	};


	enum class TokenType
	{
		Invalid,

		Identifier,

		DataType,

		Command,

		LiteralString,
		LiteralInteger,
		LiteralData,
		LiteralInternal,

		StatementEnd,

		ParenthesisOpen,
		ParenthesisClose,

		BlockOpen,
		BlockClose,

		Operator,

		ElvisSeparatorPart,

		Yield
	};

	class Token
	{
	private:
		TokenType _type;
		union Data {
			std::string* identifier;
			DataType* type;
			Command command;
			std::string* literalString;
			Int32 literalInteger;
			ScriptToken literalData;
			ScriptInternal literalInternal;
			Operator oper;
		} _data;

	public:
		SourcePosition start_position;
		SourcePosition end_position;

	private:
		inline Token(TokenType type, Data data, const SourcePosition& begin, const SourcePosition& end) :
			_type{ type },
			_data{ data },
			start_position{ begin },
			end_position{ end }
		{}
		inline Token(TokenType type, Data data, const SourcePosition& begin) :
			_type{ type },
			_data{ data },
			start_position{ begin },
			end_position{ begin.row, begin.column + 1 }
		{}

	public:
		Token() = default;

		Token(const Token& right);
		Token(Token&& right) noexcept;
		~Token();

		inline Token& operator= (const Token& right)
		{
			return utils::destroy(*this), utils::copy_construct(*this, right);
		}

		inline Token& operator= (Token&& right) noexcept
		{
			return utils::destroy(*this), utils::move_construct(*this, std::move(right));
		}

	public:
		inline bool isInvalid() const { return _type == TokenType::Invalid; }
		inline bool isIdentifier() const { return _type == TokenType::Identifier; }
		inline bool isDataType() const { return _type == TokenType::DataType; }
		inline bool isCommand() const { return _type == TokenType::Command; }
		inline bool isLiteralString() const { return _type == TokenType::LiteralString; }
		inline bool isLiteralInteger() const { return _type == TokenType::LiteralInteger; }
		inline bool isLiteralData() const { return _type == TokenType::LiteralData; }
		inline bool isLiteralInternal() const { return _type == TokenType::LiteralInternal; }
		inline bool isStatementEnd() const { return _type == TokenType::StatementEnd; }
		inline bool isParenthesisOpen() const { return _type == TokenType::ParenthesisOpen; }
		inline bool isParenthesisClose() const { return _type == TokenType::ParenthesisClose; }
		inline bool isBlockOpen() const { return _type == TokenType::BlockOpen; }
		inline bool isBlockClose() const { return _type == TokenType::BlockClose; }
		inline bool isOperator() const { return _type == TokenType::Operator; }
		inline bool isElvisSeparatorPart() const { return _type == TokenType::ElvisSeparatorPart; }
		inline bool isYield() const { return _type == TokenType::Yield; }

		inline TokenType getType() const { return _type; }

		inline const std::string& getIdentifier() const { return *_data.identifier; }
		inline const DataType& getDataType() const { return *_data.type; }
		inline Command getCommand() const { return _data.command; }
		inline const std::string& getLiteralString() const { return *_data.literalString; }
		inline Int32 getLiteralInteger() const { return _data.literalInteger; }
		inline ScriptToken getLiteralData() const { return _data.literalData; }
		inline ScriptInternal getLiteralInternal() const { return _data.literalInternal; }
		inline Operator getOperator() const { return _data.oper; }

		inline Token& injectPosition(const SourcePosition& position)
		{
			start_position = position;
			end_position = { position.row, position.column + 1 };
			return *this;
		}
		inline Token& injectPosition(const SourcePosition& begin, const SourcePosition& end)
		{
			start_position = utils::min(begin, end);
			end_position = utils::max(end, begin);
			return *this;
		}

	public:
		static inline Token identifier(const std::string& identifier, const SourcePosition& pbegin = {}, const SourcePosition& pend = {})
		{
			return { TokenType::Identifier, { .identifier = new std::string(identifier) }, pbegin, pend };
		}

		static inline Token type(const DataType& type, const SourcePosition& pbegin = {}, const SourcePosition& pend = {})
		{
			return { TokenType::DataType, { .type = new DataType(type) }, pbegin, pend };
		}

		static inline Token command(Command cmd, const SourcePosition& pbegin = {}, const SourcePosition& pend = {})
		{
			return { TokenType::Command, { .command = cmd }, pbegin, pend };
		}

		static inline Token literalString(const std::string& identifier, const SourcePosition& pbegin = {}, const SourcePosition& pend = {})
		{
			return { TokenType::LiteralString, { .literalString = new std::string(identifier) }, pbegin, pend };
		}

		static inline Token literalInteger(Int32 value, const SourcePosition& pbegin = {}, const SourcePosition& pend = {})
		{
			return { TokenType::LiteralInteger, { .literalInteger = value }, pbegin, pend };
		}

		static inline Token literalData(ScriptToken value, const SourcePosition& pbegin = {}, const SourcePosition& pend = {})
		{
			if (!codes::is_valid(value) || codes::is_command(value))
				return {};
			return { TokenType::LiteralData, { .literalData = value }, pbegin, pend };
		}

		static inline Token literalInternal(ScriptInternal value, const SourcePosition& pbegin = {}, const SourcePosition& pend = {})
		{
			return { TokenType::LiteralInternal, { .literalInternal = value }, pbegin, pend };
		}

		static inline Token statementEnd(const SourcePosition& position = {})
		{
			return { TokenType::StatementEnd, {}, position };
		}

		static inline Token parenthesisOpen(const SourcePosition& position = {})
		{
			return { TokenType::ParenthesisOpen, {}, position };
		}

		static inline Token parenthesisClose(const SourcePosition& position = {})
		{
			return { TokenType::ParenthesisClose, {}, position };
		}

		static inline Token blockOpen(const SourcePosition& position = {})
		{
			return { TokenType::BlockOpen, {}, position };
		}

		static inline Token blockClose(const SourcePosition& position = {})
		{
			return { TokenType::BlockClose, {}, position };
		}

		static inline Token oper(Operator op, const SourcePosition& position = {}, bool is_unary = true)
		{
			return { TokenType::Operator, { .oper = op }, position, position + utils::column_value(is_unary ? 1 : 2) };
		}

		static inline Token elvisSeparatorPart(const SourcePosition& position = {})
		{
			return { TokenType::ElvisSeparatorPart, {}, position };
		}

		static inline Token yield(const SourcePosition& pbegin = {}, const SourcePosition& pend = {})
		{
			return { TokenType::Yield, {}, pbegin, pend };
		}

		static inline Token invalid(const SourcePosition& pbegin = {}, const SourcePosition& pend = {})
		{
			return { TokenType::Invalid, {}, pbegin, pend };
		}
	};


	void init_builtin_tokens();
	Token get_builtin_token(const std::string& identifier);

	bool is_valid_identifier(const std::string& str);

	std::vector<Token> parse(CodeReader& input, ErrorManager& errors);
}
