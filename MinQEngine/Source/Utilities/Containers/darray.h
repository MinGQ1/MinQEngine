#pragma once
//Dynamic array
#include "MinQDefines.h"
#include "Memory/MinQMemory.h"
#include "Utilities/OOUtility.h"

template<typename T>
struct darray
{
public:
	typedef T* iterator;

	darray():
		m_array(NULL),
		m_size(0),
		m_capacity(0)
	{
	}

	darray(size_t size): 
		m_size(size),
		m_capacity(size)
	{
		m_array = (T*)GetMemoryManager().Allocate(size * sizeof(T), kMemDArray);
	}

	void push_back(const T& value)
	{
		size_t requestSize = m_size + 1;
		if (requestSize > m_capacity)
			reserve(requestSize);

		::new ((T*)(m_array + m_size)) T(value);
		m_size++;
	}

	void reserve(size_t targetSize)
	{
		if (targetSize <= m_capacity)
			return;

		if (m_capacity == 0 && m_array == NULL)
		{
			// create new data
			m_array = (T*)GetMemoryManager().Allocate(targetSize * sizeof(T), kMemDArray);
		}
		else
		{
			m_array = (T*)GetMemoryManager().Reallocate(m_array, targetSize, kMemDArray);
		}

		m_capacity = targetSize;
	}

	void resize(size_t targetSize)
	{
		if (targetSize == m_size || targetSize < 0)
			return;
		
		if (targetSize > m_size)
			reserve(targetSize);

		if (targetSize < m_size)
			destructor_explicit_range(m_array + targetSize, m_array + m_size);

		m_size = targetSize;
	}

	iterator begin() { return m_array; }
	iterator end() { return m_array + m_size; }

	T& operator[](size_t index)
	{
		return m_array[index];
	}

	T* data() { return m_array; };
	size_t size() const { return m_size; };

private:
	T* m_array;
	size_t m_size;
	size_t m_capacity;
};