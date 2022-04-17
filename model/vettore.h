#ifndef VETTORE_H
#define VETTORE_H
#include<iostream>

template <class T> class vettore;
template <class T> std::ostream& operator<< (std::ostream& os, const vettore<T>& a);

template <class T>
class vettore {
    friend std::ostream& operator << <T>(std::ostream&, const vettore<T>&);
 private:
    T* x;
    int dimensione, capienza;
    static T* copia(T* t, int dim, int cap);
    static void distruggi(const T* t);
 public:
    vettore(const T& t = T(), int k = 0);
    vettore(const vettore& t);
    vettore& operator=(const vettore& t);
    ~vettore();
    unsigned int size() const;
    unsigned int capacity() const;
    void resize(); //raddoppia la capienza
    bool empty() const;
    bool full() const;
    bool operator==(const vettore& a) const;
    bool operator!=(const vettore& a) const;

    class iterator {
        friend class vettore<T>;        
     private:
        T* i;
        bool isPastTheEnd;
        iterator(T* e, bool pte = false); // Convertitore da T* a iterator
     public:
        iterator();
        iterator(const iterator& it);
        iterator& operator=(iterator it);
        T& operator*() const;
        T* operator->() const;
        iterator& operator++(); //prefisso
        iterator operator++(int); //postfisso
        iterator& operator--(); //prefisso
        iterator operator--(int); //postfisso
        iterator operator+(int n) const;
        iterator operator-(int n) const;
        iterator& operator+=(int n);
        iterator& operator-=(int n);
        bool operator==(iterator it) const;
        bool operator!=(iterator it) const;
        bool operator<(iterator it) const;
        bool operator>(iterator it) const;
        bool operator<=(iterator it) const;
        bool operator>=(iterator it) const;
    };

    class const_iterator {
        friend class vettore<T>;
     private:
        T* i;
        bool isPastTheEnd;        
        const_iterator(T* e, bool pte = false); // Convertitore da T* a const_iterator
     public:
        const_iterator();
        const_iterator(const const_iterator& cit);
        const_iterator& operator=(const_iterator cit);
        const T& operator*() const;
        const T* operator->() const;
        const_iterator& operator++(); //prefisso
        const_iterator operator++(int); //postfisso
        const_iterator& operator--(); //prefisso
        const_iterator operator--(int); //postfisso
        const_iterator operator+(int n) const;
        const_iterator operator-(int n) const;
        bool operator==(const_iterator cit) const;
        bool operator!=(const_iterator cit) const;
        bool operator<(const_iterator cit) const;
        bool operator>(const_iterator cit) const;
        bool operator<=(const_iterator cit) const;
        bool operator>=(const_iterator cit) const;
    };

    T& operator[] (int pos);
    T& operator[] (vettore::iterator pos) const;
    const T& operator[] (vettore::const_iterator pos) const;
    vettore<T>& append(const vettore<T>& t);
    vettore<T> operator+(const vettore<T>& v) const;
    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void push_back(const T& t);
    void insert(const T& t, iterator it);
    void pop_back();
    T erase(iterator position);
    void clear();
};

// Implementazione dei metodi
template <class T>
std::ostream& operator<< (std::ostream& os, const vettore<T>& a){
    for (typename vettore<T>::const_iterator it=a.cbegin(); it!=a.cend(); it++){
        os <<*it <<" ";
    }
    return os;
}

template<class T>  //static T* copia
T* vettore<T>::copia(T *t, int dim, int cap){
    T* a=new T[cap];
    for (int i=0; i<dim; ++i)
        a[i]=t[i];
    return a;
}

template <class T>
void vettore<T>::distruggi(const T* t){
    delete[] t;
}

template<class T>
vettore<T>::vettore(const T& t, int k) : x(k==0 ? nullptr : new T[k*2]), dimensione(k), capienza(k*2){
    for (int i=0; i<dimensione; i++)
        x[i]=t;
}

template<class T>
vettore<T>::vettore(const vettore& t): x(copia(t.x, t.dimensione, t.capienza)), dimensione(t.dimensione), capienza(t.capienza) {}

template<class T>
vettore<T>& vettore<T>::operator=(const vettore& t){
    if (this!= &t){
        delete[] x;
        x=copia(t, t.dimensione, t.capienza);
        dimensione=t.dimensione;
        capienza=t.capienza;
    }
    return *this;
}

template<class T>
vettore<T>::~vettore(){
    delete[] x;
}

template<class T>
unsigned int vettore<T>::size() const{
    return dimensione;
}

template<class T>
unsigned int vettore<T>::capacity() const{
    return capienza;
}

template<class T>
void vettore<T>::resize(){
    if (capienza==0) ++capienza;
    x=copia(x, dimensione, capienza*2);
    capienza=capienza*2;
}

template<class T>
bool vettore<T>::empty() const{
    return dimensione==0;
}

template<class T>
bool vettore<T>::full() const{
    return dimensione==capienza;
}

template<class T>
bool vettore<T>::operator==(const vettore &a) const{
    if (this== &a) return true;
    if (dimensione!=a.dimensione) return false;
    for (int i=0; i<dimensione; i++)
        if (x[i]!=a[i])
            return false;
    return true;
}

template<class T>
bool vettore<T>::operator!=(const vettore &a) const{
    if (this== &a) return false;
    if (dimensione!=a.dimensione) return true;
    bool aux=false;
    for (int i=0; i<dimensione; i++)
        if (x[i]!=a[i])
            aux=true;
    return aux;
}


//iterator
template<class T>  //implementazione convertitore da T* a iterator
vettore<T>::iterator::iterator(T *e, bool pte): i(e), isPastTheEnd(pte) {}

template<class T> //costruttore di default
vettore<T>::iterator::iterator(): i(nullptr), isPastTheEnd(false) {}

template <class T>
vettore<T>::iterator::iterator(const vettore<T>::iterator& it):i(it.i){}

template<class T>
typename vettore<T>::iterator& vettore<T>::iterator::operator=(vettore::iterator it){
    i=it.i;
    return *this;
}

template<class T>
T& vettore<T>::iterator::operator*() const{
    return *i;
}

template<class T>
T* vettore<T>::iterator::operator->() const{
    return &(i);
}

template<class T>
typename vettore<T>::iterator& vettore<T>::iterator::operator++(){ //prefisso
    if (i){
        if (!isPastTheEnd){
            if (i+1==nullptr) {++i; isPastTheEnd=true;}
            else ++i;
        }
    }
    return *this;
}

template<class T>
typename vettore<T>::iterator vettore<T>::iterator::operator++(int){
       iterator aux=i;
       if (i){
        if (!isPastTheEnd){
            if (i+1==nullptr) {i++; isPastTheEnd=true;}
            else i++;
        }
    }
    return aux;
}

template<class T>
typename vettore<T>::iterator& vettore<T>::iterator::operator--(){ //prefisso
    if (i){
        if (i-1>=0){
            --i; if (isPastTheEnd) isPastTheEnd=false;
        }
    }
    return *this;
}

template<class T>
typename vettore<T>::iterator vettore<T>::iterator::operator--(int){ //postfisso
       int aux=i;
       if (i){
           if (i-1>=0){
               i--; if (isPastTheEnd) isPastTheEnd=false;
           }
       }
    return aux;
}

template<class T>
typename vettore<T>::iterator vettore<T>::iterator::operator+(int n) const{
    iterator aux=i;
    if (aux.i){
        if (!aux.isPastTheEnd){
            if (i+n*sizeof(T)==nullptr) {aux.i+=n; aux.isPastTheEnd=true;}
            else aux.i=i+n;
        }
    }
    return aux;
}

template<class T>
typename vettore<T>::iterator vettore<T>::iterator::operator-(int n) const{
    iterator aux=i;
    if (aux.i){
        if (aux.isPastTheEnd) {aux.i-=n; aux.isPastTheEnd=false;}
        else aux.i=i-n;
    }
    return aux;
}

template<class T>
typename vettore<T>::iterator& vettore<T>::iterator::operator+=(int n){
    if (i){
        if (!isPastTheEnd){
            if (i+n*sizeof(T)==nullptr) {i+=n; isPastTheEnd=true;}
            else i+=n;
        }
    }
    return *this;
}

template<class T>
typename vettore<T>::iterator& vettore<T>::iterator::operator-=(int n){
    if (i){
        if (isPastTheEnd) {i-=n; isPastTheEnd=false;}
        else i-=n;
    }
    return *this;
}

template<class T>
bool vettore<T>::iterator::operator==(vettore::iterator it) const{
    return i==it.i;
}

template<class T>
bool vettore<T>::iterator::operator!=(vettore::iterator it) const{
    return i!=it.i;
}

template<class T>
bool vettore<T>::iterator::operator<(vettore::iterator it) const{
    return i<it.i;
}

template<class T>
bool vettore<T>::iterator::operator>(vettore::iterator it) const{
    return i>it.i;
}

template<class T>
bool vettore<T>::iterator::operator<=(vettore::iterator it) const{
    return i<=it.i;
}

template<class T>
bool vettore<T>::iterator::operator>=(vettore::iterator it) const{
    return i>=it.i;
}

//const_iterator
template<class T>
vettore<T>::const_iterator::const_iterator(T *e, bool pte): i(e), isPastTheEnd(pte) {}

template<class T>
vettore<T>::const_iterator::const_iterator(): i(nullptr), isPastTheEnd(false) {}

template <class T>
vettore<T>::const_iterator::const_iterator(const vettore<T>::const_iterator& cit):i(cit.i){}

template<class T>
typename vettore<T>::const_iterator& vettore<T>::const_iterator::operator=(vettore::const_iterator it){
    i=it.i;
    return *this;
}

template<class T>
const T& vettore<T>::const_iterator::operator*() const{
    return *i;
}

template<class T>
const T* vettore<T>::const_iterator::operator->() const{
    return &(i);
}

template<class T>
typename vettore<T>::const_iterator& vettore<T>::const_iterator::operator++(){ //prefisso
    if(i){
        if(!isPastTheEnd){
            if(i+sizeof(T)==nullptr) {++i; isPastTheEnd=true;}
            else ++i;
        }
    }
    return *this;
}

template<class T>
typename vettore<T>::const_iterator vettore<T>::const_iterator::operator++(int){ //postfisso
       const_iterator aux=i;
       if (i){
        if (!isPastTheEnd){
            if (i+1==nullptr) {i++; isPastTheEnd=true;}
            else i++;
        }
    }
    return aux;
}

template<class T>
typename vettore<T>::const_iterator& vettore<T>::const_iterator::operator--(){ //prefisso
    if (i) {
        if (i-1>=0){
            --i; if (isPastTheEnd) isPastTheEnd=false;
        }
    }
    return *this;
}

template<class T>
typename vettore<T>::const_iterator vettore<T>::const_iterator::operator--(int){ //postfisso
       const_iterator aux=i;
       if (i) {
           if (i-1>=0){
               i--; if (isPastTheEnd) isPastTheEnd=false;
           }
       }
    return aux;
}

template<class T>
typename vettore<T>::const_iterator vettore<T>::const_iterator::operator+(int n) const{
    const_iterator aux=i;
    if (aux.i){
        if (!aux.isPastTheEnd){
            if (i+n*sizeof(T)==nullptr) {aux.i+=n; aux.isPastTheEnd=true;}
            else aux.i+=n;
        }
    }
    return aux;
}

template<class T>
typename vettore<T>::const_iterator vettore<T>::const_iterator::operator-(int n) const{
    const_iterator aux=i;
    if (aux.i){
        if (aux.isPastTheEnd) {aux.i-=n; aux.isPastTheEnd=false;}
        else aux.i-=n;
    }
    return aux;
}

template<class T>
bool vettore<T>::const_iterator::operator==(vettore::const_iterator cit) const{
    return i==cit.i;
}

template<class T>
bool vettore<T>::const_iterator::operator!=(vettore::const_iterator cit) const{
    return i!=cit.i;
}

template<class T>
bool vettore<T>::const_iterator::operator<(vettore::const_iterator cit) const{
    return i<cit.i;
}

template<class T>
bool vettore<T>::const_iterator::operator>(vettore::const_iterator cit) const{
    return i>cit.i;
}

template<class T>
bool vettore<T>::const_iterator::operator<=(vettore::const_iterator cit) const{
    return i<=cit.i;
}

template<class T>
bool vettore<T>::const_iterator::operator>=(vettore::const_iterator cit) const{
    return i>=cit.i;
}


//altri metodi di vettore
template<class T>
T& vettore<T>::operator[](int pos) {
    return *(x+pos);
}

template<class T>
T& vettore<T>::operator[](vettore::iterator pos) const{
    return *(pos.i);
}

template<class T>
const T& vettore<T>::operator[](vettore::const_iterator pos) const{
    return *(pos.i);
}

template <class T>
vettore<T>& vettore<T>::append(const vettore<T>& t){
    if(t.size!=0){
        T* aux=new T[capienza=size()+t.size()];
        for(unsigned int i=0; i<dimensione; ++i){
            aux[i]=x[i];
        }
        for(unsigned int i=0; i<t.dimensione; ++i){
            aux[dimensione+i]=t[i];
        }
        dimensione+=t.dimensione;
        delete [] x;
        x=aux;
    }
    return *this;
}

template <class T>
vettore<T> vettore<T>::operator+(const vettore<T> &v) const{
    vettore<T> aux(*this);
    aux.append(v);
    return aux;
}

template<class T>
typename vettore<T>::iterator vettore<T>::begin() const{
    if (empty()) return nullptr;
    return &x[0];
}

template<class T>
typename vettore<T>::iterator vettore<T>::end() const{
    if (empty()) return nullptr;
    return iterator(&x[dimensione], true);
}

template<class T>
typename vettore<T>::const_iterator vettore<T>::cbegin() const{
    if (empty()) return nullptr;
    return &x[0];
}

template<class T>
typename vettore<T>::const_iterator vettore<T>::cend() const{
    if (empty()) return nullptr;
    return const_iterator(&x[dimensione], true);
}

template<class T>
const T& vettore<T>::front() const{
        if(!empty()) return x[0];
}

template<class T>
T& vettore<T>::front(){
       if(!empty()) return x[0];
}

template<class T>
const T& vettore<T>::back() const{
        if(!empty()) return x[dimensione-1];
}

template<class T>
T& vettore<T>::back(){
       if(!empty()) return x[dimensione-1];
}

template<class T>
void vettore<T>::push_back(const T &t){
    if (full()) resize();
    x[dimensione]=t;
    dimensione++;
}

template <class T>
void vettore<T>::insert(const T& t, iterator it){
    if(it==end()){
      push_back(t);
    }
    else{
        if(dimensione==capienza) resize();
        iterator aux=end()+1;
        for(; aux!=it; aux--) (*aux)=(*aux-1);
        (*aux)=t;
    }
}

template<class T>
void vettore<T>::pop_back(){
    if (!empty()){
        delete x[dimensione];
        dimensione--;
    }
}

template<class T>
T vettore<T>::erase(vettore::iterator position){
    T aux=*position;
    for (; position!=end(); position++){
        *position=*(position+1);
    }
    dimensione--;
    return aux;
}

template<class T>
void vettore<T>::clear(){
    delete[] x;
    x=new T[capienza];
    dimensione=0;
}

#endif // VETTORE_H
