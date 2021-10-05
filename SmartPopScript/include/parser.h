#pragma once

#include "common.h"
#include "script.h"
#include "langdata.h"

namespace parser
{
	struct SourcePosition
	{
		Offset row;
		Offset column;

		bool operator== (const SourcePosition&) const = default;
	};

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

	public:
		inline bool hasNext(Size extra_displ = 0) { return peekNext(extra_displ); }
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

		ParenthesisOpen,
		ParenthesisClose,

		BlockOpen,
		BlockClose,

		Operator,

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
		SourcePosition position;

	private:
		inline Token(TokenType type, Data data) :
			_type{ type },
			_data{ data },
			position{}
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
		inline bool isParenthesisOpen() const { return _type == TokenType::ParenthesisOpen; }
		inline bool isParenthesisClose() const { return _type == TokenType::ParenthesisClose; }
		inline bool isBlockOpen() const { return _type == TokenType::BlockOpen; }
		inline bool isBlockClose() const { return _type == TokenType::BlockClose; }
		inline bool isOperator() const { return _type == TokenType::Operator; }
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

	public:
		static inline Token identifier(const std::string& identifier)
		{
			return { TokenType::Identifier, { .identifier = new std::string(identifier) } };
		}

		static inline Token type(const DataType& type)
		{
			return { TokenType::DataType, { .type = new DataType(type) } };
		}

		static inline Token command(Command cmd)
		{
			return { TokenType::Command, { .command = cmd } };
		}

		static inline Token literalString(const std::string& identifier)
		{
			return { TokenType::LiteralString, { .literalString = new std::string(identifier) } };
		}

		static inline Token literalInteger(Int32 value)
		{
			return { TokenType::LiteralInteger, { .literalInteger = value } };
		}

		static inline Token literalData(ScriptToken value)
		{
			if (!codes::is_valid(value) || codes::is_command(value))
				return {};
			return { TokenType::LiteralData, { .literalData = value } };
		}

		static inline Token literalInternal(ScriptInternal value)
		{
			return { TokenType::LiteralInternal, { .literalInternal = value } };
		}

		static inline Token parenthesisOpen()
		{
			return { TokenType::ParenthesisOpen, {} };
		}

		static inline Token parenthesisClose()
		{
			return { TokenType::ParenthesisClose, {} };
		}

		static inline Token blockOpen()
		{
			return { TokenType::BlockOpen, {} };
		}

		static inline Token blockClose()
		{
			return { TokenType::BlockClose, {} };
		}

		static inline Token oper(Operator op)
		{
			return { TokenType::Operator, { .oper = op } };
		}

		static inline Token yield()
		{
			return { TokenType::Yield, {} };
		}
	};
}
