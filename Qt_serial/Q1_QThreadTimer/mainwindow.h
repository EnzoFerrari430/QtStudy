#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = Q_NULLPTR);
	~mainwindow();
public:
	void initThreadTimer();
	void stopThreadTimer();

public slots:
	void printSth();
	void startTimer();

	void on_pbStartThread_clicked();
	void on_pbStopThread_clicked();

private:
    Ui::mainwindowClass ui;
private:
	QTimer* _workTimer;
	QThread* _workThread;
};
