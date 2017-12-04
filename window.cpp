#include "window.h"
#define GOD  0
extern char Is_AYmark;
Window::Window(QWidget *parent): QWidget(parent)
{
    RFIDReader = new Reader;
    memset(RFIDReader->PileNumber, 0, 13);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget((QWidget*)createInputPileGroup(),       0, 0);
    grid->addWidget((QWidget*)createChargingModeGroup(),    0, 1);
    grid->addWidget((QWidget*)createWriteButtonGroup(),     1, 0);
    grid->addWidget((QWidget*)createReadButtonGroup(),      1, 1);
    grid->addWidget((QWidget*)createsavetextGroup(),        2, 0,1,0);
    grid->addWidget((QWidget*)createcleanButtonGroup(),     3, 0,Qt::AlignLeft);
    grid->addWidget((QWidget*)createsavebutGroup(),3,1,Qt::AlignRight);
    grid->addWidget((QWidget*)createhelpbutGroup(),3,0,1,0,Qt::AlignHCenter);
   //http://bbs.csdn.net/topics/360067516
    setLayout(grid);
    QIcon tem(":/new/prefix/1");
    setWindowIcon(tem);
    setWindowTitle(tr("埃士读写卡助手 V5.0 "));
    resize(700,500);
    if (!RFIDReader->LoadDll())
    {
        QMessageBox msgBox;
        msgBox.setText("库文件装载失败！");
        msgBox.exec();
        parent->close();
    }
}

QGroupBox *Window::createInputPileGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("桩号[13] 写卡模式选择"));
    checkbox01 = new  QRadioButton (tr("写卡后桩号自动+1 卡号不变"));
    checkbox02 = new  QRadioButton (tr("写卡后卡号自动+1 桩号不变"));
    checkbox03 = new  QRadioButton (tr("写卡后卡号不变   桩号不变"));
    checkbox01->setChecked(true);
    lineEdit5 = new QLineEdit();
    lineEdit5->setMaxLength(13);
    lineEdit5->setText("E0043B7071000");
    connect(lineEdit5,SIGNAL(returnPressed()),this,SLOT(on_lineEdit_returnPressed()));
    connect(   checkbox02,SIGNAL(toggled(bool)),this,SLOT(on_checkbox_Pressed(bool) ));
                            // clicked(bool)不好 上面的好！
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(lineEdit5);
    vbox->addWidget(checkbox01);
    vbox->addWidget(checkbox02);
    vbox->addWidget(checkbox03);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    return groupBox;
}


void Window::on_checkbox_Pressed(bool a)
{
    if( a )
    {
    popupButton3->show();
    lineEdit8->show();
    }
    else
    {
        popupButton3->hide();
        lineEdit8->hide();
    }
}

QGroupBox *Window::createChargingModeGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("卡号[15] 对应桩号显示 "));

    lb1 = new QLabel(QWidget::tr(" 对应桩号"));
    lineEdit6 = new QLineEdit();
    lineEdit6->setMaxLength(13);
    lineEdit6->setText("");


    lb2 = new QLabel(QWidget::tr(" 卡片卡号"));
    lineEdit7 = new QLineEdit();
    lineEdit7->setMaxLength(15);
    lineEdit7->setText("");

    popupButton3 = new QPushButton(tr("设置卡号起点"));
    lineEdit8 = new QLineEdit();
    lineEdit8->setMaxLength(2);
    lineEdit8->setText("");

    popupButton3->hide();
    lineEdit8->hide();

    connect(popupButton3, SIGNAL(clicked()),this, SLOT(isCheckedButton3()));


    QGridLayout *grid = new QGridLayout;
    grid->addWidget(lb1,             0, 0);
    grid->addWidget(lineEdit6,       0, 1);
    grid->addWidget(lb2,             1, 0);
    grid->addWidget(lineEdit7,       1, 1);
    grid->addWidget(popupButton3,    2, 0);
    grid->addWidget(lineEdit8,       2, 1);
    grid -> setColumnStretch(0, 1);
    grid -> setColumnStretch(1, 3);
    groupBox->setLayout(grid);
    return groupBox;
}


QGroupBox *Window::createcleanButtonGroup()
{
    QGroupBox *groupBox = new QGroupBox();
    popupButton6= new QPushButton(tr("写管理员卡"));
    QIcon tem(":/new/prefix/2");
    popupButton6->setIcon(tem);
    popupButton6->setIconSize(QSize(180,30));
    connect(popupButton6, SIGNAL(clicked()),this, SLOT(isCheckedButton6()));
  //  popupButton6->setEnabled(false);//   ->setCheckable(false);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(popupButton6);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

QGroupBox *Window::createsavetextGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr(""));
    textBrowser = new QTextBrowser;
    textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textBrowser->setTextColor(Qt::blue);//Qt::lightGray
    connect(textBrowser, SIGNAL(textChanged()),this, SLOT(on_textBrowser_textChanged()));
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(textBrowser);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    return groupBox;
}
QGroupBox *Window::createsavebutGroup()
{
    QGroupBox *groupBox = new QGroupBox();
    popupButton7 = new QPushButton(tr("保存写卡记录"));
    QIcon tem(":/new/prefix/2");
    popupButton7->setIcon(tem);
    popupButton7->setIconSize(QSize(180,30));
    connect(popupButton7, SIGNAL(clicked()),this, SLOT(isCheckedButton7()));
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(popupButton7);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    return groupBox;
}




QGroupBox *Window::createhelpbutGroup()
{
    QGroupBox *groupBox = new QGroupBox();
    popupButton7 = new QPushButton(tr("帮助"));
    QIcon tem(":/new/prefix/2");
    popupButton7->setIcon(tem);
    popupButton7->setIconSize(QSize(30,30));
    connect(popupButton7, SIGNAL(clicked()),this, SLOT(isCheckedButtonhelp()));
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(popupButton7);
    vbox->addStretch(0);
    groupBox->setLayout(vbox);
    return groupBox;
}


void Window::on_lineEdit_returnPressed()
{

}





void Window:: isCheckedButtonhelp()
{
       QMessageBox msgBox;
       msgBox.setText("                                             软件说明\n\n\
1电脑连接读卡器，左上角输入框键入桩号，点击写卡。\n\n\
2严格执行桩号13位，卡号15位的规则，故桩号苛求13位。\n\n\
3写卡后桩号+1卡号不变，例如本次键入桩号ASP2017110217,\n\点击写卡，写出卡号ASP201711021700。随后桩号自动变成ASP2017110218，\n\换一张卡再次点击写卡，写出卡号成ASP201711021800\n\n\
4写卡后卡号+1桩号不变，例如本次键入桩号ASP2017110217,\n\点击写卡，写出卡号ASP201711021700。随后桩号依旧保持ASP2017110217，\n\换一张卡再次点击写卡，写出卡号成ASP201711021801\n\n\
5写卡后卡号桩号都不变，例如本次键入桩号ASP2017110217,\n\点击写卡，写出卡号ASP201711021700。随后每次写卡都如初\n\n\
6写卡以后可以点击读卡，确认写卡如你所愿。\n\n\
7软件下方显示桩号和卡号的对应关系，保存按键，方便工作存档。\n\n\
8左下角添加管理员卡，与输入桩号无关，软件强行写入管理员卡号。\n\n\
9新增：写卡后卡号+1桩号不变模式时可以手动设置卡号起点。\n\n"                    );
       msgBox.exec();


}
void Window::isCheckedButton3()
{
#if 0
    if(memcmp("A1SM1P",lineEdit8->text().toLatin1(),6)==0||memcmp("a1sm1p",lineEdit8->text().toLatin1(),6)==0)
        /*.toLatin1()一句话QStr转char**/
       {
        popupButton6->setEnabled(true);
        QMessageBox::information(this, "提示消息", tr("授权成功"), QMessageBox::Ok);
       }
    else
    {
        popupButton6->setEnabled(false);
        QMessageBox::information(this, "提示消息", tr("貌似没有输入正确的密码呀"), QMessageBox::Ok);
    }
# endif


    QString str=lineEdit8->text();/*拿到QSTR*/
    bool ok;
    int dec=str.toInt(&ok,10); //dec=255 ; ok=rue
    if(ok)
    {
        if(dec<10&&dec>=0)
        {
            RFIDReader->ADDA=0;
            RFIDReader->ADDB=dec-1;
        }
        else if(dec<153)//0x99
        {
            RFIDReader->ADDA=str.mid(0,1).toInt(&ok,10);
            RFIDReader->ADDB=str.mid(1,1).toInt(&ok,10)-1;
        }
       QMessageBox::information(this, "提示消息", tr("卡号结尾已经设置好"), QMessageBox::Ok);
    }
    else
       QMessageBox::information(this, "提示消息", tr("貌似并不是0-99的数据哦"), QMessageBox::Ok);


}

/*龚金华版本*/
bool flypage=false;
void Window::isCheckedButton6()
{
    const unsigned char admin[16]={0x12,0x34,0x56,0x78,0xED,0xCB,0xFF,0x07,0x80,0x69,0x56,0x78,0x01,0xFE,0x01,0xFE};
#if GOD
    if(1)
#else
    if(flypage)
#endif
    {
        memcpy(RFIDReader->CardNumber, admin, 16);
        if(RFIDReader->writeAllBlk())
        QMessageBox::information(this, "提示消息", tr("写管理员成功"), QMessageBox::Ok);
        else
        QMessageBox::information(this, "提示消息", tr("写管理员失败！！"), QMessageBox::Ok);
        memset(RFIDReader->CardNumber, 0, 16);
        flypage=false;
    }
    else
    {
        Password = new password();
        Password->resize(180,80);
        Password->show();
    }
}



void Window::isCheckedButton7()
{
    if(textBrowser->toPlainText().isEmpty())
       {
           QMessageBox::information(this, "提示消息", tr("貌似还没有数据记录哦!"), QMessageBox::Ok);
           return;
       }

       QString filename = QFileDialog::getSaveFileName(this, tr("另存为"), tr("未命名.txt"));
       QFile file(filename);
       //如果用户取消了保存则直接退出函数
       if(file.fileName().isEmpty())
       {
           return;
       }
       //如果打开失败则给出提示并退出函数
       if(!file.open(QFile::WriteOnly | QIODevice::Text))
       {
           QMessageBox::warning(this, tr("保存文件"), tr("打开文件 %1 失败, 无法保存\n%2").arg(filename).arg(file.errorString()), QMessageBox::Ok);
           return;
       }
       //写数据到文件
       QTextStream out(&file);
       out<<textBrowser->toPlainText();
       file.close();
       //修改窗口标题为保存文件路径
       setWindowTitle("saved: " + QFileInfo(filename).canonicalFilePath());

}

QGroupBox *Window::createWriteButtonGroup()
{
    QGroupBox *groupBox = new QGroupBox();
    QPushButton *pushButton = new QPushButton(tr("写卡"));
    QIcon tem(":/new/prefix/2");
    pushButton->setIcon(tem);
    pushButton->setFont(QFont( "Times", 25, QFont::Bold ) );/*字体*/

    pushButton->setIconSize(QSize(80,110));
    pushButton->setFlat(false);

    connect(pushButton, SIGNAL(clicked()),this, SLOT(writeButtonClicked()));
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(pushButton);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

QGroupBox *Window::createReadButtonGroup()
{
    QGroupBox *groupBox = new QGroupBox();

    QPushButton *pushButton = new QPushButton(tr("读卡"));
    QIcon tem(":/new/prefix/2");
    pushButton->setIcon(tem);
    pushButton->setIconSize(QSize(80,110));
    pushButton->setFlat(false);

    pushButton->setFont(QFont( "Times", 25, QFont::Bold ) );/*字体*/
    connect(pushButton, SIGNAL(clicked()),this, SLOT(readButtonClicked()));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(pushButton);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}





void Window::writeButtonClicked()
{
    memset(RFIDReader->PileNumber, 0, 13);
#if GOD
    if(!QString(lineEdit5->text()).isEmpty())
#else
    if(QString(lineEdit5->text()).length()==13)//龚金华修改
#endif

        {
          QByteArray ByteArray = lineEdit5->text().toLatin1();
          memcpy(RFIDReader->PileNumber, ByteArray.data(), lineEdit5->text().size());
        }
    else
       {
         QMessageBox msgBox;
         msgBox.setText("桩号貌似并不是13位呀");
         msgBox.exec();
        }


/*处理桩号++*/
       if(checkbox01->isChecked())
       {

           ForPlusPlusLog1();
           QString str = lineEdit5->text();/*拿到QSTR*/
           QString last3old = str.mid(10,3);/*拿到QSTR结尾3个*/
           int last3plus = last3old.toInt()+1;/*转化QSTR结尾3个为int*/


           if(last3plus<=999)
           {
               QString last3new=QString::number(last3plus, 10);/*int转QSTR*/
               QString tem1="0",tem2="00";
               if(last3new.length()==1)
               {
                   tem2+=last3new;
                   str.replace(10,3,tem2);
               }
               else if(last3new.length()==2)
               {
                   tem1+=last3new;
                   str.replace(10,3,tem1);
               }
               else
                   str.replace(10,3,last3new);

               lineEdit5->setText( str );
           }
           else
           {
               QMessageBox msgBox;
               msgBox.setText("桩号流水已经0--999不能再写了！");
               msgBox.exec();
           }
       }

/*处理卡号++*/
           if(checkbox02->isChecked())
           {
               QString str = lineEdit5->text();
               lineEdit5->setText( str );
               ForPlusPlusLog2();
           }
/*不变*/
           if(checkbox03->isChecked())
           {
               RFIDReader->ADDA=0;
               RFIDReader->ADDB=0;
           }



           if(RFIDReader->writeAllBlk())

           {
               RFIDReader->PtoC_Conversion();
               static QString filestr = 0;
               filestr += "桩号";
               filestr+=lineEdit5->displayText();
               filestr+="------>卡号";
               QString strtem = QString( (char*)RFIDReader->CardNumber );/*char*转QSTR*/
               strtem=strtem.mid(0,15);/*遗留问题后面有乱码所以我就拿前面15个*/
               filestr += strtem;
               filestr += "\n";
               textBrowser->setText(filestr);

           }
           else
           {
             if(Is_AYmark==0)
             {
             QMessageBox msgBox;
             msgBox.setText("写卡失败");
             msgBox.exec();
             }
             else
             {
                 Is_AYmark=0;
                 QMessageBox msgBox;
                 msgBox.setText("该卡为安悦卡，请勿写卡");
                 msgBox.exec();

             }
           }
}


void Window::ForPlusPlusLog1(void)
{
     RFIDReader->ADDA=0;
     RFIDReader->ADDB=0;
}



void Window::ForPlusPlusLog3(void)
{

}

void Window::ForPlusPlusLog2(void)
{
  if(RFIDReader->ADDA<=9)
  {
      if(RFIDReader->ADDB==9)
      {
        RFIDReader->ADDA+=1;
        RFIDReader->ADDB = 0;
       }
      else
      {
          RFIDReader->ADDB++;
      }
  }
  else
  {
    QMessageBox msgBox;
    msgBox.setText("write over 100！");
    msgBox.exec();
   }
}



void Window::readButtonClicked()
{
    QMessageBox msgBox;
    if(!RFIDReader->readAllBlk())
    {
      msgBox.setText("读卡失败！");
      msgBox.exec();
      return;
    }
    else
    {
        if(RFIDReader->CardNumber[0]==0x12&&
           RFIDReader->CardNumber[1]==0x34&&
           RFIDReader->CardNumber[2]==0x56&&
           RFIDReader->CardNumber[3]==0x78&&
           RFIDReader->CardNumber[4]==0xED&&
           RFIDReader->CardNumber[5]==0xCB&&
           RFIDReader->CardNumber[12]==0x01)
        {
            lineEdit6->setText("管理员");
            lineEdit7->setText("管理员");
            msgBox.setText("管理员卡");
            msgBox.exec();
            memset(RFIDReader->CardNumber, 0, 15);
        }
        else
        {
            RFIDReader->CtoP_Conversion();
            lineEdit6->setText(QString(((char *)RFIDReader->PileNumber)));
            lineEdit7->setText(QString(QLatin1String((char *)RFIDReader->CardNumber)));
        //    msgBox.setText("读卡成功");
        //    msgBox.exec();
            memset(RFIDReader->CardNumber, 0, 15);
        }
    }
}





//https://wenku.baidu.com/view/5d4c8b3a804d2b160b4ec0cc.html  移动
void Window::on_textBrowser_textChanged()
{
    textBrowser->moveCursor(QTextCursor::End);
}




void Window::mouseDoubleClickEvent(QMouseEvent *event)
{
     QMessageBox msgBox;
    // 如果是鼠标左键按下
    if(event->button() == Qt::LeftButton)
    {
        msgBox.setText("                                             软件说明\n\n\
1电脑连接读卡器，左上角输入框键入桩号，点击写卡。\n\n\
2严格执行桩号13位，卡号15位的规则，故桩号苛求13位。\n\n\
3写卡后桩号+1卡号不变，例如本次键入桩号ASP2017110217,\n\点击写卡，写出卡号ASP201711021700。随后桩号自动变成ASP2017110218，\n\换一张卡再次点击写卡，写出卡号成ASP201711021800\n\n\
4写卡后卡号+1桩号不变，例如本次键入桩号ASP2017110217,\n\点击写卡，写出卡号ASP201711021700。随后桩号依旧保持ASP2017110217，\n\换一张卡再次点击写卡，写出卡号成ASP201711021801\n\n\
5写卡后卡号桩号都不变，例如本次键入桩号ASP2017110217,\n\点击写卡，写出卡号ASP201711021700。随后每次写卡都如初\n\n\
6写卡以后可以点击读卡，确认写卡如你所愿。\n\n\
7软件下方显示桩号和卡号的对应关系，保存按键，方便工作存档。\n\n\
8左下角添加管理员卡，与输入桩号无关，软件强行写入管理员卡号。\n\n\
9新增：写卡后卡号+1桩号不变模式时可以手动设置卡号起点。\n\n"                    );

        msgBox.exec();
    }
}


void Window::mousePressEvent(QMouseEvent *event)
{
#if 0
     QMessageBox msgBox;
    // 如果是鼠标左键按下
    if(event->button() == Qt::LeftButton)
    {
          msgBox.setText("瞎点什么左键！");
          msgBox.exec();
    }
    // 如果是鼠标右键按下
    else if(event->button() == Qt::RightButton)
    {
        msgBox.setText("瞎点什么右键！");
        msgBox.exec();
    }
#endif
}


