#include "MemoryBitStream.h"
#include <algorithm>

void OutputMemoryBitStream::ReallocBuffer(uint32_t inNewBitCapacity)
{
	//uint32_t last = inNewBitCapacity & 0x7;
	uint32_t ByteCount;
	if(inNewBitCapacity & 0x7)
	{
		ByteCount = inNewBitCapacity >> 3 + 1;
	}
	else
	{
		ByteCount = inNewBitCapacity >> 3;
	}
	mBuffer = static_cast<char*>(std::realloc(mBuffer, ByteCount));
	mBitCapacity = inNewBitCapacity;
}


const ByteStream OutputMemoryBitStream::GetBufferPtr() const
{
	return mBuffer; 
}


uint32_t OutputMemoryBitStream::GetBitLength() const
{
	return mBitHead; 
}


uint32_t OutputMemoryBitStream::GetByteLength() const
{
	return (mBitHead + 7) >> 3; 
}


void OutputMemoryBitStream::WriteBits(uint8_t inData, size_t inBitCount)
{
	//
	uint32_t nextBitHead = mBitHead + static_cast<uint32_t>(inBitCount);

	if(nextBitHead > mBitCapacity)
	{
		ReallocBuffer(std::max(mBitCapacity * 2, nextBitHead));
	}

	uint32_t const byteOffset = mBitHead >> 3;
	uint32_t const bitOffset = mBitHead & 0x7; // 0111 take the last 3 bit
	uint8_t const currentMask = ~(0xff << bitOffset);

	mBuffer[byteOffset] = (mBuffer[byteOffset] & currentMask) | (inData << bitOffset);

	uint32_t const bitsFreeThisByte = 8 - bitOffset;
	if(bitsFreeThisByte < inBitCount)
	{
		mBuffer[byteOffset + 1] = inData >> bitsFreeThisByte;
	}

	mBitHead = nextBitHead;
}

void OutputMemoryBitStream::WriteBits(const void* inData, size_t inBitCount)
{
	char const* srcByte = static_cast<char const*>(inData);
	while (inBitCount > 8)
	{
		WriteBits(*srcByte, 8);
		++srcByte;
		inBitCount -= 8;
	}

	if(inBitCount > 0)
	{
		WriteBits(*srcByte, inBitCount);
	}
}







void InputMemoryBitStream::ReadBits(uint8_t& outData, uint32_t inBitCount)
{
	uint32_t byteOffset = mBitHead >> 3;
	uint32_t bitOffset = mBitHead & 0x7;

	outData = static_cast<uint8_t>(mBuffer[byteOffset]) >> bitOffset;

	uint32_t bitsFreeThisByte = 8 - bitOffset;
	if (bitsFreeThisByte < inBitCount)
	{
		//we need another byte
		outData |= static_cast<uint8_t>(mBuffer[byteOffset + 1]) << bitsFreeThisByte;
	}

	//don't forget a mask so that we only read the bit we wanted...
	outData &= (~(0x00ff << inBitCount));

	mBitHead += inBitCount;
}



template< typename T >
void InputMemoryBitStream::Read(T& inData, uint32_t inBitCount )
{
	static_assert(std::is_arithmetic< T >::value ||
		std::is_enum< T >::value,
		"Generic Read only supports primitive data types");
	ReadBits(&inData, inBitCount);
}

void InputMemoryBitStream::ReadBits(void* outData, uint32_t inBitCount)
{
	uint8_t* destByte = reinterpret_cast<uint8_t*>(outData);
	//write all the bytes
	while (inBitCount > 8)
	{
		ReadBits(*destByte, 8);
		++destByte;
		inBitCount -= 8;
	}
	//write anything left
	if (inBitCount > 0)
	{
		ReadBits(*destByte, inBitCount);
	}
}






