#include "BsGpuParamBlockBuffer.h"
#include "BsGpuParamBlock.h"

namespace BansheeEngine
{
	GpuParamBlockBuffer::GpuParamBlockBuffer()
		:mSize(0), mUsage(GPBU_DYNAMIC), mParamBlock(nullptr)
	{

	}

	GpuParamBlockBuffer::~GpuParamBlockBuffer()
	{
		if(mParamBlock != nullptr)
			bs_delete(mParamBlock);
	}

	void GpuParamBlockBuffer::initialize(UINT32 size, GpuParamBlockUsage usage)
	{
		mSize = size;
		mUsage = usage;

		mParamBlock = bs_new<GpuParamBlock, PoolAlloc>(size);

		CoreObject::initialize();
	}

	void GenericGpuParamBlockBuffer::writeData(const UINT8* data)
	{
		memcpy(mData, data, mSize);
	}

	void GenericGpuParamBlockBuffer::readData(UINT8* data) const
	{
		memcpy(data, mData, mSize);
	}

	void GenericGpuParamBlockBuffer::initialize_internal()
	{
		mData = (UINT8*)bs_alloc<ScratchAlloc>(mSize);
		memset(mData, 0, mSize);

		GpuParamBlockBuffer::initialize_internal();
	}

	void GenericGpuParamBlockBuffer::destroy_internal()
	{
		if(mData != nullptr)
			bs_free<ScratchAlloc>(mData);

		GpuParamBlockBuffer::destroy_internal();
	}
}