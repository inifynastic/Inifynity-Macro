#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "macroengine.h"
#include <Windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(742, 465);
    this->setWindowTitle("Inifynity Macro");

    ui->btnStop->setEnabled(false);

    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::handlebtnStart);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::handlebtnStop);

    connect(ui->hurBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
    connect(ui->minBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
    connect(ui->secBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
    connect(ui->milSecBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
    
    connect(ui->edithotKey, &QKeySequenceEdit::keySequenceChanged, this, [this](const QKeySequence &keySequence){
        hotkey = keySequence;
    });
    ui->edithotKey->setEnabled(false); // Temporary solution cuz I am too lazy to make editable hot key
    // TODO: Make the hotkey editable

    RegisterHotKey((HWND)winId(),1, 0,  VK_F6);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handlebtnStart(){
    macro_start_click();
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
}

void MainWindow::handlebtnStop(){
    macro_stop_click();
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
}

void MainWindow::handlechangedTimer(){
    int mstime = ui->hurBox->value() * 3600000 + ui->minBox->value() * 60000 + ui->secBox->value() * 1000 + ui->milSecBox->value();
    // I used AI for above cuz I sux at math.
    macro_set_timer(mstime);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result){
    MSG* msg = reinterpret_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY) {
        if (msg->wParam == 1) {

            qDebug() << "Hotkey pressed!";
            if (!flag) {
                handlebtnStart();
                flag = true;
            } else {
                handlebtnStop();
                flag = false;
            }
            return true;
        }
    }
    return false;
}