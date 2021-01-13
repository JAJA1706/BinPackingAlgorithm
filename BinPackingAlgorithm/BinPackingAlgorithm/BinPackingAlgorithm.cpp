#include <iostream>
#include "BinPacking.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

enum Wybor
{
    wyjdz = 0,
    z_pliku = 1
};
void program_z_pliku(std::string);
void clear_screen();

int main()
{
    int opcja = -1;

    while (static_cast<Wybor>(opcja) != Wybor::wyjdz)
    {
        clear_screen();
        std::cout << "Program testujacy algorytm BinPacking." << std::endl << "Wybierz opcje:" << std::endl;
        std::cout << "0. Wyjdz" << std::endl << "1. Uruchom program dla danych z pliku." << std::endl;
        std::cin >> opcja;
    
            switch (static_cast<Wybor>(opcja))
            {
            case Wybor::z_pliku:
                std::string filename;
                std::cout << "Podaj nazwe pliku:" << std::endl;
                std::cin >> filename;
                clear_screen();
                program_z_pliku(filename);
            }
            std::cout << "0. Wyjdz" << std::endl << "1. Powrot do programu" << std::endl;
            std::cin >> opcja;
    }

    /*float ar[] = { .85, .1, .9, .9, .1, .1, .1};
    BinPacking::mergeSort(ar, sizeof(ar)/sizeof(ar[0]));
    for (float item : ar)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    std::cout << BinPacking::BestFit(ar, sizeof(ar) / sizeof(ar[0])) << std::endl;
    */
    return 0;
}

void program_z_pliku(const std::string filename)
{
    
    std::ifstream file(filename);
    int count = 1;
    float value;

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<float> sizes;
        while (iss >> value)
        {
            sizes.push_back(value);
        }
        if (sizes.size() != 0)
            std::cout << "Wynik dla linii " << count << ": " << BinPacking::BestFit(&sizes[0], sizes.size()) << std::endl;
        else
            std::cout << "Wynik dla linii " << count << ": " << 0 << std::endl;
        ++count;
    }
    std::cout << std::endl;
    file.close();
}

void clear_screen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
