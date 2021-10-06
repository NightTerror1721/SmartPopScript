#pragma once

#include "common.h"

namespace parser
{
	struct CodeReaderElement;
}

struct Error
{
	SourcePosition begin;
	SourcePosition end;
	std::string message;
};

class ErrorManager
{
private:
	std::vector<Error> _errors;

public:
	ErrorManager() = default;
	ErrorManager(const ErrorManager&) = default;
	ErrorManager(ErrorManager&&) noexcept = default;
	~ErrorManager() = default;

	ErrorManager& operator= (const ErrorManager&) = default;
	ErrorManager& operator= (ErrorManager&&) noexcept = default;

public:
	inline void registerError(const SourcePosition& begin, const SourcePosition& end, const std::string& message)
	{
		_errors.push_back({ begin, end, message });
	}

	inline bool hasErrors() const { return !_errors.empty(); }
	inline Size getErrorCount() const { return _errors.size(); }

	inline const Error& getErrror(Offset index) const { return _errors[index]; }

	inline const std::vector<Error>& getAllErrors() const { return _errors; }

	inline operator bool() const { return !_errors.empty(); }
	inline bool operator! () const { return _errors.empty(); }

public:
	void registerError(const SourcePosition& begin, const parser::CodeReaderElement& elem, const std::string& message);

private:
	class Builder
	{
	public:
		friend ErrorManager;

	private:
		ErrorManager& _manager;
		std::ostringstream _ss;

	private:
		inline Builder(ErrorManager& manager) :
			_manager(manager),
			_ss()
		{}

	public:
		Builder(const Builder&) = default;
		Builder(Builder&&) noexcept = default;
		~Builder() = default;

		Builder& operator= (const Builder&) = default;
		Builder& operator= (Builder&&) noexcept = default;

	public:
		const 
	};
};
