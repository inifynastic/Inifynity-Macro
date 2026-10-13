

#include <qjsonobject.h>

#include <QKeySequence>
#include <QJsonObject>
#include <QString>


struct configuration {
  QKeySequence hotkey;
  int click_interval;
  int click_mode;
};  

class HandleData {
public:
  bool save_hotkey(const QKeySequence &QKey);
  void write_json(void);
  bool load_configuration(void);

private:
  QJsonObject object;

  QJsonObject save_json(const QString& property, const QString& value);
  QJsonObject save_json(const QString &property, const int value);

};  
