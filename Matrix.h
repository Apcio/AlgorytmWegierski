#ifndef MATRIX_H
#define MATRIX_H

/*Klasa ta obsługuje całą macierz, mimo iż wykorzystuję tutaj kontener z języka C++, to powinna ona ewentualnie ułatwić obsługę
 *macierzy i zachować jej skalowalność. Jest interfejsem do klasy vector, ułatwiającym mi obsługę tej klasy
 */

#include <vector>

#include "Cell.h"

class Matrix
{
public:
    /*Konstruktor domyślny, inicjalizuje tylko macierz
     */
    Matrix()
    {
        Array = new std::vector< std::vector<Cell> >;
        //Rows = 0;
        //Columns = 0;
        Good = true;
        //SetNewRow();
    }

    /*Konstruktor kopiujący, gdy mamy już utworzoną wcześniej kontener
     */
    Matrix(const Matrix &other)
    {
        this->Array = other.Array;
        this->Good = other.Good;
        //this->Rows = other.Rows;
        //this->Columns = other.Columns;
    }

    /*Destruktor
     */
    ~Matrix()
    {
        delete Array;
    }

    /*Metoda przekazuje pełną tablicę
     */
    std::vector< std::vector<Cell> > *getArray()
    {
        return Array;
    }

    /*Metoda wstawia nowy wiersz do tablicy, można wykonać to też na wiele innych sposobów, ja wybrałem ten
     */
    void SetNewRow()
    {
        //Array->resize(++Rows);
        Array->resize(Row() + 1);
        //std::vector<Cell> t;

        //Array->push_back(t);
    }

    /*Metoda wstawia na ostatnim wierszu i ostatniej kolumnie nowy element. Najpiwerw wybieram wiersz ostatni, potem metodą push_back
     *wstawiam na końcu tablicy, czyli w ostatniej kolumnie element
     */
    void AddElement(const Cell &el)
    {
        //Array->at(Rows - 1).resize(++Columns);

        //Array->at(r).resize(c + 1);

        std::vector<Cell> &tmp = Array->at(Row() - 1);
        tmp.push_back(el);
        //Array->at(r).push_back(tmp);
        //tmp = Array[r].data();
        //Array[r][c].push_back(el);
        //tmp->push_back(el);
    }

    /*Metoda przekazuje informacje, czy macierz jest w porządku
     */
    bool isGood();

    /*unsigned int GetColumnCount()
    {
        return Columns;
    }*/

    /*unsigned int GetRowCount()
    {
        return Array->size();
    }*/

    Cell *GetCell(unsigned int row, unsigned int col) const;

    unsigned int Row() const
    {
        return Array->size();
    }

    unsigned int Col(int row) const
    {
        return Array->at(row).size();
    }

    std::vector< Cell > *GetRow(unsigned int R);

private:
    /*Macierz - wektor w wektorze, dwuwymiarowa, czyli kolumny i wiersze
     */
    std::vector< std::vector< Cell > > *Array;

    /*Poniższe zmienne służą do przechowywania ilości kolumn i infromacji, czy macierz jest poprawna
     */
    //unsigned int Rows;
    //unsigned int Columns;
    bool Good;
};

#endif // MATRIX_H
