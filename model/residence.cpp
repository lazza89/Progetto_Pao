#include "residence.h"

Residence::~Residence(){};
Residence::Residence(int dimensione, int letti, int piano, double prezzo, int ospiti=0, periodo stagione=periodo::bassa, status stato=status::libero, bool disabile=false, bool piscina=false, bool spiaggia=false):
    dimensione(dimensione),
    n_letti(letti),
    n_ospiti(ospiti),
    piano(piano),
    prezzomin(prezzo),
    stagione(stagione),
    stato(stato),
    disabile(disabile),
    piscina(piscina),
    spiaggia(spiaggia),
    prezzoPiscina(3.20), //a persona
    prezzoSpiaggia(4.50) //a persona
{};

double Residence::aumentoStagione(periodo p){ //aumento percentuale
    if(p==periodo::alta) return 1.45;
    else if(p==periodo::media) return 1.20;
    else return 1.0;
  };
double Residence::prezzoMinStagione(){return getPrezzomin()*aumentoStagione(getStagione());};

int Residence::getDimensione() const{return dimensione;};
int Residence::getLetti() const{return n_letti;};
int Residence::getOspiti() const{return n_ospiti;};
int Residence::getPiano() const{return piano;};
double Residence::getPrezzomin() const{return prezzomin;}
bool Residence::getDisabile() const{return disabile;};
status Residence::getStato() const{return stato;};
periodo Residence::getStagione() const{return stagione;};
bool Residence::servizioPiscina() const{return piscina;};
bool Residence::servizioSpiaggia() const{return spiaggia;};
void Residence::setOspiti(int o){n_ospiti=o;};
void Residence::setStato(status s){stato=s;};
void Residence::setStagione(periodo p=periodo::bassa){stagione=p;};
void Residence::setPiscina(bool p=false){piscina=p;};
void Residence::setSpiaggia(bool s=false){spiaggia=s;};
