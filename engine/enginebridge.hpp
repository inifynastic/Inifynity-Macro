#pragma once

#include <QObject>

class EngineBridge : public QObject {
  Q_OBJECT

public:
  void macro_on();
  void macro_off();

signals:
  void notify_macro_on();
  void notify_macro_off();
  
}; 
