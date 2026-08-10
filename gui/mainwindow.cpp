#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "macroengine.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  start_hotkey_engine();
  register_new_hotkey(&hotkey);

  ui->setupUi(this);

	 ui->btnStop->setEnabled(false);



    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::handlebtnStart);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::handlebtnStop);

    connect(ui->hurBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
    connect(ui->minBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
    connect(ui->secBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
    connect(ui->milSecBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);

    connect(ui->edithotKey, &QKeySequenceEdit::keySequenceChanged, this,
            [this](const QKeySequence &keySequence) {
              hotkey = keySequence;
			   register_new_hotkey(&hotkey);

    });

}

MainWindow::~MainWindow(){
	stop_hotkey_engine();
	delete ui;
  
}

void MainWindow::handlebtnStart(){
    macro_toggle();
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
}

void MainWindow::handlebtnStop(){
    macro_toggle();
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
}

void MainWindow::handlechangedTimer(){
    int mstime = ui->hurBox->value() * 3600000 + ui->minBox->value() * 60000 + ui->secBox->value() * 1000 + ui->milSecBox->value();
    // I used AI for above cuz I sux at math.
    macro_set_timer(mstime);
}

