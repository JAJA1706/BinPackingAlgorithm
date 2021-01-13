#include <iostream>
#include "BinPacking.h"
#include <fstream>
#include <string>
#include "BinPackingAlgorithm.h"
#include <vector>

enum Wybor
{
    wyjdz = 0,
    z_pliku = 1
};
void program_z_pliku(std::string);

int main()
{
    int opcja = -1;
    std::cout << "Program testujacy algorytm BinPacking." << std::endl << "Wybierz opcje:" << std::endl;
    std::cout << "0. WyjdŸ" << std::endl << "1. Uruchom program dla danych z pliku." << std::endl;
    std::cin >> opcja;
    
    while (static_cast<Wybor>(opcja) != Wybor::wyjdz)
    {
        switch (static_cast<Wybor>(opcja))
        {
        case Wybor::z_pliku:
            std::string filename;
            std::cout << "Podaj nazwê pliku:" << std::endl;
            std::cin >> filename;
            program_z_pliku(filename);
        }
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
    int count = 0;
    float value;
    std::vector<float> sizes;
    while (file >> value)
    {
        sizes.push_back(value);
    }
    file.close();
    if (sizes.size() != 0)
        std::cout << BinPacking::BestFit(&sizes[0], sizes.size()) << std::endl;
    else
        std::cout << "Nie znaleziono pliku lub plik jest pusty." << std::endl;
}
