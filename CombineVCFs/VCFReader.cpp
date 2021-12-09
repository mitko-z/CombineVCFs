#include "VCFReader.h"
#include "VCFReader3_0.h"
#include "VCFReader2_1.h"

VCFReader *VCFReader::makeVCFReader(std::wstring version)
{
	if (version == L"VERSION:3.0")
	{
		return new VCFReader3_0;
	}
	else if (version == L"VERSION:2.1")
	{
		return new VCFReader2_1;
	}
	else
	{
		std::string throwMessage = "Unsupported version: " + std::string(version.begin(), version.end());
		throw throwMessage.c_str();
	}
}
