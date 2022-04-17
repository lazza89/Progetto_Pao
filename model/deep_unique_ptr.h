#ifndef DEEP_UNIQUE_PTR_H
#define DEEP_UNIQUE_PTR_H

template<class T>
class uniqueP{
  private:
    T* ptr;
  public:
    uniqueP(T* =nullptr);
    uniqueP(const uniqueP& p);
    ~uniqueP();
    bool operator==(const uniqueP& p) const;
    bool operator!=(const uniqueP& p) const;
    uniqueP& operator=(const uniqueP& p);
    T& operator*() const;
    T* operator->() const;
    T& operator[](unsigned int i) const;
    T* release();
    void reset(uniqueP p);
};

template<class T>
uniqueP<T>::uniqueP(T* t): ptr(t) {};

template<class T>
uniqueP<T>::uniqueP(const uniqueP& p): ptr(p.ptr!=nullptr ? p.ptr->clone() : nullptr) {};

template<class T>
uniqueP<T>::~uniqueP(){if(ptr) delete ptr;};

template<class T>
bool uniqueP<T>::operator==(const uniqueP& p) const{return ptr==(p.ptr);};

template<class T>
bool uniqueP<T>::operator!=(const uniqueP& p) const{return ptr!=(p.ptr);};

template<class T>
uniqueP<T>& uniqueP<T>::operator=(const uniqueP& p){
    if(this!=&p){
       if(p!= nullptr){
          delete ptr;
       }
       ptr = p.ptr ? (p.ptr)->clone() : nullptr;
    };
    return *this;
};

template<class T>
T& uniqueP<T>::operator*() const{return *ptr;};

template<class T>
T* uniqueP<T>::operator->() const{return ptr;};

template<class T>
T& uniqueP<T>::operator[](unsigned int i) const{return *(ptr+i);};

template<class T>
T* uniqueP<T>::release(){
    T aux=*this;
    this=nullptr;
    return aux;
};

template<class T>
void uniqueP<T>::reset(uniqueP p){delete *p;}

#endif // DEEP_UNIQUE_PTR_H
