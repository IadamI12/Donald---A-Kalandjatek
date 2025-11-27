#include "jatekelemek.h"
//#include "gtest_lite.h"
//#include "memtrace.h"
/*
A jatek betoltese egy filebol.
    parameterek:
        fp (filenev) - const char*
        j (jatekos) - Jatekos&
        h (szornyek) - Harc&
*/
void Jatekelem::kezdet(const char* fp, Jatekos& j, Harc& h)
{
            std::ifstream file(fp);
            int szam;
            file >> szam;
            int hanyadik;
            file >> hanyadik;
            for (int i = -1; i < hanyadik; i++)
                h.inchanyadik();
            for (int j = 0; j < szam; j++)
                i++;
            file >> szam;
            j.setmaxeletero(szam);
            file >> szam;
            j.setcurreletero(szam);
            file >> szam;
            j.setsebzes(szam);
            file >> szam;
            j.kaparany(szam);
            file.close();
    }
/*
A szoveg kiolvasasa egy filebol.
    parameterek:
        fp (filenev) - const char*
*/
std::string Jatekelem::szoveg(const char* fp) const
{
std::ifstream file(fp);
std::string paragrafus;
for (int j = 0; j < i; j++)
    getline(file,paragrafus,'$');
file.close();
return paragrafus;
}
/*
A jatek lementese egy fileba.
    parameterek:
        fp (filenev) - const char*
        j (jatekos) - Jatekos&
*/
void Jatekelem::save(const char*fp, Jatekos& j, Harc& h) const
{
            std::ofstream file(fp);
            file << i-1 << std::endl;
            file << h.gethanyadik() << std::endl;
            file << j.getmaxeletero() << std::endl;
            file << j.getcurreletero() << std::endl;
            file << j.getsebzes() << std::endl;
            file << j.getarany() << std::endl;
            file.close();
}
/*
A parameterkent megadott szamok altal kepzett masodfoku egyenlet nagyobbik gyoket adja vissza.
    parameterek:
        x (egyik valtozo) - int
        y (masik valtozo) - int
    visszateresi ertek:
        eredmeny - int
*/

int Kuldetes::nagyobbgyok(int x, int y) const
{
#ifndef CPORTA
    std::cout << "x^2 " << -1*x + -1*y << "x + " << x * y << " \nAdd meg a kifejezes nagyobbik gyoket! ";
#endif
    if (x > y)
        return x;
    return y;
}

/*
A parameterkent megadott szamok altal kepzett masodfoku egyenlet kisebbik gyoket adja vissza.
    parameterek:
        x (egyik valtozo) - int
        y (masik valtozo) - int
    visszateresi ertek:
        eredmeny - int
*/
int Kuldetes::kisebbgyok(int x, int y) const
{
#ifndef CPORTA
    std::cout << "x^2 " << -1*x + -1*y << "x + " << x * y << " \nAdd meg a kifejezes kisebbik gyoket! ";
#endif
    if (x < y)
        return x;
    return y;
}
/*
A parameterkent megadott szamok legnagyobb kozos osztojat adja vissza.
    parameterek:
        x (egyik valtozo) - int
        y (masik valtozo) - int
    visszateresi ertek:
        eredmeny - int
*/
int Kuldetes::lnko(int x, int y) const
{
#ifndef CPORTA
    std::cout << x + 1 << " es " << y + 1<< " legnagyobb kozos osztoja: ";
#endif
    int v1 = x+1;
    int v2 = y+1;
    while(v2 != 0)
    {
        int temp = v2;
        v2 = v1 % v2;
        v1 = temp;
    }
    return v1;
}
/*
A parameterkent megadott szamok legkisebb kozos tobbszoroset adja vissza.
    parameterek:
        x (egyik valtozo) - int
        y (masik valtozo) - int
    visszateresi ertek:
        eredmeny - int
*/
int Kuldetes::lkkt(int x, int y) const
{
#ifndef CPORTA
       std::cout << x << " es " << y << " legkisebb kozos tobbszorose: ";
#endif
    int eredmeny = x*y;
    int v = x;
        while(y != 0)
    {
        int temp = y;
        y = v % y;
        v = temp;
    }
       return eredmeny/v;
}
/*
A parameterkent megadott szamok osszegenek szamjegyeinek az osszeget adja vissza.
    parameterek:
        x (egyik valtozo) - int
        y (masik valtozo) - int
    visszateresi ertek:
        eredmeny - int
*/
int Kuldetes::szamjegyek(int x, int y) const
{
#ifndef CPORTA
        std::cout << x << " es " << y << " osszegenek szamjegyeinek az osszege: ";
#endif
        int eredmeny = x + y;
        int vegleges = 0;
        while(eredmeny > 0)
        {
            vegleges += eredmeny % 10;
            eredmeny = eredmeny / 10;
        }
    return vegleges;
}
/*
A parameterkent megadott szamok osszeget adja vissza.
    parameterek:
        x (egyik valtozo) - int
        y (masik valtozo) - int
    visszateresi ertek:
        eredmeny - int
*/
 int Kuldetes::osszead(int x, int y) const
    {
#ifndef CPORTA
        std::cout << x << " + " << y << " = ";
#endif
        return x + y;
    }
/*
A parameterkent megadott szamok kulonbseget adja vissza.
    parameterek:
        x (egyik valtozo) - int
        y (masik valtozo) - int
    visszateresi ertek:
        eredmeny - int
*/
int Kuldetes::kivon(int x, int y) const
    {
#ifndef CPORTA
        std::cout << x << " - " << y << " = ";
#endif
        return x - y;
    }

 /*
 A kuldetesek nehezseget szamítja ki, a jatek allasa alapjan.
    parameterek:
        je (jatekallas) - Jatekelem
    visszateresi ertek
        jatekallas - int
 */

int Kuldetes::difficulty(Jatekelem je) const{
    int x = 1;
    for (int i = 0; i < ((je.geti()/3)+1); i++)
        x = x*10;
    return x;
    }
 /*
 A kuldetesek kozul  vegrehajtja a "melyik" parametereben kapottat.
    parameterek:
        int x - egyik random szam
        int y - masik random szam
        int melyik - melyik feladat lett kisorsolva
    visszateresi ertek
        a valasztott kuldetes eredmenye - int
 */
int Kuldetes::vegrehajt(int x, int y, int melyik) const
    {
        int eredmeny;
        if (melyik == 1)
            eredmeny = osszead(x,y);
        else if (melyik == 2)
            eredmeny = kivon(x,y);
        else if (melyik == 3)
            eredmeny= lnko(x%50,y%50);
        else if (melyik == 4)
            eredmeny = lkkt(x%50,y%50);
        else if (melyik == 5)
            eredmeny = szamjegyek(x,y);
        else if (melyik == 6)
            eredmeny = nagyobbgyok(x%20,y%20);
        else if (melyik == 7)
            eredmeny = kisebbgyok(x%20,y%20);
        return eredmeny;
    }

 /*
 A boltban tarolando targyak beolvasasa egy filebol.
    parameterek:
        fp (filenev) - const char* fp
 */
void Bolt::add(const char* fp)
{
    std::ifstream file(fp);
    std::string nev;
    std::string kinez;
    int maxel,currel,seb,ar;
    for (int i = 0; i < 10; i++)
    {
        getline(file,nev);
        getline(file,kinez,'$');
        file >> maxel;
        file >> currel;
        file >> seb;
        file >> ar;
        file.ignore();
        t[i] = new Targy(nev,maxel,currel,seb,ar,kinez);
    }
    file.close();
}


 /*
 Kilistazza a boltban tarolt elemeket.
 */
void Bolt::kilistaz() const
    {
        for (int i = 0; i < 10; i ++){
            std::cout << "[" << i << "] ";
            std::cout << t[i]->getnev();
            std::cout << '\n';
            }
    }
 /*
 A boltban tarolt targyak kozul megmutatja a parameterben megadott targy tulajdonsagait.
    parameterek:
        i (a targy indexe) - int
 */
void Bolt::kiir(int i) const
    {
        std::cout << "Nev: "<< t[i]->getnev();
        std::cout << '\n';
        std::cout << "Max eletero: "<< t[i]->getmaxeletero();
        std::cout << '\n';
        std::cout << "Currrent eletero: " << t[i]->getcurreletero();
        std::cout << '\n';
        std::cout << "Sebzes: " << t[i]->getsebzes();
        std::cout << '\n';
        std::cout << "Ar: " << t[i]->getar();
        std::cout << '\n';
        std::cout << t[i]->getkinezet();
        std::cout << '\n';
    }
 /*
 A jatekos megveheti a targyat ha van ra elegendo anyaga.
    parameterek:
        j (jatekos) - Jatekos&
        a (a targy indexe) - int
        c (hany db targy) - int
    throw: (const char*)
        Megmutatja hogy volt-e a jatekosnak eleg aranya a megvasarlashoz.
 */
void Bolt::megvesz(Jatekos& j,int a,int c)
    {
        if (j.getarany() >= c * t[a]->getar())
        {
            j.kaparany( -1 * ( c * t[a]->getar()));
            j.setmaxeletero(j.getmaxeletero() +c * t[a]->getmaxeletero());
            j.setsebzes(j.getsebzes() + c * t[a]->getsebzes());
            if (j.getcurreletero() + c * t[a]->getcurreletero() <= j.getmaxeletero())
                j.setcurreletero(j.getcurreletero() + c * t[a]->getcurreletero());
            else
                j.setcurreletero(j.getmaxeletero());
        }
        else
            throw "A targy megvasarlasa sikertelen, nincs eleg aranyad.";
    }
 /*
 A szornyek beolvasasa a filebol.
    parameterek:
        fp (filenev) - const char* fp
 */
void Harc::add(const char* fp)
{
    std::ifstream file(fp);
    std::string nev;
    int maxel,currel,seb;
    file >> szornyekszama;
    file.ignore(1);
    sz = new Szorny*[szornyekszama];
    for (int i = 0; i < szornyekszama; i++)
    {
        getline(file,nev);
        file >> maxel;
        file >> currel;
        file >> seb;
        file.ignore();
        sz[i] = new Szorny(nev,maxel,currel,seb);
    }
    file.close();
}
 /*
 A harc lefuttatasa.
    parameterek:
        j (jatekos) - Jatekos&
        je (jatekallas) - Jatekelem&
    visszateresi ertek: bool
        ha a harcot a jatekos nyerte false-szal ter vissza
        ha a harcot a szorny nyerte true-val ter vissza
 */
bool Harc::harc(Jatekos& j,Jatekelem& je)
    {
        bool yourturn = true;
        inchanyadik();
        while(j.getcurreletero() > 0 && sz[hanyadik]->getcurreletero() > 0){
        if (yourturn){
            sz[hanyadik]->setcurreletero(sz[hanyadik]->getcurreletero() - j.getsebzes());
#ifndef CPORTA
            std::cout << sz[hanyadik]->getnev() << " eletero: " << sz[hanyadik]->getcurreletero() << std::endl;
#endif
            yourturn = false;
        }
        else{
            j.setcurreletero(j.getcurreletero() - sz[hanyadik]->getsebzes());
#ifndef CPORTA
            std::cout << j.getnev() << " eletero: " << j.getcurreletero() << std::endl;
#endif
            yourturn = true;
        }
        }
    return yourturn;
    }

