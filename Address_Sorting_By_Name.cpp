#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#define NDEBUG
#include <cassert>

#define _ASSERT_MESSAGE(exp, msg) assert(((void)msg, exp))

class Address_Storage
{
    std::string Name_City;
    std::string Name_Street;
    int Num_House;
    int Num_Apartment;

public:
    void set_custom_address(std::string& city, std::string& street, int& house, int& apartment)
    {
        Name_City = city;
        Name_Street = street;
        Num_House = house;
        Num_Apartment = apartment;
    }

    std::string get_name_city()
    {
        return Name_City;
    }
/*
    std::string get_name_street()
    {
        return Name_Street;
    }

    int get_num_house()
    {
        return Num_House;
    }
*/
    std::string string_assembly()
    {
        return Name_City + ", " + Name_Street + ", " + std::to_string(Num_House) + ", " + std::to_string(Num_Apartment);
    }

    Address_Storage(const std::string city = "Санкт-Петербург", const std::string street = "Невский проспект", const int house = 17, const int apartment = 7)
    {
        Name_City = city;
        Name_Street = street;
        Num_House = house;
        Num_Apartment = apartment;
    }
};

void sort(Address_Storage* addresses, int &size)
{
    std::string str1, str2;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            _ASSERT_MESSAGE((j + 1) < size, "Превышен допустимый размер!");
//            assert((void("Превышен допустимый размер!"), (j + 1) < size));
            if (addresses[j].get_name_city() > addresses[j + 1].get_name_city())
                std::swap(addresses[j], addresses[j + 1]);

/*            if (addresses[j].get_name_city() == addresses[j + 1].get_name_city()) // Сортировка по названию улиц. Не нарушает сортировку по названиям городов
            {
                if (addresses[j].get_name_street() > addresses[j + 1].get_name_street())
                    std::swap(addresses[j], addresses[j + 1]);
            }*/

/*            if (addresses[j].get_name_city() == addresses[j + 1].get_name_city() && addresses[j].get_name_street() == addresses[j + 1].get_name_street() && addresses[j].get_num_house() > addresses[j + 1].get_num_house()) // Сортировка по номерам домов. Не нарушает сортировку по названиям городов и улиц
                std::swap(addresses[j], addresses[j + 1]);*/
        }
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    std::ifstream input("in.txt");

    if (input.is_open())
    {
        int size;
        input >> size;
        if (size <= 0)
        {
            std::cout << "Файл должен содержать больше 0 строк!\nПроверьте файл. Заполните строки и укажите их количество.";
            input.close();
            return 1;
        }
        else
        {
            Address_Storage* address_arr = new Address_Storage[size];
            std::string str1, str2;
            int tmp1, tmp2;

            for (int i = 0; i < size; i++)
            {
                if (!(input >> str1 >> str2 >> tmp1 >> tmp2))
                    break;
                address_arr[i].set_custom_address(str1, str2, tmp1, tmp2);
            }

            input.close();
            sort(address_arr, size);

            std::ofstream output("out.txt");
            output << size << std::endl;

            std::cout << "Количество строк: " << size << std::endl;

            for (int i = 0; i < size; i++)
            {
                std::cout << address_arr[i].string_assembly() << std::endl;
                output << address_arr[i].string_assembly() << std::endl;
            }

            output.close();
            delete[] address_arr;
        }
    }
    else
    {
        input.close();
        std::cout << "Файл поврежден или не найден!\nПроверьте файл и повторите попытку.";
        return 2;
    }
}
