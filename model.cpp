#include "model.h"

    Model::Model(vettore<uniqueP<Residence>> v): strutture(v){};
    Model::~Model() {strutture.clear();}
    const vettore<uniqueP<Residence>>& Model::getVettoreStrutture()const{return strutture;};
    vettore<uniqueP<Residence>>& Model::getVettoreStrutture(){return strutture;};
    uniqueP<Residence> Model::getStruttura(unsigned int i){return strutture[i];};
    void Model::aggiungiStruttura(Residence* const struttura) {strutture.push_back(struttura);};
    void Model::deleteStruttura(vettore<uniqueP<Residence>>::iterator i){strutture.erase(i);};

    void Model::ospiti(vettore<uniqueP<Residence>>::iterator i, int o){strutture[i]->Residence::setOspiti(o);};
    void Model::stato(vettore<uniqueP<Residence>>::iterator i, status s=status::libero){strutture[i]->Residence::setStato(s);};
    void Model::stagione(vettore<uniqueP<Residence>>::iterator i, periodo p=periodo::bassa){strutture[i]->Residence::setStagione(p);};
    void Model::piscina(vettore<uniqueP<Residence>>::iterator i,bool p=true){strutture[i]->Residence::setPiscina(p);};
    void Model::spiaggia(vettore<uniqueP<Residence>>::iterator i,bool s=false){strutture[i]->Residence::setSpiaggia(s);};
    void Model::puliziaCucina(vettore<uniqueP<Residence>>::iterator i,bool c=true){dynamic_cast<Appartamento*>(&*strutture[i])->Appartamento::setPuliziaCucina(c);};
    void Model::ristorante(vettore<uniqueP<Residence>>::iterator i,pensione r=pensione::colazione){dynamic_cast<Hotel*>(&*strutture[i])->Hotel::setRistorante(r);};
    void Model::servizioinCamera(vettore<uniqueP<Residence>>::iterator i,bool s=true){dynamic_cast<Suite*>(&*strutture[i])->Suite::setServizioCamera(s);};
    void Model::ufficioSuite(vettore<uniqueP<Residence>>::iterator i,bool u=false){dynamic_cast<Suite*>(&*strutture[i])->Suite::setUfficio(u);};
    void Model::relaxSuite(vettore<uniqueP<Residence>>::iterator i,bool r=false){dynamic_cast<Suite*>(&*strutture[i])->Suite::setRelax(r);};
    void Model::acquaCamper(vettore<uniqueP<Residence>>::iterator i, bool a=true){dynamic_cast<Camper*>(&*strutture[i])->Camper::setAcqua(a);};
    void Model::correnteCamper(vettore<uniqueP<Residence>>::iterator i, bool c=true){dynamic_cast<Camper*>(&*strutture[i])->Camper::setCorrente(c);};

