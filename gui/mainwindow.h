#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "handledata.h"

#include <QMainWindow>
#include <QKeySequence>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
  private slots:
	HandleData handler;

    void handlebtnStartStop();
    void handlechangedTimer();
    void handleHotkeyChange(const QKeySequence &keySequence);
    void handleMacroOn();
    void handleMacroOff();
    void handleModeSwitch(bool checked); // Left, Right, Middle
	void handleTypeSwitch(); // Double, Single, Hold
    
private:
  Ui::MainWindow *ui;

	
    QKeySequence hotkey = QKeySequence(Qt::Key_F6); // Temporary Solution ofc

};
#endif // MAINWINDOW_H
