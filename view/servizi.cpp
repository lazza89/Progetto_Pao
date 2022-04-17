#include "servizi.h"

Servizi::Servizi(QWidget *parent) : tipoStruttura(0){
    mainLayout=new QVBoxLayout(parent);
    QLabel* serviziText = new QLabel(parent);
    serviziText->setText("Seleziona i Servizi");
    serviziText->setAlignment(Qt::AlignHCenter);
    serviziText->setSizePolicy(QSizePolicy::Minimum , QSizePolicy::Maximum);
    serviziText->setFont(QFont("Verdana", 17, QFont::Bold));
    mainLayout->addWidget(serviziText);

    serviziFunct(parent);
    ristoranteFunct(parent);
    appartamentoFunct(parent);
    camperFunct(parent);
    suiteFunct(parent);
    servizi_pulsantiFunct(parent);
    setLayout(mainLayout);

    connect(servizi_home, &QPushButton::clicked, this, &Servizi::backToHomeView); // quando il segnale del bottone clicked(viene cliccato il pulsante home) viene emesso questa classe emette il segnale goBackToHomeView()
    connect(servizi_prosegui, &QPushButton::clicked, this, &Servizi::toStructureView); //quando si preme il pulsante prosegui viene emesso da questa classe il segnale goToStructureView()
}

Servizi::~Servizi(){
    delete ristoranteGroup;
    delete appartamentoGroup;
};

void Servizi::serviziFunct(QWidget* parent){
    servizi_=new QLabel(parent);
    servizi_->setText(QString("SERVIZI"));
    servizi_->setAlignment(Qt::AlignCenter);
    spiaggia=new QCheckBox(parent);
    piscina=new QCheckBox(parent);
    spiaggia->setText("Spiaggia");
    piscina->setText("Piscina");
    serviziLayout=new QHBoxLayout(parent);
    serviziLayout->addWidget(servizi_);
    serviziLayout->addWidget(spiaggia);
    serviziLayout->addWidget(piscina);
    serviziLayout->addSpacing(200);
    serviziLayout->setSpacing(30);
    mainLayout->addLayout(serviziLayout);
}

void Servizi::ristoranteFunct(QWidget* parent){
    ristoranteLayout=new QHBoxLayout(parent);
    ristorante=new QLabel(parent);
    ristorante->setText(QString("RISTORANTE"));
    ristorante->setAlignment(Qt::AlignCenter);
    ristoranteGroup=new QButtonGroup(parent);
    colazione=new QRadioButton(parent);
    mezza=new QRadioButton(parent);
    completa=new QRadioButton(parent);
    colazione->setText("Colazione");
    mezza->setText("Mezza pensione");
    completa->setText("Pensione completa");
    colazione->setChecked(true);
    ristoranteGroup->addButton(colazione);
    ristoranteGroup->addButton(mezza);
    ristoranteGroup->addButton(completa);
    ristoranteLayout->addWidget(ristorante);
    ristoranteLayout->addWidget(colazione);
    ristoranteLayout->addWidget(mezza);
    ristoranteLayout->addWidget(completa);
    ristoranteLayout->setSpacing(30);
    mainLayout->addLayout(ristoranteLayout);
}

void Servizi::appartamentoFunct(QWidget* parent){
    appartamentoLayout=new QHBoxLayout(parent);
    pulizia=new QLabel(parent);
    pulizia->setText("PULIZIA CUCINA \n (da parte del residence)");
    pulizia->setAlignment(Qt::AlignCenter);
    appartamentoGroup=new QButtonGroup(parent);
    si=new QRadioButton(parent);
    no=new QRadioButton(parent);
    si->setText("Si");
    no->setText("No");
    si->setChecked(true);
    appartamentoGroup->addButton(si);
    appartamentoGroup->addButton(no);
    appartamentoLayout->addWidget(pulizia);
    appartamentoLayout->addWidget(si);
    appartamentoLayout->addWidget(no);
    appartamentoLayout->setSpacing(30);
    appartamentoLayout->addSpacing(200);
    mainLayout->addLayout(appartamentoLayout);
}

void Servizi::camperFunct(QWidget* parent){
    camperLayout=new QHBoxLayout(parent);
    camperText=new QLabel(parent);
    camperText->setText("CAMPER");
    camperText->setAlignment(Qt::AlignCenter);
    acqua=new QCheckBox(parent);
    corrente=new QCheckBox(parent);
    acqua->setText("Acqua");
    corrente->setText("Presa di corrente");
    camperLayout->addWidget(camperText);
    camperLayout->addWidget(acqua);
    camperLayout->addWidget(corrente);
    camperLayout->addSpacing(200);
    camperLayout->setSpacing(30);
    mainLayout->addLayout(camperLayout);
}

void Servizi::suiteFunct(QWidget* parent){
    suiteLayout=new QHBoxLayout();
    suiteText=new QLabel(parent);
    suiteText->setText("Servizi SUITE \n privati");
    suiteText->setAlignment(Qt::AlignCenter);
    relax=new QCheckBox(parent);
    ufficio=new QCheckBox(parent);
    servizioristorante=new QCheckBox(parent);
    relax->setText("Centro benessere");
    ufficio->setText("Ufficio / Sala riunioni");
    servizioristorante->setText("Servizio ristorante in camera");
    suiteLayout->addWidget(suiteText);
    suiteLayout->addWidget(relax);
    suiteLayout->addWidget(ufficio);
    suiteLayout->addWidget(servizioristorante);
    suiteLayout->setSpacing(30);
    mainLayout->addLayout(suiteLayout);
}

void Servizi::servizi_pulsantiFunct(QWidget* parent){
    servizi_pulsantiLayout=new QHBoxLayout(parent);
    servizi_home=new QPushButton(parent);
    servizi_prosegui=new QPushButton(parent);
    servizi_home->setText("HOME");
    servizi_prosegui->setText("PROSEGUI");
    servizi_home->setMaximumWidth(100);
    servizi_prosegui->setMaximumWidth(100);
    servizi_pulsantiLayout->addWidget(servizi_home);
    servizi_pulsantiLayout->addWidget(servizi_prosegui);
    mainLayout->addLayout(servizi_pulsantiLayout);
}

void Servizi::uncheckButtons(int n)
{
    tipoStruttura = n;
    switch (n) {
    case 1:
        camperText->setVisible(false);
        acqua->setVisible(false);
        corrente->setVisible(false);
        suiteText->setVisible(false);
        relax->setVisible(false);
        ufficio->setVisible(false);
        servizioristorante->setVisible(false);
        ristorante->setVisible(false);
        colazione->setVisible(false);
        completa->setVisible(false);
        colazione->setVisible(false);
        mezza->setVisible(false);
        break;

    case 2:
        piscina->setChecked(true);
        piscina->setEnabled(false);

        camperText->setVisible(false);
        acqua->setVisible(false);
        corrente->setVisible(false);
        suiteText->setVisible(false);
        relax->setVisible(false);
        ufficio->setVisible(false);
        servizioristorante->setVisible(false);
        pulizia->setVisible(false);
        si->setVisible(false);
        no->setVisible(false);
        no->setChecked(true);
        break;

    case 3:
        piscina->setChecked(true);
        piscina->setEnabled(false);
        servizioristorante->setChecked(true);

        camperText->setVisible(false);
        acqua->setVisible(false);
        corrente->setVisible(false);
        pulizia->setVisible(false);
        si->setVisible(false);
        no->setVisible(false);
        no->setChecked(true);
        break;
    case 4:
        ristorante->setVisible(false);
        colazione->setVisible(false);
        completa->setVisible(false);
        colazione->setVisible(false);
        mezza->setVisible(false);
        suiteText->setVisible(false);
        relax->setVisible(false);
        ufficio->setVisible(false);
        servizioristorante->setVisible(false);
        pulizia->setVisible(false);
        si->setVisible(false);
        no->setVisible(false);
        no->setChecked(true);

        break;
    }
}

void Servizi::backToHomeView()
{
    //reset check dei pulsanti
    piscina->setChecked(false);
    spiaggia->setChecked(false);
    piscina->setEnabled(true);
    si->setChecked(true);
    acqua->setChecked(false);
    corrente->setChecked(false);
    relax->setChecked(false);
    ufficio->setChecked(false);

    //reset della visibilità dei pulsanti
    ristorante->setVisible(true);
    colazione->setVisible(true);
    completa->setVisible(true);
    colazione->setVisible(true);
    mezza->setVisible(true);
    camperText->setVisible(true);
    acqua->setVisible(true);
    corrente->setVisible(true);
    suiteText->setVisible(true);
    relax->setVisible(true);
    ufficio->setVisible(true);
    servizioristorante->setVisible(true);
    pulizia->setVisible(true);
    si->setVisible(true);
    no->setVisible(true);



    emit goBackToHomeView();
}

void Servizi::toStructureView()
{
    switch (tipoStruttura) {
    //caso appartamento
    case 1:
        emit addPuliziaCucina(si->isChecked());
        emit addSpiaggia(spiaggia->isChecked());
        emit addPiscina(piscina->isChecked());

        break;
    //caso camera
    case 2:
        emit addPiscina(piscina->isChecked());
        emit addSpiaggia(spiaggia->isChecked());

        if(colazione->isChecked())
            emit addPensione(1);
        else if(mezza->isChecked())
            emit addPensione(2);
        else if(completa->isChecked())
            emit addPensione(3);

        break;
    //caso Suite
    case 3:
         emit addPiscina(piscina->isChecked());
         emit addSpiaggia(spiaggia->isChecked());

        if(colazione->isChecked())
            emit addPensione(1);
        else if(mezza->isChecked())
            emit addPensione(2);
        else if(completa->isChecked())
            emit addPensione(3);

        emit addSuiteCentroBenessere(relax->isChecked());
        emit addSuiteSalaRiunioni(ufficio->isChecked());
        emit addSuiteServizioCamera(servizioristorante->isChecked());

        break;
    //caso Camper
    case 4:
        emit addPiscina(piscina->isChecked());
        emit addSpiaggia(spiaggia->isChecked());
        emit addAcquaCamper(acqua->isChecked());
        emit addCorrenteCamper(corrente->isChecked());

        break;
    }

    emit goToStructureView();
}















