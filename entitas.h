#ifndef ENTITAS_H_INCLUDED
#define ENTITAS_H_INCLUDED
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
//#include "gtest_lite.h"
//#include "memtrace.h"
/* Az entitasok tarolasara alkalmas osztaly.
    nev - entitas neve
    maxeletero - az entitas maximalis eletereje
    curreletero - az entitas mostani eletereje
    sebzes - az entitas sebzese
*/
class Entitas {
std::string nev;
int maxeletero;
int curreletero;
int sebzes;
public:
    //Konstruktor, letrehoz egy a parameterek altal megadott objektumot.
    Entitas(const std::string& n = "",int a = 0, int b = 0, int c = 0) :  nev(n),maxeletero(a),curreletero(b),sebzes(c){}
    //Visszaadja a mostani eleterot.
    //Visszateresi erteke: int
    int getcurreletero() const {return curreletero;}
     //Visszaadja a maximalis eleterot.
     //Visszateresi erteke: int
    int getmaxeletero() const {return maxeletero;}
    //Visszaadja a sebzest.
    //Visszateresi erteke: int
    int getsebzes() const {return sebzes;}
    //Visszaadja az entitas nevet.
    //Visszateresi erteke: std::string
    std::string getnev() const{ return nev;}
    //Beallitja a mostani eleterot a parameterkent megadott "a"  ertekre.
    void setcurreletero(int a) {curreletero = a;}
    //Beallitja a maximalis eleterot a parameterkent megadott "a"  ertekre.
    void setmaxeletero(int a) {maxeletero = a;}
    //Beallitja a sebzest a parameterkent megadott "a"  ertekre.
    void setsebzes(int a) {sebzes = a;}
    //Virtualis destruktor, mivel vannak akik tole orokolnek, igy ez fontos.
    virtual ~Entitas() {}
};
/*
A jatekos tarolasara alkalmas osztaly.
Az Entitastol orokol, egy uj privat adattag:
    arany - a jatekos aranya
*/
class Jatekos : public Entitas {
int arany;
public:
    //A Jatekos osztaly konstruktora, mivel a jatekos elo meg van hatarozva, igy ez egy elore determinalt adat.
    Jatekos() : Entitas("Donald",50,50,5), arany(0) {}
    //A jatekos aranyat a parameterkent megadott "i" ertekkel noveli.
    void kaparany(int i) {arany += i;}
    //Visszaadja a jatekos aranyat.
    //Visszateresi erteke: int
    int getarany() const {return arany;}
};
/*
A szornyek tarolasara alkalmas osztaly.
Funkcionalitasa megegyezik az Entitaseval, azonban jobban lathatova teszi a kodot.
*/
class Szorny : public Entitas {
public:
    //A Szorny osztaly konstruktora.
    Szorny(const std::string& n = "",int a = 0, int b = 0, int c = 0) : Entitas(n,a,b,c){}
};
/*
A targyak tarolasara alkalmas osztaly.
Az Entitastol orokol, ket uj privat adattag:
    ar - a targynak az ara
    kinezet - a targy kinezete
*/
class Targy : public Entitas{
int ar;
std::string kinezet;
public:
    //A Targy osztaly konstruktora.
    Targy(const std::string& n = "",int a = 0,int b = 0, int c = 0, int d = 0, std::string kinezetfile = "") : Entitas(n,a,b,c) ,ar(d),kinezet(kinezetfile) {}
    //Visszaadja a targy arat.
    //Visszateresi erteke: int
    int getar() const {return ar;}
    //Visszaadja a targy kinezetet.
    //Visszateresi erteke: std::string
    std::string getkinezet() const {return kinezet;}
};


#endif // ENTITAS_H_INCLUDED
