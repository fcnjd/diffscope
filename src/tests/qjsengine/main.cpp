#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QJSEngine>
#include <QMainWindow>
#include <QPushButton>

#include "Global/GlobalObject.h"
#include "Global/GlobalRegistryObject.h"
#include "Project/ProjectObject.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    auto win = new QMainWindow;
    win->show();
    GlobalObject global;
    global.engine()->installExtensions(QJSEngine::ConsoleExtension);
    auto ret = global.load(":/scripts/main.js");
    if (ret.isError())
        qDebug() << ret.toString();
    qDebug() << global.registry()->scripts();
    ProjectObject project(win);
    ret = project.invoke("test");
    if (ret.isError())
        qDebug() << ret.toString();
    return a.exec();
}