#ifndef RESIDENCE_H
#define RESIDENCE_H

enum class periodo{bassa, media, alta};
enum class status{libero, occupato, lavori};
class Residence{
  private:
    int dimensione; //in Mq
    int n_letti; //max letti disponibili
    int n_ospiti; //ospiti realmente presenti nella struttura
    int piano; //0=piano terra
    double prezzomin;
    periodo stagione;
    status stato;
    bool disabile;
    bool piscina;
    bool spiaggia;
  public:
    virtual ~Residence();
    Residence(int, int, int, double, int, periodo, status, bool, bool, bool);
    virtual double costoPiscina()=0;
    virtual double costoSpiaggia()=0;
    virtual double prezzo()=0;
    virtual double aumentoStagione(periodo p); //aumento percentuale
    double prezzoMinStagione();
    int getDimensione()const;
    int getLetti()const;
    int getOspiti()const;
    int getPiano()const;
    double getPrezzomin()const;
    bool getDisabile()const;
    status getStato()const;
    periodo getStagione()const;
    bool servizioPiscina()const;
    bool servizioSpiaggia()const;
    void setOspiti(int o);
    void setStato(status s);
    void setStagione(periodo p);
    void setPiscina(bool p);
    void setSpiaggia(bool s);
    virtual Residence* clone() const=0;
protected:
    double prezzoPiscina;
    double prezzoSpiaggia;
};

#endif // RESIDENCE_H
