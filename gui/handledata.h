

#include <qjsonobject.h>
#include <string>

#include <QKeySequence>
#include <QJsonObject>


class HandleData {
public:
  void save_hotkey(const QKeySequence& QKey);

private:
  QJsonObject parse_json(const std::string& value);
  int save_json();
  
};  
