#include "jatekelemek.h"
//#include "gtest_lite.h"
//#include "memtrace.h"
//#define CPORTA
/*
Az allapotok tarolasa. Ezen allapotok alapjan fog a main-ben levo allapotgep mukodni.
*/
enum Allapot{
kuldetes,
harcelott,
bolt,
vege
};
/*
Ha definialva van a CPORTA akkor a teszteseteket futtatja, ha pedig nincs akkor pedig a vezerlesert felelos.
*/
#ifdef CPORTA
//Ennek segitsegevel tudjuk a fileba irasokat hatekonyan tesztelni
void segedfile(const char* fp, const std::string& str)
    {
        std::ofstream file(fp);
        file << str;
        file.close();
    }
#endif
int main()
{
#ifndef CPORTA
//A hasznalando objektumok alaphelyzetbe hozasa.
    srand(time(0));
    Jatekelem je;
    Jatekos j;
    Bolt b;
    Harc h;
    Kuldetes k;
    b.add("targyak.txt");
    h.add("szornyek.txt");

//A jatekos eldonheti, hogy uj jatekot szeretne-e kezdeni. Amig nem helyes a valasz (I/N, amelyet a hibas flaggel figyelunk,
//addig kerjuk be az adatot. Ha uj jatekot szeretne, alapallapotba all a karakter es a jatekelemek, ha nem a mentes.txt-bol kiolvasodnak.
    std::cout << "Udv kalandor!\nUj jatekot szeretne kezdeni? (I/N) : ";
        bool hibas = true;
        char c;
        while (hibas){
        std::cin >> c;
        if (c == 'i' || c == 'I')
            hibas = false;
        else if (c == 'n' || c == 'N'){
            je.kezdet("mentes.txt",j,h);
            hibas = false;
        }
       else
            std::cout << "Hibas adatot adtal meg!\n";
        }


//Az allapotgep megvalositasa, kezdetben a kuldetes allapotba allitjuk.
    Allapot all = kuldetes;
    while(all != vege)
    {
        switch (all){
/*A kuldetes allapotban 3 kuldetesen fog vegigmenni. A je i privat adattagjaval tudjuk vizsgalni, mikor lesz vege a haromnak (modulo)
   A vegrehajt fgv segitsegevel eloallitjuk a random kisorsolt szamok alapjan az eredmenyt. A konzolrol beolvasunk a felhasznalo altal
   megadott szamot "szam" valtozoba (amig helyes formatumban nem adja meg). Ha a feladvany helyes, a jatekos kap egy aranyat.
*/
            case kuldetes:
                if (je.geti() % 4 != 0)
                {
                std::cout << je.szoveg("szoveg.txt");
                je.inci();
                std::cout << "Mennyi az eredmenye az alabbi feladvanynak?"<<std::endl;
                int x = rand() % k.difficulty(je);
                int y = rand() % k.difficulty(je);
                int melyik = 1 + rand() % 7;
                int eredmeny = k.vegrehajt(x,y,melyik);
                int szam;
                int warrctr = 0;
                while(true)
                {
                    std::string input;
                    std::getline(std::cin,input);

                    std::stringstream ss(input);
                    if(ss >> szam)
                        break;
                    else if(warrctr != 0)
                        std::cout << "Hibas adatot adott meg!" << std::endl;
                    warrctr++;
                }
                if (szam == eredmeny){
                    j.kaparany(1);
                    std::cout << "Helyes a feladvany eredmenye!\n";
                }
                else
                    std::cout << "Hibas a feladvany eredmenye!\n";
                }
                else
                    all = harcelott;
            break;
/*
A felhasznalo a 1-es gombbal a "bolt" allapotba ugorhat. A 2-es gomb hatasara elindul a harc. A harc fgv. bool vagy false-szal tér vissza
ezt kezelni kell. Ha vege lett a korenek akkor a jatekos nyert/továbbhalad ha az o kore lett volna de meghalt akkor vesztett.
*/
            case harcelott:
                int szam;
        std::cout << "<--------------------------------------------#Opciok#-------------------------------------------->" << std::endl;
                std::cout << "[" << 1 << "] " << "Bolt megnyitasa.\n";
                std::cout << "[" << 2 << "] " << "Harc elinditasa.\n";
                while(true)
                {
                    std::string input;
                    std::getline(std::cin,input);

                    std::stringstream ss(input);
                    if(ss >> szam)
                        break;
                    else
                        std::cout << "Hibas adatot adott meg!" << std::endl;
                }
                if (szam == 1)
                {
                std::cout << "<---------------------------------------------#Bolt#--------------------------------------------->" << std::endl;
                    all = bolt;
                    b.kilistaz();
                }
                else if(szam == 2){
                std::cout << je.szoveg("szoveg.txt");
                je.inci();
                bool eredmeny = h.harc(j,je);
                    if (!eredmeny)
                    {
                        if (h.gethanyadik()+1 == h.getszornyekszama())
                        {
                            all = vege;
                            std::cout <<  "Nyertel!";
                        }
                        else
                        {
                            all = kuldetes;
                            std::cout << "Sikeresen legyozted a szornyet!\n";
                            break;
                        }
                    }
                    else
                    {
                        all = vege;
                        std::cout << "Vesztettel!";
                    }
                    }
            break;
/*
A bolt-ban az alabbi formatumban kiirodik a jatekos statjai, es lehetosegei vannak:
    x y formatum (x 0-9ig a targy szama, y 0 vagy 1 ha 0 akkor megnezni a targyat ha 1 akkor megvenni)
    -1 -1 visszalepni a harcelott allapotba
    10 10 a jatekallas elmentese
A user inputok szigor�an vannak kezelve.
*/
            case bolt:
                int a,c;
                std::cout << "<--------------------------------------------#Statok#-------------------------------------------->" << std::endl;
                std::cout << "Max eletero: " << j.getmaxeletero() << std::endl;
                std::cout << "Current eletero: " << j.getcurreletero() << std::endl;
                std::cout << "Sebzes: " << j.getsebzes() << std::endl;
                 std::cout <<"Az aranyad:" << j.getarany() <<std::endl;
                 std::cout << "\nx y formatum" << std::endl;
                 std::cout << "[-1 -1] " << "Visszalepes\n";
                 std::cout <<  "[10 10] " << "Mentes\n";
                while(true)
                {
                    std::string input;
                    std::getline(std::cin,input);

                    std::stringstream ss(input);
                    if(ss >> a >> c)
                        break;
                    else
                        std::cout << "Hibas adatot adott meg!" << std::endl;
                }
                if (a == -1 && c == -1){
                    all = harcelott;
                    break;}
                if (a == 10 && c == 10){
                    all = vege;
                    je.save("mentes.txt",j,h);
                    std::cout << "Jatek mentese sikeres!";
                    break;}
                if (c == 0)
                    b.kiir(a);
                else
                {
                   bool megvett = true;

                try{
                b.megvesz(j,a,c);
                } catch (const char* p)
                {
                    std::cout << p << std::endl;
                    megvett = false;
                }
                if (megvett)
                    std::cout << "Targy megvetele sikeres." << std::endl;
                }
            break;
/*
Ha a jateknak vege van, lepjunk ki a ciklusbol.
*/
            case vege:
                break;
    }

    }
    #endif
    #ifdef CPORTA
//Getterek, setterek tesztelese
TEST(ENTITAS, URESLETREHOZAS){
    Entitas e;
    EXPECT_EQ(0,e.getmaxeletero()) << "A max eleterot rosszul adja meg" << std::endl;
    EXPECT_EQ(0,e.getcurreletero()) << "A current eleterot rosszul adja meg" << std::endl;
    EXPECT_EQ(0,e.getsebzes()) << "A sebzest rosszul adja meg" << std::endl;
} ENDM

TEST(ENTITAS, LETREHOZAS){
    Entitas e("Entitas",10,10,5);
    EXPECT_EQ(10,e.getmaxeletero()) << "A max eleterot rosszul adja meg" << std::endl;
    EXPECT_EQ(10,e.getcurreletero()) << "A current eleterot rosszul adja meg" << std::endl;
    EXPECT_EQ(5,e.getsebzes()) << "A sebzest rosszul adja meg" << std::endl;
} ENDM

TEST(ENTITAS, SETTEREK){
    Entitas e("Entitas",10,10,5);
    e.setmaxeletero(e.getmaxeletero()+1);
    e.setcurreletero(e.getcurreletero()+1);
    e.setsebzes(e.getsebzes()+1);
    EXPECT_EQ(11,e.getmaxeletero()) << "A max eleterot rosszul valtoztatja" << std::endl;
    EXPECT_EQ(11,e.getcurreletero()) << "A current eleterot rosszul valtoztatja" << std::endl;
    EXPECT_EQ(6,e.getsebzes()) << "A sebzest rosszul valtoztatja" << std::endl;
} ENDM

TEST(JATEKOS, LETREHOZAS){
    Jatekos j;
    EXPECT_EQ(50,j.getmaxeletero()) << "A max eleterot rosszul adja meg" << std::endl;
    EXPECT_EQ(50,j.getcurreletero()) << "A current eleterot rosszul adja meg" << std::endl;
    EXPECT_EQ(5,j.getsebzes()) << "A sebzest rosszul adja meg" << std::endl;
} ENDM

TEST(JATEKOS, SETTEREK){
    Jatekos j;
    EXPECT_EQ(0,j.getarany()) << "Nem 0-ra �ll�t�dott be alapbol az arany." << std::endl;
    j.kaparany(5);
    EXPECT_EQ(5,j.getarany()) << "Rosszul ad hozza aranyat" << std::endl;
} ENDM

TEST(SZORNY, LETREHOZAS){
    Szorny sz("Szorny",10,10,5);
    EXPECT_EQ(10,sz.getmaxeletero()) << "A max eleterot rosszul adja meg" << std::endl;
    EXPECT_EQ(10,sz.getcurreletero()) << "A current eleterot rosszul adja meg" << std::endl;
    EXPECT_EQ(5,sz.getsebzes()) << "A sebzest rosszul adja meg" << std::endl;
} ENDM

TEST(TARGY, LETREHOZAS){
    Targy t("Targy",10,10,5,2,"<----I");
    EXPECT_STREQ("Targy",t.getnev().c_str()) << "A targy neve helytelen.";
    EXPECT_EQ(10,t.getmaxeletero()) << "A max eleterot rosszul adja meg" << std::endl;
    EXPECT_EQ(10,t.getcurreletero()) << "A current eleterot rosszul adja meg" << std::endl;
    EXPECT_EQ(5,t.getsebzes()) << "A sebzest rosszul adja meg" << std::endl;
    EXPECT_EQ(2,t.getar()) << "Az aranyat rosszul allitja be" << std::endl;
    EXPECT_STREQ("<----I",t.getkinezet().c_str()) << "Helytelenul adja meg a targy kinezetet.";
} ENDM

TEST(JATEKELEM, MUVELETEK){
    Jatekelem je;
    EXPECT_EQ(1,je.geti()) << "Rossz a jatekelem kezdeti inicializalasa." << std::endl;
    je.inci();
    je.inci();
     EXPECT_EQ(3,je.geti()) << "Index leptetese hibas." << std::endl;
} ENDM

TEST(HARC, INIC){
   Harc h;
    h.inchanyadik();
     EXPECT_EQ(0,h.gethanyadik()) << "Index leptetese hibas." << std::endl;
     EXPECT_EQ(0,h.getszornyekszama()) << "Szornyekszama rosszul allt be" << std::endl;
} ENDM
//Getterek, setterek tesztelese

//Jatek funkciojinak tesztelese

TEST(JATEKELEM,KEZDET)
{
    Jatekelem je;
    Jatekos j;
    Harc h;
    segedfile("test.txt","4\n1\n70\n60\n10\n5");
    je.kezdet("test.txt",j,h);
    EXPECT_EQ(5,je.geti()) << "Rossz a jatekelem indexe" << std::endl;
    EXPECT_EQ(1,h.gethanyadik()) << "Rosszan hatarozza meg hogy hanyadik szornynel tart." << std::endl;
    EXPECT_EQ(70,j.getmaxeletero()) << "Rosszul allitja vissza a jatekos maxeleterejet" << std::endl;
    EXPECT_EQ(60,j.getcurreletero()) << "Rosszul allitja vissza a jatekos current eleterejet" << std::endl;
    EXPECT_EQ(10,j.getsebzes()) << "Rosszul allitja vissza a jatekos sebzeset" << std::endl;
    EXPECT_EQ(5,j.getarany()) << "Rosszul allitja vissza a jatekos aranyat" << std::endl;
    std::remove("test.txt");
}ENDM

TEST(JATEKELEM,SZOVEG)
{


    Jatekelem je;
    segedfile("test.txt","Banan$Alma$");
    std::string str = je.szoveg("test.txt");
    EXPECT_STREQ("Banan",str.c_str()) << "Helytelenul olvassa ki a szoveget a filebol.";
    std::remove("test.txt");
} ENDM

TEST(JATEKELEM,SAVE)
{
Jatekelem je;
Jatekos j;
Harc h;
je.save("test.txt",j,h);
je.kezdet("test.txt",j,h);
EXPECT_EQ(1,je.geti()) << "Rossz a jatekelem indexe" << std::endl;
EXPECT_EQ(-1,h.gethanyadik()) << "Rosszan hatarozza meg hogy hanyadik szornynel tart." << std::endl;
EXPECT_EQ(50,j.getmaxeletero()) << "Rosszul allitja vissza a jatekos maxeleterejet" << std::endl;
EXPECT_EQ(50,j.getcurreletero()) << "Rosszul allitja vissza a jatekos current eleterejet" << std::endl;
EXPECT_EQ(5,j.getsebzes()) << "Rosszul allitja vissza a jatekos sebzeset" << std::endl;
EXPECT_EQ(0,j.getarany()) << "Rosszul allitja vissza a jatekos aranyat" << std::endl;
std::remove("test.txt");

} ENDM

TEST(KULDETES,DIFFICULTY)
{
    Jatekelem je;
    Kuldetes k;
    int i = k.difficulty(je);
EXPECT_EQ(10,i) << "Rosszul hatarozza meg a difficultyt" << std::endl;
} ENDM



TEST(KULDETES,NAGYOBBGYOK)
{
    Kuldetes k;
    EXPECT_EQ(12, k.nagyobbgyok(12,3)) << "a nagyobbik gyok kiszamitasa helytelen.";
    EXPECT_EQ(12, k.nagyobbgyok(3,12)) << "a nagyobbik gyok kiszamitasa helytelen.";
} ENDM

TEST(KULDETES,KISEBBGYOK)
{
    Kuldetes k;
    EXPECT_EQ(3, k.kisebbgyok(12,3)) << "a kisebbik gyok kiszamitasa helytelen.";
    EXPECT_EQ(3, k.kisebbgyok(3,12)) << "a kisebbik gyok kiszamitasa helytelen.";
} ENDM

TEST(KULDETES,LNKO)
{
    Kuldetes k;
    EXPECT_EQ(10, k.lnko(19,9)) << "lnko szamitasat nem hajtja jol vegre.";
} ENDM

TEST(KULDETES,LKKT)
{
    Kuldetes k;
    EXPECT_EQ(12, k.lkkt(3,4)) << "lkkt szamitasat nem hajtja jol vegre.";
} ENDM

TEST(KULDETES,SZAMJEGYEK)
{
    Kuldetes k;
    EXPECT_EQ(12, k.szamjegyek(123,321)) << "szamok osszegenek a szamjegyeinek az osszegenek a szamitasat nem hajtja jol vegre.";
} ENDM
TEST(KULDETES,OSSZEAD)
{
    Kuldetes k;
    EXPECT_EQ(10, k.osszead(3,7)) << "Osszeadast nem hajtja jol vegre.";
} ENDM

TEST(KULDETES,KIVONAS)
{
    Kuldetes k;
    EXPECT_EQ(10, k.kivon(20,10)) << "Kivonast nem hajtja jol vegre.";
} ENDM
TEST(KULDETES,VEGREHAJT)
{
    Kuldetes k;

    EXPECT_EQ(2, k.vegrehajt(1,1,1)) << "Vegrehajt rossz az osszeadassal.";
    EXPECT_EQ(0, k.vegrehajt(1,1,2)) << "Vegrehajt rossz a kivonassal.";
    EXPECT_EQ(2, k.vegrehajt(1,1,3)) << "Vegrehajt rossz az lnkoval.";
    EXPECT_EQ(1, k.vegrehajt(1,1,4)) << "Vegrehajt rossz az lkktval.";
    EXPECT_EQ(2, k.vegrehajt(1,1,5)) << "Vegrehajt rossz a szamjegyek fgv-el.";
    EXPECT_EQ(1, k.vegrehajt(1,1,6)) << "Vegrehajt rossz a nagyobbgyokkel.";
    EXPECT_EQ(1, k.vegrehajt(1,1,7)) << "Vegrehajt rossz a kisebbgyokkel.";

} ENDM


TEST(BOLT, VASARLAS){

    Bolt b;
    Jatekos j;
    segedfile("test.txt","Test\nTest$\n1\n1\n1\n10\nTest\nTest$\n1\n1\n1\n10\nTest\nTest$\n1\n1\n1\n10\nTest\nTest$\n1\n1\n1\n10\nTest\nTest$\n1\n1\n1\n10\nTest\nTest$\n1\n1\n1\n10\nTest\nTest$\n1\n1\n1\n10\nTest\nTest$\n1\n1\n1\n10\nTest\nTest$\n1\n1\n1\n10\nTest\nTest$\n1\n1\n1\n10\n");
    b.add("test.txt");
    EXPECT_STREQ("Test",b.getnev(0).c_str()) << "Helytelenul olvassa ki a targyakat a filebol.";
    EXPECT_THROW(b.megvesz(j,1,1),const char*) << "Nincs eleg aranyad, dobni kell!";
    j.kaparany(1000);
    EXPECT_NO_THROW(b.megvesz(j,1,1)) << "Van eleg aranyad nem kene dobnia kivetelt!";
    std::remove("test.txt");
} ENDM

TEST(HARC,TOVABB)
{

    Jatekelem je;
    Jatekos j;
    Harc h;
    segedfile("test.txt","3\nA\n1\n1\n1\nA\n1\n1\n1\nA\n1\n1\n1\n");
    h.add("test.txt");
    EXPECT_FALSE(h.harc(j,je)) << "False-t kellett volna dobni!";
    std::remove("test.txt");
} ENDM
TEST(HARC,VESZTETT)
{

    Jatekelem je;
    Jatekos j;
    Harc h;
    segedfile("test.txt","3\nA\n1000\n1000\n1000\nA\n1\n1\n1\nA\n1\n1\n1\n");
    h.add("test.txt");
    EXPECT_TRUE(h.harc(j,je)) << "True-t kellett volna dobni!";
    std::remove("test.txt");
} ENDM

TEST(HARC,NYERT)
{
    Jatekelem je;
    Jatekos j;
    Harc h;
    segedfile("test.txt","3\nA\n1000\n1000\n1000\nA\n1\n1\n1\nA\n1\n1\n1\n");
    h.add("test.txt");
    h.inchanyadik();
    h.inchanyadik();
    EXPECT_FALSE(h.harc(j,je)) << "False-t kellett volna dobni!";
    std::remove("test.txt");
} ENDM
//Jatek funkciojinak tesztelese
    #endif // CPORTA
    return 0;
}
