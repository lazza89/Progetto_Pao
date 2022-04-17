#include "camper.h"

    Camper::~Camper(){};
    Camper::Camper(int dimensione, double prezzo, int letti, int ospiti, int piano, periodo stagione, status stato, bool disabile, bool piscina, bool spiaggia, bool acqua, bool corrente):
        Residence(dimensione, letti, piano, prezzo, ospiti, stagione, stato, disabile, piscina, spiaggia),
        acqua(acqua),
        corrente(corrente)
    {};

    bool Camper::servizioAcqua() const{return acqua;};
    bool Camper::servizioCorrente() const{return corrente;};
    void Camper::setAcqua(bool a) {acqua=a;};
    void Camper::setCorrente(bool c) {corrente=c;};
    double Camper::costoPiscina(){return getOspiti()*prezzoPiscina;};
    double Camper::costoSpiaggia(){return getOspiti()*prezzoSpiaggia;};
    double Camper::costoAcqua(){return getOspiti()*prezzoAcqua;};
    double Camper::costoCorrente(){return getOspiti()*prezzoCorrente;};
    double Camper::prezzo(){
        double aux=getPrezzomin()+getOspiti()*costoPersona;
        aux=aux*aumentoStagione(getStagione());
        if(servizioPiscina()) aux+=costoPiscina();
        if(servizioSpiaggia()) aux+=costoSpiaggia();
        if(servizioAcqua()) aux+=costoAcqua()*getOspiti();
        if(servizioCorrente()) aux+=costoCorrente()*getOspiti();
        return aux;
    };
    Camper* Camper::clone() const{return new Camper(*this);};
double Camper::costoPersona=5.00;
double Camper::prezzoAcqua=0.30; //al giorno per ospite
double Camper::prezzoCorrente=0.10; //al giorno per ospite
