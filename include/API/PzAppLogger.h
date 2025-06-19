///////////////////////////////////////////////////////////////////////////
// Copyright (C) V-Nova 2025. All rights reserved.
// All rights reserved.

#ifndef _logger_h_
#define _logger_h_

#include "export.h"

#include "PzConstants.h"
// needed for defining C-String variadic function
#include <stdarg.h>
#include <stddef.h>

/// \file pzAppLogger.h

/// @brief Get the PresenZ version from the DLL.
/// @param[out] major major version number
/// @param[out] minor minor version number
/// @param[out] patch patch version number
/// 
extern "C" {
    presenz_plugin_sdk_PYEXPORT const char* PzGetVersion(int& major, int& minor, int& patch);
}


namespace PresenZ {
namespace Logger {
namespace PRESENZ_VERSION_NS {

/// \defgroup PzAppLogger Logging interface
///
/// \brief Interface needed to invoke and drive internal PresenZ logging system.
/// \details Ideally, the setup features should be invoked as soon as the application starts. 
///
///   - You can adjust the desired verbosity with PzSetConsoleLogLevel().
///   - You can enable/disable timestamps/log_level in front of log lines with PzSetDateHeader().
///   - PzSetConsole() can enable/disable printing to the STD output.
///
/// For the sake of convenience, defines are offered to quickly invoke PresenZ logging with various log levels:
///
///     PZ_ERROR / PZ_WARNING / PZ_INFO / PZ_DEBUG / PZ_TRACE
///
/// Alternatively, you can invoke PzOutputLogString() with the corresponding parameters.
///
/// Often, the host application has its own logging system. It is possible to redirect all
/// PresenZ logging systems to this system. You can define the callback with the function:
///
///     PzSetCallBackLogLevel()
/// 
/// The host application may or may not need a carriage return at the end of each logging line. If this
/// impacts logging readability, you can force a carriage return/no carriage return with:
/// 
///     PzSetCallbackCarriageReturnMode()
///
/// Some PresenZ utilities also use the logging system for displaying progression while processing data.
/// This can be achieved with the following methods:
///
///     PzResetprogress() (will re-initialize the progress bar).
///     PzIncreaseprogress()
///     PzSetDoneProgression() (operations are complete)
///
/// \{


//////////////////////////////////////////////////////////////////////////
//   Callback system

/// @brief This is the main log callback that client applications have to implement. All PresenZ 
///       message/warning/errors will be forwarded to this callback.
/// @param[in] lvl log level severity
/// @param[in] message null terminated C string containing log message
/// @param[in] userData pointer that was notified in PzSetCallBackLogLevel 
typedef void(*AppLoggerCallback) (const LogLevel &lvl, const char* message, void *userData);

/// @brief Set the loglevel, which will be the callback for the current application.
/// @param[in] lvl log level severity
/// @param[in] callback callback function
/// @param[in] userData pointer that was notified in PzSetCallBackLogLevel 
presenz_plugin_sdk_EXPORT void PzSetCallBackLogLevel(LogLevel lvl, AppLoggerCallback callback, void * userData);



typedef void(*progressBeginCB) (int totalTaskNumber, void *userData);
typedef void(*progressIncreaseCB) (void *userData);
typedef void(*progressDoneCB) (void *userData);
typedef void(*progressSetTaskNameCB) (const char *taskName, void *userData);
presenz_plugin_sdk_EXPORT void PzSetProgressBarCallback(progressBeginCB beginCallback, progressIncreaseCB increaseCallback, progressDoneCB doneCallBack, progressSetTaskNameCB setNameCallBack, void *userData);

typedef int(*progressGetAbortCB) (void *userData);


/// @brief Force enable/disable end of line at each line forwarded to the callback.
/// @details It is possible that the application callback handles carriage returns in a special way.
/// For this very specific reason, you can force or totally disable carriage returns at the end 
/// of lines forwarded to the callback.
/// @param[in] carriageMode desired carriage mode (see CarriageReturnMode)
presenz_plugin_sdk_EXPORT void PzSetCallbackCarriageReturnMode(CarriageReturnMode carriageMode);


presenz_plugin_sdk_EXPORT void PzSetCallBackLogLevel(LogLevel lvl, AppLoggerCallback callback, void * userData);

//////////////////////////////////////////////////////////////////////////
//
// Log system customization.
//

/// @brief Enable/disable the date/time header
/// @param[in] enabled enable/disable
presenz_plugin_sdk_EXPORT void PzSetDateHeader(bool enabled);

/// @brief Enable/disable logging in the header, if enabled the highest level of logging will be used
/// @param[in] enabled enable/disable
presenz_plugin_sdk_EXPORT void PzSetLogLevelHeader(bool enabled);

/// @brief Do you want the logs to appear in the STD out
/// @param[in] enabled enable/disable
presenz_plugin_sdk_EXPORT void PzSetConsole(bool enabled);

/// @brief Set the percent character. By default %, but can cause issues in your logger
/// @param[in] percent Replace % with this value.
presenz_plugin_sdk_EXPORT void PzSetPercentCharacter(const char* percent);

/// @brief Set the severity that you want to see on STD out 
/// @param[in] l severity level
presenz_plugin_sdk_EXPORT void PzSetConsoleLogLevel(LogLevel l);

/// @brief Set the severity that you want to see in the log files
/// @param[in] l maximum log level verbosity you want to see in the log file
/// @param[in] path file path destination
/// @param[in] mode file mode (will append as default)
presenz_plugin_sdk_EXPORT void PzSetFileLogLevel(LogLevel l, const char * path, const char * mode = "a");

/// @brief Enable a [PresenZ] prefix for each file in the logs
/// @param[in] enable enable/disable
presenz_plugin_sdk_EXPORT void PzHeaderEnable(bool enable);

//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Forward C-String/Printf const char strings to PresenZ log pipeline

/// @brief Output a c-style string onto PresenZ logs
/// @param[in] logLevel log level severity
/// @param[in] text null terminated C string containing log message
presenz_plugin_sdk_EXPORT void PzOutputLogCStr(const LogLevel &logLevel, const char* text);

/// @brief Output a printf-style string into the PresenZ logs
/// @param[in] logLevel log level severity
/// @param[in] format variadic (printf like) null terminated C string containing the format of the log message
presenz_plugin_sdk_EXPORT void PzOutputLogString(const LogLevel &logLevel, const char* format, ...);

//////////////////////////////////////////////////////////////////////////
//
// Progression tracker helpers (for PresenZ tools etc...)
/// @brief change the name of a progress bar (only for Callback Progressbar)
presenz_plugin_sdk_EXPORT  void PzProgressTaskName(const char * taskName);

/// @brief switch to an horizontal progress bax or to a vertical percentage counter
/// @param[in] type of progress
presenz_plugin_sdk_EXPORT void PzSetProgressBarType(ProgressBarType progressType);

/// @brief Reset the progression tracker (only for STD out)
/// @param[in] maximum maximum number of increment in the progress bar
presenz_plugin_sdk_EXPORT void PzResetprogress(const size_t &maximum);

/// @brief Increase the progress bar (only for STD out)
presenz_plugin_sdk_EXPORT void PzIncreaseprogress();

/// @brief Make the progress bar complete (only for STD out)
presenz_plugin_sdk_EXPORT void PzSetDoneProgression();

/// @brief Add a callback to the logger to check if the host program has been interupted
presenz_plugin_sdk_EXPORT void PzSetGetAbortCB(progressGetAbortCB getAbortCb, void * userData);

/// @brief return the states of the progression.
presenz_plugin_sdk_EXPORT int  PzGetAbortState();
//////////////////////////////////////////////////////////////////////////
//
// MACROS, are there for readability and convenience. They only invoke methods defined above.

/// @brief Variadic macro for writing in the PresenZ log system
#define APPLOGGER(a, b, ...) PresenZ::Logger::PzOutputLogString(a, b, ##__VA_ARGS__);

/// @brief Enable the header in log lines
#define APPLOGGER_HEADON PresenZ::Logger::PzHeaderEnable(true);

/// @brief Disable the header in log lines
#define APPLOGGER_HEADOFF PresenZ::Logger::PzHeaderEnable(false);

/// @brief Macro that prints text in front of the progress bar
#define APPLOGGER_SETPROGRESSTASKNAME(taskName) PresenZ::Logger::PzProgressTaskName(taskName);

/// @brief Macro that resets the progress bar
#define APPLOGGER_CLEARPROGRESS(max) PresenZ::Logger::PzResetprogress(max);

/// @brief Macro that increases the progress bar
#define APPLOGGER_PROGRESS PresenZ::Logger::PzIncreaseprogress();

/// @brief Macro that marks the progress bar as completed
#define APPLOGGER_PROGRESSDONE  PresenZ::Logger::PzSetDoneProgression();

/// @brief Printf-like defined method that forwards a trace message with current FILE/LINE to the logging system
#define APPLOGGER_TRACE(message) PresenZ::Logger::PzOutputLogString(PresenZ::Logger::LL_Trace, "%s %s line: %d %s\n", __FUNCTION__, __FILE__, __LINE__, message );

/// @brief Printf-like defined method that forwards an INFO message to PresenZ logging system
#define PZ_INFO(a,...) PresenZ::Logger::PzOutputLogString(PresenZ::Logger::LL_Info, a, ##__VA_ARGS__);

/// @brief Printf-like define that forwards a WARNING message to PresenZ logging system
#define PZ_WARNING(a,...) PresenZ::Logger::PzOutputLogString(PresenZ::Logger::LL_Warning, a, ##__VA_ARGS__);

/// @brief Printf analog define that forwards an ERROR message to PresenZ logging system
#define PZ_ERROR(a,...) PresenZ::Logger::PzOutputLogString(PresenZ::Logger::LL_Error, a, ##__VA_ARGS__);

/// @brief Printf analog define that forwards a DEBUG message to PresenZ logging system
#define PZ_DEBUG(a,...) PresenZ::Logger::PzOutputLogString(PresenZ::Logger::LL_Debug, a, ##__VA_ARGS__);

/// @brief Printf analog define that forwards a TRACE message to PresenZ logging system
#define PZ_TRACE(a,...) PresenZ::Logger::PzOutputLogString(PresenZ::Logger::LL_Trace, a, ##__VA_ARGS__);

/*\}*/

} // End namespace PRESENZ_VERSION_NS
using namespace PRESENZ_VERSION_NS;
} // End namespace Logger
} // End namespace PresenZ



#endif


