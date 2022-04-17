#include <QApplication>
#include <iostream>

#include "view.h"
#include "controller.h"
#include "model.h"


int main(int argc, char *argv[])
{

    Model model;

    QApplication a(argc, argv);
    Controller controller(&model);
    View view(&controller);
    controller.setView(&view);
    view.show();

    return a.exec();

    return 0;
}

