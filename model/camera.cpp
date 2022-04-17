#include "camera.h"

Camera::~Camera(){};
Camera::Camera(int dimensione, int letti, int piano, double prezzo, int ospiti, periodo stagione, status stato, bool disabile, bool piscina, bool spiaggia, pensione ristorante):
    Hotel(dimensione,letti,piano ,prezzo, ospiti, stagione, stato, disabile, piscina, spiaggia, ristorante)
{};

double Camera::prezzo(){
    double aux=getPrezzomin();
    aux=aux*aumentoStagione(getStagione());
    aux+=costoRistorante();
    if(servizioPiscina()) aux+=costoPiscina();
    if(servizioSpiaggia()) aux+=costoSpiaggia();
    return aux;
};
Camera* Camera::clone() const{return new Camera(*this);};
