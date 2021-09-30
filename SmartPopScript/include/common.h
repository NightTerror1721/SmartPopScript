#pragma once

#include <algorithm>
#include <concepts>
#include <iostream>
#include <utility>
#include <cstdint>
#include <string>
#include <vector>
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
		return *(new (std::addressof(object)) _Ty{ args });
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
}
