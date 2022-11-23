#include <sstream>

// a wrap of std:stringbuf
class ByteBuffer
{
public:
	ByteBuffer();
	virtual ~ByteBuffer();

	template<typename T>
	void Put(const T& input);

	template<typename T>
	void Get(T& output);

private:
	std::stringbuf* m_StringBuf;
};