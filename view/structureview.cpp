#include "structureview.h"

StructureView::StructureView(Controller* controller, QWidget* parent):
    _controller(controller),
    tableRow(10)
{
    //main vertical layout
    mainLayout = new QVBoxLayout(parent);

    //upper text
    structureText = new QLabel(parent);
    structureText->setText(QString("Elenco Strutture"));
    structureText->setFont(QFont("Times", 14, QFont::Bold));
    structureText->setAlignment(Qt::AlignHCenter);

    //table proprieties  -- da aggiungere il resize delle celle
    table = new QTableWidget(parent);
    QFont tableCellFont("Times", 11, QFont::Bold);
    table->setFont(tableCellFont);
    table->verticalHeader()->hide(); //nasconde i numeri di sinistra della tabella
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setRowCount(tableRow); // da definire, varia con il vettore
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView* header = table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    header->setStretchLastSection(true);

    buttonLayout = new QHBoxLayout(parent);
    buttonLayout->setAlignment(Qt::AlignLeft);
    backSpacer = new QSpacerItem(600, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    backButton = new QPushButton(parent);
    backButton->setText("BACK");
    backButton->setFixedSize(100, 30);
    homeButton = new QPushButton(parent);
    homeButton->setText("HOME");
    homeButton->setFixedSize(100, 30);
    buttonLayout->addWidget(backButton);
    buttonLayout->addSpacerItem(backSpacer);
    buttonLayout->addWidget(homeButton);

    //popup dialog button
    infoDialog = new InfoDialog();
    popupDialog = new QPushButton();
    popupDialog->setText("?");
    popupDialog->setFixedSize(25, 25);

    mainLayout->addWidget(structureText);
    mainLayout->addWidget(popupDialog);
    mainLayout->setAlignment(popupDialog, Qt::AlignRight);
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);   

    //slots and connection
    connect(table, &QTableWidget::cellDoubleClicked, this, &StructureView::goToStructureDetailsView);
    connect(backButton, &QPushButton::clicked, this, &StructureView::unloadInfoAndImages);
    connect(popupDialog, &QPushButton::clicked, this, &StructureView::openPopUpDialog);
    connect(homeButton, &QPushButton::clicked, this, &StructureView::goBackToHomeView);
}

void StructureView::openPopUpDialog()
{
    infoDialog->exec();
}

void StructureView::goBackToHomeView()
{
    table->clear();
    headerItemList.clear();
    emit goBackToHomeViewFromStructureView();
}

StructureView::~StructureView(){
    delete infoDialog;
    table->clear();
    headerItemList.clear();
}

void StructureView::unloadInfoAndImages()
{
    table->clear();
    headerItemList.clear();
    emit goBackToServiziView();
}



QLabel *StructureView::getIconDisabile(bool b)
{
    QString path;
    if(b)
        path = ":/images/resources/disabile.png";
    else
        return nullptr;

    QPixmap disabilePath(path);
    QPixmap disabilePix = disabilePath.scaled(27, 27, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QLabel* disabile = new QLabel;
    disabile->setPixmap(disabilePix);
    disabile->setAlignment(Qt::AlignCenter);
    return disabile;
}

QLabel *StructureView::getIconStato(status n)
{
    QString path;
    switch(n){
    case status::libero:
        path = ":/images/resources/Green.png";
        break;
    case status::occupato:
        path = ":/images/resources/Red.png";
        break;
    case status::lavori:
        path = ":/images/resources/Maintenance.png";
        break;
    }

    QPixmap statusPath(path);
    QPixmap statuxPix = statusPath.scaled(22, 22, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QLabel* status = new QLabel;
    status->setPixmap(statuxPix);
    status->setAlignment(Qt::AlignCenter);
    return status;
}

QLabel *StructureView::getIconLavatrice(bool b)
{
    QString path;
    if(b)
        path = ":/images/resources/lavatrice_si.png";
    else
        path = ":/images/resources/lavatrice_no.png";

    QPixmap lavatricePath(path);
    QPixmap lavatricePix = lavatricePath.scaled(23, 27, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QLabel* lavatrice = new QLabel;
    lavatrice->setPixmap(lavatricePix);
    lavatrice->setAlignment(Qt::AlignCenter);
    return lavatrice;
}

QLabel *StructureView::getIconBed()
{
    QString path = ":/images/resources/letto.png";
    QPixmap lettoPath(path);
    QPixmap lettoPix = lettoPath.scaled(27, 27, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QLabel* letto = new QLabel;
    letto->setPixmap(lettoPix);
    letto->setAlignment(Qt::AlignCenter);
    return letto;
}

void StructureView::loadListHeaderItem()
{      
    int j = 0;

    if(dynamic_cast<Appartamento*>(&**(_controller->getVettore().begin()))){    
        //set up table
        headerItemList.push_back(QString("Struttura"));
        headerItemList.push_back(QString("Stato"));
        headerItemList.push_back(QString("N°Stanze"));
        headerItemList.push_back(QString("N°Letti"));
        headerItemList.push_back(QString("Piano"));
        headerItemList.push_back(QString("Lavatrice"));
        headerItemList.push_back(QString("Disabile"));
        headerItemList.push_back(QString("Prezzo Min"));

        table->setRowCount(_controller->getVettore().size());
        table->setColumnCount(headerItemList.size());

        for(auto i = _controller->getVettore().begin(); i != _controller->getVettore().end(); i++){
            Appartamento* tmp = dynamic_cast<Appartamento*>(&**i);

            QTableWidgetItem* struttura = new QTableWidgetItem(QString::number(j + 1));
            QTableWidgetItem* nStanze = new QTableWidgetItem(QString::number(tmp->getStanze()));
            QTableWidgetItem* nLetti = new QTableWidgetItem(QString::number(tmp->getLetti()));
            QTableWidgetItem* piano = new QTableWidgetItem(QString::number(tmp->getPiano()));
            QTableWidgetItem* prezzoMin = new QTableWidgetItem(QString::number(tmp->prezzoMinStagione()));

            struttura->setTextAlignment(Qt::AlignCenter);
            nStanze->setTextAlignment(Qt::AlignCenter);
            nLetti->setTextAlignment(Qt::AlignCenter);
            piano->setTextAlignment(Qt::AlignCenter);
            prezzoMin->setTextAlignment(Qt::AlignCenter);

            table->setItem(j, 0, struttura);
            if(tmp->getOspiti() > tmp->getLetti() && tmp->getStato() == status::libero)
                table->setCellWidget(j, 1, getIconBed());
            else
                table->setCellWidget(j, 1, getIconStato(tmp->getStato()));
            table->setItem(j, 2, nStanze);
            table->setItem(j, 3, nLetti);
            table->setItem(j, 4, piano);
            table->setCellWidget(j, 5, getIconLavatrice(tmp->getLavatrice()));
            table->setCellWidget(j, 6, getIconDisabile(tmp->getDisabile()));
            table->setItem(j, 7, prezzoMin);

            j++;
        }

    }else if(dynamic_cast<Camera*>(&**(_controller->getVettore().begin()))){
        headerItemList.push_back(QString("Struttura"));
        headerItemList.push_back(QString("Stato"));
        headerItemList.push_back(QString("N°Letti"));
        headerItemList.push_back(QString("Piano"));
        headerItemList.push_back(QString("Disabile"));
        headerItemList.push_back(QString("Prezzo Min"));

        table->setRowCount(_controller->getVettore().size());
        table->setColumnCount(headerItemList.size());

        for(auto i = _controller->getVettore().begin(); i != _controller->getVettore().end(); i++){
            Camera* tmp = dynamic_cast<Camera*>(&**i);

            QTableWidgetItem* struttura = new QTableWidgetItem(QString::number(j + 1));
            QTableWidgetItem* nLetti = new QTableWidgetItem(QString::number(tmp->getLetti()));
            QTableWidgetItem* piano = new QTableWidgetItem(QString::number(tmp->getPiano()));
            QTableWidgetItem* prezzoMin = new QTableWidgetItem(QString::number(tmp->prezzoMinStagione()));

            struttura->setTextAlignment(Qt::AlignCenter);
            nLetti->setTextAlignment(Qt::AlignCenter);
            piano->setTextAlignment(Qt::AlignCenter);
            prezzoMin->setTextAlignment(Qt::AlignCenter);

            table->setItem(j, 0, struttura);
            if(tmp->getOspiti() > tmp->getLetti() && tmp->getStato() == status::libero)
                table->setCellWidget(j, 1, getIconBed());
            else
                table->setCellWidget(j, 1, getIconStato(tmp->getStato()));
            table->setItem(j, 2, nLetti);
            table->setItem(j, 3, piano);
            table->setCellWidget(j, 4, getIconDisabile(tmp->getDisabile()));
            table->setItem(j, 5, prezzoMin);

            j++;
        }

    }else if(dynamic_cast<Suite*>(&**(_controller->getVettore().begin()))){
        //set up table
        headerItemList.push_back(QString("Struttura"));
        headerItemList.push_back(QString("Stato"));
        headerItemList.push_back(QString("N°Stanze"));
        headerItemList.push_back(QString("N°Letti"));
        headerItemList.push_back(QString("Ufficio"));
        headerItemList.push_back(QString("Relax"));
        headerItemList.push_back(QString("Piano"));
        headerItemList.push_back(QString("Disabile"));
        headerItemList.push_back(QString("Prezzo Min"));

        table->setRowCount(_controller->getVettore().size());
        table->setColumnCount(headerItemList.size());

        for(auto i = _controller->getVettore().begin(); i != _controller->getVettore().end(); i++){
            Suite* tmp = dynamic_cast<Suite*>(&**i);

            QTableWidgetItem* struttura = new QTableWidgetItem(QString::number(j + 1));
            QTableWidgetItem* nStanze = new QTableWidgetItem(QString::number(tmp->getStanze()));
            QTableWidgetItem* nLetti = new QTableWidgetItem(QString::number(tmp->getLetti()));
            QTableWidgetItem* ufficio = new QTableWidgetItem(tmp->getUfficio() ? "Si" : "No");
            QTableWidgetItem* relax = new QTableWidgetItem(tmp->getRelax() ? "Si" : "No");
            QTableWidgetItem* piano = new QTableWidgetItem(QString::number(tmp->getPiano()));
            QTableWidgetItem* prezzoMin = new QTableWidgetItem(QString::number(tmp->prezzoMinStagione()));

            struttura->setTextAlignment(Qt::AlignCenter);
            nStanze->setTextAlignment(Qt::AlignCenter);
            nLetti->setTextAlignment(Qt::AlignCenter);
            ufficio->setTextAlignment(Qt::AlignCenter);
            relax->setTextAlignment(Qt::AlignCenter);
            piano->setTextAlignment(Qt::AlignCenter);
            prezzoMin->setTextAlignment(Qt::AlignCenter);

            table->setItem(j, 0, struttura);
            if(tmp->getOspiti() > tmp->getLetti() && tmp->getStato() == status::libero)
                table->setCellWidget(j, 1, getIconBed());
            else
                table->setCellWidget(j, 1, getIconStato(tmp->getStato()));
            table->setItem(j, 2, nStanze);
            table->setItem(j, 3, nLetti);
            table->setItem(j, 4, ufficio);
            table->setItem(j, 5, relax);
            table->setItem(j, 6, piano);
            table->setCellWidget(j, 7, getIconDisabile(tmp->getDisabile()));
            table->setItem(j, 8, prezzoMin);

            j++;
        }

    }else if(dynamic_cast<Camper*>(&**(_controller->getVettore().begin()))){
        headerItemList.push_back(QString("Piazzola N°"));
        headerItemList.push_back(QString("Stato"));
        headerItemList.push_back(QString("Dimensione Piazz."));
        headerItemList.push_back(QString("Prezzo Min"));

        table->setRowCount(_controller->getVettore().size());
        table->setColumnCount(headerItemList.size());

        for(auto i = _controller->getVettore().begin(); i != _controller->getVettore().end(); i++){
            Camper* tmp = dynamic_cast<Camper*>(&**i);

            QTableWidgetItem* struttura = new QTableWidgetItem(QString::number(j + 1));
            QTableWidgetItem* dimensione = new QTableWidgetItem(QString::number(tmp->getDimensione()));
            QTableWidgetItem* prezzoMin = new QTableWidgetItem(QString::number(tmp->prezzoMinStagione()));

            struttura->setTextAlignment(Qt::AlignCenter);
            dimensione->setTextAlignment(Qt::AlignCenter);
            prezzoMin->setTextAlignment(Qt::AlignCenter);

            table->setItem(j, 0, struttura);
            table->setCellWidget(j, 1, getIconStato(tmp->getStato()));
            table->setItem(j, 2, dimensione);
            table->setItem(j, 3, prezzoMin);

            j++;
        }
    }

    table->setHorizontalHeaderLabels(headerItemList);
}

