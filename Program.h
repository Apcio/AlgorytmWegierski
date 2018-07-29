#ifndef PROGRAM_H
#define PROGRAM_H

/*Klasa program służy do obsługi programu - zastępuje interfejs i obsługuje resztę klas, jest mostem (nawiązuje interakcję z nimi).
 *Można było napisać bez tej klasy, bądź paru innych, ale staram się wszystko oprzeć na obiektach i utworzyć odpowiednie klasy
 *do obsługi pewnych zadań, aby program dał się łatwiej rozbudować. W końcu język C++ jest obiektowy i na takiej zasadzie działa.
 */

#include <iostream>
#include <fstream>
#include <string>

#include "Matrix.h"
#include "Algorithm.h"
#include "Cell.h"

/*Moje własne kody błędów, gdyby coś nie wypaliło
 */

#define EXIT_SUCCESS 0
#define WRONG_ARGS 1
#define WRONG_MATRIX 2

#define STREAM_BUFFER 32

#define READ_NOSTATUS -1
#define READ_DIGIT 0
#define READ_ROW 1
#define READ_END 2

/*Część kodu może być umieszczona w deklaracji klasy. Znaczy to tyle samo, co słówko inline przed nazwą metody.
 *Jeżeli metodę umieszczę poza plikiem nagłówkowym, a oznaczę ją jako inline, wtedy się nie skompiluje.
 *Jeżeli jednak umieszczę ją w tym pliku nagłówkowym, poza definicją klasy - wtedy się skompiluje.
 */

class Program
{
public:
    /*Konstruktor
     */
    Program(int argc, char* argv[])
    {
        /*
         *Konstruktor tworzy obiekt klasy Program i sprawdza, czy jest parametr ze ścieżką do pliku.
         *Jeżeli nie ma parametróW, bądź jest ich za dużo, klasa ustawi flagę informującą o złych parametrach.
         */
        if(argc != 2)
        {
            ArgsGood = false;
            return;
        }

        /*Jeżeli parametry się zgadzają, to kontynuuje - zapisuje ścieżką do zmiennej typu string,
         *aby łatwiej nią manipulować w razie potrzeby
         */
        FilePath.append(argv[1]);
        ArgsGood = true;
        Alg = 0;
    }

    /*Destruktor
     */
    ~Program()
    {

    }

    /*Metoda zwraca zawartość flagi poprawności argumentow.
     *W zasadzie może być jako prywatna, bo używam ją tylko w tej klasie, ale można jeszcze dodać do funkcji main() jej wywołanie
     *i jeżeli będzie niepoprawna to zakończyć program, albo kontynuować. Tylko tutaj nie zwrócę wartości błędu, dlatego zrezygnowałem
     *z jej wywołania w main()
     */
    bool isArgsGood()
    {
        return ArgsGood;
    }

    /*Metoda Run() - w niej wszystko się zaczyna i kończy. Jest Alfa i Omegą :D
     */
    int Run();

    /*Metoda wyświetla na ekran macierz
     */
    void ShowMatrix(const Matrix &M) const;

private:
    /*Flaga/zmienna przechowuje informacje czy są poprawne wartości argumentów
     */
    bool ArgsGood;

    /*Zmienna przechowuje ścieżkę do pliku jako łacuch, aby później łatwiej nim operować
     */
    std::string FilePath;

    /*Zmienna przechowuje obiekt klasy Matrix
     */
    Matrix M_Array;

    /*Metoda wykonuje polecenie wczytania macierzy z pliku i zapisuje ją w odpowiednie miejsce
     */
    bool LoadMatrix();

    /*Metoda pobiera z pliku file dane i zapisuje je w input. Koń1czy się,
     *gdy znajdzie znak spacji (' '), końca wiersza ('/n'), końca łańcucha ('\0')
     */
    int ReadFile(std::fstream &file, std::string &input);

    /*Obiekt klasy Algorytmu Węgierskiego
     */
    Algorithm *Alg;

    /*Metoda wyświetla graf przydzielonych zadań, format: Komputer<nr> -> Hot-Spotk<nr> (wartość)
     */
    void ShowGraph();
};


#endif // PROGRAM_H
