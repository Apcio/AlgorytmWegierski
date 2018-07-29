#include "Program.h"

int Program::Run()
{
    /*Upewniam się, że jest ścieżka do pliku
     */
    if(ArgsGood == false) return WRONG_ARGS;

    if(LoadMatrix() == false) return WRONG_MATRIX;

    std::cout << "Liczba wierszy: " << M_Array.Row();
    std::cout << "\n" << "Liczba kolumn: " << M_Array.Col(0);
    ShowMatrix(M_Array);

    /*Ok, przygotowanie wstępne zakończne, macierz wczytana i poprawna, trzeba uruchomić algoryt. Zaczynam od minimalizacji tabeli
     *i po jej zminimalizowaniu, wyświetlam wynik
     */
    Alg = new Algorithm(&M_Array);
    Alg->OpeningStage();

    std::cout << "\n\n\n" << "Etap wstepny zakonczony";
    ShowMatrix(Alg->GetMatrix());

    /*Ok, teraz czas na etap iteracyjny, czyli wykreślenie elementów zerowych
     */
    unsigned int steps = 0;

    while(Alg->IsEndIterations() != true)
    {
        Alg->IterationStage();

        std::cout << "\n\n\n" << "Etap iteracji numer: " << ++steps;
        ShowMatrix(Alg->GetMatrix());
    }

    /*Spoko, etap iteracyjny zakończony, teraz etap końcowy
     */
    Alg->EndingStage();

    std::cout << "\n\n\n" << "Etap koncowy zakonczony";
    ShowMatrix(M_Array);

    /*Etap końcowy zakończony, podane są już komórki, które są optymalne, teraz wystarczy tylko zapisać graf
     */
    std::cout << "\n\n\n" << "Etap koncowy zakonczony. Przyipsane wartosci:\n";
    ShowGraph();

    /*Wszystko w porządku, program zakończy się z odpowiednim numerem kodu
     */
    return EXIT_SUCCESS;
}

bool Program::LoadMatrix()
{
    /*Przygotowuję się do wczytania pliku i jego zawartości, najpierw inicjalizacja zmiennych
     */
    std::fstream file;
    file.open(FilePath, std::ios_base::in);

    /*Ooops - coś jest nie tak ze ścieżką - możliwe, że nie poprawna
     */
    if(file.is_open() == false) return false;

    std::string digit;
    int status = READ_NOSTATUS;

    /*Ponieważ do poprawnego działania muszę najpierw dodać wiersz dla macerzy, aby bbyło gdzie wstawiać elelemnty
     *dodaję tutaj wywołanie metody SetNewRow() z Matrix, a usuwam z konstruktowa. Po prostu bedę miał większą kontrolę nad tym
     */
    M_Array.SetNewRow();

    /*Tutaj wykonuję pętlę, dopóki nie odczytam całej macierzy
     */
    while(status != READ_END)
    {
        status = ReadFile(file, digit);

        M_Array.AddElement(Cell(std::stoul(digit)));
        if(status == READ_ROW) M_Array.SetNewRow();
    }

    file.close();
    return M_Array.isGood();
}

int Program::ReadFile(std::fstream &file, std::string &input)
{
    char c;
    input.clear();

    /*No, ok, czytam, dopóki nie natrafię na koniec pliku, czytam po jednym znaku, sprawdzam i dopasowuje znak
     *do odpowiedniej kategorii
     */
    while(file.good() != false)
    {
        c = file.get();

        switch (c)
        {
        /*Przeczytałem znak spacji, więc cała liczba została wczytana
         */
        case ' ':
            return READ_DIGIT;
            break;

         /*Przeczytałem znak końca wiersza, więc cała liczba została wczytana
         */
        case '\0':
        case '\n':
            return READ_ROW;
            break;

        /*Domyślnie to dodaję znak do mojego łańcucha
         */
        default:
            input.push_back(c);
            break;
        }
    }

    return READ_END;
}

void Program::ShowMatrix(const Matrix &M) const
{
    unsigned int rows = M.Row();
    unsigned int col = M.Col(rows - 1);

    std::cout << "\n\n";

    Cell *c;

    for(unsigned int i = 0; i < rows; ++i)
    {
        for(unsigned int j = 0; j < col; ++j)
        {
            c = M.GetCell(i,j);
            if(c == 0) return;

            std::cout << c->GetValue();
            if(c->isAsterisk() == true) std::cout << "*";
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

void Program::ShowGraph()
{
    Cell *c;

    for(unsigned int i = 0; i < M_Array.Row(); ++i)
        for(unsigned int j = 0; j < M_Array.Col(i); ++j)
        {
            c = M_Array.GetCell(i,j);
            if(c == 0) return;

            if(c->isAsterisk() == false) continue;

            std::cout << "Komputer<" << i << "> -> Hot-Spot<" << j << "> (" << c->GetValue() << ")";
            std::cout << "\n";
        }
}
