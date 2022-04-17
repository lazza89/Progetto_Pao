#include "appartamento.h"

    Appartamento::~Appartamento(){};
    Appartamento::Appartamento(int dimensione, int stanze, int letti, int piano, double prezzo, int ospiti, periodo stagione, status status, bool disabile, bool piscina, bool spiaggia, bool lavatrice, fornelli cucina, bool pulizia):
        Residence(dimensione, letti, piano, prezzo, ospiti, stagione, status, disabile, piscina, spiaggia),
        n_stanze(stanze),
        lavatrice(lavatrice),
        cucina(cucina),
        puliziaCucina(pulizia)
    {};

    int Appartamento::getStanze() const{return n_stanze;};
    bool Appartamento::getLavatrice() const{return lavatrice;};
    fornelli Appartamento::getCucina() const{return cucina;};
    bool Appartamento::servizioPuliziaCucina() const{return puliziaCucina;};
    void Appartamento::setPuliziaCucina(bool pulizia){puliziaCucina=pulizia;};
    double Appartamento::puliziaFinale(){
        double aux=costopulizia;
        if(servizioPuliziaCucina()) aux+=costopuliziacucina;
        return aux;
    };
    double Appartamento::costoPiscina(){return getOspiti()*prezzoPiscina;};
    double Appartamento::costoSpiaggia(){return getOspiti()*prezzoSpiaggia;};
    double Appartamento::prezzo(){
        double aux=getPrezzomin()+getOspiti()*costopersona;
        aux+=puliziaFinale();
        aux=aux*aumentoStagione(getStagione());
        if(servizioPiscina()) aux+=costoPiscina();
        if(servizioSpiaggia()) aux+=costoSpiaggia();
        return aux;
    }
    Appartamento* Appartamento::clone() const{return new Appartamento(*this);};
    double Appartamento::costopersona=6.50;
    double Appartamento::costopulizia=25.0;
    double Appartamento::costopuliziacucina=15.0;
