#include "mypage.h"


pdjly::pdjly(QWidget *parent)
    : QWidget(parent)
{


    namelabel=new QLabel(tr("������"));
    stylelabel=new QLabel(tr("��ϵ��"));
    speclabel=new QLabel(tr("�ص�"));
    conslabel=new QLabel(tr("���ϣ�"));
    introlabel=new QLabel(tr("������飺"));

    nameline=new QLineEdit(tr("�罷  ����"));
    styleline=new QLineEdit(tr("����"));
    specline=new QLineEdit(tr("ɫ�����ޣ���ζ�ɿڣ�������ʪ"));

    consline=new QListWidget;
    consline->setSpacing(3);
    QListWidgetItem *consitem=new QListWidgetItem(consline);
    consitem->setText(tr("����ɾ�������һ��"));
    QListWidgetItem *consitem3=new QListWidgetItem(consline);
    consitem3->setText(tr("���ʵĻ���һ�� ���Ρ���Ҷ����Ƭ"));
    QListWidgetItem *consitem4=new QListWidgetItem(consline);
    consitem4->setText(tr("�׾ơ����͡��״ס����ѽ�"));
    QListWidgetItem *consitem2=new QListWidgetItem(consline);
    consitem2->setText(tr("���ǡ���ĩ�����顢����"));




      introline=new QListWidget;
      introline->setSpacing(3);
      QListWidgetItem *it1=new QListWidgetItem(introline);
      it1->setText(tr("1��������Ĩ�Σ���Ƥ�����Ҷ����Ƭ�����Сʱ"));
      QListWidgetItem *it2=new QListWidgetItem(introline);
      it2->setText(tr("2�����㸹�ٿ���ȥ�ǣ�̯ƽ���⣬���߸��г��������������׾ơ��������͡������״ף��Ӱ뱭ˮ��װ��΢����"));
      QListWidgetItem *it3=new QListWidgetItem(introline);
      it3->setText(tr("3�������΢��¯�պü��޳ߴ����б���������Բ�̣���Ϊ����Ҫ��ת�����ܼ��ȣ�����ֻҪ������ȥ���ɡ� "));
      QListWidgetItem *it4=new QListWidgetItem(introline);
      it4->setText(tr("4.ʱ�䵽����΢������������������֭���ӷ��ѽ������ǡ���ĩ�����顢���ۡ��׾ơ��Σ�������֭"));
      QListWidgetItem *it5=new QListWidgetItem(introline);
      it5->setText(tr("5�����õ���֭���ȵĽ��������õ����ϼ��ɡ�"));
      QListWidgetItem *it6=new QListWidgetItem(introline);
      it6->setText(tr("6����׺�������ס����ඹ���罷������Ҷ��ζ����������"));

      QListWidget *pic=new QListWidget;
      QListWidgetItem *picitem=new QListWidgetItem(pic);
      picitem->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/djly.PNG"));
      pic->setIconSize(QSize(470,370));

      QPushButton *ok=new QPushButton;
      ok->setText(tr("���"));
      connect(ok,SIGNAL(clicked()),this,SLOT(ok_clicked()));

     // QTextEdit *ordered=new QTextEdit;//����������ʾ�Ѿ���õĲ˵�Ŀ¼
      ordered=new QListWidget;//����������ʾ�Ѿ���õĲ˵�Ŀ¼


    QGridLayout *glayout=new QGridLayout(this);//����һ������Ĳ��ֹ�����
    //glayout->setSpacing(12);

    glayout->addWidget(namelabel,0,0);//����Ŀnamelabel��ӽ����ֹ�����

    glayout->addWidget(nameline,0,1);     //���ֲ��������꣬�����꣬ռ���и�����ռ���и���
    glayout->addWidget(stylelabel,1,0);
    glayout->addWidget(styleline,1,1);
    glayout->addWidget(speclabel,2,0);
    glayout->addWidget(specline,2,1);
    //glayout->addWidget(packagegroup,2,0,2,2);
    glayout->addWidget(conslabel,3,0);
    glayout->addWidget(consline,3,1);

    glayout->addWidget(pic,0,3,4,4);

    glayout->addWidget(introlabel,4,0);
    glayout->addWidget(introline,4,1,4,4);
    glayout->addWidget(ok,8,5,1,1);
    glayout->addWidget(ordered,9,1,1,5);



    this->setLayout(glayout);//�����ֹ�������ӽ�����
 //------------------------------------
    reflash();
//----------------------------------


}

void pdjly::ok_clicked()
{
    ordered->clear();

    ofstream ofile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::out|ios::app);
    ofile<<1<<endl;
    ofile.close();

    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();

    /*
    djly
    sbj
    xglc
    srfssb
    zgdxj
    zlhgr
    lkjc
    dazj
    */
}


//--------------------------
void pdjly::reflash()
{
    ordered->clear();


    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();

    /*
    djly
    sbj
    xglc
    srfssb
    zgdxj
    zlhgr
    lkjc
    dazj
    */
}

//-----------------------------







psbj::psbj(QWidget *parent)
    : QWidget(parent)
{
    namelabel=new QLabel(tr("������"));
    stylelabel=new QLabel(tr("��ϵ��"));
    speclabel=new QLabel(tr("�ص�"));
    conslabel=new QLabel(tr("���ϣ�"));
    introlabel=new QLabel(tr("������飺"));

    nameline=new QLineEdit(tr("�� �� ��"));
    styleline=new QLineEdit(tr("ɽ��"));
     specline=new QLineEdit(tr("����Ϯ�ˣ��ڸм���"));

    consline=new QListWidget;
    consline->setSpacing(3);
    QListWidgetItem *consitem=new QListWidgetItem(consline);
    consitem->setText(tr("�����"));
    QListWidgetItem *consitem3=new QListWidgetItem(consline);
    consitem3->setText(tr("���ͣ��ϳ飬��"));
    QListWidgetItem *consitem4=new QListWidgetItem(consline);
    consitem4->setText(tr("�У�������"));
    QListWidgetItem *consitem2=new QListWidgetItem(consline);
    consitem2->setText(tr("�ǣ���ͣ��Σ�����ۣ�����"));




      introline=new QListWidget;
      introline->setSpacing(3);
      QListWidgetItem *it1=new QListWidgetItem(introline);
      it1->setText(tr("1������ϴ���󣬿�ˮ���������ӣ�ȥѪĩ"));
      QListWidgetItem *it2=new QListWidgetItem(introline);
      it2->setText(tr("2���õ��ڼ����Ͽڣ��ý��ס��жΡ��Ͼƣ���ͣ���������ȣ���һСʱ"));
      QListWidgetItem *it3=new QListWidgetItem(introline);
      it3->setText(tr("3����ú󣬲��������ϵĽ���֮��,Ҫ����ɾ� "));
      QListWidgetItem *it4=new QListWidgetItem(introline);
      it4->setText(tr("4.���ﵹ�����ͣ�����жΡ���Ƭ����귭�����������뼦�鳴����������Ի�"));
      QListWidgetItem *it5=new QListWidgetItem(introline);
      it5->setText(tr("5�����뽴����ɫ���ٵ����Ͼƣ��������"));
      QListWidgetItem *it6=new QListWidgetItem(introline);
      it6->setText(tr("6����С��������������󣬴����֭������ж��ٷ������¼���"));

      QListWidget *pic=new QListWidget;
      QListWidgetItem *picitem=new QListWidgetItem(pic);
      picitem->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/sbj.PNG"));
      pic->setIconSize(QSize(470,370));

      QPushButton *ok=new QPushButton;
      ok->setText(tr("���"));
      connect(ok,SIGNAL(clicked()),this,SLOT(ok_clicked()));

      ordered=new QListWidget;//����������ʾ�Ѿ���õĲ˵�Ŀ¼


    QGridLayout *glayout=new QGridLayout(this);//����һ������Ĳ��ֹ�����
    //glayout->setSpacing(12);

    glayout->addWidget(namelabel,0,0);//����Ŀnamelabel��ӽ����ֹ�����
    glayout->addWidget(speclabel);
    glayout->addWidget(nameline,0,1);     //���ֲ��������꣬�����꣬ռ���и�����ռ���и���
    glayout->addWidget(stylelabel,1,0);
    glayout->addWidget(styleline,1,1);
    glayout->addWidget(speclabel,2,0);
    glayout->addWidget(specline,2,1);
    //glayout->addWidget(packagegroup,2,0,2,2);
    glayout->addWidget(conslabel,3,0);
    glayout->addWidget(consline,3,1);

    glayout->addWidget(pic,0,3,4,4);

    glayout->addWidget(introlabel,4,0);
    glayout->addWidget(introline,4,1,4,4);
    glayout->addWidget(ok,8,5,1,1);
    glayout->addWidget(ordered,9,1,1,5);


    this->setLayout(glayout);//�����ֹ�������ӽ�����
    reflash();
}

void psbj::ok_clicked()
{
    ordered->clear();

    ofstream ofile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::out|ios::app);
    ofile<<2<<endl;
    ofile.close();

    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();
}
//--------------------------
void psbj::reflash()
{
    ordered->clear();


    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();

    /*
    djly
    sbj
    xglc
    srfssb
    zgdxj
    zlhgr
    lkjc
    dazj
    */
}

//-----------------------------





pxglc::pxglc(QWidget *parent)
    : QWidget(parent)
{
    namelabel=new QLabel(tr("������"));
    stylelabel=new QLabel(tr("��ϵ��"));
    speclabel=new QLabel(tr("�ص�"));
    conslabel=new QLabel(tr("���ϣ�"));
    introlabel=new QLabel(tr("������飺"));

    nameline=new QLineEdit(tr("�ʹ�  ����"));
    styleline=new QLineEdit(tr("����"));
     specline=new QLineEdit(tr("�ۡ��ʡ�������Ӫ��"));

    consline=new QListWidget;
    consline->setSpacing(3);
    QListWidgetItem *consitem=new QListWidgetItem(consline);
    consitem->setText(tr("����"));
    QListWidgetItem *consitem3=new QListWidgetItem(consline);
    consitem3->setText(tr("���̡�����"));
    QListWidgetItem *consitem4=new QListWidgetItem(consline);
    consitem4->setText(tr("�Ρ�ζ��"));
    QListWidgetItem *consitem2=new QListWidgetItem(consline);
    consitem2->setText(tr("�ƾơ�ˮ���"));




      introline=new QListWidget;
      introline->setSpacing(3);
      QListWidgetItem *it1=new QListWidgetItem(introline);
      it1->setText(tr("1��������ȥ����"));
      QListWidgetItem *it2=new QListWidgetItem(introline);
      it2->setText(tr("2��ȥ�ǡ�����Ƭ"));
      QListWidgetItem *it3=new QListWidgetItem(introline);
      it3->setText(tr("3���������Ͻ� "));
      QListWidgetItem *it4=new QListWidgetItem(introline);
      it4->setText(tr("4.���������͹���һ�£�����"));
      QListWidgetItem *it5=new QListWidgetItem(introline);
      it5->setText(tr("5�����ڼ������������"));
      QListWidgetItem *it6=new QListWidgetItem(introline);
      it6->setText(tr("6������տ����� �������̣�������ۼ��ɡ�"));

      QListWidget *pic=new QListWidget;
      QListWidgetItem *picitem=new QListWidgetItem(pic);
      picitem->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/xglc.PNG"));
      pic->setIconSize(QSize(470,370));

      QPushButton *ok=new QPushButton;
      ok->setText(tr("���"));
      connect(ok,SIGNAL(clicked()),this,SLOT(ok_clicked()));

      ordered=new QListWidget;//����������ʾ�Ѿ���õĲ˵�Ŀ¼


    QGridLayout *glayout=new QGridLayout(this);//����һ������Ĳ��ֹ�����
    //glayout->setSpacing(12);

    glayout->addWidget(namelabel,0,0);//����Ŀnamelabel��ӽ����ֹ�����
    glayout->addWidget(nameline,0,1);     //���ֲ��������꣬�����꣬ռ���и�����ռ���и���
    glayout->addWidget(stylelabel,1,0);
    glayout->addWidget(styleline,1,1);
    glayout->addWidget(speclabel,2,0);
    glayout->addWidget(specline,2,1);
    //glayout->addWidget(packagegroup,2,0,2,2);
    glayout->addWidget(conslabel,3,0);
    glayout->addWidget(consline,3,1);

    glayout->addWidget(pic,0,3,4,4);

    glayout->addWidget(introlabel,4,0);
    glayout->addWidget(introline,4,1,4,4);
    glayout->addWidget(ok,8,5,1,1);
    glayout->addWidget(ordered,9,1,1,5);



    this->setLayout(glayout);//�����ֹ�������ӽ�����
    reflash();
}

void pxglc::ok_clicked()
{
    ordered->clear();

    ofstream ofile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::out|ios::app);
    ofile<<3<<endl;
    ofile.close();
    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();
}
//--------------------------
void pxglc::reflash()
{
    ordered->clear();


    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();

    /*
    djly
    sbj
    xglc
    srfssb
    zgdxj
    zlhgr
    lkjc
    dazj
    */
}

//-----------------------------





psrfssb::psrfssb(QWidget *parent)
    : QWidget(parent)
{

    namelabel=new QLabel(tr("������"));
    stylelabel=new QLabel(tr("��ϵ��"));
    speclabel=new QLabel(tr("�ص�"));
    conslabel=new QLabel(tr("���ϣ�"));
    introlabel=new QLabel(tr("������飺"));

    nameline=new QLineEdit(tr("���ط�˿�ȱ�"));
    styleline=new QLineEdit(tr("�㶫"));
    specline=new QLineEdit(tr("ɫ�����ۣ�Ӫ����ζ���ڸм���"));

    consline=new QListWidget;
    consline->setSpacing(3);
    QListWidgetItem *consitem=new QListWidgetItem(consline);
    consitem->setText(tr("�����ȱ�"));
    QListWidgetItem *consitem3=new QListWidgetItem(consline);
    consitem3->setText(tr("���⡢���"));
    QListWidgetItem *consitem4=new QListWidgetItem(consline);
    consitem4->setText(tr("ɫ���͡���"));
    QListWidgetItem *consitem2=new QListWidgetItem(consline);
    consitem2->setText(tr("���ۡ����ڷ�˿"));




      introline=new QListWidget;
      introline->setSpacing(3);
      QListWidgetItem *it1=new QListWidgetItem(introline);
      it1->setText(tr("1����ϴ�ɾ���������ȫ�޳�����"));
      QListWidgetItem *it2=new QListWidgetItem(introline);
      it2->setText(tr("2������ˮ�����������ӣ��ÿ���˳ʱ����ת���⣬��������Ŀ����ʹ����������ɳ�������"));
      QListWidgetItem *it3=new QListWidgetItem(introline);
      it3->setText(tr("3���ѱ���������У����ִ�ϴ�����������ˮϴһ�鼴�ɡ� "));
      QListWidgetItem *it4=new QListWidgetItem(introline);
      it4->setText(tr("4.���ڷ�˿��������ˮ�а��Сʱ������"));
      QListWidgetItem *it5=new QListWidgetItem(introline);
      it5->setText(tr("5�������Ƥ���ô�����������飬����дл������á�"));
      QListWidgetItem *it6=new QListWidgetItem(introline);
      it6->setText(tr("6�������ص����͹���Ѹ�ٷ����������ص���ɫ������һ�������У����á�"));
      QListWidgetItem *it7=new QListWidgetItem(introline);
      it7->setText(tr("7�����������м����κͼ��۵�ζ��"));
      QListWidgetItem *it8=new QListWidgetItem(introline);
      it8->setText(tr("8������˿����״�ֱ�����ȱ����У�Ȼ�󽫱����ڷ��ڷ�˿�ϡ�"));
      QListWidgetItem *it9=new QListWidgetItem(introline);
      it9->setText(tr("9����������ͬɫ����һ��ͿĨ���ȱ����˿�ϡ�"));
      QListWidgetItem *it10=new QListWidgetItem(introline);
      it10->setText(tr("10�������ѿ������ǽ��ȱ�����ذ������У�����������������ӣ����ɡ�"));
      QListWidgetItem *it11=new QListWidgetItem(introline);
      it11->setText(tr("11��������������������дл��ϼ��ɡ�"));

      QListWidget *pic=new QListWidget;
      QListWidgetItem *picitem=new QListWidgetItem(pic);
      picitem->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/srfssb.PNG"));
      pic->setIconSize(QSize(470,370));

      QPushButton *ok=new QPushButton;
      ok->setText(tr("���"));
      connect(ok,SIGNAL(clicked()),this,SLOT(ok_clicked()));

      ordered=new QListWidget;//����������ʾ�Ѿ���õĲ˵�Ŀ¼


    QGridLayout *glayout=new QGridLayout(this);//����һ������Ĳ��ֹ�����
    //glayout->setSpacing(12);

    glayout->addWidget(namelabel,0,0);//����Ŀnamelabel��ӽ����ֹ�����
    glayout->addWidget(nameline,0,1);     //���ֲ��������꣬�����꣬ռ���и�����ռ���и���
    glayout->addWidget(stylelabel,1,0);
    glayout->addWidget(styleline,1,1);
    glayout->addWidget(speclabel,2,0);
    glayout->addWidget(specline,2,1);
    //glayout->addWidget(packagegroup,2,0,2,2);
    glayout->addWidget(conslabel,3,0);
    glayout->addWidget(consline,3,1);

    glayout->addWidget(pic,0,3,4,4);

    glayout->addWidget(introlabel,4,0);
    glayout->addWidget(introline,4,1,4,4);
    glayout->addWidget(ok,8,5,1,1);
    glayout->addWidget(ordered,9,1,1,5);



    this->setLayout(glayout);//�����ֹ�������ӽ�����
    reflash();
}

void psrfssb::ok_clicked()
{
    ordered->clear();

    ofstream ofile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::out|ios::app);
    ofile<<4<<endl;
    ofile.close();

    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();
}
//--------------------------
void psrfssb::reflash()
{
    ordered->clear();


    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();

    /*
    djly
    sbj
    xglc
    srfssb
    zgdxj
    zlhgr
    lkjc
    dazj
    */
}

//-----------------------------





pzgdxj::pzgdxj(QWidget *parent)
    : QWidget(parent)
{
    namelabel=new QLabel(tr("������"));
    stylelabel=new QLabel(tr("��ϵ��"));
    speclabel=new QLabel(tr("�ص�"));
    conslabel=new QLabel(tr("���ϣ�"));
    introlabel=new QLabel(tr("������飺"));

    nameline=new QLineEdit(tr("黹� �� С��"));
    styleline=new QLineEdit(tr("����"));
     specline=new QLineEdit(tr("��������Ʒζ����"));

    consline=new QListWidget;
    consline->setSpacing(3);
    QListWidgetItem *consitem=new QListWidgetItem(consline);
    consitem->setText(tr("�۹���һֻ"));
    QListWidgetItem *consitem3=new QListWidgetItem(consline);
    consitem3->setText(tr("黹�"));
    QListWidgetItem *consitem4=new QListWidgetItem(consline);
    consitem4->setText(tr("�ɺ�����"));
    QListWidgetItem *consitem2=new QListWidgetItem(consline);
    consitem2->setText(tr("�˽ǡ��н���"));




      introline=new QListWidget;
      introline->setSpacing(3);
      QListWidgetItem *it1=new QListWidgetItem(introline);
      it1->setText(tr("1���Ģ��ϴ�ɾ�������ˮ�ݷ�30���ӣ����ɴ���"));
      QListWidgetItem *it2=new QListWidgetItem(introline);
      it2->setText(tr("2����ϴ�������С��"));
      QListWidgetItem *it3=new QListWidgetItem(introline);
      it3->setText(tr("3�������ڿ�ˮ����3���ӣ��̳�����ˮ��ȥ��ĭ������ˮ�ֱ��á� "));
      QListWidgetItem *it4=new QListWidgetItem(introline);
      it4->setText(tr("4.������ͣ����Ⱥ����뼦���𱬳�5����"));
      QListWidgetItem *it5=new QListWidgetItem(introline);
      it5->setText(tr("5���Ѵн���˽Ǻͺ콷�ù��׵����ͱ��㣬Ȼ���ô�𷭳�һ���ӡ�"));
      QListWidgetItem *it6=new QListWidgetItem(introline);
      it6->setText(tr("6�������Ͼƣ��������飬���ǣ�����ˮ����տ���ת�л���20���ӡ�"));
      QListWidgetItem *it7=new QListWidgetItem(introline);
      it7->setText(tr("7������ݷ��õ�黹�����С�����20���ӣ���������ε�ζ��"));
      QListWidgetItem *it8=new QListWidgetItem(introline);
      it8->setText(tr("8�������֭������ǰ����л����ɡ�"));

      QListWidget *pic=new QListWidget;
      QListWidgetItem *picitem=new QListWidgetItem(pic);
      picitem->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/zgdxj.PNG"));
      pic->setIconSize(QSize(470,370));

      QPushButton *ok=new QPushButton;
      ok->setText(tr("���"));
      connect(ok,SIGNAL(clicked()),this,SLOT(ok_clicked()));

      ordered=new QListWidget;//����������ʾ�Ѿ���õĲ˵�Ŀ¼


    QGridLayout *glayout=new QGridLayout(this);//����һ������Ĳ��ֹ�����
    //glayout->setSpacing(12);

    glayout->addWidget(namelabel,0,0);//����Ŀnamelabel��ӽ����ֹ�����
    glayout->addWidget(nameline,0,1);     //���ֲ��������꣬�����꣬ռ���и�����ռ���и���
    glayout->addWidget(stylelabel,1,0);
    glayout->addWidget(styleline,1,1);
    glayout->addWidget(speclabel,2,0);
    glayout->addWidget(specline,2,1);
    //glayout->addWidget(packagegroup,2,0,2,2);
    glayout->addWidget(conslabel,3,0);
    glayout->addWidget(consline,3,1);

    glayout->addWidget(pic,0,3,4,4);

    glayout->addWidget(introlabel,4,0);
    glayout->addWidget(introline,4,1,4,4);
    glayout->addWidget(ok,8,5,1,1);
    glayout->addWidget(ordered,9,1,1,5);



    this->setLayout(glayout);//�����ֹ�������ӽ�����
    reflash();
}

void pzgdxj::ok_clicked()
{

    ordered->clear();
    ofstream ofile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::out|ios::app);
    ofile<<5<<endl;
    ofile.close();

    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();
}
//--------------------------
void pzgdxj::reflash()
{
    ordered->clear();


    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();

    /*
    djly
    sbj
    xglc
    srfssb
    zgdxj
    zlhgr
    lkjc
    dazj
    */
}

//-----------------------------





pzlhgr::pzlhgr(QWidget *parent)
    : QWidget(parent)
{
    namelabel=new QLabel(tr("������"));
    stylelabel=new QLabel(tr("��ϵ��"));
    speclabel=new QLabel(tr("�ص�"));
    conslabel=new QLabel(tr("���ϣ�"));
    introlabel=new QLabel(tr("������飺"));

    nameline=new QLineEdit(tr(" ���� �� ����"));
    styleline=new QLineEdit(tr("����"));
     specline=new QLineEdit(tr("��ζ�˱ǰ��׿��ţ���ˬ��ζ"));

    consline=new QListWidget;
    consline->setSpacing(3);
    QListWidgetItem *consitem=new QListWidgetItem(consline);
    consitem->setText(tr("���廨��"));
    QListWidgetItem *consitem3=new QListWidgetItem(consline);
    consitem3->setText(tr("���⣨���磩���Ͻ����Ͻ�˿"));
    QListWidgetItem *consitem4=new QListWidgetItem(consline);
    consitem4->setText(tr("��ɰ�ǡ����顢���� "));
    QListWidgetItem *consitem2=new QListWidgetItem(consline);
    consitem2->setText(tr("�а�˿����������������ˮ���� "));




      introline=new QListWidget;
      introline->setSpacing(3);
      QListWidgetItem *it1=new QListWidgetItem(introline);
      it1->setText(tr("1���������廨��ϴ�������Ͻ�Ƭһ���ڹ���С�������̳�����ˮ������"));
      QListWidgetItem *it2=new QListWidgetItem(introline);
      it2->setText(tr("2�����⣨���磩�г�3cm���ĶΡ��������廨���гɾ��������ı�Ƭ"));
      QListWidgetItem *it3=new QListWidgetItem(introline);
      it3->setText(tr("3���л���Ⱦ����������廨��Ƭ������Գ��͡� "));
      QListWidgetItem *it4=new QListWidgetItem(introline);
      it4->setText(tr("4������Ƭ����������һ�ߣ��Ĵ�������������������ˮ���������Ⱥ��Ͻ�˿�ʹа�˿����"));
      QListWidgetItem *it5=new QListWidgetItem(introline);
      it5->setText(tr("5�������ɰ�ǣ������⣨���磩�η���ͬ��3���ӣ�����������ͼ������ɡ�"));

      QListWidget *pic=new QListWidget;
      QListWidgetItem *picitem=new QListWidgetItem(pic);
      picitem->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/zlhgr.PNG"));
      pic->setIconSize(QSize(470,370));

      QPushButton *ok=new QPushButton;
      ok->setText(tr("���"));
      connect(ok,SIGNAL(clicked()),this,SLOT(ok_clicked()));

      ordered=new QListWidget;//����������ʾ�Ѿ���õĲ˵�Ŀ¼


    QGridLayout *glayout=new QGridLayout(this);//����һ������Ĳ��ֹ�����
    //glayout->setSpacing(12);

    glayout->addWidget(namelabel,0,0);//����Ŀnamelabel��ӽ����ֹ�����
    glayout->addWidget(nameline,0,1);     //���ֲ��������꣬�����꣬ռ���и�����ռ���и���
    glayout->addWidget(stylelabel,1,0);
    glayout->addWidget(styleline,1,1);
    glayout->addWidget(speclabel,2,0);
    glayout->addWidget(specline,2,1);
    //glayout->addWidget(packagegroup,2,0,2,2);
    glayout->addWidget(conslabel,3,0);
    glayout->addWidget(consline,3,1);

    glayout->addWidget(pic,0,3,4,4);

    glayout->addWidget(introlabel,4,0);
    glayout->addWidget(introline,4,1,4,4);
    glayout->addWidget(ok,8,5,1,1);
    glayout->addWidget(ordered,9,1,1,5);


    this->setLayout(glayout);//�����ֹ�������ӽ�����
    reflash();
}

void pzlhgr::ok_clicked()
{
    ordered->clear();

    ofstream ofile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::out|ios::app);
    ofile<<6<<endl;
    ofile.close();

    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();
}
//--------------------------
void pzlhgr::reflash()
{
    ordered->clear();


    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();

    /*
    djly
    sbj
    xglc
    srfssb
    zgdxj
    zlhgr
    lkjc
    dazj
    */
}

//-----------------------------





plkjc::plkjc(QWidget *parent)
    : QWidget(parent)
{
    namelabel=new QLabel(tr("������"));
    stylelabel=new QLabel(tr("��ϵ��"));
    speclabel=new QLabel(tr("�ص�"));
    conslabel=new QLabel(tr("���ϣ�"));
    introlabel=new QLabel(tr("������飺"));

    nameline=new QLineEdit(tr("����  ����"));
    styleline=new QLineEdit(tr("����"));
     specline=new QLineEdit(tr("���ڴ��㣬�ڸм���"));

    consline=new QListWidget;
    consline->setSpacing(3);
    QListWidgetItem *consitem=new QListWidgetItem(consline);
    consitem->setText(tr("����"));
    QListWidgetItem *consitem3=new QListWidgetItem(consline);
    consitem3->setText(tr("�Ρ����ǡ�����"));
    QListWidgetItem *consitem4=new QListWidgetItem(consline);
    consitem4->setText(tr("���ۡ����͡��Ͼ�"));
    QListWidgetItem *consitem2=new QListWidgetItem(consline);
    consitem2->setText(tr("�����ۡ������ۡ������"));




      introline=new QListWidget;
      introline->setSpacing(3);
      QListWidgetItem *it1=new QListWidgetItem(introline);
      it1->setText(tr("1���������е��Ϸ��뼦�⣬���ȣ��ü�����ȵ�մ�����ϡ�"));
      QListWidgetItem *it2=new QListWidgetItem(introline);
      it2->setText(tr("2���������ܷ���������ر���12��Сʱ��"));
      QListWidgetItem *it3=new QListWidgetItem(introline);
      it3->setText(tr("3������õļ�����ȷ��뿾�̣�ˢ�ϵ��ϣ����ϻ�10���ӡ� "));
      QListWidgetItem *it4=new QListWidgetItem(introline);
      it4->setText(tr("4.ȡ�����ᣬ���棬ˢ�ϵ��ϣ��ٷ��뿾�俾10���ӣ��������ʽ��ɫ���ɡ�"));
      QListWidgetItem *it5=new QListWidgetItem(introline);
      it5->setText(tr("5��ʳ��ʱ���������������ۡ�"));

      QListWidget *pic=new QListWidget;
      QListWidgetItem *picitem=new QListWidgetItem(pic);
      picitem->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/lkjc.PNG"));
      pic->setIconSize(QSize(470,370));

      QPushButton *ok=new QPushButton;
      ok->setText(tr("���"));
      connect(ok,SIGNAL(clicked()),this,SLOT(ok_clicked()));

      ordered=new QListWidget;//����������ʾ�Ѿ���õĲ˵�Ŀ¼


    QGridLayout *glayout=new QGridLayout(this);//����һ������Ĳ��ֹ�����
    //glayout->setSpacing(12);

    glayout->addWidget(namelabel,0,0);//����Ŀnamelabel��ӽ����ֹ�����
    glayout->addWidget(nameline,0,1);     //���ֲ��������꣬�����꣬ռ���и�����ռ���и���
    glayout->addWidget(stylelabel,1,0);
    glayout->addWidget(styleline,1,1);
    glayout->addWidget(speclabel,2,0);
    glayout->addWidget(specline,2,1);
    //glayout->addWidget(packagegroup,2,0,2,2);
    glayout->addWidget(conslabel,3,0);
    glayout->addWidget(consline,3,1);

    glayout->addWidget(pic,0,3,4,4);

    glayout->addWidget(introlabel,4,0);
    glayout->addWidget(introline,4,1,4,4);
    glayout->addWidget(ok,8,5,1,1);
    glayout->addWidget(ordered,9,1,1,5);



    this->setLayout(glayout);//�����ֹ�������ӽ�����
    reflash();
}

void plkjc::ok_clicked()
{
    ordered->clear();

    ofstream ofile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::out|ios::app);
    ofile<<7<<endl;
    ofile.close();

    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();
}
//--------------------------
void plkjc::reflash()
{
    ordered->clear();


    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();

    /*
    djly
    sbj
    xglc
    srfssb
    zgdxj
    zlhgr
    lkjc
    dazj
    */
}

//-----------------------------





pdazj::pdazj(QWidget *parent)
    : QWidget(parent)
{
    namelabel=new QLabel(tr("������"));
    stylelabel=new QLabel(tr("��ϵ��"));
    speclabel=new QLabel(tr("�ص�"));
    conslabel=new QLabel(tr("���ϣ�"));
    introlabel=new QLabel(tr("������飺"));

    nameline=new QLineEdit(tr("����  �Ӽ�"));
    styleline=new QLineEdit(tr("����"));
     specline=new QLineEdit(tr("������ۣ�ζ����������"));

    consline=new QListWidget;
    consline->setSpacing(3);
    QListWidgetItem *consitem=new QListWidgetItem(consline);
    consitem->setText(tr("������ĸ��"));
    QListWidgetItem *consitem3=new QListWidgetItem(consline);
    consitem3->setText(tr("С�ʺ콷�����͡��Ͼ�"));
    QListWidgetItem *consitem4=new QListWidgetItem(consline);
    consitem4->setText(tr("�Ρ��״ס�ζ����������"));
    QListWidgetItem *consitem2=new QListWidgetItem(consline);
    consitem2->setText(tr("�С�����ʪ��ۡ����͡�����"));




      introline=new QListWidget;
      introline->setSpacing(3);
      QListWidgetItem *it1=new QListWidgetItem(introline);
      it1->setText(tr("1���׼�ȥë������ȥ����ϴ�����������������߳��죬�����ڲ�����Ѫʱ�̳�������ȥ����"));
      QListWidgetItem *it2=new QListWidgetItem(introline);
      it2->setText(tr("2�����5���׳�2���׿����"));
      QListWidgetItem *it3=new QListWidgetItem(introline);
      it3->setText(tr("3��С�콷ȥ��ȥ��ϴ�����뽪�г�ϸ˿�����г�3���׳��ĶΡ� "));
      QListWidgetItem *it4=new QListWidgetItem(introline);
      it4->setText(tr("4.�������յ������ȣ����뽪˿���콷˿�Գ�������ζ"));
      QListWidgetItem *it5=new QListWidgetItem(introline);
      it5->setText(tr("5���¼��鳴һ�£����Ͼƣ������Ρ��׺�����ʹ����ζ���δ�ζ��͸�뼦���ڡ�"));
      QListWidgetItem *it6=new QListWidgetItem(introline);
      it6->setText(tr("6������жΣ���֭����ʪ��۹��ͣ������ͣ�װ�̼��ɡ�"));

      QListWidget *pic=new QListWidget;
      QListWidgetItem *picitem=new QListWidgetItem(pic);
      picitem->setIcon(QIcon("C:/Qt/2010.04/qt/mymenu/dazj.PNG"));
      pic->setIconSize(QSize(470,370));

      QPushButton *ok=new QPushButton;
      ok->setText(tr("���"));
      connect(ok,SIGNAL(clicked()),this,SLOT(ok_clicked()));
      ordered=new QListWidget;//����������ʾ�Ѿ���õĲ˵�Ŀ¼


    QGridLayout *glayout=new QGridLayout(this);//����һ������Ĳ��ֹ�����
    //glayout->setSpacing(12);

    glayout->addWidget(namelabel,0,0);//����Ŀnamelabel��ӽ����ֹ�����
    glayout->addWidget(nameline,0,1);     //���ֲ��������꣬�����꣬ռ���и�����ռ���и���
    glayout->addWidget(stylelabel,1,0);
    glayout->addWidget(styleline,1,1);
    glayout->addWidget(speclabel,2,0);
    glayout->addWidget(specline,2,1);
    //glayout->addWidget(packagegroup,2,0,2,2);
    glayout->addWidget(conslabel,3,0);
    glayout->addWidget(consline,3,1);

    glayout->addWidget(pic,0,3,4,4);

    glayout->addWidget(introlabel,4,0);
    glayout->addWidget(introline,4,1,4,4);
    glayout->addWidget(ok,8,5,1,1);
    glayout->addWidget(ordered,9,1,1,5);



    this->setLayout(glayout);//�����ֹ�������ӽ�����
    reflash();
}

void pdazj::ok_clicked()
{
    ordered->clear();

    ofstream ofile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::out|ios::app);
    ofile<<8<<endl;
    ofile.close();

    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();
}
//--------------------------
void pdazj::reflash()
{
    ordered->clear();


    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("5.黹���С��"));
        }

        else if (temp==6)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("6.�����ع���"));
        }

        else if(temp==7)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("7.��������"));
        }

        else if(temp==8)
        {
            QListWidgetItem *item=new QListWidgetItem(ordered);
            item->setText(tr("8.�����Ӽ�"));
        }
    }
    ifile.close();

    /*
    djly
    sbj
    xglc
    srfssb
    zgdxj
    zlhgr
    lkjc
    dazj
    */
}

//-----------------------------
