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
    cout << "������� �������� �����, ���� �� � ����� ����� � ����������, ���� ���� �� ����� �������: ";
    cin >> file;
    ifstream in(file); // �������� ���� ��� ������
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
    cout << "������� �������� ������������ �����: ";
    cin >> file;
    ofstream out;          // ����� ��� ������
    out.open(file);      // ��������� ���� ��� ������
    if (out.is_open())
    {
        out << str << std::endl;
    }
    out.close();
    std::cout << "File has been written" << std::endl;
}