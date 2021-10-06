#pragma once

#include <unordered_map>
#include <filesystem>
#include <algorithm>
#include <exception>
#include <functional>
#include <concepts>
#include <iostream>
#include <compare>
#include <fstream>
#include <sstream>
#include <utility>
#include <cstdint>
#include <format>
#include <chrono>
#include <memory>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <regex>
#include <new>

typedef std::int8_t  Int8;
typedef std::int16_t Int16;
typedef std::int32_t Int32;
typedef std::int64_t Int64;

typedef std::uint8_t  UInt8;
typedef std::uint16_t UInt16;
typedef std::uint32_t UInt32;
typedef std::uint64_t UInt64;

typedef std::size_t Size;
typedef std::size_t Offset;

typedef std::filesystem::path Path;

namespace fs = std::filesystem;

namespace utils
{
	template <typename _Ty>
	inline _Ty* malloc(Size size) { return reinterpret_cast<_Ty*>(::operator new(size)); }

	template <typename _Ty>
	inline _Ty* calloc(Size count, Size size) { return reinterpret_cast<_Ty*>(::operator new(size * count)); }

	inline void free(void* ptr) { ::operator delete(ptr); }

	template <typename _Ty, typename... _Args> requires std::constructible_from<_Ty, _Args...>
	inline _Ty& construct(_Ty& object, _Args&&... args)
	{
		return *(new (std::addressof(object)) _Ty{ std::forward<_Args>(args)... });
	}

	template <std::copy_constructible _Ty>
	inline _Ty& copy_construct(_Ty& dst, const _Ty& src)
	{
		return construct<_Ty, const _Ty&>(dst, src);
	}

	template <std::move_constructible _Ty>
	inline _Ty& move_construct(_Ty& dst, _Ty&& src)
	{
		return construct<_Ty, _Ty&&>(dst, std::move(src));
	}

	template<typename _Ty>
	inline void destroy(_Ty& object)
	{
		object.~_Ty();
	}


	template<typename _Ty, typename _MinTy, typename _MaxTy> requires
		(std::integral<_Ty> || std::floating_point<_Ty>) &&
		std::convertible_to<_MinTy, _Ty> &&
		std::convertible_to<_MaxTy, _Ty>
	inline _Ty clamp(_Ty value, _MinTy min, _MaxTy max)
	{
		return std::min(static_cast<_Ty>(max), std::min(static_cast<_Ty>(min), value));
	}


	inline bool read_fully(void* dst, std::istream& input, Size size)
	{
		input.read(reinterpret_cast<char*>(dst), size);
		return input.gcount() != size;
	}

	inline bool skip(std::istream& input, Size size)
	{
		input.seekg(size, std::ios::cur);
		return !(input.bad() || input.fail());
	}

	inline std::chrono::milliseconds time_test(const std::function<void()>& action)
	{
		auto t0 = std::chrono::system_clock::now();
		action();
		auto t1 = std::chrono::system_clock::now();

		return std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
	}
}

inline Path operator"" _p(const char* str, Size len) { return Path(std::string(str, len)); }

struct SourcePosition
{
	Offset row;
	Offset column;

	constexpr bool operator== (const SourcePosition&) const = default;

	constexpr std::strong_ordering operator<=> (const SourcePosition& right) const
	{
		auto cmp = row <=> right.row;
		if (cmp == std::strong_ordering::equal)
			return column <=> right.column;
		return cmp;
	}
};

namespace utils
{
	constexpr SourcePosition& max(SourcePosition& left, SourcePosition& right)
	{
		return left >= right ? left : right;
	}
	constexpr const SourcePosition& max(const SourcePosition& left, const SourcePosition& right)
	{
		return left >= right ? left : right;
	}

	constexpr SourcePosition& min(SourcePosition& left, SourcePosition& right)
	{
		return left <= right ? left : right;
	}
	constexpr const SourcePosition& min(const SourcePosition& left, const SourcePosition& right)
	{
		return left <= right ? left : right;
	}

	struct row_value { Offset value; };
	struct column_value { Offset value; };
}

constexpr SourcePosition operator+ (const SourcePosition& left, utils::row_value right)
{
	return { left.row + right.value, left.column };
}
constexpr SourcePosition operator+ (utils::row_value& left, const SourcePosition right)
{
	return { right.row + left.value, right.column };
}

constexpr SourcePosition operator+ (const SourcePosition& left, utils::column_value right)
{
	return { left.row, left.column + right.value };
}
constexpr SourcePosition operator+ (utils::column_value& left, const SourcePosition right)
{
	return { right.row, right.column + left.value };
}

constexpr SourcePosition operator- (const SourcePosition& left, utils::row_value right)
{
	return { left.row - right.value, left.column };
}
constexpr SourcePosition operator- (utils::row_value& left, const SourcePosition right)
{
	return { right.row - left.value, right.column };
}

constexpr SourcePosition operator- (const SourcePosition& left, utils::column_value right)
{
	return { left.row, left.column - right.value };
}
constexpr SourcePosition operator- (utils::column_value& left, const SourcePosition right)
{
	return { right.row, right.column - left.value };
}

constexpr SourcePosition& operator+= (SourcePosition& left, utils::row_value right)
{
	return left.row + right.value, left;
}

constexpr SourcePosition& operator+= (SourcePosition& left, utils::column_value right)
{
	return left.column + right.value, left;
}

constexpr SourcePosition& operator-= (SourcePosition& left, utils::row_value right)
{
	return left.row - right.value, left;
}

constexpr SourcePosition& operator-= (SourcePosition& left, utils::column_value right)
{
	return left.column - right.value, left;
}


namespace utils
{
	template<std::default_initializable _Ty>
	class DynamicArray
	{
	public:
		using value_type = _Ty;
		using pointer_type = _Ty*;
		using reference_type = _Ty&;
		using const_value_type = const _Ty;
		using const_pointer_type = const _Ty*;
		using const_reference_type = const _Ty&;
		using rvalue_type = _Ty&&;

	private:
		pointer_type _array = nullptr;
		Size _size = 0;

	public:
		DynamicArray() = default;

		inline explicit DynamicArray(Size size) :
			_array{ size ? new value_type[size] : nullptr },
			_size{ size }
		{}
		
		inline DynamicArray(pointer_type array, Size size) :
			_array{ size ? array : nullptr },
			_size{ array ? size : 0 }
		{}

		inline DynamicArray(std::initializer_list<value_type> list) :
			DynamicArray(list.begin(), list.size())
		{}

		DynamicArray(const DynamicArray& right) :
			DynamicArray(right._size)
		{
			if(_array)
				for (Offset i = 0; i < _size; ++i)
					_array[i] = right._array[i];
		}

		DynamicArray(const std::vector<value_type>& v) :
			DynamicArray(v.size())
		{
			if (_array)
			{
				const_pointer_type vptr = v.data();
				for (Offset i = 0; i < _size; ++i)
					_array[i] = vptr[i];
			}
		}

		inline DynamicArray(DynamicArray&& right) noexcept :
			DynamicArray(right._array, right._size)
		{
			right._array = nullptr;
			right._size = 0;
		}

		inline ~DynamicArray()
		{
			if (_array)
				delete _array;
		}

		inline DynamicArray& operator= (const DynamicArray& right)
		{
			return utils::destroy(*this), utils::copy_construct(*this, right);
		}

		inline DynamicArray& operator= (DynamicArray&& right) noexcept
		{
			return utils::destroy(*this), utils::move_construct(*this, std::move(right));
		}

		inline DynamicArray& operator= (const std::pair<pointer_type, Size>& right)
		{
			return utils::destroy(*this), utils::construct(*this, right.first, right.second);
		}

	public:
		inline Size size() const { return _size; }
		inline bool empty() const { return _size == 0; }

		inline void set(Offset index, const_reference_type value) { _array[index] = value; }
		inline void set(Offset index, rvalue_type value) { _array[index] = std::move(value); }

		inline reference_type get(Offset index) { return _array[index]; }
		inline const_reference_type get(Offset index) const { return _array[index]; }

		template<typename... _Args> requires
			std::constructible_from<value_type, _Args...>
		inline void emplace(Offset index, _Args&&... args)
		{
			utils::destroy(_array[index]);
			utils::construct(_array[index], std::forward<_Args>(args)...);
		}

		inline pointer_type data() { return _array; }
		inline const_pointer_type data() const { return _array; }

		void fill(const_reference_type value)
		{
			for (Offset i = 0; i < _size; ++i)
				_array[i] = value;
		}

		void fill(const_reference_type value, Offset from)
		{
			for (Offset i = from; i < _size; ++i)
				_array[i] = value;
		}

		void fill(const_reference_type value, Offset from, Offset to)
		{
			Size len = std::min(_size, to);
			for (Offset i = from; i < len; ++i)
				_array[i] = value;
		}

		void clear()
		{
			for (Offset i = 0; i < _size; ++i)
			{
				utils::destroy(_array[i]);
				utils::construct(_array[i]);
			}
		}

	public:
		inline operator bool() const { return _size > 0; }
		inline bool operator! () const { return _size == 0; }

		inline reference_type operator* () { return *_array; }
		inline const_reference_type operator* () const { return *_array; }

		inline pointer_type operator-> () { return _array; }
		inline const_pointer_type operator-> () const { return _array; }

		inline reference_type operator[] (Offset index) { return _array[index]; }
		inline const_reference_type operator[] (Offset index) const { return _array[index]; }
	};
}
