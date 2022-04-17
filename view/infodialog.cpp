#include "infodialog.h"

InfoDialog::InfoDialog()
{
    setWindowTitle("Symbol Helper");
    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::WindowModal);

    setFixedSize(350, 300);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setSizePolicy(sizePolicy);

    mainLayout = new QGridLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    QFont font("Verdana", 11, QFont::Medium);

    disabile = new QLabel("<img src=:/images/resources/disabile.png width=33 height=33>");
    disabileText = new QLabel(" Struttura adatta ai disabili");
    disabileText->setFont(font);
    mainLayout->addWidget(disabile, 0, 0);
    mainLayout->addWidget(disabileText, 0, 1);

    greenButton = new QLabel("<img src=:/images/resources/Green.png width=33 height=33>");
    greenButtonText = new QLabel(" Struttura disponibile");
    greenButtonText->setFont(font);
    mainLayout->addWidget(greenButton, 1, 0);
    mainLayout->addWidget(greenButtonText, 1, 1);

    redButton = new QLabel("<img src=:/images/resources/Red.png width=33 height=33>");
    redButtonText = new QLabel(" Struttura già prenotata");
    redButtonText->setFont(font);
    mainLayout->addWidget(redButton, 2, 0);
    mainLayout->addWidget(redButtonText, 2, 1);

    lavori = new QLabel("<img src=:/images/resources/Maintenance.png width=33 height=33>");
    lavoriText = new QLabel(" Struttura in manutenzione");
    lavoriText->setFont(font);
    mainLayout->addWidget(lavori, 3, 0);
    mainLayout->addWidget(lavoriText, 3, 1);

    lavatrice = new QLabel("<img src=:/images/resources/lavatrice_si.png width=30 height=33> <img src=:/images/resources/lavatrice_no width=30 height=33>");
    lavatriceText = new QLabel(" Lavatrice");
    lavatriceText->setFont(font);
    mainLayout->addWidget(lavatrice, 4, 0);
    mainLayout->addWidget(lavatriceText, 4, 1);

    letto = new QLabel("<img src=:/images/resources/letto.png width=33 height=33>");
    lettoText = new QLabel(" N°ospiti superiore ai Letti");
    lettoText->setFont(font);
    mainLayout->addWidget(letto, 5, 0);
    mainLayout->addWidget(lettoText, 5, 1);
}

InfoDialog::~InfoDialog(){}
