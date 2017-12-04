#include "window.h"
#include <QApplication>
#include<QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    Window window;
    window.show();

    return a.exec();
}

