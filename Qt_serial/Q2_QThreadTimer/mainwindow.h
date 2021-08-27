#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <QThread>


class mainwindow;
class CMyThread : public QThread
{
	Q_OBJECT
public:
	CMyThread(mainwindow*);
	~CMyThread();
public:
	virtual void run() override;
private:
	mainwindow* _pMain;
};



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

	void on_pbStartThread_clicked();
	void on_pbStopThread_clicked();
private:
    Ui::mainwindowClass ui;
private:
	CMyThread* _workThread;
};
