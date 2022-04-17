#ifndef HOME_H
#define HOME_H

#include "view/clickablelabel.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QAbstractButton>
#include <QButtonGroup>
#include <QBoxLayout>
#include <QSizePolicy>
#include <QRadioButton>
#include <QPushButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QDebug>
#include <QGroupBox>

class Home: public QWidget{
    Q_OBJECT
private:    
    QVBoxLayout* mainLayout;
    QLabel* titolo;

    QHBoxLayout* ospitiLayout;
    QLabel* ospiti;
    QSpinBox* numero;

    QButtonGroup* periodoGroup;
    QHBoxLayout* periodoLayout;
    QRadioButton* bassa;
    QRadioButton* media;
    QRadioButton* alta;

    QButtonGroup* strutturaGroup;
    QHBoxLayout* strutturaLayout;
    QRadioButton* camera;
    QRadioButton* suite;
    QRadioButton* appartamento;
    QRadioButton* camper;

    QHBoxLayout* home_pulsantiLayout;
    QPushButton* home_prosegui;

    QGroupBox* addImageButton(QWidget* parent, ClickableLabel* label, QRadioButton* button, QString path, QString nomeStruttura);

public:
    Home(QWidget *parent=nullptr);
    virtual ~Home();
   void titoloFunct(QWidget *parent);
   void ospitiFunct(QWidget *parent);
   void periodoFunct(QWidget *parent);
   void strutturaFunct(QWidget *parent);
   void home_pulsantiFunct(QWidget *parent);

   private:
   int nOspiti;
   ClickableLabel* cameraImg;
   ClickableLabel* suiteImg;
   ClickableLabel* appartamentoImg;
   ClickableLabel* camperImg;
   ClickableLabel* bassaImg;
   ClickableLabel* mediaImg;
   ClickableLabel* altaImg;


signals:
   void goToServiziView();

   //filter
   void stagioneSelected(int);
   void structureSelected(int);

   //update degli sopiti
   void sendUpdateOspiti(int);

   //qlabe che fanno da pulsanti
   void clickedLabelCamera();
   void clickedLabelSuite();

public slots:
   void toServiziView();
   void updateOspiti(int);
   void cameraLabelReciever();
   void suiteLabelReciever();
   void appartamentoLabelReciever();
   void camperLabelReciever();
   void bassaLabelReciever();
   void mediaLabelReciever();
   void altaLabelReciever();

};

#endif // HOME_H
