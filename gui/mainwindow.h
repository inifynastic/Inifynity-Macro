#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QKeySequence>
#include "enginebridge.h"

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
    void handlebtnStart();
    void handlebtnStop();
    void handlechangedTimer();
private:
	Ui::MainWindow *ui;
	EngineBridge bridge;
	
    QKeySequence hotkey = QKeySequence(Qt::Key_F6); // Temporary Solution ofc

};
#endif // MAINWINDOW_H
