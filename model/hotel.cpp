#include "hotel.h"
Hotel::~Hotel(){};
Hotel::Hotel(int dimensione, int letti, int piano, double prezzo, int ospiti=0, periodo stagione=periodo::bassa, status stato=status::libero, bool disabile=false, bool piscina=true, bool spiaggia=false, pensione ristorante=pensione::colazione) :
    Residence(dimensione, letti, piano, prezzo, ospiti, stagione, stato, disabile, piscina, spiaggia),
    ristorante(ristorante)
{
    prezzoPiscina=0; //gratuita per i clienti dell'Hotel
    prezzoSpiaggia=14.50; //prezzo a camera (e non a persona)
    colazione=5.50;
    pranzo=17.50;
    cena=23.0;
};

pensione Hotel::getRistorante() const{return ristorante;};
void Hotel::setRistorante(pensione r){ristorante=r;};

double Hotel::costoRistorante(){
    double aux=colazione; //è obbligatorio fare almeno la colazione
    if(ristorante==pensione::mezza) aux+=cena;
    else if(ristorante==pensione::completa) aux=aux+pranzo+cena;
    aux=aux*getOspiti();
    return aux;
};

double Hotel::costoPiscina(){return prezzoPiscina;};
double Hotel::costoSpiaggia(){return prezzoSpiaggia;};

