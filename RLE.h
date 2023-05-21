#include "incudes.h"

void RLE()
{
    cout << "Введите название файла (с расширением), если он в одной папке с программой, либо укажите полный путь до файла, включая расширение: ";
    string file;
    cin >> file;
    ifstream f(file, ios::in | ios::binary);
    string str, sub_str="";
    while (!f.eof())
    {
        getline(f, sub_str);
        str += sub_str;
    }
    cout << "файл считан" << endl;
    f.close();
    ofstream g("output.bin");
    int n = str.length();
    for (int i = 0; i < n; i++) 
    {
        sub_str = "";
        int count = 0;
        while (i < n && str[i] != str[i+1])
        {
            sub_str += str[i];
            count++;
            i++;
        }
        if(count) 
            cout << count * (-1) << sub_str;
        g << count * (-1) << sub_str;
        sub_str = "";
        count = 1;
        while (i < n && str[i] == str[i + 1])
        {
            sub_str += str[i];
            count++;
            i++;
        }
        if (i != n) 
        { 
            cout << count << str[i]; 
            g << count << str[i];
        }
        // Count occurrences of current character
        /*int count = 1;
        while (i < n - 1 && str[i] == str[i + 1]) 
        {
            count++;
            i++;
        }*/
        // Print character and its count
        /*cout << str[i] << count;
        g << str[i] << count;*/
    }
    g.close();
    cout << "\nсжатые данные записаны в файл 'output.bin'." << endl;

    cout << "Декодировать файл обратно?[Y(y)/N(n)]: ";
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y')
    {
        cout << "Декодирование:" << endl;
        ifstream F("output.bin", ios::in | ios::binary);
        while (!F.eof())
        {
            getline(F, sub_str);
            str += sub_str;
        }
        for (int i = 0; i < str.length(); i++)
        {
            sub_str = "";
            if (str[i] == '-')
            {
                i++;
                while (isdigit(str[i]))
                {
                    sub_str += str[i];
                    i++;
                }
                int count = stoi(sub_str);
                for (int j = 0; j < count; j++)
                {
                    cout << str[j + i];
                }
            }
            if (isdigit(str[i]))
            {
                while (isdigit(str[i]))
                {
                    sub_str += str[i];
                    i++;
                }
                int count = stoi(sub_str);
                for (int j = 0; j < count; j++)
                {
                    cout << str[i];
                }
            }
        }
    }
}