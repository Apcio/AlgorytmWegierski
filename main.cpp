#include "Program.h"
#include <iostream>

int main(int argc, char* argv[])
{
    Program p(argc, argv);
    int status = p.Run();
    std::cout << "\n\n" << "Kod wyjscia: " << status << "\n";
    return status;
}
