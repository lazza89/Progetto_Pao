#ifndef APPARTAMENTO_H
#define APPARTAMENTO_H

#include "residence.h"

enum class fornelli{gas, induzione};
class Appartamento: public Residence{
  private:
    int n_stanze;
    bool lavatrice; //true=lavatrice in appartamento
    fornelli cucina;
    bool puliziaCucina;  //true=richiesta la pulizia della cucina, false=non richiesta)
  public:
    virtual ~Appartamento();
    Appartamento(int, int, int, int, double, int=0, periodo=periodo::bassa, status=status::libero, bool=false, bool=false, bool=false, bool=false, fornelli=fornelli::gas, bool=true);
    static double costopersona;
    static double costopulizia;
    static double costopuliziacucina;
    int getStanze() const;
    bool getLavatrice() const;
    fornelli getCucina() const;
    bool servizioPuliziaCucina() const;
    void setPuliziaCucina(bool c);
    virtual double puliziaFinale();
    virtual double costoPiscina() override;
    virtual double costoSpiaggia() override;
    virtual double prezzo() override;
    virtual Appartamento* clone() const override;
};

#endif // APPARTAMENTO_H
