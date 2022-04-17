#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include "model.h"
#include "view.h"

class View;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Model* model = nullptr);
    void setView(View* view);

    const vettore<uniqueP<Residence>>& getVettore() const;

private:
    Model* _model;
    View* _view;

signals:
    void uncheckButton(int);
    void loadStructureInfoPage(int);

public slots:
    void goToServiziPage();
    void goBackToHomePage();
    void goToStructurePage();
    void goBackToServiziPage();
    void goToStructureDetailsPage(int);
    void goBackToStructurePage();

    void stagioneFilter(int);
    void structureFilter(int);
    void updateOspiti(int);

    //servizi handler
    void spiaggiaAdder(bool);
    void piscinaAdder(bool);
    void pensioneAdder(int);
    void puliziaCucinaAdder(bool);
    void camperAcquaAdder(bool);
    void camperCorrenteAdder(bool);
    void suiteBenessereAdder(bool);
    void suiteRiunioniAdder(bool);
    void suiteServizioCameraAdder(bool);

};


#endif // CONTROLLER_H
