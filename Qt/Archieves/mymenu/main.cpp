#include <QtGui/QApplication>
#include "menu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//�Ӵ�������ȷ��ʾ����

    menu w;
    w.show();

    return a.exec();
}
