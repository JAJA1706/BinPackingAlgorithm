#include <iostream>
#include "BinPacking.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <random>
#include <time.h>

#define GEN_SAVE_FILENAME "test_generowane.txt"

enum Wybor
{
    wyjdz = 0,
    z_pliku = 1,
    genenerowany = 2
};
void program_z_pliku(std::string);
void clear_screen();
void program_generowany(float, float, unsigned);
void generuj(float, float,unsigned, std::vector<float>&);

int main()
{
    int opcja = -1;

    while (static_cast<Wybor>(opcja) != Wybor::wyjdz)
    {
        clear_screen();
        std::cout << "Program testujacy algorytm BinPacking." << std::endl << "Wybierz opcje:" << std::endl;
        std::cout << "0. Wyjdz" << std::endl << "1. Uruchom program dla danych z pliku." << std::endl << "2. Uruchom program dla danych generowanych." << std::endl;
        std::cin >> opcja;
    
            switch (static_cast<Wybor>(opcja))
            {
            case Wybor::z_pliku:
                {
                std::string filename;
                std::cout << "Podaj nazwe pliku:" << std::endl;
                std::cin >> filename;
                clear_screen();
                program_z_pliku(filename);
                }
                break;
            case Wybor::genenerowany:
                {
                float bot, top;
                unsigned ilosc;
                std::cout << "Podaj najmniejsza liczbe generowana <0,1>:" << std::endl;
                std::cin >> bot;
                std::cout << "Podaj najwieksza liczbe generowana <0,1>:" << std::endl;
                std::cin >> top;
                if (bot > top)
                {
                    std::cout << "Najmniejsza liczba nie moze byc wieksza niz najmniejsza!" << std::endl;
                    break;
                }
                std::cout << "Podaj ilosc generowanych liczb:" << std::endl;
                std::cin >> ilosc;
                program_generowany(bot, top, ilosc);
                }
                break;
            }

            if(static_cast<Wybor>(opcja) != Wybor::wyjdz)
            {
                std::cout << "0. Wyjdz" << std::endl << "1. Powrot do programu" << std::endl;
                std::cin >> opcja;
            }
    }

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

void program_generowany(float bot, float top, unsigned ilosc)
{
    
    std::vector<float> sizes;
    std::ofstream file(GEN_SAVE_FILENAME);
    int res = -1;
    generuj(bot, top, ilosc, sizes);
    res = BinPacking::BestFit(&sizes[0], sizes.size());
    std::cout << "Wynik: " << res << std::endl << std::endl;

    std::cout << "Wygenerowane liczby oraz wynik zostaly zapisane do pliku test_generowane.txt" << std::endl;
    file << "Wygenerowane liczby: ";
    for (float f : sizes)
    {
        file << f << " ";
    }
    file << std::endl;
    file << "Wynik: " << res;
    file.close();
}

void generuj(float bot, float top, unsigned ilosc, std::vector<float>& vec)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis1(bot, top);
    for (unsigned i = 0; i < ilosc; ++i)
    {
        vec.push_back((float)dis1(gen));
    }
}

void clear_screen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
