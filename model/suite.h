#ifndef SUITE_H
#define SUITE_H

#include "residence.h"
#include "hotel.h"

class Suite: public Hotel{
  private:
    int n_stanze;
    bool ufficio;
    bool relax; //comprende sauna, idromassaggio
    bool servizioincamera;
  public:
    virtual ~Suite();
    Suite(int, int, int, int, double, int=0, periodo=periodo::bassa, status=status::libero, bool=false, bool=true, bool=false, pensione=pensione::colazione, bool=false, bool=false, bool=true);
    static double costoincamera;
    static double costoUfficio;
    static double costoRelax;
    int getStanze() const;
    bool getUfficio() const;
    bool getRelax() const;
    bool getServizioCamera() const;
    void setUfficio(bool);
    void setRelax(bool);
    void setServizioCamera(bool);
    virtual double costoRistorante() override;
    virtual double aumentoStagione(periodo p) override;

    virtual double prezzo() override;
    virtual Suite* clone() const override;
};

#endif // SUITE_H
