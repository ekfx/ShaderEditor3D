#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include "pfd/portable-file-dialogs.h"
#include "Errors.hpp"

namespace LogProperties {
	static bool LogBoxes = true;
}

class Log {
private:
	inline static void internalError();

public:

	// checks if pfd is available in the system
	inline static bool isAvailable();
	
	// Don't returns any value, just warns
	inline static void errm(const std::string& title, const std::string& msg);

	// Don't returns any value, just warns with a personalized icon.
	inline static void errm(const std::string& title, const std::string& msg, const pfd::icon& _icon = pfd::icon::warning);

	// Don't returns any value, just warns a standard  layout.
	inline static void errm(const std::string& msg);

	// int to hexadecimal
	inline static std::string hex(const int& value);

	// format error
	inline static void errf(const ERR& error_code, const std::string& info = "No description available. Check Errors.hpp for more info.\n");

	// doesn't need convert to int
	inline static void err(const ERR& error_code);

	// Personalized Box
	inline static int msg(const std::string& title, const std::string& msg, const pfd::icon& _icon = pfd::icon::warning);
};

void Log::internalError() {
	if (LogProperties::LogBoxes) {
		auto wndBox = pfd::message{
			"Internal Error",
			"Some error ocurred inside in the window error LogProperties::LogBoxes file management (DiaLog.hpp).\n"
			"Some possible causes:\n"
			" - Incompatible type in err() or errf() template functions: those functions\nexpects a type convertible to integer (source Errors.hpp is 16-bit \nhexadecimal enum class errors);\n"
			" - Inexistent Error: check Errors.hpp to see all available;\n"
			" - Some incorrect code writed and modified in DiaLog.hpp;\n"
			"Check DiaLog.hpp to see more.",
			pfd::choice::ok,
			pfd::icon::error
		};

		wndBox.result();
	}
}

bool Log::isAvailable() {
	if (!pfd::settings::available()) {
		// aren't available in this platform.
		return 0;
	}
	else {
		// Set verbosity to true
		pfd::settings::verbose(false);
		// "Calling pfd::settings::verbose(true) 
		// may help debug the library. It will output 
		// debug information to std::cout about some 
		// operations being performed." portable-file-Log/doc/pfd.md

		return 1;
	}
}

void Log::errf(const ERR& error_code, const std::string& info) {
	if (LogProperties::LogBoxes) {
		if (error_code != ERR::SUCCESS) {
			std::string final_msg =
				"-----------------------------------------------\n"
				"Error Code (Check Errors.hpp): " + hex((int)error_code) + "\n"
				"-----------------------------------------------\n"
				"Information: \n"
				+ info + "\n"
				"-----------------------------------------------";

			auto wndBox = pfd::message(
				"Error",
				final_msg,
				pfd::choice::ok,
				pfd::icon::error
			);

			wndBox.result();
		}
	}
}

void Log::err(const ERR& error_code) {
	if (LogProperties::LogBoxes) {
		if (error_code != ERR::SUCCESS) {
			errf(error_code);
		}
	}
}

// Don't returns any value, just warns
void Log::errm(const std::string& title, const std::string& msg) {
	if (LogProperties::LogBoxes) {
		auto wndBox = pfd::message(
			title,
			msg,
			pfd::choice::ok,
			pfd::icon::warning);
		wndBox.result();	
	}
}

// Don't returns any value, just warns with a personalized icon.
void Log::errm(const std::string& title, const std::string& msg, const pfd::icon& _icon) {
	if (LogProperties::LogBoxes) {
		auto wndBox = pfd::message(
			title,
			msg,
			pfd::choice::ok,
			_icon);
		wndBox.result();
	}
}

// Don't returns any value, just warns a standard  layout.
void Log::errm(const std::string& msg) {
	if (LogProperties::LogBoxes) {
		auto wndBox = pfd::message(
			"Error",
			msg,
			pfd::choice::ok,
			pfd::icon::error);
		wndBox.result();
	}
}

std::string Log::hex(const int& value) {
	std::stringstream msg_t{};
	msg_t << "0x" << std::setfill('0') << std::setw(sizeof(ERR) * 2) << std::hex << value;

	return msg_t.str();
}

int Log::msg(const std::string& title, const std::string& msg, const pfd::icon& _icon) {
	if (LogProperties::LogBoxes) {
		auto wndBox = pfd::message(
			title,
			msg,
			pfd::choice::yes_no,
			_icon);
		switch (wndBox.result()) {
		case pfd::button::yes: return 1; break;
		case pfd::button::no: return 0; break;
		default: return -1; break;
		}
	}
	else {
		return -2;
	}
}
