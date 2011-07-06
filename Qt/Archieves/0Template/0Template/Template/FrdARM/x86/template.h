/**********************************************************
Author		: Lan Xin , xinlan_al@yahoo.com
Date		: 2010.01.12
Version		: V0.1
Discription	: template.h

This program is to demostrate how to -----

***********************************************************/
#ifndef MYHELLOFORM_H
#define MYHELLOFORM_H
#include "template_base.h"


class MyHelloForm : public HelloBaseForm
{ 
    Q_OBJECT
	
    public:		// Constructor and Destructor
    MyHelloForm( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    virtual ~MyHelloForm();
    
    /********************************************************************/   
    public:		// User defined public global variable
        const QPixmap *eddy;
    
    private slots:      // User defined private global variable
        void showMe();
        void sayHello();
};

#endif // MYHELLOFORM_H
