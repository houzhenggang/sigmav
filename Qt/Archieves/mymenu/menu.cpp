#include "menu.h"

menu::menu(QWidget *parent)
    : QWidget(parent)
{
    list=new QListWidget;//�½�����list

    list->setIconSize(QSize(100,45));//������Ŀ��ͼƬ����С
    list->setSpacing(12);//������Ŀ��ͼƬ�����
    list->setViewMode(QListView::IconMode);//������ʾ��Ŀ��ע����ʾ�ڶ�Ӧ��Ŀ����
    list->setMaximumWidth(120);//���������ʾ���
    list->setMovement(QListView::Static);//��ͼƬ����Ϊ��̬�Ĳ�����ק��




    QListWidgetItem *djly=new QListWidgetItem;//���ͼƬ��Ŀ��menu
    djly->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/djly.PNG"));//���ͼƬ·��

    djly->setText(tr("�罷����"));//����Ŀ����ע��

    QListWidgetItem *sbj=new QListWidgetItem;
    sbj->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/sbj.PNG"));
    sbj->setText(tr("������"));

    QListWidgetItem *xglc=new QListWidgetItem;
    xglc->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/xglc.PNG"));
    xglc->setText(tr("�ʹ�����"));

    QListWidgetItem *srfssb=new QListWidgetItem;
    srfssb->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/srfssb.PNG"));
    srfssb->setText(tr("��˿�ȱ�"));

    QListWidgetItem *zgdxj=new QListWidgetItem;
    zgdxj->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/zgdxj.PNG"));
    zgdxj->setText(tr("黹���С��"));

    QListWidgetItem *zlhgr=new QListWidgetItem;
    zlhgr->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/zlhgr.PNG"));
    zlhgr->setText(tr("�����ع���"));

    QListWidgetItem *lkjc=new QListWidgetItem;
    lkjc->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/lkjc.PNG"));
    lkjc->setText(tr("��������"));

    QListWidgetItem *dazj=new QListWidgetItem;
    dazj->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/dazj.PNG"));
    dazj->setText(tr("�����Ӽ�"));

    //QTextEdit *ordered=new QTextEdit;//����������ʾ�Ѿ���õĲ˵�Ŀ¼


    list->addItem(djly);//��ͼƬdjly���뵽list����
    list->addItem(sbj);
    list->addItem(xglc);
    list->addItem(srfssb);
    list->addItem(zgdxj);
    list->addItem(zlhgr);
    list->addItem(lkjc);
    list->addItem(dazj);


    QPushButton * clo=new QPushButton;//������ť
    connect(clo,SIGNAL(clicked()),this,SLOT(close()));
                                     //����źŲ�clo����ť��
                                    //SIGNAL(clicked())�����clo��ť�����źţ�
                                   //this������������źţ�
                                  //SLOT(close()):���ú���close��������

    clo->setText(tr("�ر�"));//��ť����ʾ���֣��ر�
    //clo->resize(20,5);
    QPushButton * allok=new QPushButton;
    allok->setText(tr("ȷ�ϵ��"));
    connect(allok,SIGNAL(clicked()),this,SLOT(sendorder()));


    infowidget=new QStackedWidget;//����infowidget����
    wdjly=new pdjly;//����ʵ�����ռ�
    wsbj=new psbj;
    wxglc=new pxglc;
    wsrfssb=new psrfssb;
    wzgdxj=new pzgdxj;
    wzlhgr=new pzlhgr;
    wlkjc=new plkjc;
    wdazj=new pdazj;

    infowidget->addWidget(wdjly);//��menu���ж������Ŀ��ӽ�ȥ
    infowidget->addWidget(wsbj);
    infowidget->addWidget(wxglc);
    infowidget->addWidget(wsrfssb);
    infowidget->addWidget(wzgdxj);
    infowidget->addWidget(wzlhgr);
    infowidget->addWidget(wlkjc);
    infowidget->addWidget(wdazj);

    connect(list,SIGNAL(currentRowChanged(int)),this,SLOT(pagechanged(int)));
    //connect(list,SIGNAL(currentRowChanged(int)),this,SLOT());


/*
    QVBoxLayout *vlayout=new QVBoxLayout(this);//�½����ֹ�����
    vlayout->addWidget(list);//�����ֹ��������뵽list������
    vlayout->addWidget(ordered);//���ĵ��鿴�����뵽���ֹ�����
    vlayout->addWidget(clo);//��clo��ӵ����ֹ�������ʹ�ò��ֹ���������
    this->setLayout(vlayout);//���ò��ֹ������ĺ������ϵ
*/

    QHBoxLayout *hlayout=new QHBoxLayout;//����һ�����򲼾ֹ�����
    hlayout->addWidget(list);//���
    hlayout->addWidget(infowidget);

    QGridLayout *mainlayout=new QGridLayout(this);//���������ֹ�����
    mainlayout->addLayout(hlayout,0,0,1,6);//�����ֹ������Ĵ��ڼ���������ֹ�����
    //mainlayout->addWidget(ordered,1,6,1,1);
    mainlayout->addWidget(allok,1,3,1,1);
    mainlayout->addWidget(clo,1,5,1,1);
    this->resize(800,600);//���ô��ڴ�С




}

menu::~menu()
{
    ofstream ofile("C:/Qt/2010.04/qt/mymenu/menu.txt",ios::out);

    ofile.clear();

    ofile.close();

}

void menu::pagechanged(int index)//�Զ���Ľ��ܺ���
{
    infowidget->setCurrentIndex(index);
   // infowidget->
    switch(index)
    {
    //infowidget->widget(index);

    case 0:
        ((pdjly *)infowidget->widget(index))->reflash();
        break;
    case 1:
        ((psbj *)infowidget->widget(index))->reflash();
        break;
    case 2:
        ((pxglc *)infowidget->widget(index))->reflash();
        break;
    case 3:
        ((psrfssb *)infowidget->widget(index))->reflash();
        break;
    case 4:
        ((pzgdxj *)infowidget->widget(index))->reflash();
        break;
    case 5:
        ((pzlhgr *)infowidget->widget(index))->reflash();
        break;
    case 6:
        ((plkjc *)infowidget->widget(index))->reflash();
        break;
    case 7:
        ((pdazj *)infowidget->widget(index))->reflash();
        break;
    }
}

void menu::sendorder()
{
    char temp;


    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    port=new Win_QextSerialPort("COM4");

    port->setBaudRate(BAUD115200);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);



    port->open(QIODevice::ReadWrite);


   ifile.seekg(0);

    while(!ifile.eof())
    {
          ifile>>temp;

          if(temp!='a')
          {

              while(!port->isWritable())
                {;}

              port->putChar('0');
              while(!port->isWritable())
                {;}
              port->putChar('0');
              while(!port->isWritable())
                {;}
              port->putChar('1');

              while(!port->isWritable())
                {;}
              port->putChar('0');
              while(!port->isWritable())
                {;}
              port->putChar('0');
              while(!port->isWritable())
                {;}
              port->putChar(temp);

              temp='a';
          }
    }

    port->close();

}


