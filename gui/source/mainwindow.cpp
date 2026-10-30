#pragma once

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inifynityengine.hpp"
#include "enginebridge.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  ui->btnStop->setEnabled(false);
  ui->leftClick->toggle();


  
  start_engine();
  EngineBridge *bridge = get_engine_bridge();


    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::handlebtnStartStop);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::handlebtnStartStop);

    connect(ui->hurBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
    connect(ui->minBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
    connect(ui->secBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
    connect(ui->milSecBox, &QSpinBox::valueChanged, this, &MainWindow::handlechangedTimer);
	connect(ui->leftClick, &QRadioButton::toggled, this, &MainWindow::handleModeSwitch);
	connect(ui->rightClick, &QRadioButton::toggled, this, &MainWindow::handleModeSwitch);
	//connect(ui->click_type, &QComboBox::currentIndexChanged, this, &MainWindow::handleTypeSwitch);
        
    connect(ui->edithotKey, &QKeySequenceEdit::keySequenceChanged, this,
            &MainWindow::handleHotkeyChange);
    connect(bridge, &EngineBridge::notify_macro_on, this, &MainWindow::handleMacroOn);
    connect(bridge, &EngineBridge::notify_macro_off, this,
            &MainWindow::handleMacroOff);

	load_settings();


}

MainWindow::~MainWindow() {
	handler.write_json();
	stop_engine();
	delete ui;
  
}

void MainWindow::handlebtnStartStop(){
    clicker_engine_toggle();
}


void MainWindow::handlechangedTimer(){
    int mstime = ui->hurBox->value() * 3600000 + ui->minBox->value() * 60000 + ui->secBox->value() * 1000 + ui->milSecBox->value();

	handler.save_interval(mstime);
    clicker_engine_timer(mstime);
}

 void MainWindow::handleHotkeyChange(const QKeySequence &keySequence) { // Terrifying
   hotkey = keySequence; // A private attribute cuz local variable would die after the function ends.
   if (sender() != ui->edithotKey) {
	   ui->edithotKey->setKeySequence(hotkey);
   } else {
	   handler.save_hotkey(hotkey);
     }
   
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

void MainWindow::handleTypeSwitch() { //TBA

}
void MainWindow::handleModeSwitch(bool checked) {
  if (sender() == ui->leftClick) {
    if (checked) {
      handler.save_mode(1);
      switch_mode(1);      
                    
    }
    
  }
  if (checked) {
	  handler.save_mode(0);
	  switch_mode(0);
  }
}

void MainWindow::load_settings() {
  configuration config = handler.load_config();

  // Keybind
  handleHotkeyChange(config.hotkey);

  clicker_engine_timer(config.interval);
  [&]() { //Lambda Function
    int totalMs = config.interval;
	ui->hurBox->setValue(totalMs / 3600000);
	totalMs %= 3600000;

	ui->minBox->setValue(totalMs / 60000);
	totalMs %= 60000;

	ui->secBox->setValue(totalMs / 1000);
    ui->milSecBox->setValue(totalMs % 1000);
       
        
    }();    
  
}  
