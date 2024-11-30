#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <optional>
#include <concepts> //For concept variable PointerReturnType 

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

//Make custom variable using concept to return something very elegantly
template <typename T>
concept PointerReturnType = 

//Choose between either systime decider

using specified_time_variable = std::string(*)();
template <typename T>
specified_time_variable GetTime() {

}	
template <typename T>
class EvalType {
	public:
		explicit EvalType(const std::optional<T>& type) noexcept : type_(type) {}
		operator std::string() const{
			if (type != std::nullopt) {
				return typeid(_type).name();
			}
			else { return "No value"; }
		}
		Derived& ReturnDerived() {
			return static_cast<EvalType&>(*this);
		}
	};
private:
	std::optional<T> type_;
}
