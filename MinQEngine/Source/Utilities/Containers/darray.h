#pragma once
//Dynamic array
#include "MinQDefines.h"
#include "Memory/MinQMemory.h"

template<typename T>
struct darray
{
public:
	darray():
		m_array(NULL),
		m_size(0),
		m_capacity(0)
	{

	}

	void push_back(T& value)
	{
		size_t requestSize = m_size + 1;
		if (requestSize > m_capacity)
			reserve(requestSize);
		
		
	}

	void reserve(size_t targetSize)
	{
		if (targetSize <= m_capacity)
			return;

		if (m_capacity == 0 && m_array == NULL)
		{
			// create new data
			m_array = MemoryManager::Allocate(targetSize * sizeof(T), kMemDArray);
		}
		else
		{
			m_array = MemoryManager::Reallocate(m_array, targetSize, kMemDArray)
		}

		m_capacity = targetSize;
	}

private:
	T* m_array;
	size_t m_size;
	size_t m_capacity;
};