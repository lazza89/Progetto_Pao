#include "suite.h"
#include <QDebug>

Suite::~Suite(){};
Suite::Suite(int dimensione, int stanze, int letti, int piano, double prezzo, int ospiti, periodo stagione, status stato, bool disabile, bool piscina, bool spiaggia, pensione ristorante, bool ufficio, bool relax, bool serviziocamera):
    Hotel(dimensione, letti, piano, prezzo ,ospiti, stagione, stato, disabile, piscina, spiaggia, ristorante),
    n_stanze(stanze),
    ufficio(ufficio),
    relax(relax),
    servizioincamera(serviziocamera)
{
    colazione=8.50;
    pranzo=25;
    cena=35;
};

int Suite::getStanze() const{return n_stanze;};
bool Suite::getUfficio() const{return ufficio;};
bool Suite::getRelax() const{return relax;};
bool Suite::getServizioCamera() const{return servizioincamera;};
void Suite::setUfficio(bool u){ufficio=u;};
void Suite::setRelax(bool r){relax=r;};
void Suite::setServizioCamera(bool s){servizioincamera=s;};
double Suite::costoRistorante(){
    double aux=colazione;
    if(getRistorante()==pensione::mezza) aux+=cena;
    else if(getRistorante()==pensione::completa) aux=aux+pranzo+cena;
    if(servizioincamera) aux=aux*costoincamera;
    aux=aux*getOspiti();
    return aux;
};
double Suite::aumentoStagione(periodo p){
    if(p==periodo::alta) return 1.5;
    else if(p==periodo::media) return 1.35;
    else return 1.0;
}
double Suite::prezzo(){
    double aux=getPrezzomin();
    if(ufficio) aux+=costoUfficio;
    if(relax) aux+=costoRelax;
    aux=aux*aumentoStagione(getStagione());
    aux+=costoRistorante();
    if(servizioPiscina()) aux+=costoPiscina();
    if(servizioSpiaggia()) aux+=costoSpiaggia();
    return aux;
};
Suite* Suite::clone() const{return new Suite(*this);};
double Suite::costoincamera=1.4;
double Suite::costoUfficio=50.0;
double Suite::costoRelax=70.0;
