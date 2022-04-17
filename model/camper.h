#ifndef CAMPER_H
#define CAMPER_H

#include "residence.h"

class Camper: public Residence{
 private:
    bool acqua;
    bool corrente;
 public:
    virtual ~Camper();
    Camper(int, double, int=0, int=0, int=0, periodo=periodo::bassa, status=status::libero, bool=false, bool=false, bool=false, bool=true, bool=true);
    static double costoPersona;
    static double prezzoAcqua;
    static double prezzoCorrente;
    bool servizioAcqua() const;
    bool servizioCorrente() const;
    void setAcqua (bool a);
    void setCorrente (bool c);
    virtual double costoPiscina() override;
    virtual double costoSpiaggia() override;
    virtual double costoAcqua();
    virtual double costoCorrente();
    virtual double prezzo() override;
    virtual Camper* clone() const override;
};

#endif // CAMPER_H
