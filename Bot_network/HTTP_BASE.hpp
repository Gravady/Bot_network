//Only base file without appropirate source file 

//NOTES ABOUT PROGRAM:
//(Delete) Please for the love of god use concept and requires, so cool concepts
//https://en.cppreference.com/w/cpp/language/constraints


#pragma once 

#ifndef SOCKET_PACKAGE 
#define SOCKET_PACKAGE 

#include <winsock.h> 
#include <arpa/inet.h>

#endif

#ifndef HTTP_BASE
#define HTTP_BASE 

//For time things time related
#include <chrono>
#include <ctime>

#include <memory>
#include <fstream>
#include <regex>
#include <optional>
#include <map>
#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <concepts>

//Namespace for http_base
namespace http_base_using {
	template <typename T>
	using buffer_ptr = char[size_t](*)(*char); 

};

//Change later only example
constexpr size_t DEFAULT_BUFFER_SIZE = 2000;

//Maybe this isnt like how its suppose to be?
std::string encryption_password_file = "../Bot_network/Source_Files/Password/pass_file.txt"; 

const std::string HTTP_VERSION = "HTTP/3";

const std::unordered_map<std::string, std::string> FILE_TYPES = {
	{".html", "text/html"},
	{".json", "application/json"},
	{".xml", "application/xml"},
	{".pdf", "application/pdf"},
	{".png", "image/png"},
	{".jpg", "image/jpg"},
	{".webimg", "image/webimag"}
};

//https://en.wikipedia.org/wiki/List_of_HTTP_status_codes

const std::unordered_map<int, std::string> STATUS_MESSAGES_DEFAULT = {
	{100, "Continue"},
	{101, "Switching protocols"},
	{102, "Processing"},
	{103, "Early hints"},
	{200, "OK" },
	{201, "Socket created"},
	{202, "Connection accepted"},
	{203, "Non-Authoritative Information"},
	{204, "No content found"},
	{205, "Reset Content"},
	{206, "Partial Content"},
	{207, "Multi-Status"},
	{208, "Already reported"},
	{226, "IM used"},
	{300, "Multiple Choices"},
	{301, "Moved Permanently"},
	{302, "Found"},
	{303, "See Other"},
	{304, "Not modified"},
	{305, "Use Proxy"},
	{307, "Temporary Redirect"},
	{308, "Permanent Redirect"},
	{400, "Bad request"},
	{401, "Unauthorized"},
	{402, "Payment required"}, //This will most likely not be used unless this becomes a service
	{403, "Forbidden"},
	{404, "Not found"},
	{405, "Method Not Allowed"},
	{406, "Not Acceptable"},
};

//Map to hold different error types
//Not to be confused with HTTP_STATUS_MESSAGE_DEFAULT
//NOTE: Add more later
const std::vector<std::string> error_types = {
	{"Faulty value"},
	{""}
};

//For time function
#ifndef SYSTEM_TIME
#define SYSTEM_TIME
#include "gettime.hpp"
#endif

std::vector <std::string> custom_error_types_list = {
	{"Unspecified variable"},
	{""}
};

namespace error_logging {
	std::unique_ptr<std::unordered_map<int, std::string>> STATUS_MESSAGES_DEFAULT
		= std::make_unique<std::unordered_map<int, std::string>>();

	template <typename T>
	constexpr auto asssert_erorr(T error_message, T** Status_default_messages_unique_ptr) {
		
	}
};

//NOTE(Delete): Check the function in a simple way
template <typename ...Args, typename T>
void asser_code(Args ...args) {
	auto ErrorAsserMessage(T & t) {
		std::cerr << "Decltype: " << t << " is invalid" << std::endl; 
		return t;
	}
	constexpr size_t sizeof_args = [&]() {return sizeof...(Args); };
	static_assert(std::is_same_v<decltype(sizeof_args), size_t,
		ErrorAsserMessage(sizeof_args);
	for(const auto )
}
	
#endif HTTP_BASE