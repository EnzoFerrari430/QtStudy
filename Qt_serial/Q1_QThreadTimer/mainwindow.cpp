#include "mainwindow.h"
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <windows.h>

#pragma execution_character_set("UTF-8")



mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
	, _workTimer(nullptr)
	, _workThread(nullptr)
{
    ui.setupUi(this);

}

mainwindow::~mainwindow()
{
	stopThreadTimer();
}

void mainwindow::initThreadTimer()
{
	qDebug() << __FUNCTION__ << ": 当前线程: " << QThread::currentThread();
	if (!_workTimer)
	{
		//这里不能加this 因为timer和mainwindow不在同一个线程
		_workTimer = new QTimer(/*this*/);
	}

	if (!_workThread)
	{
		_workThread = new QThread(/*this*/);//自己控制线程释放
	}

	_workTimer->moveToThread(_workThread);

	/*
	QObject::startTimer: Timers cannot be started from another thread
	这里要直连，QThread::started信号是在_workThread子线程里发出的，所以这里调用startTimer也要在子线程里调用
	不然就会报上述错误
	*/
	connect(_workThread, SIGNAL(started()), this, SLOT(startTimer()), Qt::DirectConnection);
	/*
	这里也要直连，不然printSth会在this所在的线程执行
	而this所在的线程是在主界面线程，所以Sleep会造成界面卡顿
	*/
	connect(_workTimer, SIGNAL(timeout()), this, SLOT(printSth()), Qt::DirectConnection);

	_workThread->start();
}

void mainwindow::stopThreadTimer()
{
	qDebug() << __FUNCTION__ << ": 当前线程: " << QThread::currentThread();
	if (_workThread && _workTimer)
	{
		//QObject::~QObject: Timers cannot be stopped from another thread
		//因为_workTimer对象属于子线程,stop槽函数不能在主线程中调用
		//_workTimer->stop();
		//使用阻塞队列的方式调用定时器stop
		QMetaObject::invokeMethod(_workTimer, "stop", Qt::BlockingQueuedConnection);
		_workThread->quit();
		_workThread->wait();

		delete _workThread;
		delete _workTimer;

		_workThread = nullptr;
		_workTimer = nullptr;
	}
}

void mainwindow::startTimer()
{
	qDebug() << __FUNCTION__ << ": 当前线程: " << QThread::currentThread();
	_workTimer->start(10000);
}

void mainwindow::on_pbStartThread_clicked()
{
	initThreadTimer();
}

void mainwindow::on_pbStopThread_clicked()
{
	stopThreadTimer();
}

void mainwindow::printSth()
{
	qDebug() << __FUNCTION__ << ": 当前线程: " << QThread::currentThread();
	qDebug() << "begin do sth";
	Sleep(9000);
	qDebug() << "end do sth";
}
