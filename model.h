#ifndef MODEL_H
#define MODEL_H
#include "model/vettore.h"
#include "model/deep_unique_ptr.h"
#include "model/residence.h"
#include "model/appartamento.h"
#include "model/hotel.h"
#include "model/camera.h"
#include "model/suite.h"
#include "model/camper.h"
#include <QDebug>


class Model{
  private:
    vettore<uniqueP<Residence>> strutture;

  public:
    Model(vettore<uniqueP<Residence>> v = vettore<uniqueP<Residence>>());
    ~Model();
    const vettore<uniqueP<Residence>>& getVettoreStrutture()const;
    vettore<uniqueP<Residence>>& getVettoreStrutture();
    uniqueP<Residence> getStruttura(unsigned int i);
    void aggiungiStruttura(Residence* const struttura);
    void deleteStruttura(vettore<uniqueP<Residence>>::iterator i);

    void ospiti(vettore<uniqueP<Residence>>::iterator i,int o);
    void stato(vettore<uniqueP<Residence>>::iterator i, status s);
    void stagione(vettore<uniqueP<Residence>>::iterator i, periodo p);
    void piscina(vettore<uniqueP<Residence>>::iterator i,bool p);
    void spiaggia(vettore<uniqueP<Residence>>::iterator i,bool s);
    void puliziaCucina(vettore<uniqueP<Residence>>::iterator i,bool c);
    void ristorante(vettore<uniqueP<Residence>>::iterator i,pensione r);
    void servizioinCamera(vettore<uniqueP<Residence>>::iterator i,bool s);
    void ufficioSuite(vettore<uniqueP<Residence>>::iterator i,bool u);
    void relaxSuite(vettore<uniqueP<Residence>>::iterator i,bool r);    
    void acquaCamper(vettore<uniqueP<Residence>>::iterator i,bool a);
    void correnteCamper(vettore<uniqueP<Residence>>::iterator i,bool c);
};

#endif // MODEL_H
