#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <optional>
#include <concepts>

// Check if sysinfoapi.h is available
#ifdef _WIN32
#include <sdkddkver.h>
#if defined(__has_include)
#if __has_include(<sysinfoapi.h>)
#include <sysinfoapi.h>
#define SYSINFOAPI_AVAILABLE 1
#else
#define SYSINFOAPI_AVAILABLE 0
#endif
#else
#define SYSINFOAPI_AVAILABLE 0
#endif
#endif

#if SYSINFOAPI_AVAILABLE
	#include <sysinfoapi.h>
	template <typename T>
	constexpr auto GetTime() {
		T* time = new time;
		time = GetLocalTime(); 
		
	}
#else
	#include <chrono>
#endif

template <typename From, typename To>
concept IsConvertableTo = std::is_convertible_v<From, To>; 

template <typename T>
concept IsValidDataTypeTime = requires(T t) {
	{ std::is_same_v<T, char> } -> std::convertible_to<int>;
	requires IsConvertableTo<T, char>;
	requires IsConvertableTo<T, int>;
	requires IsConvertableTo<T, float>;
};

template <typename T>
auto ReturnTime() {
	if (time) {
		return IsValidDataTypeTime<time>;
	}
	else {
		return std::chrono::system_clock;
	}
}


//Testing