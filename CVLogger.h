#pragma once

#include <opencv2/core/utils/logger.hpp>

enum class CVLogLevel {
	SILENT = 0,              //!< for using in setLogVevel() call
	FATAL = 1,               //!< Fatal (critical) error (unrecoverable internal error)
	ERROR = 2,               //!< Error message
	WARNING = 3,             //!< Warning message
	INFO = 4,                //!< Info message
	DEBUG = 5,               //!< Debug message. Disabled in the "Release" build.
	VERBOSE = 6,             //!< Verbose (trace) messages. Requires verbosity level. Disabled in the "Release" build.
#ifndef CV_DOXYGEN
	FORCE_INT = INT_MAX
#endif
};

class CVLogger
{
	using _LogLevel = cv::utils::logging::LogLevel;

private:
	static CVLogLevel GLOBAL_LOG_LEVEL;

public:
	static CVLogLevel setLogLevel(CVLogLevel logLevel);

	static CVLogLevel translate(_LogLevel _logLevel);
	static _LogLevel translate(CVLogLevel _logLevel);

	template<typename ...U>
	void log(CVLogLevel logLevel, U...u) const;
};

template<typename ...U>
inline void CVLogger::log(CVLogLevel logLevel, U ...u) const
{
	_LogLevel _logLevel = _LogLevel::LOG_LEVEL_FATAL;
	switch (logLevel) {
	case CVLogLevel::SILENT:_logLevel = _LogLevel::LOG_LEVEL_SILENT; break;
	case CVLogLevel::FATAL:_logLevel = _LogLevel::LOG_LEVEL_FATAL; break;
	case CVLogLevel::ERROR:_logLevel = _LogLevel::LOG_LEVEL_ERROR; break;
	case CVLogLevel::WARNING:_logLevel = _LogLevel::LOG_LEVEL_WARNING; break;
	case CVLogLevel::INFO:_logLevel = _LogLevel::LOG_LEVEL_INFO; break;
	case CVLogLevel::DEBUG:_logLevel = _LogLevel::LOG_LEVEL_DEBUG; break;
	case CVLogLevel::VERBOSE:_logLevel = _LogLevel::LOG_LEVEL_VERBOSE; break;
#ifndef CV_DOXYGEN
	case CVLogLevel::FORCE_INT:_logLevel = _LogLevel::ENUM_LOG_LEVEL_FORCE_INT; break;
#endif
	}

	std::string s;
	((s += u), ...);
	CVLogger::GLOBAL_LOG_LEVEL = logLevel;
	cv::utils::logging::internal::writeLogMessage(_logLevel, s.c_str());
}
