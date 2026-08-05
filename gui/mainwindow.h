#ifndef MAINWINDOW_H
#define MAINWINDOW_H


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
    void handlebtnStart();
    void handlebtnStop();
    void handlechangedTimer();
private:

    Ui::MainWindow *ui;
    QKeySequence hotkey = QKeySequence(Qt::Key_F6); // Temporary Solution ofc
    bool flag = false;

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
};
#endif // MAINWINDOW_H
