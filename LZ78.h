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
        }
        cout << "файл считан" << endl;
        f.close();
        break; 
    }
    default:
        cout << "error found, fix it!" << endl;
        break;
    }
    auto st = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - st;
    st = chrono::high_resolution_clock::now();
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
        //cout << dict.at(temp.substr(0, temp.size() - 1)) << temp.back();
        g << dict.at(temp.substr(0, temp.size() - 1)) << "." << temp.back();
        dict[temp] = index;
        //cout << index << temp << endl;//словарь
        index++;
    }
    g.close();
    end = chrono::high_resolution_clock::now();
    duration = end - st;
    cout << "¬рем€ кодировки: " << duration.count() << "mils" << endl;
    cout << "\nсжатые данные записаны в файл 'output.bin'." << endl;
    text.clear();
    map<int, string> decoding_dict;
    decoding_dict[0] = "";
    string s_num = "";
    int num;
    index = 1;
    cout << "ƒекодировать файл обратно?[Y(y)/N(n)]: ";
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y')
    {
        cout << "ƒекодирование:" << endl;
        ifstream F("output.bin", ios::in | ios::binary);
        while (!F.eof())
        {
            getline(F, sub_str);
            text += sub_str;
        }
        for (int i = 0; i < text.length(); i++)
        {
            while (isdigit(text[i]))
            {
                s_num += text[i];
                i++;
            }
            num = stoi(s_num);
            s_num.clear();
            cout << decoding_dict[num];
            if (text[i] == '.' && i < text.length())
            {
                i++;
                cout << text[i];
            }
            decoding_dict[index] = decoding_dict[num] + text[i];
            index++;
        }
        F.close();
    }
}