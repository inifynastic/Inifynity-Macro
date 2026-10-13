#pragma once

#include "handledata.h"

#include <fstream>

#include <QJsonValue>
#include <QJsonDocument>

bool HandleData::save_hotkey(const QKeySequence &Qkey) {

  save_json("hotkey", Qkey.toString());
  return true;
}

bool HandleData::load_configuration(void) {

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
  extern QJsonObject object;
  object[property] = value;
  return object;
}

QJsonObject HandleData::save_json(const QString& property, const int value) {
	extern QJsonObject object;
	object[property] = value;
	return object;

}  
