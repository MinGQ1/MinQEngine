#pragma once
template<typename T>
void copy_constructor_explicit(T* ptr, T& value)
{
	::new(ptr) T(value);
}