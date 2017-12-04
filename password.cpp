#include "password.h"
extern bool flypage;
password::password()
{

    setWindowFlags(Qt::CustomizeWindowHint
                    | Qt::WindowCloseButtonHint
                    | Qt::WindowStaysOnTopHint//总在最上面的窗口
                    );


    popupButton=new QPushButton(this);
    lineEdit = new QLineEdit(this);
    popupButton->setText("密码验证");
    lineEdit->setEchoMode(QLineEdit::Password);//在lifei.cpp的lifei类构造函数里，添上初始化语句，使密码显示为小黑点。
    lineEdit->setFocus();//将光标转到用户名输入框
    connect(popupButton, SIGNAL(clicked()),this, SLOT(isCheckedButton()  ) );
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(lineEdit);
    vbox->addWidget(popupButton);
    vbox->addStretch(1);
    vbox->setSpacing(20);//设定各个控件之间的间距为20
    setLayout(vbox);
}


void password::isCheckedButton()
{

    if(memcmp("chargedot",lineEdit->text().toLatin1(),9)==0||memcmp("CHARGEDOT",lineEdit->text().toLatin1(),9)==0)
        /*.toLatin1()一句话QStr转char**/
       {
        QMessageBox::information(this, "提示消息", tr("授权成功"), QMessageBox::Ok);
        this->close();
        flypage=true;
       }
    else
       {
        QMessageBox::information(this, "提示消息", tr("貌似没有输入正确的密码呀"), QMessageBox::Ok);
        lineEdit->clear();
         lineEdit->setFocus();//将光标转到用户名输入框
       }
}



/*重写键盘事件*/
void password::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Enter)
    {
    }
    else
    {
        isCheckedButton();
    }


}

