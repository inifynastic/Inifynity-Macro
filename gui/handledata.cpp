#pragma once //TODO: make send_log avaliable here

#include "handledata.h"

#include <fstream>

#include <QJsonValue>
#include <QJsonDocument>
#include <QFile>
#include <QJsonParseError>
#include <QString>
#include <qkeysequence.h>

bool HandleData::save_hotkey(const QKeySequence &Qkey) {

  save_json("hotkey", Qkey.toString());
  return true;
}

bool HandleData::save_interval(const int interval) {
  save_json("interval", interval);
  return true;
}

bool HandleData::save_mode(const int mode) {
  save_json("clickMode", mode);
  return true;
}  

configuration HandleData::load_config(void) {
  configuration config;
  QFile file("settings.json");

  if (!file.open(QIODevice::ReadOnly)) return config; //send_logs here 

  QJsonParseError error;
  QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &error);

  if (error.error != QJsonParseError::NoError || !document.isObject()) {
    qWarning() << "Invalid config JSON:" << error.errorString();
	//send log here too
    return config;
  }
  QJsonObject object = document.object();

  config.hotkey = QKeySequence(object.value("hotkey").toString("F6"));
  config.interval = object.value("interval").toInt(100);
  config.clickMode = object.value("cliceMode").toInt(1);

  save_json("hotkey", config.hotkey.toString());
  save_json("interval", config.interval);
  save_json("clickMode",config.clickMode);
  
  return config;
}  

void HandleData::write_json(void) {
	  
  QJsonDocument document(object);

  std::ofstream jsonFile("settings.json");

  if (!jsonFile) {
	  return;
    }
  jsonFile << document.toJson().toStdString();

}  

QJsonObject HandleData::save_json(const QString& property, const QString& value) {
  object[property] = value;
  return object;
}

QJsonObject HandleData::save_json(const QString& property, const int value) {
	object[property] = value;
	return object;

}  
