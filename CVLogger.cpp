#include "CVLogger.h"

CVLogLevel CVLogger::GLOBAL_LOG_LEVEL = CVLogLevel::INFO;

CVLogLevel CVLogger::setLogLevel(CVLogLevel logLevel)
{
	CVLogLevel previous = CVLogger::GLOBAL_LOG_LEVEL;
	cv::utils::logging::setLogLevel(translate(logLevel));
	return previous;
}

CVLogLevel CVLogger::translate(_LogLevel _logLevel)
{
	CVLogLevel logLevel = CVLogLevel::FATAL;
	switch (_logLevel)
	{
	case _LogLevel::LOG_LEVEL_SILENT:logLevel = CVLogLevel::SILENT; break;
	case _LogLevel::LOG_LEVEL_FATAL:logLevel = CVLogLevel::FATAL; break;
	case _LogLevel::LOG_LEVEL_ERROR:logLevel = CVLogLevel::ERROR; break;
	case _LogLevel::LOG_LEVEL_WARNING:logLevel = CVLogLevel::WARNING; break;
	case _LogLevel::LOG_LEVEL_INFO:logLevel = CVLogLevel::INFO; break;
	case _LogLevel::LOG_LEVEL_DEBUG:logLevel = CVLogLevel::DEBUG; break;
	case _LogLevel::LOG_LEVEL_VERBOSE:logLevel = CVLogLevel::VERBOSE; break;
#ifndef CV_DOXYGEN
	case _LogLevel::ENUM_LOG_LEVEL_FORCE_INT:logLevel = CVLogLevel::FORCE_INT; break;
#endif
	}
	return logLevel;
}

CVLogger::_LogLevel CVLogger::translate(CVLogLevel _logLevel)
{
	_LogLevel logLevel = _LogLevel::LOG_LEVEL_FATAL;
	switch (_logLevel) {
	case CVLogLevel::SILENT:logLevel = _LogLevel::LOG_LEVEL_SILENT; break;
	case CVLogLevel::FATAL:logLevel = _LogLevel::LOG_LEVEL_FATAL; break;
	case CVLogLevel::ERROR:logLevel = _LogLevel::LOG_LEVEL_ERROR; break;
	case CVLogLevel::WARNING:logLevel = _LogLevel::LOG_LEVEL_WARNING; break;
	case CVLogLevel::INFO:logLevel = _LogLevel::LOG_LEVEL_INFO; break;
	case CVLogLevel::DEBUG:logLevel = _LogLevel::LOG_LEVEL_DEBUG; break;
	case CVLogLevel::VERBOSE:logLevel = _LogLevel::LOG_LEVEL_VERBOSE; break;
#ifndef CV_DOXYGEN
	case CVLogLevel::FORCE_INT:logLevel = _LogLevel::ENUM_LOG_LEVEL_FORCE_INT; break;
#endif
	}
	return logLevel;
}