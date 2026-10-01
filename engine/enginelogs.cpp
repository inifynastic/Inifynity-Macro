#pragma once

#include "enginelogs.h"
#include "string"

#include <chrono>
#include <fstream>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <qjsonobject.h>
#include <qobject.h>

typedef struct {
  std::int64_t timestamp;
  int statusCode;
	std::string message;
} LogData;

QJsonArray jsonList;

QJsonObject translate_qobject(const LogData& LogEntry) {
  QJsonObject logObj;
  logObj["timestamp"] = LogEntry.timestamp;
  logObj["statuscode"] = LogEntry.statusCode;
  logObj["message"] = QString::fromStdString(LogEntry.message);

  return logObj;
}

void file_logger(const QJsonArray& jsonList) {
  
  QJsonDocument document(jsonList);

  std::ofstream jsonFile("log.json");

  if (!jsonFile) {
	  return;
    }
  jsonFile << document.toJson().toStdString();
}  

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
  jsonList.append(translate_qobject(logEntry));
  file_logger(jsonList);
  
}


