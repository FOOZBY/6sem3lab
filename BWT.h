#include "incudes.h"

string cyclic_shift(string source, int distance) 
{
    return source.substr(distance, string::npos) + source.substr(0, distance);
}

bool comp_tuples(pair<char, int> a, pair<char, int> b) 
{
    return (a.first < b.first);
}

void BWT()//декодирует, только когда в тексте нет символов, имеющих отрицательное значение
{
    
    int eof = 0;
    string text = "", sub_str = "";
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

    text += (char)(eof);
    cout << (char)(eof) << endl;

    //Generate the n cyclic shifts and put them in a list
    vector<string> shifts;

    for (unsigned int i = 0; i < text.length(); i++) 
    {
        string shift = cyclic_shift(text, i);

        shifts.push_back(shift);
    }

    //Sort the list lexicographically
    sort(shifts.begin(), shifts.end());

    //Return a string comprised of the last letter of each word in the sorted list
    string encoding = "";

    for (vector<string>::iterator it = shifts.begin(); it != shifts.end(); it++) 
    {
        encoding += it->at(it->length() - 1);
    }
    ofstream g("output.bin");
    g << encoding;
    g.close();
    cout << "ƒекодировать файл обратно?[Y(y)/N(n)]: ";
    char choice;
    cin >> choice;
    text.clear();
    if (choice == 'Y' || choice == 'y')
    {
        cout << "ƒекодирование:" << endl;
        ifstream F("output.bin", ios::in | ios::binary);
        while (!F.eof())
        {
            getline(F, sub_str);
            text += sub_str;
        }
        F.close();
        string decoding = "";
        vector<pair<char, int>> coding_tuples;
        int j = 0;
        for (unsigned int i = 0; i < text.length(); i++) 
        {
            char coded_char = text[i];
            //Find the index of the special end of text character
            if (coded_char == (char)(eof))
            {
                j = i;
            }
            coding_tuples.push_back(pair<char, int>(coded_char, i));
        }

        //Sort the tuples by their character preserving order (stable)
        /*
         * This is because the order in which we encountered the same character provides us
         * with a different index leading to a different cyclic shift and thus a different following character
         */
        stable_sort(coding_tuples.begin(), coding_tuples.end(), comp_tuples);

        //Follow the indicies to retrieve the letters in the source text

        do 
        {
            decoding = decoding + coding_tuples[j].first;
            j = coding_tuples[j].second;
        } while (coding_tuples[j].first != (char)(eof));

        cout << decoding << endl;
    }
}