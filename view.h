#ifndef VIEW_H
#define VIEW_H
#include "view/home.h"
#include "view/servizi.h"
#include "view/structuredetailsview.h"
#include "view/structureview.h"
#include "controller.h"

#include <QStackedWidget>

class Controller;
class StructureView;
class StructureDetailsView;

class View : public QStackedWidget
{
    Q_OBJECT

public:
    View(Controller* controller);

    Home* getHomeView() const;
    Servizi* getServiziView() const;
    StructureView* getStructureView() const;
    StructureDetailsView* getStructureDetailsView() const;


private:
    Controller* _controller;

    Home* homeScreen;
    Servizi* serviziScreen;
    StructureView* structureScreen;
    StructureDetailsView * structureDetailsScreen;



};

#endif // VIEW_H
