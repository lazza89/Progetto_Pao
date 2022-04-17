#include "view.h"


View::View(Controller* controller) :
    _controller(controller),
    homeScreen(new Home()),
    serviziScreen(new Servizi()),
    structureScreen(new StructureView(controller)),
    structureDetailsScreen(new StructureDetailsView(controller))
{
    addWidget(homeScreen);
    addWidget(serviziScreen);
    addWidget(structureScreen);
    addWidget(structureDetailsScreen);
    setWindowIcon(QIcon(":/images/resources/logo.png"));

    setFixedSize(800, 700);
}

Home *View::getHomeView() const
{
    return homeScreen;
}

Servizi *View::getServiziView() const
{
    return serviziScreen;
}

StructureView *View::getStructureView() const
{
    return structureScreen;
}

StructureDetailsView *View::getStructureDetailsView() const
{
    return structureDetailsScreen;
}




