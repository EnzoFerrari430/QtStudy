#include "mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <windows.h>


#pragma execution_character_set("UTF-8")


CMyThread::CMyThread(mainwindow* p)
	: QThread()
	, _pMain(p)
{

}

CMyThread::~CMyThread()
{

}

void CMyThread::run()
{
	/*
	Cannot create children for a parent that is in a different thread
	因为这个this是在主线程里创建的，67行创建的_workThread;
	run函数已经在子线程中了，所以timer不能将_workThread设置为自己的parent
	*/
	QTimer* timer = new QTimer(/*this*/);
	connect(timer, &QTimer::timeout, _pMain, &mainwindow::printSth, Qt::DirectConnection);
	timer->start(10000);

	exec();

	delete timer;
	timer = nullptr;

}

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
	, _workThread(nullptr)
{
    ui.setupUi(this);
}

mainwindow::~mainwindow()
{
	stopThreadTimer();
}

void mainwindow::on_pbStartThread_clicked()
{
	initThreadTimer();
}

void mainwindow::on_pbStopThread_clicked()
{
	stopThreadTimer();
}

void mainwindow::initThreadTimer()
{
	qDebug() << __FUNCTION__ << ": 当前线程: " << QThread::currentThread();

	if (!_workThread)
	{
		_workThread = new CMyThread(this);//传入mainwindow指针
	}

	_workThread->start();
}

void mainwindow::stopThreadTimer()
{
	qDebug() << __FUNCTION__ << ": 当前线程: " << QThread::currentThread();
	if (_workThread)
	{
		_workThread->quit();
		_workThread->wait();

		delete _workThread;

		_workThread = nullptr;
	}
}

void mainwindow::printSth()
{
	qDebug() << __FUNCTION__ << ": 当前线程: " << QThread::currentThread();
	qDebug() << "begin do sth";
	Sleep(9000);
	qDebug() << "end do sth";
}


