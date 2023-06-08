#include "incudes.h"

void MTF()
{
    string text = "", sub_str = "";
    HANDLE descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
    short key = 0, code = 0;
    set<char> char_table;
    do
    {
        system("cls");
        key = key % 2;
        code = 0;
        if (key == 0)
        {
            SetConsoleTextAttribute(descriptor, 2);
            cout << "1. ¬вод вручную" << endl;
            SetConsoleTextAttribute(descriptor, 7);
            cout << "2. ¬вод с файла" << endl;
        }
        if (key)
        {
            cout << "1. ¬вод вручную" << endl;
            SetConsoleTextAttribute(descriptor, 2);
            cout << "2. ¬вод с файла" << endl;
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
        cout << "¬ведите текст: ";
        getline(cin, text);
        break;
    }
    case 1:
    {
        cout << "¬ведите название файла (с расширением), если он в одной папке с программой, либо укажите полный путь до файла, включа€ расширение: ";
        string file;
        cin >> file;
        ifstream f(file, ios::in | ios::binary);
        while (!f.eof())
        {
            getline(f, sub_str);
            text += sub_str;
            for (int i = 0; i < sub_str.length(); i++)
            {
                char_table.insert(sub_str[i]);
            }
        }
        cout << "файл считан" << endl;
        f.close();
        break;
    }
    default:
        cout << "error found, fix it!" << endl;
        break;
    }
    vector<char> vec;
    for (set <char> ::iterator it = char_table.begin(); it != char_table.end(); it++)
    {
        vec.push_back(*it);
    }

    string encode = "";

    for (int i = 0; i < text.length(); i++)
    {
        for (int j = 0; j < vec.size(); j++)
        {
            if (text[i] == vec[j])
            {
                encode += to_string(j)+=" ";
                vec.insert(vec.begin(), vec[j]);
                vec.erase(vec.begin()+j+1);
                break;
            }
        }
    }
    cout << encode << endl;
    ofstream g("output.bin");
    g << encode;
    g.close();
    sort(vec.begin(), vec.end());
    cout << "ƒекодировать файл обратно?[Y(y)/N(n)]: ";
    char choice;
    cin >> choice;
    text.clear();
    if (choice == 'Y' || choice == 'y')
    {
        cout << "ƒекодирование:" << endl;
        ifstream F("output.bin", ios::in | ios::binary);
        string decode = "";
        while (!F.eof())
        {
            getline(F, sub_str);
            text += sub_str;
        }
        for (int i = 0; i < text.length(); i++)
        {
            string num="";
            while (isdigit(text[i]))
            {
                num += text[i];
                i++;
            }
            int pos = stoi(num);
            decode += vec[pos];
            vec.insert(vec.begin(), vec[pos]);
            vec.erase(vec.begin() + pos + 1);
        }
        cout << decode << endl;
    }
}