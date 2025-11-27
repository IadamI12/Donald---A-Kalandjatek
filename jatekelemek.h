    #ifndef JATEKELEMEK_H_INCLUDED
    #define JATEKELEMEK_H_INCLUDED
    #include <cstdlib>
    #include <ctime>
    #include "entitas.h"
    #include <string>
    #include <sstream>
  //  #include "gtest_lite.h"
//#include "memtrace.h"
    /* A jatek vezerlesehez szukseges osztaly.
        i - a jatekallast koveto index
    */
    class Harc;
    class Jatekelem{
    int i;
    public:
        //A Jatekelem konstruktora, az indexet 1-re allitja.
        Jatekelem() : i(1) {}
        //Az indexet megnoveli eggyel, tovabblep a jatekallasban.
        void inci() {i++;}
        //Visszaadja a mostani jatekallast.
        //Visszateresi ertek: int
        int geti() const {return i;}
        //A jatek beolvasasa egy filebol.
        void kezdet(const char* fp, Jatekos& j, Harc& h);
        //A tortenet kiolvasasa egy filebol.
        std::string szoveg(const char* fp) const;
        //A jatek mentese egy fileba.
        void save(const char*fp, Jatekos& j, Harc& h) const ;
    };
    /* A kuldetesek vezerlesehez szukseges osztaly.
    */
    class Kuldetes {
    public:
        int osszead(int x, int y) const;
        int kivon(int x, int y) const;
        int lnko(int x, int y) const;
        int lkkt(int x, int y) const;
        int szamjegyek(int x, int y) const;
        int nagyobbgyok(int x, int y) const;
        int kisebbgyok(int x, int y) const;
        int difficulty(Jatekelem je) const;
        int vegrehajt(int x, int y, int melyik) const;
    };
    /* A targyak tarolasahoz, illetve a bolt vezerlesehez szukseges osztaly.
        Targy* t[10] - a targyakat ebben a tombben tarolhatjuk
    */
    class Bolt {
    Targy* t[10];
    public:
        //Targyak beolvasasa a tombbe egy filebol.
        void add(const char* fp);
        std::string getnev(int i) const
        {
            return t[i]->getnev();
        }
        //A targyak kilistazasa.
        void kilistaz() const;
        //Egy parameterkent megadott indexu targy tulajdonsagainak kilistazasa.
        void kiir(int i) const;
        //Egy targy megvetele.
        void megvesz(Jatekos& j,int a,int c);
        //A targyak altal foglalt dinamikusan allokalt memoria felszabaditasa.
        ~Bolt() {for (int i = 0; i < 10 ; i++) delete t[i];}
    };
    /* A szornyek tarolasahoz, illetve a harc vezerlesehez szukseges osztaly.
        Szorny* sz[3] - a szornyeket ebben a tombben tarolhatjuk
        int hanyadik - hanyadik szorny kovetkezik eppen a soron
        int szornyekszama - hany db szorny ellen kuzd a kalandor
    */
    class Harc {
        int hanyadik;
        int szornyekszama;
        Szorny** sz;
    public:
        //Konstruktor.
        Harc() : hanyadik(-1),szornyekszama(0),sz(NULL) {}
        //A szornyek beolvasasa egy filebol.
        void add(const char* fp);
        //A kovetkezo szornyre leptetes.
        void inchanyadik() {hanyadik++;}
        //Visszater azzal hogy hanyadik szorny van soron.
        //Visszateresi erteke: int
        int gethanyadik() const {return hanyadik;}
        //Visszater azzal hogy hany szorny van.
        //Visszateresi erteke: int
        int getszornyekszama() const {return szornyekszama;}
        //A harc vezerlese.
        bool harc(Jatekos& j,Jatekelem& je);
        //A szornyek altal foglalt dinamikusan allokalt memoria felszabaditasa.
        ~Harc() {for (int i = 0; i < szornyekszama ; i++) delete sz[i]; delete[] sz;}
    };


    #endif // JATEKELEMEK_H_INCLUDED
