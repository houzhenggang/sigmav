#ifndef MENU_H
#define MENU_H

#include <QtGui/QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QTextCodec>//���������ַ��������ͷ�ļ�
#include <QPushButton>
#include <QTextEdit>
#include <QStackedWidget>
#include <QHBoxLayout>
#include "mypage.h"
#include "qextserialport.h"


class menu : public QWidget
{
    Q_OBJECT

public:
    menu(QWidget *parent = 0);
    ~menu();

    QListWidget *list;//����һ��list����

    pdjly *wdjly;//����djly�Ĵ���
    psbj *wsbj;
    pxglc *wxglc;
    psrfssb *wsrfssb;
    pzgdxj *wzgdxj;
    pzlhgr *wzlhgr;
    plkjc *wlkjc;
    pdazj *wdazj;

    QStackedWidget * infowidget;//����洢��

    Win_QextSerialPort *port;//���崮��

protected slots:
    void pagechanged(int index);
    void sendorder();



};

#endif // MENU_H

