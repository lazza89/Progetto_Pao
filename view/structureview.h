#ifndef STRUCTUREVIEW_H
#define STRUCTUREVIEW_H
#include <iostream>

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
#include <QPushButton>
#include <QSpacerItem>

#include "controller.h"
#include "view/infodialog.h"

class Controller;

class StructureView : public QWidget
{
    Q_OBJECT

public:
    StructureView(Controller* controller, QWidget* parent = nullptr);
    ~StructureView();

private:
    Controller* _controller;

    QLabel* structureText;
    QVBoxLayout* mainLayout;

    QTableWidget* table;
    int tableRow;

    QHBoxLayout* buttonLayout;
    QSpacerItem* backSpacer;
    QPushButton* backButton;
    QPushButton* homeButton;

    //popup dialog
    InfoDialog* infoDialog;
    QPushButton* popupDialog;

    //proprietà tabella
    QStringList headerItemList;

    //images
    QLabel* getIconDisabile(bool);
    QLabel* getIconStato(status);
    QLabel* getIconLavatrice(bool);
    QLabel* getIconBed();

signals:
    void goBackToServiziView();
    void goToStructureDetailsView(int);
    void goBackToHomeViewFromStructureView();

public slots:
    void loadListHeaderItem();
    void unloadInfoAndImages();
    void openPopUpDialog();
    void goBackToHomeView();


};

#endif // STRUCTUREVIEW_H
