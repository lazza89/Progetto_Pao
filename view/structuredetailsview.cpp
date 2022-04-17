#include "structuredetailsview.h"

StructureDetailsView::StructureDetailsView(Controller* controller, QWidget* parent) :
    _controller(controller)
{
    mainLayout = new QVBoxLayout(parent);

    textInfoStruttura = new QLabel(parent);
    textInfoStruttura->setText(QString("Informazioni e Servizi Struttura"));
    textInfoStruttura->setFont(QFont("Verdana", 16, QFont::Bold));
    textInfoStruttura->setSizePolicy(QSizePolicy::Minimum , QSizePolicy::Maximum);
    textInfoStruttura->setAlignment(Qt::AlignHCenter);
    textInfoStruttura->setMinimumHeight(60);

    infoLayout = new QGridLayout(parent);
    infoLayout->setVerticalSpacing(20);
    //colored text
    stringDisabile = QString("Appartamento <font color='green'>accessibile</font>  ai disabili");
    stringPuliziaCucina = QString("<font color='green'>Pulizia Cucina</font> <br>");
    stringSpiaggia = QString("<font color='green'>Spiaggia Privata</font> <br>");
    stringPiscina = QString("<font color='green'>Accesso Piscina</font> <br>");
    stringstatolibero = QString("<font color='green'> Prenotabile</font>");
    stringStatoOccupato = QString("<font color='red'> Già Prenotato</font>");
    stringStatoLavori = QString("<font color='#E67E22'> Lavori in Corso</font>");
    stringLettiMinori = QString("Stato Struttura:<br><font color='red'>Numero ospiti maggiore del numero letti</font>");

    backSpacerLayout = new QHBoxLayout(parent);
    backSpacerLayout->setAlignment(Qt::AlignLeft);
    backButton = new QPushButton(parent);
    backButton->setText("BACK");
    backButton->setFixedSize(100, 30);
    backSpacerLayout->addWidget(backButton);

    mainLayout->addWidget(textInfoStruttura);
    mainLayout->addLayout(infoLayout);
    mainLayout->addLayout(backSpacerLayout);

    setLayout(mainLayout);
    loadStructureInformation(1);

    //connect per il back button
    connect(backButton, &QPushButton::clicked, this, &StructureDetailsView::deleteDetails);
}


StructureDetailsView::~StructureDetailsView(){}

void StructureDetailsView::loadStructureInformation(int n)
{
    if(n <= static_cast<int>(_controller->getVettore().size())){
        auto i = _controller->getVettore().begin() + n;
        if(auto tmp = dynamic_cast<Appartamento*>((&**i))){

            infoVector.push_back(new QLabel("Dimensione in Mq: " + QString::number(tmp->getDimensione())));
            infoVector.push_back(new QLabel("Numero Stanze: " + QString::number(tmp->getStanze())));
            infoVector.push_back(new QLabel("Numero Letti: " + QString::number(tmp->getLetti())));
            infoVector.push_back(new QLabel("L'appartamento si trova al " + QString::number(tmp->getPiano()) + "° Piano"));

            if(tmp->getCucina() == fornelli::gas)
                infoVector.push_back(new QLabel("Tipologia Cucina: fornelli a Gas"));
            else
                infoVector.push_back(new QLabel("Tipologia Cucina: fornelli ad Induzione"));

            if(tmp->getLavatrice())
                infoVector.push_back(new QLabel("E' Presente la <font color='green'>Lavatrice</font>"));
            if(tmp->getDisabile())
                infoVector.push_back(new QLabel(stringDisabile));

            QString nessuno;
            if(!tmp->servizioPuliziaCucina() && !tmp->servizioSpiaggia() && !tmp->servizioPiscina())
                nessuno = QString("<font color='red'>Nessun servizio aggiuntivo selezionato</font>");

            infoVector.push_back(new QLabel("Servizi Selezionati: <br>"
            + (tmp->servizioPuliziaCucina() ? stringPuliziaCucina : "")
            + (tmp->servizioSpiaggia() ? stringSpiaggia : "")
            + (tmp->servizioPiscina() ? stringPiscina : "")
            + (!nessuno.isEmpty() ? nessuno : "")));

            QString stagione;
            switch (tmp->getStagione()) {
            case periodo::bassa:
                stagione = QString(" Bassa ");
                break;
            case periodo::media:
                stagione = QString(" Media ");
                break;
            case periodo::alta:
                stagione = QString(" Alta ");
                break;
            }

            QString stato;
            switch (tmp->getStato()) {
            case status::libero:
                stato = QString(stringstatolibero);
                break;
            case status::occupato:
                stato = QString(stringStatoOccupato);
                break;
            case status::lavori:
                stato = QString(stringStatoLavori);
                break;
            }
            if(tmp->getOspiti() > tmp->getLetti() && tmp->getStato() == status::libero)
                infoVector.push_back(new QLabel(stringLettiMinori));
            else
                infoVector.push_back(new QLabel("Stato Struttura:" + stato));

            QString ospiti(" Ospite ");
            if(tmp->getOspiti() > 1)
                ospiti = QString(" Ospiti ");

            infoVector.push_back(new QLabel("Per " + QString::number(tmp->getOspiti()) + ospiti + "nel periodo di" + stagione + "Stagione\n"
            + "Il Prezzo a notte è di: " + QString::number(tmp->prezzo()) + "€"));

            infoVector.push_back(new QLabel("Per la prenotazione o ulteriori informazioni \nsi prega di telefonare al residence"));

            unsigned int j = 0, m = 0;
            for(auto f = infoVector.begin(); f != infoVector.end(); f++){
                if(j == infoVector.size() - 3){
                    m = 1;
                    j = 0;
                }
                (**f).setAlignment(Qt::AlignHCenter);
                (**f).setFont(QFont("Comic Sans MS", 12, QFont::Light));
                infoLayout->addWidget(&**f, j, m);
                j++;
            }


        }else if(auto tmp = dynamic_cast<Camera*>((&**i))){

                infoVector.push_back(new QLabel("Dimensione in Mq: " + QString::number(tmp->getDimensione())));
                infoVector.push_back(new QLabel("Numero Letti: " + QString::number(tmp->getLetti())));
                infoVector.push_back(new QLabel("La camera si trova al " + QString::number(tmp->getPiano()) + "° Piano"));

                if(tmp->getDisabile())
                    infoVector.push_back(new QLabel(stringDisabile));

                QString pensione;
                switch (tmp->getRistorante()) {
                case pensione::colazione:
                    pensione = QString(" Solo colazione");
                    break;
                case pensione::mezza:
                    pensione = QString(" Mezza pensione");
                    break;
                case pensione::completa:
                    pensione = QString(" Pensione completa");
                    break;
                }
                infoVector.push_back(new QLabel("Opzione di alloggio:" + pensione));

                infoVector.push_back(new QLabel("Servizo Incluso: " + stringPiscina  + "Servizi aggiuntivi selezionati:<br>"
                + (tmp->servizioSpiaggia() ? QString(stringSpiaggia) : "<font color='red'>Nessun servizio aggiuntivo selezionato</font>")));

                QString stagione;
                switch (tmp->getStagione()) {
                case periodo::bassa:
                    stagione = QString(" Bassa ");
                    break;
                case periodo::media:
                    stagione = QString(" Media ");
                    break;
                case periodo::alta:
                    stagione = QString(" Alta ");
                    break;
                }

                QString stato;
                switch (tmp->getStato()) {
                case status::libero:
                    stato = QString(stringstatolibero);
                    break;
                case status::occupato:
                    stato = QString(stringStatoOccupato);
                    break;
                case status::lavori:
                    stato = QString(stringStatoLavori);
                    break;
                }
                if(tmp->getOspiti() > tmp->getLetti() && tmp->getStato() == status::libero)
                    infoVector.push_back(new QLabel(stringLettiMinori));
                else
                    infoVector.push_back(new QLabel("Stato Struttura:" + stato));

                QString ospiti(" Ospite ");
                if(tmp->getOspiti() > 1)
                    ospiti = QString(" Ospiti ");

                infoVector.push_back(new QLabel("Per " + QString::number(tmp->getOspiti()) + ospiti + "nel periodo di" + stagione + "Stagione\n"
                + "Il Prezzo a notte è di: " + QString::number(tmp->prezzo()) + "€"));

                infoVector.push_back(new QLabel("Per la prenotazione o ulteriori informazioni \nsi prega di telefonare al residence"));

                unsigned int j = 0, m = 0;
                for(auto f = infoVector.begin(); f != infoVector.end(); f++){
                    if(j == infoVector.size() - 3){
                        m = 1;
                        j = 0;
                    }
                    (**f).setAlignment(Qt::AlignHCenter);
                    (**f).setFont(QFont("Comic Sans MS", 12, QFont::Light));
                    infoLayout->addWidget(&**f, j, m);
                    j++;
                }

        }else if(auto tmp = dynamic_cast<Suite*>((&**i))){

            infoVector.push_back(new QLabel("Dimensione in Mq: " + QString::number(tmp->getDimensione())));
            infoVector.push_back(new QLabel("Numero Stanze: " + QString::number(tmp->getStanze())));
            infoVector.push_back(new QLabel("Numero Letti: " + QString::number(tmp->getLetti())));
            infoVector.push_back(new QLabel("La Suite si trova al " + QString::number(tmp->getPiano()) + "° Piano"));

            if(tmp->getDisabile())
                infoVector.push_back(new QLabel(stringDisabile));

            QString pensione;
            switch (tmp->getRistorante()) {
            case pensione::colazione:
                pensione = QString(" Solo colazione");
                break;
            case pensione::mezza:
                pensione = QString(" Mezza pensione");
                break;
            case pensione::completa:
                pensione = QString(" Pensione completa");
                break;
            }
            infoVector.push_back(new QLabel("Opzione di alloggio:" + pensione));

            QString nessuno;
            if(!tmp->getRelax() && !tmp->getServizioCamera() && !tmp->getUfficio() && !tmp->servizioSpiaggia())
                nessuno = QString("<font color='red'>Nessun servizio aggiuntivo selezionato</font>");

            infoVector.push_back(new QLabel("Servizi Inclusi: " + stringPiscina + "Servizi aggiuntivi Selezionati:<br>"
            + (tmp->getServizioCamera() ? QString("<font color='green'>Servizio in camera</font><br>") : "")
            + (tmp->getUfficio() ? QString("<font color='green'>Ufficio Privato</font><br>") : "")
            + (tmp->servizioSpiaggia() ? QString(stringSpiaggia) : "")
            + (tmp->getRelax() ? QString("<font color='green'>Centro benessere Riservato</font>") : "")
            + (!nessuno.isEmpty() ? QString(nessuno) : "")));

            QString stagione;
            switch (tmp->getStagione()) {
            case periodo::bassa:
                stagione = QString(" Bassa ");
                break;
            case periodo::media:
                stagione = QString(" Media ");
                break;
            case periodo::alta:
                stagione = QString(" Alta ");
                break;
            }

            QString stato;
            switch (tmp->getStato()) {
            case status::libero:
                stato = QString(stringstatolibero);
                break;
            case status::occupato:
                stato = QString(stringStatoOccupato);
                break;
            case status::lavori:
                stato = QString(stringStatoLavori);
                break;
            }
            if(tmp->getOspiti() > tmp->getLetti() && tmp->getStato() == status::libero)
                infoVector.push_back(new QLabel("Stato Struttura: " + stringLettiMinori));
            else
                infoVector.push_back(new QLabel("Stato Struttura: " + stato));

            QString ospiti(" Ospite ");
            if(tmp->getOspiti() > 1)
                ospiti = QString(" Ospiti ");

            infoVector.push_back(new QLabel("Per " + QString::number(tmp->getOspiti()) + ospiti + "nel periodo di" + stagione + "Stagione\n"
            + "Il Prezzo a notte è di: " + QString::number(tmp->prezzo()) + "€"));

            infoVector.push_back(new QLabel("Per la prenotazione o ulteriori informazioni \nsi prega di telefonare al residence"));

            unsigned int j = 0, m = 0;
            for(auto f = infoVector.begin(); f != infoVector.end(); f++){
                if(j == infoVector.size() - 3){
                    m = 1;
                    j = 0;
                }
                (**f).setAlignment(Qt::AlignHCenter);
                (**f).setFont(QFont("Comic Sans MS", 12, QFont::Light));
                infoLayout->addWidget(&**f, j, m);
                j++;
            }
        }else if(auto tmp = dynamic_cast<Camper*>((&**i))){
            infoVector.push_back(new QLabel("Dimensione Piazzola in Mq: " + QString::number(tmp->getDimensione())));

            QString nessuno;
            if(!tmp->servizioCorrente() && !tmp->servizioAcqua() && !tmp->servizioPiscina() && !tmp->servizioPiscina())
                nessuno = QString("<font color='red'>Nessun servizio aggiuntivo selezionato</font>");

            infoVector.push_back(new QLabel("Servizi aggiuntivi Selezionati:<br>"
            + (tmp->servizioCorrente() ? QString("<font color='green'>Colonnina corrente elettrica 220V</font><br>") : "")
            + (tmp->servizioAcqua() ? QString("<font color='green'>Attacco acqua</font><br>") : "")
            + (tmp->servizioSpiaggia() ? QString(stringSpiaggia) : "")
            + (tmp->servizioPiscina() ? QString(stringPiscina) : "")
            + (!nessuno.isEmpty() ? nessuno : "")));

            infoVector.push_back(new QLabel(""));

            QString stagione;
            switch (tmp->getStagione()) {
            case periodo::bassa:
                stagione = QString(" Bassa ");
                break;
            case periodo::media:
                stagione = QString(" Media ");
                break;
            case periodo::alta:
                stagione = QString(" Alta ");
                break;
            }

            QString stato;
            switch (tmp->getStato()) {
            case status::libero:
                stato = QString(stringstatolibero);
                break;
            case status::occupato:
                stato = QString(stringStatoOccupato);
                break;
            case status::lavori:
                stato = QString(stringStatoLavori);
                break;
            }
            infoVector.push_back(new QLabel("Stato Struttura:" + stato));

            QString ospiti(" Ospite ");
            if(tmp->getOspiti() > 1)
                ospiti = QString(" Ospiti ");

            infoVector.push_back(new QLabel("Per " + QString::number(tmp->getOspiti()) + ospiti + "nel periodo di" + stagione + "Stagione\n"
            + "Il Prezzo a notte è di: " + QString::number(tmp->prezzo()) + "€"));

            infoVector.push_back(new QLabel("Per la prenotazione o ulteriori informazioni \nsi prega di telefonare al residence"));

            unsigned int j = 0, m = 0;
            for(auto f = infoVector.begin(); f != infoVector.end(); f++){
                if(j == infoVector.size() - 3){
                    m = 1;
                    j = 0;
                }
                (**f).setAlignment(Qt::AlignHCenter);
                (**f).setFont(QFont("Comic Sans MS", 12, QFont::Light));
                infoLayout->addWidget(&**f, j, m);
                j++;
            }
        }
    }
}

void StructureDetailsView::deleteDetails()
{
    for(auto i = infoVector.begin(); i != infoVector.end(); i++){
        infoLayout->removeWidget(*i);
        delete *i;
    }
    infoVector.clear();

    emit goBackToStructureView();
}




















