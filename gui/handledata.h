

#include <qjsonobject.h>

#include <QKeySequence>
#include <QJsonObject>
#include <QString>
#include <qkeysequence.h>


struct configuration {
  QKeySequence hotkey = QKeySequence("F6");
  int interval = 100;
  int clickMode = 1;
};  

class HandleData {
public:
  bool save_hotkey(const QKeySequence &QKey);
  bool save_interval(const int interval);
  bool save_mode(const int mode);

  void write_json(void);
  configuration load_config(void);

private:
  QJsonObject object;
  
  QJsonObject save_json(const QString& property, const QString& value);
  QJsonObject save_json(const QString &property, const int value);

};  
