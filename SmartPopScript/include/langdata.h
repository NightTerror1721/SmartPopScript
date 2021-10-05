#pragma once

#include "script.h"

enum class TypeModifier
{
	Default,
	Var,
	Const,
	Internal
};

enum class RawType
{
	Int,
	State,
	Action,
	Tribe,
	AttackTarget,
	AttackMode,
	GuardMode,
	CountWild,
	Shot,
	Vehicle
};

class DataType
{
private:
	TypeModifier _modifier = TypeModifier::Default;
	RawType _type = RawType::Int;

public:
	constexpr DataType() = default;
	constexpr DataType(const DataType&) = default;
	constexpr DataType(DataType&&) noexcept = default;
	constexpr ~DataType() = default;

	constexpr DataType& operator= (const DataType&) = default;
	constexpr DataType& operator= (DataType&&) noexcept = default;

public:
	constexpr DataType(TypeModifier modifier, RawType type) :
		_modifier(modifier),
		_type(type)
	{}

	constexpr DataType(RawType type) :
		_modifier(TypeModifier::Default),
		_type(type)
	{}

	constexpr DataType(TypeModifier modifier) :
		_modifier(modifier),
		_type(RawType::Int)
	{}

	constexpr TypeModifier modifier() const { return _modifier; }
	constexpr RawType type() const { return _type; }

	constexpr bool isVar() const
	{
		return _modifier == TypeModifier::Var ||
			(_modifier == TypeModifier::Default && _type == RawType::Int);
	}

	constexpr bool isConst() const { return _modifier == TypeModifier::Const; }

	constexpr bool isInternal() const
	{
		return _modifier == TypeModifier::Internal ||
			(_modifier == TypeModifier::Default && _type != RawType::Int);
	}

public:
	constexpr bool operator== (const DataType& right) const
	{
		if (_type != right._type)
			return false;

		if (_modifier == TypeModifier::Default)
		{
			if (_type == RawType::Int)
				return right._modifier == TypeModifier::Default || right._modifier == TypeModifier::Var;
			return right._modifier == TypeModifier::Default || right._modifier == TypeModifier::Internal;
		}

		if (right._modifier == TypeModifier::Default)
		{
			if (_type == RawType::Int)
				return _modifier == TypeModifier::Var;
			return _modifier == TypeModifier::Internal;
		}

		return _modifier == right._modifier;
	}

public:
	static constexpr const char* get_modifier_langname(TypeModifier modifier)
	{
		switch (modifier)
		{
			using enum TypeModifier;

			case Default: return "";
			case Var: return "var";
			case Const: return "const";
			case Internal: return "internal";

			default: return "<invalid-type-modifier>";
		}
	}

	static constexpr const char* get_type_langname(RawType type)
	{
		switch (type)
		{
			using enum RawType;

			case Int: return "int";
			case State: return "state_t";
			case Action: return "action_t";
			case Tribe: return "tribe_t";
			case AttackTarget: return "attack_target_t";
			case AttackMode: return "attack_mode_t";
			case GuardMode: return "guard_mode_t";
			case CountWild: return "count_wild_t";
			case Shot: return "shot_t";
			case Vehicle: return "vehicle_t";

			default: return "<invalid-raw-type>";
		}
	}
};

enum class Operator
{
	FieldResolver,

	Call,

	SufixIncrease,
	SufixDecrease,

	PrefixIncrease,
	PrefixDecrease,
	Not,
	UnaryMinus,

	Multiply,
	Divide,

	Add,
	Subtract,

	Greater,
	Less,
	GreaterEquals,
	LessEquals,

	Equals,
	NotEquals,

	And,

	Or,

	Elvis,

	Assignment,
	AssignmentAdd,
	AssignmentSubtract,
	AssignmentMultiply,
	AssignmentDivide
};

namespace lang
{
	constexpr int get_priority(Operator op)
	{
		switch (op)
		{
			using enum Operator;

			case FieldResolver:
				return 11;

			case Call:
				return 10;

			case SufixIncrease:
			case SufixDecrease:
				return 9;

			case PrefixIncrease:
			case PrefixDecrease:
			case Not:
			case UnaryMinus:
				return 8;

			case Multiply:
			case Divide:
				return 7;

			case Add:
			case Subtract:
				return 6;

			case Greater:
			case Less:
			case GreaterEquals:
			case LessEquals:
				return 5;

			case Equals:
			case NotEquals:
				return 4;

			case And:
				return 3;

			case Or:
				return 2;

			case Elvis:
				return 1;

			case Assignment:
			case AssignmentAdd:
			case AssignmentSubtract:
			case AssignmentMultiply:
			case AssignmentDivide:
				return 0;

			default:
				return -1;
		}
	}

	constexpr const char* get_symbol(Operator op)
	{
		switch (op)
		{
			using enum Operator;

			case FieldResolver: return ".";
			case Call: return "()";
			case SufixIncrease: return "++";
			case SufixDecrease: return "--";
			case PrefixIncrease: return "++";
			case PrefixDecrease: return "--";
			case Not: return "!";
			case UnaryMinus: return "-";
			case Multiply: return "*";
			case Divide: return "/";
			case Add:return "+";
			case Subtract: return "-";
			case Greater:return ">";
			case Less: return "<";
			case GreaterEquals: return ">=";
			case LessEquals: return "<=";
			case Equals: return "==";
			case NotEquals: return "!=";
			case And: return "&&";
			case Or: return "||";
			case Elvis: return "?:";
			case Assignment: return "=";
			case AssignmentAdd: return "+=";
			case AssignmentSubtract: return "-=";
			case AssignmentMultiply: return "*=";
			case AssignmentDivide: return "/=";

			default: "<invalid-operator>";
		}
	}

	constexpr bool has_left_order(Operator op)
	{
		switch (op)
		{
			using enum Operator;

			case FieldResolver: return true;
			case Call: return true;
			case SufixIncrease: return true;
			case SufixDecrease: return true;
			case PrefixIncrease: return false;
			case PrefixDecrease: return false;
			case Not: return false;
			case UnaryMinus: return false;
			case Multiply: return true;
			case Divide: return true;
			case Add:return true;
			case Subtract: return true;
			case Greater:return true;
			case Less: return true;
			case GreaterEquals: return true;
			case LessEquals: return true;
			case Equals: return true;
			case NotEquals: return true;
			case And: return true;
			case Or: return true;
			case Elvis: return true;
			case Assignment: return false;
			case AssignmentAdd: return false;
			case AssignmentSubtract: return false;
			case AssignmentMultiply: return false;
			case AssignmentDivide: return false;

			default: "<invalid-operator>";
		}
	}

	constexpr bool has_right_order(Operator op)
	{
		return !has_left_order(op);
	}

	constexpr std::strong_ordering operator<=> (Operator left, Operator right)
	{
		int pleft = get_priority(left);
		int pright = get_priority(right);
		if (pleft == pright)
			return has_left_order(left) || has_right_order(right)
				? std::strong_ordering::less
				: std::strong_ordering::equal;
		return pleft < pright ? std::strong_ordering::less : std::strong_ordering::greater;
	}

	constexpr bool has_priority_over(Operator left, Operator right)
	{
		return left > right;
	}

	constexpr bool is_unary(Operator op)
	{
		return static_cast<int>(op) >= static_cast<int>(Operator::SufixIncrease) &&
			static_cast<int>(op) <= static_cast<int>(Operator::UnaryMinus);
	}

	constexpr bool is_sufix_unary(Operator op)
	{
		return op == Operator::SufixIncrease || op == Operator::SufixDecrease;
	}

	constexpr bool is_prefix_unary(Operator op)
	{
		return static_cast<int>(op) >= static_cast<int>(Operator::PrefixIncrease) &&
			static_cast<int>(op) <= static_cast<int>(Operator::UnaryMinus);
	}

	constexpr bool is_binary(Operator op)
	{
		return static_cast<int>(op) >= static_cast<int>(Operator::Multiply) &&
			static_cast<int>(op) <= static_cast<int>(Operator::Or);
	}

	constexpr bool is_assignment(Operator op)
	{
		return static_cast<int>(op) >= static_cast<int>(Operator::Assignment) &&
			static_cast<int>(op) <= static_cast<int>(Operator::AssignmentDivide);
	}

	constexpr bool is_elvis(Operator op)
	{
		return op == Operator::Elvis;
	}

	constexpr bool is_call(Operator op)
	{
		return op == Operator::Call;
	}

	constexpr bool is_field_resolver(Operator op)
	{
		return op == Operator::FieldResolver;
	}
}



enum class Command
{
	If,
	Else,
	Every,
	Macro,
	Main,
	Import,
	Namespace,
	Yield
};

namespace lang
{
	constexpr const char* get_name(Command cmd)
	{
		switch (cmd)
		{
			using enum Command;

			case If: return "if";
			case Else: return "else";
			case Every: return "every";
			case Macro: return "macro";
			case Main: return "main";
			case Import: return "import";
			case Namespace: return "namespace";
			case Yield: return "yield";

			default: return "<invalid-command>";
		}
	}
}



namespace lang
{
	constexpr DataType get_type(ScriptToken value)
	{
		using enum RawType;

		if (codes::is_state_t(value))
			return State;
		if (codes::is_action(value))
			return Action;
		if (codes::is_tribe_t(value))
			return Tribe;
		if (codes::is_attack_mode_t(value))
			return AttackMode;
		if (codes::is_attack_target_t(value))
			return AttackTarget;
		if (codes::is_guard_mode_t(value))
			return GuardMode;
		if (codes::is_shot_t(value))
			return Shot;
		if (codes::is_vehicle_t(value))
			return Vehicle;
		if (codes::is_count_wild_t(value))
			return CountWild;

		return {};
	}

	constexpr const char* get_name(ScriptToken value)
	{
		return codes::get_token_langname(value);
	}
}
