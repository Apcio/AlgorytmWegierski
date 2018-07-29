#include "Matrix.h"

Cell *Matrix::GetCell(unsigned int row, unsigned int col) const
{
    if(row > (Row() - 1) || col > (Col(row) - 1)) return 0;

    std::vector <Cell> &tmp = Array->at(row);

    return &tmp.at(col);
}

bool Matrix::isGood()
{
    for(unsigned int i = 1; i < Row(); ++i)
    {
        if(Array->at(i - 1).size() != Array->at(i).size())
        {
            Good = false;
            break;
        }
    }

    return Good;
}

std::vector< Cell > *Matrix::GetRow(unsigned int R)
{
    if(R > Row()) return 0;

    std::vector <Cell> &tmp = Array->at(R);
    return &tmp;
}
