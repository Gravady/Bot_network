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
concept IsConvertableTo = std::is_convertible_to<From, To>; 

template <typename T>
concept IsValidDataTypeTime = requires(T t){
	{ std::is_same_v<T, char> } -> std::convertible_to<int>; 
	{ std::common_with<decltype<T, char>> } -> std::assignable_from<char>; //std::common_type_v eval 

		requires IsConvertableTo<T, char>;
}

template <typename T>
class EvalType {
public:

};
