void show(QWiget *a)
{
    int temp;
    ifstream ifile("C:\\Qt\\2010.04\\qt\\mymenu\\menu.txt",ios::in);

    while(!ifile.eof())
    {
        temp=0;
        ifile>>temp;

        if(temp==1)
        {
            QListWidgetItem *item=new QListWidgetItem(a.ordered);
            item->setText(tr("1.�罷����"));
        }

        else if(temp==2)
        {
            QListWidgetItem *item=new QListWidgetItem(a.ordered);
            item->setText(tr("2.������"));
        }

        else if(temp==3)
        {
            QListWidgetItem *item=new QListWidgetItem(a.ordered);
            item->setText(tr("3.�ʹ�����"));

        }

        else if(temp==4)
        {
            QListWidgetItem *item=new QListWidgetItem(a.ordered);
            item->setText(tr("4.���ط�˿�ȱ�"));
        }

        else if(temp==5)
        {
            QListWidgetItem *item=new QListWidgetItem(a.ordered);
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
