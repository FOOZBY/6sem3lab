#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>//handle
#include <conio.h>//_getch
#include <vector>
#include <map>
#include <list>

using namespace std;

string get_text_from_file()
{
	string str, file;
    cout << "¬ведите название файла, если он в одной папке с программой, либо путь до файла целиком: ";
    cin >> file;
    ifstream in(file); // окрываем файл дл€ чтени€
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
    cout << "¬ведите название сохран€емого файла: ";
    cin >> file;
    ofstream out;          // поток дл€ записи
    out.open(file);      // открываем файл дл€ записи
    if (out.is_open())
    {
        out << str << std::endl;
    }
    out.close();
    std::cout << "File has been written" << std::endl;
}