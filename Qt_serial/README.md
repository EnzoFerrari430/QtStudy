# Qt serial
## 前言 ##
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;从19年10月入职海康以来，一直在公司使用Qt5.6.0配合vs2013进行windows PC端软件开发。其中遇到了有关Qt的大大小小的无数问题，但由于一直忙忙碌碌也没有时间对这种问题进行整理。现在开始一点一点记录回忆保存今年来遇到的各种Qt问题

## 工程说明 ##
1. Q1_QThreadTimer  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这是最近遇到的一个问题，项目里要与服务器进行http通信定时上传数据，但是不能阻塞主界面操作。一开始使用QThread创建线程并启动QTimer定时器，以间隔相同的时间后发送数据。这里打算用创建一个QThread，并将QTimer moveToThread到这个线程中。然后启动定时器与线程。但是这里有坑，定时器的使用需要有事件循环，所以要把握好QThread的事件循环和定时器的启动的先后顺序。


