

#include <qjsonobject.h>

#include <QKeySequence>
#include <QJsonObject>
#include <QString>


struct configuration {
  QKeySequence hotkey;
  int interval;
  int clickMode;
};  

class HandleData {
public:
  bool save_hotkey(const QKeySequence &QKey);

  void write_json(void);
  configuration load_config(void);

private:
  QJsonObject object;

  QJsonObject save_json(const QString& property, const QString& value);
  QJsonObject save_json(const QString &property, const int value);

};  
