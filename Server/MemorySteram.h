#pragma once

#include <cstdint>

typedef char* ByteStream;

class IMemoryStream
{
public:
	virtual  const ByteStream GetBufferPtr() = 0;
	virtual  uint32_t GetLength() = 0;


protected:
	ByteStream mBuffer;
};


class InputMemoryStream : IMemoryStream
{

public:
	const ByteStream GetBufferPtr() override;
	uint32_t GetLength() override;
	void Read();

};

class OutputMemoryStream:IMemoryStream
{
public:
	const ByteStream GetBufferPtr() override;
	uint32_t GetLength() override;
	
};