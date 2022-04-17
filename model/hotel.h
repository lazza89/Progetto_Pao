#ifndef HOTEL_H
#define HOTEL_H

#include "residence.h"

enum class pensione{colazione, mezza, completa};
class Hotel: public Residence{
  private:
    pensione ristorante;
  public:
    virtual ~Hotel();
    Hotel(int, int, int, double, int, periodo, status, bool, bool, bool, pensione);
    double colazione;
    double pranzo;
    double cena;
    pensione getRistorante() const;
    void setRistorante(pensione r);
    virtual double costoRistorante();
    virtual double costoPiscina() override;
    virtual double costoSpiaggia() override;
};

#endif // HOTEL_H
