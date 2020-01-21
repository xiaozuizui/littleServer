#pragma once

typedef char* ByteStream;

#include <cstring>
#include <string>

class OutputMemoryBitStream
{
public:
	OutputMemoryBitStream():mBitHead(0),mBuffer(nullptr) { ReallocBuffer(256); }
	~OutputMemoryBitStream() { std::free(mBuffer); }

	void WriteBits(uint8_t inData, size_t inBitCount);
	void WriteBits(const void* inData, size_t inBitCount);

	const ByteStream GetBufferPtr() const;
	uint32_t GetBitLength() const;
	uint32_t GetByteLength() const;


	//void WriteByte(const void* Data, size_t inByteCount);


	//

	void WriteBytes(void const * inData,size_t inByteCount)
	{
		WriteBits(inData, inByteCount << 3);
	}

	void Write(uint32_t inData,size_t inBitCount = sizeof(uint32_t)* 8)
	{
		WriteBits(inData, inBitCount);
	}

	void Write(int inData,size_t inBitCount = sizeof(int)*8)
	{
		WriteBits(inData, inBitCount);
	}

	void Write(float inData)
	{
		WriteBits(&inData, sizeof(float) * 8 );
	}

	void Write(uint16_t inData,size_t inBitCount = sizeof(uint16_t) * 8)
	{
		WriteBits(inData, inBitCount);
	}

	void Write(int16_t inData,size_t inBitCount = sizeof(int16_t) * 8 )
	{
		WriteBits(inData, inBitCount);
	}

	char *const GetBytePtr()
	{
		return mBuffer;
	}
private:

	void ReallocBuffer(uint32_t inNewBitCapacity);

#ifdef DEBUG
public:
#endif
	ByteStream mBuffer;
	uint32_t mBitHead;
	uint32_t mBitCapacity;
};

class InputMemoryBitStream
{

public:
	InputMemoryBitStream(char* inBuffer, uint32_t inBitCount) :
		mBuffer(inBuffer),
		mBitCapacity(inBitCount),
		mBitHead(0),
		mIsBufferOwner(false) {}

	InputMemoryBitStream(const InputMemoryBitStream& inOther) :
		mBitCapacity(inOther.mBitCapacity),
		mBitHead(inOther.mBitHead),
		mIsBufferOwner(true)
	{
		//allocate buffer of right size
		int byteCount = mBitCapacity / 8;
		mBuffer = static_cast<char*>(malloc(byteCount));
		//copy
		memcpy(mBuffer, inOther.mBuffer, byteCount);
	}

	~InputMemoryBitStream() { if (mIsBufferOwner) { free(mBuffer); }; }

	const 	char* GetBufferPtr()		const { return mBuffer; }
	uint32_t	GetRemainingBitCount() 	const { return mBitCapacity - mBitHead; }

	void		ReadBits(uint8_t& outData, uint32_t inBitCount);
	void		ReadBits(void* outData, uint32_t inBitCount);

	void		ReadBytes(void* outData, uint32_t inByteCount) { ReadBits(outData, inByteCount << 3); }

	template< typename T >
	void Read(T& inData, uint32_t inBitCount = sizeof(T) * 8);
	

	void		Read(uint32_t& outData, uint32_t inBitCount = 32) { ReadBits(&outData, inBitCount); }
	void		Read(int& outData, uint32_t inBitCount = 32) { ReadBits(&outData, inBitCount); }
	void		Read(float& outData) { ReadBits(&outData, 32); }

	void		Read(uint16_t& outData, uint32_t inBitCount = 16) { ReadBits(&outData, inBitCount); }
	void		Read(int16_t& outData, uint32_t inBitCount = 16) { ReadBits(&outData, inBitCount); }

	void		Read(uint8_t& outData, uint32_t inBitCount = 8) { ReadBits(&outData, inBitCount); }
	void		Read(bool& outData) { ReadBits(&outData, 1); }

	void		ResetToCapacity(uint32_t inByteCapacity) { mBitCapacity = inByteCapacity << 3; mBitHead = 0; }


	void Read(std::string& inString);
	

	


#ifdef DEBUG
public:
#else
private:
#endif
	char* mBuffer;
	uint32_t	mBitHead;
	uint32_t	mBitCapacity;
	bool		mIsBufferOwner;

};