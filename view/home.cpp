#include "home.h"
#include <iostream>

Home::Home(QWidget *parent) : nOspiti(1){
    mainLayout=new QVBoxLayout(parent);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSpacing(15);
    titoloFunct(parent);
    ospitiFunct(parent);
    periodoFunct(parent);
    strutturaFunct(parent);
    home_pulsantiFunct(parent);
    setLayout(mainLayout);

    connect(home_prosegui, &QPushButton::pressed, this, &Home::toServiziView);
    connect(numero, SIGNAL(valueChanged(int)), this, SLOT(updateOspiti(int)));

    //connectin image to radiobutton
    connect(cameraImg, &ClickableLabel::clicked, this, &Home::cameraLabelReciever);
    connect(suiteImg, &ClickableLabel::clicked, this, &Home::suiteLabelReciever);
    connect(appartamentoImg, &ClickableLabel::clicked, this, &Home::appartamentoLabelReciever);
    connect(camperImg, &ClickableLabel::clicked, this, &Home::camperLabelReciever);
    connect(bassaImg, &ClickableLabel::clicked, this, &Home::bassaLabelReciever);
    connect(mediaImg, &ClickableLabel::clicked, this, &Home::mediaLabelReciever);
    connect(altaImg, &ClickableLabel::clicked, this, &Home::altaLabelReciever);
}
void Home::cameraLabelReciever(){camera->setChecked(true);}

void Home::suiteLabelReciever(){suite->setChecked(true);}

void Home::appartamentoLabelReciever(){appartamento->setChecked(true);}

void Home::camperLabelReciever(){camper->setChecked(true);}

void Home::bassaLabelReciever(){bassa->setChecked(true);}

void Home::mediaLabelReciever(){media->setChecked(true);}

void Home::altaLabelReciever(){alta->setChecked(true);}

Home::~Home(){
    delete strutturaGroup;
    delete strutturaLayout;
    delete periodoGroup;
};

void Home::updateOspiti(int n)
{
    nOspiti = n;
}

void Home::toServiziView(){

    if(appartamento->isChecked()){
        emit structureSelected(1);
    }else if(camera->isChecked()){
        emit structureSelected(2);
    }else if(suite->isChecked()){
        emit structureSelected(3);
    }else if(camper->isChecked()){
        emit structureSelected(4);
    }

    if(bassa->isChecked()){
        emit stagioneSelected(1);
    }else if(media->isChecked()){
        emit stagioneSelected(2);
    }else if(alta->isChecked()){
        emit stagioneSelected(3);
    }

    emit sendUpdateOspiti(nOspiti);
    emit goToServiziView();
}


void Home::titoloFunct(QWidget *parent){
    QHBoxLayout* titoloLayout = new QHBoxLayout(parent);
    titolo=new QLabel(parent);
    titolo->setText(QString("BENVENUTI AL RESIDENCE STELLA"));
    titolo->setFont(QFont("Verdana", 18, QFont::Bold));
    titolo->setAlignment(Qt::AlignHCenter);
    titolo->setMaximumHeight(30);

    QPixmap logo(":/images/resources/logo.png");
    QPixmap logoPix = logo.scaled(80, 80, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QLabel* logoLabel = new QLabel;
    QLabel* logoLabel2 = new QLabel;
    logoLabel->setPixmap(logoPix);
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel2->setPixmap(logoPix);
    logoLabel2->setAlignment(Qt::AlignCenter);
    titoloLayout->addWidget(logoLabel);
    titoloLayout->addWidget(titolo);
    titoloLayout->addWidget(logoLabel2);
    mainLayout->addLayout(titoloLayout);
}

void Home::ospitiFunct(QWidget *parent){
    ospiti=new QLabel(parent);
    ospiti->setText(QString("NUMERO OSPITI \n (per struttura)"));
    numero=new QSpinBox(parent);
    numero->setMinimum(1);
    numero->setMaximum(8);
    numero->setMaximumSize(50,25);
    numero->setAlignment(Qt::AlignHCenter);
    numero->setFixedSize(50, 25);
    numero->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    ospiti->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    ospitiLayout=new QHBoxLayout(parent);
    ospitiLayout->addWidget(ospiti);
    ospitiLayout->setAlignment(Qt::AlignmentFlag(8));
    ospitiLayout->addWidget(numero);
    ospitiLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(ospitiLayout);
}

void Home::periodoFunct(QWidget *parent){
    bassa=new QRadioButton(parent);
    media=new QRadioButton(parent);
    alta=new QRadioButton(parent);
    bassa->setChecked(true);
    periodoGroup=new QButtonGroup(parent);
    periodoGroup->addButton(bassa, 1);
    periodoGroup->addButton(media, 2);
    periodoGroup->addButton(alta, 3);
    periodoLayout=new QHBoxLayout(parent);
    periodoLayout->setAlignment(Qt::AlignCenter);

    bassaImg = new ClickableLabel(parent);
    mediaImg = new ClickableLabel(parent);
    altaImg = new ClickableLabel(parent);

    QString bassaPath(":/images/resources/bassa.png");
    QString mediaPath(":/images/resources/media.png");
    QString altaPath(":/images/resources/alta.png");

    periodoLayout->addWidget(addImageButton(parent, bassaImg, bassa, bassaPath, "Bassa\nStagione"));
    periodoLayout->addWidget(addImageButton(parent, mediaImg, media, mediaPath, "Media\nStagione"));
    periodoLayout->addWidget(addImageButton(parent, altaImg, alta, altaPath, "Alta\nStagione"));

    QLabel* stagione = new QLabel("Seleziona il periodo");
    QHBoxLayout* stagioneLayout = new QHBoxLayout(parent);
    stagione->setFont(QFont("Verdana", 12, QFont::Bold));
    stagione->setAlignment(Qt::AlignCenter);
    stagione->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    stagioneLayout->addWidget(stagione);
    mainLayout->addLayout(stagioneLayout);
    mainLayout->addLayout(periodoLayout);
}

QGroupBox *Home::addImageButton(QWidget *parent, ClickableLabel* img, QRadioButton *button, QString path, QString nomeStruttura)
{
    QPixmap ImgPath(path);
    QPixmap ImgPix = ImgPath.scaled(120, 120, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    img->setPixmap(ImgPix);
    img->setAlignment(Qt::AlignCenter);

    QLabel* text = new QLabel(nomeStruttura, parent);
    text->setFont(QFont("Verdana", 10, QFont::Bold));
    text->setAlignment(Qt::AlignCenter);

    QGroupBox* box = new QGroupBox(parent);
    QVBoxLayout* VBox = new QVBoxLayout(parent);
    QHBoxLayout* HBox = new QHBoxLayout(parent);
    HBox->addWidget(button);
    HBox->setAlignment(Qt::AlignCenter);
    VBox->setAlignment(Qt::AlignCenter);
    VBox->addLayout(HBox);
    VBox->addWidget(img);
    VBox->addWidget(text);
    box->setLayout(VBox);
    return box;
}


void Home::strutturaFunct(QWidget *parent){
    camera=new QRadioButton(parent);
    suite=new QRadioButton(parent);
    appartamento=new QRadioButton(parent);
    camper=new QRadioButton(parent);
    camera->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    camera->setChecked(true);

    strutturaGroup=new QButtonGroup(parent);
    strutturaGroup->addButton(camera, 2);
    strutturaGroup->addButton(suite, 3);
    strutturaGroup->addButton(appartamento, 1);
    strutturaGroup->addButton(camper, 4);

    strutturaLayout=new QHBoxLayout(parent);
    strutturaLayout->setAlignment(Qt::AlignCenter);

    cameraImg = new ClickableLabel(parent);
    suiteImg = new ClickableLabel(parent);
    appartamentoImg = new ClickableLabel(parent);
    camperImg = new ClickableLabel(parent);

    QString cameraPath = ":/images/resources/camera.png";
    QString suitePath = ":/images/resources/suite.png";
    QString appartamentoPath = ":/images/resources/appartamento.png";
    QString camperPath = ":/images/resources/camper.png";

    strutturaLayout->addWidget(addImageButton(parent, cameraImg, camera, cameraPath, "Camera"));
    strutturaLayout->addWidget(addImageButton(parent, suiteImg, suite, suitePath, "Suite"));
    strutturaLayout->addWidget(addImageButton(parent, appartamentoImg, appartamento, appartamentoPath, "Appartamento"));
    strutturaLayout->addWidget(addImageButton(parent, camperImg, camper, camperPath, "Piazzola Camper"));

    QLabel* stagione = new QLabel("Seleziona la Struttura");
    QHBoxLayout* stagioneLayout = new QHBoxLayout(parent);
    stagione->setFont(QFont("Verdana", 12, QFont::Bold));
    stagione->setAlignment(Qt::AlignCenter);
    stagione->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    stagioneLayout->addWidget(stagione);
    mainLayout->addLayout(stagioneLayout);
    mainLayout->addLayout(strutturaLayout);
}



void Home::home_pulsantiFunct(QWidget *parent){
    home_prosegui=new QPushButton(parent);
    home_prosegui->setText("PROSEGUI");
    home_prosegui->setFixedSize(QSize(100, 30));

    home_pulsantiLayout=new QHBoxLayout(parent);
    home_pulsantiLayout->addWidget(home_prosegui);
    mainLayout->addLayout(home_pulsantiLayout);
}
