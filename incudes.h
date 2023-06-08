#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>//handle
#include <conio.h>//_getch
#include <vector>
#include <map>
#include <list>
#include <iomanip>
#include <algorithm>
#include <set>
#include <chrono>

using namespace std;

string get_text_from_file()
{
	string str, file;
    cout << "Введите название файла, если он в одной папке с программой, либо путь до файла целиком: ";
    cin >> file;
    ifstream in(file); // окрываем файл для чтения
    if (in.is_open())
    {
        while (std::getline(in, str))
        {
            std::cout << str << std::endl;
        }
    }
    in.close();
	return str;
}

void put_text_to_file(string str)
{
    string file;
    cout << "Введите название сохраняемого файла: ";
    cin >> file;
    ofstream out;          // поток для записи
    out.open(file);      // открываем файл для записи
    if (out.is_open())
    {
        out << str << std::endl;
    }
    out.close();
    std::cout << "File has been written" << std::endl;
}