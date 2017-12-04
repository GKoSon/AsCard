#ifndef WINDOW_H
#define WINDOW_H
#include "reader.h"

#include "password.h"
#include<QString>
#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QLCDNumber>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QMenu>
#include <QLineEdit>
#include <QAction>
#include <QIcon>
#include <QPalette>
#include <QTextBrowser>
#include <QFile>
#include <QInputDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QMouseEvent>
#include <QCheckBox>
#include <QLabel>
QT_BEGIN_NAMESPACE
class QGroupBox;
class QRadioButton;
class QPushButton;
class QLineEdit;
QT_END_NAMESPACE


class Window : public QWidget
{
    Q_OBJECT

public:
    class Reader *RFIDReader;

    Window(QWidget *parent = 0);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    private:
    QLabel *lb1 ;
    QLabel *lb2 ;
    QLabel *lb3 ;
    QPushButton *popupButton3;
    QRadioButton  *checkbox01;
    QRadioButton  *checkbox02;
    QRadioButton  *checkbox03;
    QTextBrowser *textBrowser;

    QPushButton *popupButton6;
    QPushButton *popupButton7;

    QLineEdit *lineEdit5;
    QLineEdit *lineEdit6;
    QLineEdit *lineEdit7;
    QLineEdit *lineEdit8;

    QGroupBox *createInputPileGroup();
    QGroupBox *createChargingModeGroup();
    QGroupBox *createWriteButtonGroup();
    QGroupBox *createReadButtonGroup();
    QGroupBox *createcleanButtonGroup();
    QGroupBox *createsavetextGroup();
    QGroupBox *createsavebutGroup();
     QGroupBox *createhelpbutGroup();
    password *Password;

private slots:
    void on_lineEdit_returnPressed();
    void on_checkbox_Pressed(bool);

    void isCheckedButton6();
    void isCheckedButton7();
    void isCheckedButton3();
       void isCheckedButtonhelp();
    void writeButtonClicked();
    void readButtonClicked();
    void on_textBrowser_textChanged();
        void ForPlusPlusLog1(void);
    void ForPlusPlusLog2(void);
 void ForPlusPlusLog3(void);
};

#endif
