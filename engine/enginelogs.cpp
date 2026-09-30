#pragma once

#include "enginelogs.h"
#include "vector"
#include "string"
#include <chrono>

typedef struct {
  std::int64_t timestamp;
  int statusCode;
	std::string message;
} LogData;

extern std::vector<LogData> logsList;

void send_logs(int logCode) {
  LogData logEntry;
  logEntry.timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                           std::chrono::system_clock::now().time_since_epoch())
                           .count(); // Returns unix timestamp
  logEntry.statusCode = logCode;

  switch(logCode){
#define X(code, text)                                                          \
  case code:                                                                   \
    logEntry.message = text;                                                   \
    break;
    
#include "logcode.def"
#undef X
  }
  logsList.push_back(logEntry);
}
