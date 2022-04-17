#ifndef SERVIZI_H
#define SERVIZI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QStackedLayout>
#include "home.h"

class Servizi: public QWidget{
    Q_OBJECT
private:
    QVBoxLayout* mainLayout;

    QHBoxLayout* serviziLayout;
    QLabel* servizi_;
    QCheckBox* spiaggia;
    QCheckBox* piscina;

    QAbstractButton* struttura_selezionata;

    QButtonGroup* ristoranteGroup;
    QHBoxLayout* ristoranteLayout;
    QLabel* ristorante;
    QRadioButton* colazione;
    QRadioButton* mezza;
    QRadioButton* completa;

    QButtonGroup* appartamentoGroup;
    QHBoxLayout* appartamentoLayout;
    QLabel* pulizia;
    QRadioButton* si;
    QRadioButton* no;

    QHBoxLayout* camperLayout;
    QLabel* camperText;
    QCheckBox* acqua;
    QCheckBox* corrente;

    QHBoxLayout* suiteLayout;
    QLabel* suiteText;
    QCheckBox* relax;
    QCheckBox* ufficio;
    QCheckBox* servizioristorante;

    QHBoxLayout* servizi_pulsantiLayout;
    QPushButton* servizi_home;
    QPushButton* servizi_prosegui;

    int tipoStruttura;

public:
    Servizi(QWidget* parent=nullptr);
    virtual ~Servizi();
    void serviziFunct(QWidget* parent);
    void ristoranteFunct(QWidget* parent);
    void appartamentoFunct(QWidget* parent);
    void camperFunct(QWidget* parent);
    void suiteFunct(QWidget* parent);
    void servizi_pulsantiFunct(QWidget* parent);

signals:
    void goBackToHomeView();
    void goToStructureView();

    //filtri
    void addSpiaggia(bool);
    void addPiscina(bool);
    void addPensione(int);
    void addPuliziaCucina(bool);
    void addAcquaCamper(bool);
    void addCorrenteCamper(bool);
    void addSuiteCentroBenessere(bool);
    void addSuiteSalaRiunioni(bool);
    void addSuiteServizioCamera(bool);

public slots:
    void uncheckButtons(int);
    void backToHomeView();
    void toStructureView();



};

#endif // SERVIZI_H
