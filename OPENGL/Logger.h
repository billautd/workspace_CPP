#pragma once
#include <iostream>
#include <map>
#include <sstream>
enum LogLevel {DEBUG, INFO, WARN, FATAL, ERROR};

class Logger
{
private:
	inline static std::map<LogLevel, bool> levels = {
		 {DEBUG, true},
		 { INFO, true },
		 { WARN, true },
		 { FATAL, true },
		 { ERROR, true }
	};

	static void log(LogLevel level, std::string message) {
		// Get current timestamp
		std::time_t now = time(0);
		std::tm bt{};
		localtime_s(&bt, &now);
		char timestamp[20];
		strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &bt);

		if (levels[level]) {
			// Create log entry
			std::ostringstream logEntry;
			logEntry << "[" << timestamp << "] "
				<< levelToString(level) 
				<< " : " << message
				<< std::endl;

			// Output to console
			std::cout << logEntry.str();
		}
	}

	static void log(LogLevel level, char* message) {
		log(level, std::string(message));
	}

	static void log(LogLevel level, const char* message) {
		log(level, std::string(message));
	}

	static void log(LogLevel level, unsigned char* message) {
		log(level, reinterpret_cast<char*>(message));
	}

	static void log(LogLevel level, const unsigned char* message) {
		log(level, reinterpret_cast<const char*>(message));
	}

	// Converts log level to a string for output
	static std::string levelToString(LogLevel level)
	{
		switch (level) {
		case DEBUG:
			return "[DEBUG]";
		case INFO:
			return "[INFO ]";
		case WARN:
			return "[WARN ]";
		case ERROR:
			return "[ERROR]";
		case FATAL:
			return "[CRITICAL]";
		default:
			return "[UNK  ]";
		}
	}
public:

	static void debug(std::string content) { log(DEBUG, content); }
	static void debug(char* content) { log(DEBUG, content); }
	static void debug(const char* content) { log(DEBUG, content); }
	static void debug(unsigned char* content) { log(DEBUG, content); }
	static void debug(const unsigned char* content) { log(DEBUG, content); }

	static void info(std::string content) { log(INFO, content); }
	static void info(char* content) { log(INFO, content); }
	static void info(const char* content) { log(INFO, content); }
	static void info(unsigned char* content) { log(INFO, content); }
	static void info(const unsigned char* content) { log(INFO, content); }

	static void warn(std::string content) { log(WARN , content); }
	static void warn(char* content) { log(WARN , content); }
	static void warn(const char* content) { log(WARN , content); }
	static void warn(unsigned char* content) { log(WARN , content); }
	static void warn(const unsigned char* content) { log(WARN , content); }

	static void fatal(std::string content) { log(FATAL, content); }
	static void fatal(char* content) { log(FATAL, content); }
	static void fatal(const char* content) { log(FATAL, content); }
	static void fatal(unsigned char* content) { log(FATAL, content); }
	static void fatal(const unsigned char* content) { log(FATAL, content); }

	static void error(std::string content) { log(ERROR, content); }
	static void error(char* content) { log(ERROR, content); }
	static void error(const char* content) { log(ERROR, content); }
	static void error(unsigned char* content) { log(ERROR, content); }
	static void error(const unsigned char* content) { log(ERROR, content); }
};