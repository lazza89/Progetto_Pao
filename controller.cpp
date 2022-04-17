#include "controller.h"
#include "database.cpp"

Controller::Controller(Model* model):
    _model(model),
    _view(nullptr)
{

}

void Controller::setView(View *view){
    _view = view;    

    connect(_view->getHomeView(), &Home::goToServiziView, this, &Controller::goToServiziPage); //quando premi il pulsante prosegui sulla schermata home fa lo swap fra home e servizi
    connect(_view->getServiziView(), &Servizi::goBackToHomeView, this, &Controller::goBackToHomePage);
    connect(_view->getServiziView(), &Servizi::goToStructureView, this, &Controller::goToStructurePage);
    connect(_view->getStructureView(), &StructureView::goBackToServiziView, this, &Controller::goBackToServiziPage);
    connect(_view->getStructureView(), &StructureView::goToStructureDetailsView, this, &Controller::goToStructureDetailsPage);
    connect(_view->getStructureDetailsView(), &StructureDetailsView::goBackToStructureView, this, &Controller::goBackToStructurePage);
    connect(_view->getStructureView(), &StructureView::goBackToHomeViewFromStructureView, _view->getServiziView(), &Servizi::backToHomeView);

    //updater ospiti
    connect(_view->getHomeView(), SIGNAL(sendUpdateOspiti(int)), this, SLOT(updateOspiti(int)));

    //connessione filtri
    connect(_view->getHomeView(), SIGNAL(stagioneSelected(int)), this, SLOT(stagioneFilter(int)));
    connect(_view->getHomeView(), SIGNAL(structureSelected(int)), this, SLOT(structureFilter(int)));

    //uncheck button
    connect(this, SIGNAL(uncheckButton(int)), _view->getServiziView(), SLOT(uncheckButtons(int)));

    //servizi handler
    connect(_view->getServiziView(), SIGNAL(addSpiaggia(bool)), this, SLOT(spiaggiaAdder(bool)));
    connect(_view->getServiziView(), SIGNAL(addPiscina(bool)), this, SLOT(piscinaAdder(bool)));
    connect(_view->getServiziView(), SIGNAL(addPensione(int)), this, SLOT(pensioneAdder(int)));
    connect(_view->getServiziView(), SIGNAL(addPuliziaCucina(bool)), this, SLOT(puliziaCucinaAdder(bool)));
    connect(_view->getServiziView(), SIGNAL(addAcquaCamper(bool)), this, SLOT(camperAcquaAdder(bool)));
    connect(_view->getServiziView(), SIGNAL(addCorrenteCamper(bool)), this, SLOT(camperCorrenteAdder(bool)));
    connect(_view->getServiziView(), SIGNAL(addSuiteCentroBenessere(bool)), this, SLOT(suiteBenessereAdder(bool)));
    connect(_view->getServiziView(), SIGNAL(addSuiteSalaRiunioni(bool)), this, SLOT(suiteRiunioniAdder(bool)));
    connect(_view->getServiziView(), SIGNAL(addSuiteServizioCamera(bool)), this, SLOT(suiteServizioCameraAdder(bool)));

    //structure view
    connect(_view->getServiziView(), &Servizi::goToStructureView, _view->getStructureView(), &StructureView::loadListHeaderItem);

    //go to structure details view
    connect(this, &Controller::loadStructureInfoPage, _view->getStructureDetailsView(), &StructureDetailsView::loadStructureInformation);
}

const vettore<uniqueP<Residence>>& Controller::getVettore() const
{
    return _model->getVettoreStrutture();
}

//slots per scambiare le varie interfaccie
void Controller::goToServiziPage(){
    _view->setCurrentWidget(_view->getServiziView());
}

void Controller::goBackToHomePage(){
    _model->getVettoreStrutture().clear();
    _view->setCurrentWidget(_view->getHomeView());
}

void Controller::goToStructurePage(){
    _view->setCurrentWidget(_view->getStructureView());
}

void Controller::goBackToServiziPage(){
    _view->setCurrentWidget(_view->getServiziView());
}

void Controller::goToStructureDetailsPage(int n)
{
    emit loadStructureInfoPage(n);
    _view->setCurrentWidget(_view->getStructureDetailsView());
}

void Controller::goBackToStructurePage()
{
    _view->setCurrentWidget(_view->getStructureView());
}

void Controller::updateOspiti(int n)
{
    for(auto i = _model->getVettoreStrutture().begin(); i != _model->getVettoreStrutture().end(); i++){
        _model->ospiti(i, n);
    }
}

//filtri stagione e struttura
void Controller::stagioneFilter(int n)
{
    periodo p = periodo::bassa;
    switch (n) {
     case 1:
        p = periodo::bassa;
        break;
    case 2:
        p = periodo::media;
        break;
    case 3:
        p = periodo::alta;
        break;

    }
    for(auto i = _model->getVettoreStrutture().begin(); i != _model->getVettoreStrutture().end(); i++){
        _model->stagione(i, p);
    }
}

void Controller::structureFilter(int n)
{
    _model->getVettoreStrutture().clear();
    emit uncheckButton(n);
    checkFile();
    loadResidence(*_model, n);
}

void Controller::spiaggiaAdder(bool b)
{
    for(auto i = _model->getVettoreStrutture().begin(); i != _model->getVettoreStrutture().end(); i++){
        _model->spiaggia(i, b);
    }
}

void Controller::piscinaAdder(bool b)
{
    for(auto i = _model->getVettoreStrutture().begin(); i != _model->getVettoreStrutture().end(); i++){
        _model->piscina(i, b);
    }
}

void Controller::pensioneAdder(int n)
{
    pensione p = pensione::colazione;
    switch (n) {
    case 1:
        p = pensione::colazione;
        break;
    case 2:
        p = pensione::mezza;
        break;
    case 3:
        p = pensione::completa;
        break;
    }

    for(auto i = _model->getVettoreStrutture().begin(); i != _model->getVettoreStrutture().end(); i++){
        _model->ristorante(i, p);
    }
}

void Controller::puliziaCucinaAdder(bool b)
{
    for(auto i = _model->getVettoreStrutture().begin(); i != _model->getVettoreStrutture().end(); i++){
        _model->puliziaCucina(i, b);
    }
}

void Controller::camperAcquaAdder(bool b)
{
    for(auto i = _model->getVettoreStrutture().begin(); i != _model->getVettoreStrutture().end(); i++){
        _model->acquaCamper(i, b);
    }
}

void Controller::camperCorrenteAdder(bool b)
{
    for(auto i = _model->getVettoreStrutture().begin(); i != _model->getVettoreStrutture().end(); i++){
        _model->correnteCamper(i, b);
    }
}

void Controller::suiteRiunioniAdder(bool b)
{
    for(auto i = _model->getVettoreStrutture().begin(); i != _model->getVettoreStrutture().end(); i++){
        _model->ufficioSuite(i, b);
    }
}

void Controller::suiteBenessereAdder(bool b)
{
    for(auto i = _model->getVettoreStrutture().begin(); i != _model->getVettoreStrutture().end(); i++){
        _model->relaxSuite(i, b);
    }
}

void Controller::suiteServizioCameraAdder(bool b)
{
    for(auto i = _model->getVettoreStrutture().begin(); i != _model->getVettoreStrutture().end(); i++){
        _model->servizioinCamera(i, b);
    }
}


