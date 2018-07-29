#ifndef ALGORITHM_H
#define ALGORITHM_H

/*Klasa algorytm zawiera wszelkie metody potrzebne do wykonania algorytmu Węgierskiego
 */

#include "Matrix.h"
#include "Cell.h"

class Algorithm
{
public:
    Algorithm(Matrix *m)
    {
        M_Original = m;
        /*Początkowa inicjalizacja zmiennej ma znaczenie, ponieważ w klasie Program wykonuję pętlę, aż zmienna będzie miała wartość false
         */
        MoreIterations = true;
    }

    /*Metoda wywoływana jako pierwsza, wykonuje etap wstępny, czyli redukcji wartości w wierszach i kolumnach
     */
    void OpeningStage();

    /*Metoda wywoływana jest w procesie iteracji - kolejnych kroków służących do redukcji tabeli
     */
    void IterationStage();

    /*Proces kończący algorytm - na etapie końcowym wybiera się optymalny przydział
     */
    void EndingStage();

    /*Metoda informuje, czy nie potrzebne są następne kroki
     */
    bool IsEndIterations()
    {
        return !MoreIterations;
    }

    const Matrix &GetMatrix() const
    {
        return M_Temporary;
    }

private:

    /*Przechowuję wskaźnikdo oryginalnej macierzy, oraz tworze lokalną kopię tymczasową, aby w niej przechowywać nowe wartości w tablicy
     */
    Matrix *M_Original;
    Matrix M_Temporary;
    bool MoreIterations;

    /*Metoda służy do minimalizacji wierszy na etapie początkowym
     */
    void MinimizeFirst(const std::vector<Cell> &Row);

    /*Metoda służy do minimalizacji kolumn na etapie początkowym
     */
    void MinimizeSecond(const unsigned int &Col);

    /*Metody przeszukują wiersze bądź kolumny i zliczają ilość zer
     */
    unsigned int CountZeroRow(const unsigned int &row, bool UnderlinesSensitive = true);
    unsigned int CountZeroCol(const unsigned int &col, bool UnderlinesSensitive = true);

    bool CountCellIfZero(const Cell *C, bool Underlines)
    {
        if( C->GetValue() == 0)
        {
            if(Underlines == true && C->GetUnderlines() == 0) return true;
            if(Underlines == false) return true;
        }
        return false;
    }

    /*Metody skreślają wyznaczoną kolumnę, bądź wiersz
     */
    void CoverRow(const unsigned int &row);
    void CoverCol(const unsigned int &col);

    /*Metoda sprawdza wystąpienie skreśleń, odpowiednio traktuje wartość komórki i od razu resetuje liczbę skreśleń
     */
    void CoverCount();

    /*Metoda wyszukuje najmniejszą wartośc x, z tych elementów nieskreślonych
     */
    int FindMinX();

    /*Metoda sprawdza, czy dany wiersz, bądź kolumna jest wykreślona z działania
     */
    bool IsDeleted(const std::vector< int > &Deleted, const int &Number)
    {
        for(unsigned int i = 0; i < Deleted.size(); ++i)
        {
            if(Deleted.at(i) == Number) return true;
        }
        return false;
    }

    /*Metody te ułatwiają mi obsługę etapu końcowego. Najpierw poszukam zer które są jedynymi w wierszu i kolumnie, a potem resztę zer
     */
    void AsteriskRowColWithOneZero(std::vector< int > &Del_Row, std::vector< int > &Del_Col);
    void AsteriskRowCol(std::vector< int > &Del_Row, std::vector< int > &Del_Col);

    /*Tak na szybko - scal gwiazdki, czyli te pola z informacją, kto ma jakie zadanie robić do oryginalnej macierzy
     */
    void Merge_Asterisk_To_Matrix();
};

#endif // ALGORITHM_H
