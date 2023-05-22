#include "incudes.h"

void LZ78()
{
    string text="", sub_str = "";
    HANDLE descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
    short key = 0, code = 0;
    do
    {
        system("cls");
        key = key % 2;
        code = 0;
        if (key == 0)
        {
            SetConsoleTextAttribute(descriptor, 2);
            cout << "1. ���� �������" << endl;
            SetConsoleTextAttribute(descriptor, 7);
            cout << "2. ���� � �����" << endl;
        }
        if (key)
        {
            cout << "1. ���� �������" << endl;
            SetConsoleTextAttribute(descriptor, 2);
            cout << "2. ���� � �����" << endl;
            SetConsoleTextAttribute(descriptor, 7);
        }
        if (code != 13)
        {
            code = _getch();
            if (code == 80 || code == 115)
                ++key;
            if (code == 72 || code == 119)
                --key;
        }
    } while (code != 13);
    system("cls");
    switch (key)
    {
    case 0:
    {
        cout << "������� �����: ";
        getline(cin, text);
        break; 
    }
    case 1:
    {
        cout << "������� �������� ����� (� �����������), ���� �� � ����� ����� � ����������, ���� ������� ������ ���� �� �����, ������� ����������: ";
        string file;
        cin >> file;
        ifstream f(file, ios::in | ios::binary);
        while (!f.eof())
        {
            getline(f, sub_str);
            text += sub_str;
        }
        cout << "���� ������" << endl;
        f.close();
        break; 
    }
    default:
        cout << "error found, fix it!" << endl;
        break;
    }
    ofstream g("output.bin");
    map<string, int> dict;
    int index = 1;
    dict[""] = 0;
    for (int i = 0; i < text.length(); i++)
    {
        
        string temp= "";
        temp += text[i];
        while (dict.find(temp) != dict.end())
        {
            i++;
            temp += text[i];
        }
        cout << dict.at(temp.substr(0, temp.size() - 1)) << temp.back();
        g << dict.at(temp.substr(0, temp.size() - 1)) << temp.back();
        dict[temp] = index;
        //cout << index << temp << endl;//�������
        index++;
    }
    g.close();
    cout << "\n������ ������ �������� � ���� 'output.bin'." << endl;
    text.clear();
    cout << "������������ ���� �������?[Y(y)/N(n)]: ";
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y')
    {
        cout << "�������������:" << endl;
        ifstream F("output.bin", ios::in | ios::binary);
        while (!F.eof())
        {
            getline(F, sub_str);
            text += sub_str;
        }
        for (int i = 0; i < text.length(); i++)
        {
            cout << text[i];
        }
        F.close();
    }
}