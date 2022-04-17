#ifndef STRUCTUREDETAILSVIEW_H
#define STRUCTUREDETAILSVIEW_H
#include <QObject>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include "controller.h"

class Controller;

class StructureDetailsView : public QWidget
{
    Q_OBJECT
public:
    StructureDetailsView(Controller* controller = nullptr, QWidget* parent = nullptr);
    ~StructureDetailsView();

private:
    vettore<QLabel*> infoVector;
    Controller* _controller;

    QVBoxLayout* mainLayout;
    QGridLayout* infoLayout;
    QHBoxLayout* backSpacerLayout;

    QLabel* textInfoStruttura;

    QPushButton* backButton;

    //text
    QString stringDisabile;
    QString stringPuliziaCucina;
    QString stringSpiaggia;
    QString stringPiscina;
    QString stringstatolibero;
    QString stringStatoOccupato;
    QString stringStatoLavori;
    QString stringLettiMinori;

signals:
    void goBackToStructureView();

public slots:
    void loadStructureInformation(int);
    void deleteDetails();


};

#endif // STRUCTUREDETAILSVIEW_H
