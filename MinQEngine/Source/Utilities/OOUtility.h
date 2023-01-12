#pragma once
template<typename T> inline
void copy_constructor_explicit(T* ptr, T& value)
{
	::new(ptr) T(value);
}

template<typename T> inline
void destructor_explicit_range(T* begin, T* end)
{
	for (T* ptr = begin; ptr != end; ptr++)
	{
		ptr->~T();
	}
}