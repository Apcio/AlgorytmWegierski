#ifndef CELL_H
#define CELL_H

/*Klasa Cell przechowje zawartośc komórki w macierzy. Przechowuje także informacje, czy została skreślona itd.
 */

class Cell
{
public:
    /*Konstruktor
     */
    Cell(int val)
    {
        Value = val;
        Underlines = 0;
        Asterisk = false;
    }

    /*Konstruktor kopiujący
     */
    Cell(const Cell &other)
    {
        this->Value = other.Value;
        this->Underlines = other.Underlines;
        this->Asterisk = other.Asterisk;
    }

    /*Konstruktor domyślny
     */
    Cell()
    {
        Value = 0;
        Underlines = 0;
        Asterisk = false;
    }

    int GetValue() const
    {
        return Value;
    }

    int GetUnderlines() const
    {
        return Underlines;
    }

    bool isAsterisk() const
    {
        return Asterisk;
    }

    void SetValue(int v)
    {
        Value = v;
    }

    void SetUnderline(int v)
    {
        Underlines = v;
    }

    void SetAsterisk(bool t)
    {
        Asterisk = t;
    }

private:
    /*Zmienna Value przechowuje zawartość komórki
     */
    int Value;

    /*Zmienna Underline przechowuje informacje ile razy zmienna została skreślona przez kroki pętli
     */
    int Underlines;

    /*Zmienna Asterisk przechowuje informacje, czy komórka została wybrana na końcowym etapie
     */
    bool Asterisk;

};

#endif // CELL_H
