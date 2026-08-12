#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inifynityengine.hpp"
#include "enginebridge.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

	ui->setupUi(this);
  
	start_engine();
	register_new_hotkey(&hotkey);
	EngineBridge* bridge = get_engine_bridge();
	 ui->btnStop->setEnabled(false);

    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::handlebtnStart);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::handlebtnStop);

    connect(ui->hurBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
    connect(ui->minBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
    connect(ui->secBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
    connect(ui->milSecBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);

    connect(ui->edithotKey, &QKeySequenceEdit::keySequenceChanged, this,
            &MainWindow::handleHotkeyChange);
    connect(bridge, &EngineBridge::notify_macro_on, this, &MainWindow::handleMacroOn);
 	connect(bridge, &EngineBridge::notify_macro_off, this, &MainWindow::handleMacroOff);
   

}

MainWindow::~MainWindow(){
	stop_engine();
	delete ui;
  
}

void MainWindow::handlebtnStart(){
    clicker_engine_toggle();
}

void MainWindow::handlebtnStop(){
    clicker_engine_toggle();
}

void MainWindow::handlechangedTimer(){
    int mstime = ui->hurBox->value() * 3600000 + ui->minBox->value() * 60000 + ui->secBox->value() * 1000 + ui->milSecBox->value();
    // I used AI for above cuz I sux at math.
    clicker_engine_timer(mstime);
}

void MainWindow::handleHotkeyChange(const QKeySequence &keySequence) {
	hotkey = keySequence;
	register_new_hotkey(&hotkey);
}

void MainWindow::handleMacroOn() {
  ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
 
}

void MainWindow::handleMacroOff() {
  ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);

}  
