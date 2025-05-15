#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <algorithm>
#include <cstring>


using namespace std;


void losowanie(string *obcy, string *pol, int licznik)       // Funkcja zmieniajaca kolejnosc slow w tablicy
{   
    srand(time(NULL));
    string tmp; 
    int j;
    for(int i=0; i<licznik; i++)        // Algorytm mieszajacy (sortujacy) slowa w tablicy
    {
        j = rand()%(i+1);       // Losowanie indeksu tablicy, w ktorej ma zostac zamieniona wartosc
            
        tmp = pol[j];
        pol[j] = pol[i];
        pol[i] = tmp;

        tmp = obcy[j];
        obcy[j] = obcy[i];
        obcy[i] = tmp;
    }
}

string wielkosc_znaku(string c)     // Zmiana wielkosci slow wczytywanych przez program
{
    int i=0;
    int n = c.length();
    char char_array[n + 1];
    strcpy(char_array, c.c_str());
        while (char_array[i])
        {
            char_array[i] = tolower(char_array[i]);
            i++;
        }
    c = (string)char_array;     // Rzutowanie na typ string
    return c;
}

void tlumaczenie(bool tryb)     
{
    fstream plik_obcy;
    char nazwa_obcy[20];
    bool sprawdzanie = false;
    
    while(sprawdzanie == false)       // Otwarcie pliku ze slowkami w jezyku obcym
    {
        cout<<"Podaj nazwe pliku ze slowkami w jezyku obcym: ";
        cin>>nazwa_obcy;
        plik_obcy.open(nazwa_obcy, ios::in);
        
        if (plik_obcy.good()==true)      // Sprawdzenie czy plik zostal poprawnie otwarty
            {
                cout<<"Udalo sie otworzyc plik!"<<endl;
                sprawdzanie=true;
            }

        if (plik_obcy.good()==false)     // Sprawdzenie czy plik zostal poprawnie otwarty
            {
                cout<<"Nie udalo sie otworzyc pliku!"<<endl; 
            }
    }

    int licznik_rozmiar=0;
    string linia_rozmiar;
    while (plik_obcy >> linia_rozmiar)       // Zczytanie ilosci slow w pliku
    {
        licznik_rozmiar++;
    }

    plik_obcy.clear();       // Ustawienie flagi na poczatek pliku       
    plik_obcy.seekg(0, ios::beg);       

    string *obcy;        // Implementacja dynamicznej tablicy        
    obcy = new string[licznik_rozmiar];

    string linia;
    int licznik=0;
    while(getline(plik_obcy,linia))      // Zapis slow z pliku do tablicy
    {
        linia = wielkosc_znaku(linia);
        obcy[licznik] = linia;
        licznik++;
    }
    plik_obcy.close();

    fstream plik_pol;  
    char nazwa_pol[20];
    sprawdzanie = false;
    while(sprawdzanie == false)      // Otwarcie pliku z polskimi slowkami
    {
        cout<<"Podaj nazwe pliku z polskimi slowkami: ";
        cin>>nazwa_pol;
        plik_pol.open(nazwa_pol, ios::in);
        
        if (plik_pol.good()==true)      // Sprawdzenie czy plik zostal poprawnie otwarty
            {
                cout<<"Udalo sie otworzyc plik!"<<endl;
                sprawdzanie=true;
            }

        if (plik_pol.good()==false)     // Sprawdzenie czy plik zostal poprawnie otwarty
            {
                cout<<"Nie udalo sie otworzyc pliku!"<<endl;
            }
    }

    licznik_rozmiar=0;
    while (plik_pol >> linia_rozmiar)       // Zczytanie ilosci slow w pliku
    {
        licznik_rozmiar++;
    }

    plik_pol.clear();       // Ustawienie flagi na poczatek pliku          
    plik_pol.seekg(0, ios::beg);      

    string *pol;        // Implementacja dynamicznej tablicy
    pol = new string[licznik_rozmiar];

    licznik=0;
    while(getline(plik_pol,linia))      // Zapis slow z pliku do tablicy
    {
        linia = wielkosc_znaku(linia);
        pol[licznik] = linia;
        licznik++;
    }
    plik_pol.close();

    fstream plik_wynik;  
    char nazwa_wynik[20];
    cout<<"Podaj nazwe pliku, do ktorego maja byc zapisywane wynik: ";
    cin>>nazwa_wynik;
    plik_wynik.open(nazwa_wynik, ios::out | ios::app );     // Otwarcie pliku do zapisu wyniku, gdy plik nie istnieje, wczesniejsze jego utworzenie
        if (plik_wynik.good()==true)
        {
            cout<<"Udalo sie otworzyc plik!"<<endl<<endl;
        }

    string wpisany_wyraz;
    if( tryb == false)      // Warunek definiujacy aktualnie wykonujacy sie tryb programu (Tryb 1)
    {
        losowanie(pol,obcy,licznik);     // Przetasowanie wyrazow w tablicy
        int punkty=0;

        for(int i=0;i<licznik;i++)      // Algorytm sprawdzajacy poprawnosc wpisanego slowa i liczacy punkty
        {        
            cout<<"Tlumacz slowo: "<<obcy[i]<<endl;
            cin>>wpisany_wyraz;
            transform(wpisany_wyraz.begin(),wpisany_wyraz.end(),wpisany_wyraz.begin(),::tolower);       // Funkcja ignorujaca wielkosc liter we wpisywanym wyrazie

            if(wpisany_wyraz == pol[i])     // Zliczane punktow
                {
                    cout<<"Dobrze!"<<endl;
                    punkty++;
                }
            else 
                {
                    cout<<"Zle!"<<endl;
                }
                cout<<"Punkty : "<<punkty<<endl<<endl;
        }
            plik_wynik<<"Liczba pytan: "<<licznik<<endl<<"Poprawne odpowiedzi: "<<punkty<<endl;     // Zapis wyniku do pliku
            plik_wynik.close();
    }
    
    else if(tryb == true)        // Warunek definiujacy aktualnie wykonujacy sie tryb programu (Tryb 2)
    {
        losowanie(pol,obcy,licznik);     // Przetasowanie wyrazow w tablicy
        int punkty=0;
         
        for(int c=0;c<licznik;c++)      // Algorytm sprawdzajacy poprawnosc wpisanego slowa i liczacy punkty
        {
            srand(time(NULL));
            int b;
            b = rand()%2+1;     // Zmienna pomocnicza do losowania kolejnosci tlumaczenia
        
            if(b == 1)      // Losowanie tlumaczenia (obcy -> polski)
                {      
                    cout<<"Tlumacz slowo (obcy -> polski): "<<obcy[c]<<endl;
                    cin>>wpisany_wyraz;
                    transform(wpisany_wyraz.begin(),wpisany_wyraz.end(),wpisany_wyraz.begin(),::tolower);       // Funkcja ignorujaca wielkosc liter w wyrazie
                    
                        if(wpisany_wyraz == pol[c])     // Zliczane punktow
                            {
                                cout<<"Dobrze!"<<endl;
                                punkty++;
                            }
                        else 
                            {
                                cout<<"Zle!"<<endl;
                            }
                            cout<<"Punkty : "<<punkty<<endl<<endl;                    
                }
            
            if(b == 2)      // Losowanie tlumaczenia (polski -> obcy)
                {      
                    cout<<"Tlumacz slowo (polski -> obcy): "<<pol[c]<<endl;
                    cin>>wpisany_wyraz;
                    transform(wpisany_wyraz.begin(),wpisany_wyraz.end(),wpisany_wyraz.begin(),::tolower);       // Funkcja ignorujaca wielkosc liter w wyrazie

                        if(wpisany_wyraz == obcy[c])     // Zliczane punktow
                            {
                                cout<<"Dobrze!"<<endl;
                                punkty++;
                            }
                        else 
                            {
                                cout<<"Zle!"<<endl;
                            } 
                            cout<<"Punkty : "<<punkty<<endl<<endl;                  
                }
        } 
        plik_wynik<<"Liczba pytan: "<<licznik<<endl<<"Poprawne odpowiedzi: "<<punkty<<endl;     // Zapis wyniku do pliku
        plik_wynik.close();
    }  
    delete[] obcy;
    delete[] pol;
}



int main()
{
    //---------------------------------------------------//
    //                       Menu                        //
    //---------------------------------------------------//
    int opt;
    do
    {   
        cout<<endl;
        cout<<"Prosze wybrac tryb (wpisz 1 lub 2):  "<<endl;
        cout<<"1: Tlumaczenie slowka z jezyka obcego na polski (Tryb 1)"<<endl;
        cout<<"2: Tlumaczenia z jezyka obcego na polski, jak i z polskiego na obcy (Tryb 2)"<<endl;
        cout<<"0: Jesli chcesz wyjsc"<<endl;
        cin>>opt;

        while (cin.fail())      // Walidacja wejscia
        {   
            cout<<endl;
            cout<<"Niepoprawna opcja!"<<endl;
            cin.clear();        // Czyszczenie bufora wejscia
            cin.ignore(INT_MAX, '\n');      // Ignoruj ostatni strumien wejscia
            cout<<"Prosze wybrac tryb (wpisz 1 lub 2):  "<<endl;
            cout<<"1: Tlumaczenie slowka z jezyka obcego na polski (Tryb 1)"<<endl;
            cout<<"2: Tlumaczenia z jezyka obcego na polski, jak i z polskiego na obcy (Tryb 2)"<<endl;
            cout<<"0: Jesli chcesz wyjsc"<<endl;
            cin >> opt;
        }

        switch(opt)
        {
            case 0: 
                exit(0);
                break;

            case 1: 
                tlumaczenie(false);
                break;

            case 2: 
                tlumaczenie(true);
                break;

            default:
                cout<<endl;
                cout<<"Niepoprawna opcja! ";
                break;
        }
    } while(opt != 0);

    return 0;
}