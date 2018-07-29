#include "Algorithm.h"

void Algorithm::OpeningStage()
{
    /*Minimalizacja macierzy - zacznijmy od pierwsze, czyli od minimalizacji wierszy
     */
    for(unsigned int i = 0; i < M_Original->Row(); ++i)
    {
        MinimizeFirst(*M_Original->GetRow(i));
    }

    /*Ok, czas na drugą turę minimalizacji, czyli idziemy teraz po Kolumnach. Ponieważ macierz ma mieć równe kolumny w każdym wierszu, to mogę
     *po prostu pobrać ilość kolumn z pierwszego wiersza.
     */
    for(unsigned int i = 0; i < M_Original->Col(0); ++i)
    {
        MinimizeSecond(i);
    }
}

void Algorithm::MinimizeFirst(const std::vector<Cell> &Row)
{
    /*Przypisz pierwszy element wiersza jako minimalny
     */
    int min = ((Cell)Row.at(0)).GetValue();

    /*Wyszukaj minimalny element w wierszu
     */
    for(unsigned int i = 1; i < Row.size(); ++i)
    {
        if(min > ((Cell)Row.at(i)).GetValue())
        {
            min = ((Cell)Row.at(i)).GetValue();
        }
    }

    /*Odejmij od wiersza minimalny element
     */
    M_Temporary.SetNewRow();
    for(unsigned int i = 0; i < Row.size(); ++i)
    {
        M_Temporary.AddElement(Cell(((Cell)Row.at(i)).GetValue() - min));
    }
}

void Algorithm::MinimizeSecond(const unsigned int &Col)
{
    /*Utwórz nowe zmienne i przypisz im wartości z pierwszego wiersza
    */
    Cell *c = M_Temporary.GetCell(0, Col);
    if(c == 0) return;
    int min = c->GetValue();

    /*Wyszukaj minimalny element w kolumnie
     */
    for(unsigned int i = 1; i < M_Temporary.Row(); ++i)
    {
        c = M_Temporary.GetCell(i, Col);
        if(c == 0) return;
        if(min > c->GetValue()) min = c->GetValue();
    }

    /*Zminimalizuj kolumny
     */
    for(unsigned int i = 0; i < M_Temporary.Row(); ++i)
    {
        c = M_Temporary.GetCell(i, Col);
        if(c == 0) return;
        c->SetValue(c->GetValue() - min);
    }
}

void Algorithm::IterationStage()
{
    /*Upewniam się, że jest możliwośc dalszego wykonywania iteracji
     */
    if(MoreIterations == false) return;

    /*Zmienna count zlicza ilość przekreślonych wierszy i kolumn. Jeśli ilośc ta będzie się zgadzała z ilością wierszy bądź kolumn, operacja zostanie
     *zakończona i nie będzie można wykonywać więcej etapu iteracyjnego.
     */
    unsigned int count = 0;

    /*Row_Count i Col_Count - zmienne te przechowują liczbę zer w danym wierszu czy kolumnie
     */
    unsigned int r_c;
    unsigned int c_c;

    Cell *c;

    /*Teraz pętla sterująca, która przejdzie po wszystkich wierszach i wyszuka zera
     */
    for(unsigned int i = 0; i < M_Temporary.Row(); ++i)
    {
        for(unsigned int j = 0; j < M_Temporary.Col(i); ++j)
        {
            /*Pobierz aktualną komórkę i sprawdź jej zawartość
             */
            c = M_Temporary.GetCell(i, j);
            if(c == 0) return;
            if(c->GetValue() != 0 || c->GetUnderlines() != 0) continue;

            /*Zlicz zawartość zer w wierszu bądź kolumnie
             */
            r_c = CountZeroRow(i);
            c_c = CountZeroCol(j);

            /*Jeżeli w kolumnie jest więcej zer, zakreś kolumnę, w przeciwnym wypadku, skreśl wiersz
             */
            if(c_c > r_c) CoverCol(j);
                else CoverRow(i);
            ++count;
        }
    }

    /*Dobra, zaznaczyłem te elementy, teraz czas na zliczenie skreśleń, ale przedtem sprawdź, czy nie ma tyle skreśleń, ile jest kolumn bądź wierszy
     */
    if(count == M_Temporary.Row() || count == M_Temporary.Col(0))
    {
        MoreIterations = false;
        return;
    }

    CoverCount();
}

unsigned int Algorithm::CountZeroRow(const unsigned int &row, bool UnderlinesSensitive)
{
    if(row > (M_Temporary.Row() - 1) ) return 0;

    Cell *c;
    unsigned int count = 0;


    for(unsigned int i = 0; i < M_Temporary.Col(row); ++i)
    {
        c = M_Temporary.GetCell(row, i);
        if(c == 0) return 0;

        /*Gdy wartość jest równa 0 i nie ma skreśleń
         */
        if(CountCellIfZero(c, UnderlinesSensitive)) ++count;
    }

    return count;
}

unsigned int Algorithm::CountZeroCol(const unsigned int &col, bool UnderlinesSensitive)
{
    if(col > (M_Temporary.Col(0) - 1) ) return 0;

    Cell * c;
    unsigned int count = 0;

    for(unsigned int i = 0; i < M_Temporary.Row(); ++i)
    {
        c = M_Temporary.GetCell(i, col);
        if(c == 0) return 0;

        /*Gdy wartość jest równa 0 i nie ma skreśleń
         */
        if(CountCellIfZero(c, UnderlinesSensitive)) ++count;
    }

    return count;
}

void Algorithm::CoverRow(const unsigned int &row)
{
    if(row > (M_Temporary.Row() - 1) ) return;

    Cell *c;

    for(unsigned int i = 0; i < M_Temporary.Col(row); ++i)
    {
        c = M_Temporary.GetCell(row, i);
        if(c == 0) return;

        c->SetUnderline(c->GetUnderlines() + 1);
    }
}

void Algorithm::CoverCol(const unsigned int &col)
{
    if(col > (M_Temporary.Col(0) - 1) ) return;

    Cell * c;

    for(unsigned int i = 0; i < M_Temporary.Row(); ++i)
    {
        c = M_Temporary.GetCell(i, col);
        if(c == 0) return;

        c->SetUnderline(c->GetUnderlines() + 1);
    }
}

void Algorithm::CoverCount()
{
    Cell *c;
    int min = FindMinX();

    for(unsigned int i = 0; i < M_Temporary.Row(); ++i)
    {
        for(unsigned int j = 0; j < M_Temporary.Col(i); ++j)
        {
            c = M_Temporary.GetCell(i, j);
            if(c == 0) return;

            if(c->GetUnderlines() == 2) c->SetValue(c->GetValue() + min);
            else if(c->GetUnderlines() == 0) c->SetValue(c->GetValue() - min);

            c->SetUnderline(0);
        }
    }
}

int Algorithm::FindMinX()
{
    /*Metoda wyszukuje najmniejsze x z tych elementów nieskreślonych. Ponieważ wyszukanie pierwszego elementu nieskreślonego, może trochę zająć
     *czasu, naprzykład jedna pętla szukająca pierwszego elementu nieskreślonego, to użyję zmiennej logicznej do sprawdzenia, czy już
     *ta minimalna została znaleziona, jeśli nie to po prostu przypiszę wartość tej znalezionej
     */
    int min = 0;
    bool founded = false;
    Cell *c;

    for(unsigned int i = 0; i < M_Temporary.Row(); ++i)
    {
        for(unsigned int j = 0; j < M_Temporary.Col(i); ++j)
        {
            c = M_Temporary.GetCell(i, j);
            if(c == 0) return 0;

            if(c->GetUnderlines() != 0) continue;

            if(founded == false)
            {
                min = c->GetValue();
                founded = true;
                continue;
            }

            if(min > c->GetValue()) min = c->GetValue();
        }
    }

    return min;
}

void Algorithm::EndingStage()
{
    /*Zmienne pomocnicze - przechowują numery wierszy i kolumn, które zostały wykreślone
     */
    std::vector< int > del_row;
    std::vector< int > del_col;

    AsteriskRowColWithOneZero(del_row, del_col);
    AsteriskRowCol(del_row, del_col);

    Merge_Asterisk_To_Matrix();
}

void Algorithm::AsteriskRowColWithOneZero(std::vector<int> &Del_Row, std::vector<int> &Del_Col)
{
    Cell *c;

    /*Najpierw przeszukaj tablicę i zaznacz te zera, gdzie występuje jedyne w wierszu i w kolumnie
     */
    for(unsigned int i = 0; i < M_Temporary.Row(); ++i)
    {
        /*Sprawdź, czy ten wiersz nie jest wykreślony, jeśli jest, omiń ten wiersz
         */
        if(IsDeleted(Del_Row, i) == true) continue;

        /*Zlicz, ile jest zer w tym wierszu, jeśli liczba jest różna od jeden - omiń ten wiersz
         *Interesuje mnie ten wiersz tylko wtedy, gdy jest tu jedno zero.
         */
        if(CountZeroRow(i, false) != 1) continue;

        for(unsigned int j = 0; j < M_Temporary.Col(i); ++j)
        {
            /*Pobierz komórkę, jeśli nie jest zerem, to omiń ją
             */
            c = M_Temporary.GetCell(i, j);
            if(c == 0) return;

            if(c->GetValue() != 0) continue;

            /*Sprawdź, czy kolumna nie jest wykreślona, jeśli jest - omiń ją
             */
            if(IsDeleted(Del_Col, j) == true) continue;

            /*Sprawdź czy w kolumnie jest tylko jedno zero (włącznie z tym zerem w którym się znalazłem).
             */
            if(CountZeroCol(j, false) != 1) continue;

            /*Dobra, jest to zero, które szukałem, oznacz je
             */
            c->SetAsterisk(true);
            Del_Row.push_back(i);
            Del_Col.push_back(j);
            break;
        }
    }
}

void Algorithm::AsteriskRowCol(std::vector<int> &Del_Row, std::vector<int> &Del_Col)
{
    Cell *c;

    for(unsigned int i = 0; i < M_Temporary.Row(); ++i)
    {
        /*Sprawdź, czy ten wiersz nie jest wykreślony, jeśli jest, omiń ten wiersz
         */
        if(IsDeleted(Del_Row, i) == true) continue;

        for(unsigned int j = 0; j < M_Temporary.Col(i); ++j)
        {
            /*Sprawdź, czy kolumna nie jest wykreślona, jeśli jest - omiń ją
             */
            if(IsDeleted(Del_Col, j) == true) continue;

            /*Pobierz komórkę, jeśli nie jest zerem, to omiń ją
             */
            c = M_Temporary.GetCell(i, j);
            if(c == 0) return;

            if(c->GetValue() != 0) continue;

            /*Dobra, jest to zero, które szukałem, oznacz je
             */
            c->SetAsterisk(true);
            Del_Row.push_back(i);
            Del_Col.push_back(j);
            break;
        }
    }
}

void Algorithm::Merge_Asterisk_To_Matrix()
{
    for(unsigned int i = 0; i < M_Original->Row(); ++i)
    {
        for(unsigned int j = 0; j < M_Original->Col(i); ++j)
        {
            M_Original->GetCell(i, j)->SetAsterisk(M_Temporary.GetCell(i, j)->isAsterisk());
        }
    }
}
