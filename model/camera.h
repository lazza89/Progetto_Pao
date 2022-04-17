#ifndef CAMERA_H
#define CAMERA_H

#include "residence.h"
#include "hotel.h"

class Camera: public Hotel{
  public:
    virtual ~Camera();
    Camera(int, int, int, double, int=0, periodo=periodo::bassa, status=status::libero, bool=false, bool=true, bool=false, pensione=pensione::colazione);
    virtual double prezzo() override;
    virtual Camera* clone() const override;
};

#endif // CAMERA_H
