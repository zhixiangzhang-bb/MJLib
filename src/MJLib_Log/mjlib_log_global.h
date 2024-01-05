#pragma once

#include <iostream>



#ifdef MJLib_Log_EXPORTS
#define MJLib_Log_API __declspec(dllexport)
#else
#define MJLib_Log_API __declspec(dllimport)
#endif



//定义谷歌日志库
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
# ifdef ERROR
#  undef ERROR
# endif
const int INFO = GLOG_INFO, WARNING = GLOG_WARNING,
ERROR = GLOG_ERROR, FATAL = GLOG_FATAL;
#endif

