#ifndef PASSWORD_H
#define PASSWORD_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QApplication>
#include <QKeyEvent>
class password :public QWidget

{
   Q_OBJECT    // QT编程No such slot的解决方法
public:
    password();
    void keyPressEvent(QKeyEvent *event);
    //void keyReleaseEvent(QKeyEvent *event);
private :
    QPushButton *popupButton;
    QLineEdit *lineEdit;

private slots:
    void isCheckedButton();

};

#endif // PASSWORD_H
