#include "ByteBuffer.h"

ByteBuffer::ByteBuffer()
{
	m_StringBuf = new std::stringbuf();
}

ByteBuffer::~ByteBuffer()
{
	delete m_StringBuf;
}

template<typename T>
void ByteBuffer::Put(const T& input)
{
	m_StringBuf->sputn(reinterpret_cast<const char*>(&input), sizeof input);
}

template<typename T>
void ByteBuffer::Get(T& output)
{
	m_StringBuf->sgetn(reinterpret_cast<char*>(&output), sizeof(output));
}