#include "mainwindow.h"

#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QDomDocument doc;
    QString configPath = "/home/user/projects/XmlProbinc/text.xml";
    QFile file(configPath);


    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << file.errorString();
        return;
    }

    if(!doc.setContent(&file,&errorMsg,&errorRow,&errorColumn)) {
        qDebug() << "error msg: " << errorMsg;
        qDebug() << "error row: " << errorRow;
        qDebug() << "error column: " << errorColumn;
        qDebug() << "Failed to parse XML";
        file.close();
        return;
    }

    QDomElement docElem = doc.documentElement();

    QDomNode node = docElem.firstChild();
    while(!node.isNull()) {
        QDomElement elem = node.toElement();
        if(!elem.isNull()) {

            if(elem.tagName() == "value") {
                QDomNode value = elem.firstChild();
                if(!value.isNull()) {
                    value.setNodeValue("12345");
                }
            }

            if(elem.tagName() == "allo") {
                QDomNode value = elem.firstChild();
                if(!value.isNull()) {
                    value.setNodeValue("222");
                }
            }
        }
        node = node.nextSibling();
    }
    file.close();

    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << file.errorString();
        file.close();
        return;
    }

    QTextStream outStream(&file);
    doc.save(outStream, 4);
    file.close();
}

MainWindow::~MainWindow()
{

}
