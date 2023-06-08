#include "HA.h"
#include "AC.h"
#include "RLE.h"
#include "LZ78.h"
#include "BWT.h"
#include "MTF.h"

int main()
{
    setlocale(0, "");
    setlocale(LC_NUMERIC, "eng");
    HANDLE descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
    short key = 0, code = 0;
    cout << "Выберете алгоритм сжатия:" << endl;
    do
    {
        system("cls");
        key = (key + 7) % 7;
        code = 0;
        if (key == 0)
        {
            SetConsoleTextAttribute(descriptor, 2);
            cout << "1. Алгоритм Хаффмана (HA)" << endl;
            SetConsoleTextAttribute(descriptor, 7);
            cout << "2. Кодирование длин серий (RLE)" << endl;
            cout << "3. Алгоритм Лемпеля-Зива (LZ78)" << endl;
            cout << "4. Преобразование Барроуза-Уиллера (BWT)" << endl;
            cout << "5. Преобразование MTF" << endl;
            cout << "6. Арифметическое кодирование (AC)" << endl;
            cout << "7. PPM алгоритм" << endl;
        }
        if (key == 1)
        {
            cout << "1. Алгоритм Хаффмана (HA)" << endl;
            SetConsoleTextAttribute(descriptor, 2);
            cout << "2. Кодирование длин серий (RLE)" << endl;
            SetConsoleTextAttribute(descriptor, 7);
            cout << "3. Алгоритм Лемпеля-Зива (LZ78)" << endl;
            cout << "4. Преобразование Барроуза-Уиллера (BWT)" << endl;
            cout << "5. Преобразование MTF" << endl;
            cout << "6. Арифметическое кодирование (AC)" << endl;
            cout << "7. PPM алгоритм" << endl;
        }
        if (key == 2)
        {            
            cout << "1. Алгоритм Хаффмана (HA)" << endl;            
            cout << "2. Кодирование длин серий (RLE)" << endl;
            SetConsoleTextAttribute(descriptor, 2);
            cout << "3. Алгоритм Лемпеля-Зива (LZ78)" << endl;
            SetConsoleTextAttribute(descriptor, 7);
            cout << "4. Преобразование Барроуза-Уиллера (BWT)" << endl;
            cout << "5. Преобразование MTF" << endl;
            cout << "6. Арифметическое кодирование (AC)" << endl;
            cout << "7. PPM алгоритм" << endl;
        }
        if (key == 3)
        {            
            cout << "1. Алгоритм Хаффмана (HA)" << endl;            
            cout << "2. Кодирование длин серий (RLE)" << endl;
            cout << "3. Алгоритм Лемпеля-Зива (LZ78)" << endl;
            SetConsoleTextAttribute(descriptor, 2);
            cout << "4. Преобразование Барроуза-Уиллера (BWT)" << endl;
            SetConsoleTextAttribute(descriptor, 7);
            cout << "5. Преобразование MTF" << endl;
            cout << "6. Арифметическое кодирование (AC)" << endl;
            cout << "7. PPM алгоритм" << endl;
        }
        if (key == 4)
        {
            cout << "1. Алгоритм Хаффмана (HA)" << endl;            
            cout << "2. Кодирование длин серий (RLE)" << endl;
            cout << "3. Алгоритм Лемпеля-Зива (LZ78)" << endl;
            cout << "4. Преобразование Барроуза-Уиллера (BWT)" << endl;
            SetConsoleTextAttribute(descriptor, 2);
            cout << "5. Преобразование MTF" << endl;
            SetConsoleTextAttribute(descriptor, 7);
            cout << "6. Арифметическое кодирование (AC)" << endl;
            cout << "7. PPM алгоритм" << endl;
        }
        if (key == 5)
        {           
            cout << "1. Алгоритм Хаффмана (HA)" << endl;            
            cout << "2. Кодирование длин серий (RLE)" << endl;
            cout << "3. Алгоритм Лемпеля-Зива (LZ78)" << endl;
            cout << "4. Преобразование Барроуза-Уиллера (BWT)" << endl;
            cout << "5. Преобразование MTF" << endl;
            SetConsoleTextAttribute(descriptor, 2);
            cout << "6. Арифметическое кодирование (AC)" << endl;
            SetConsoleTextAttribute(descriptor, 7);
            cout << "7. PPM алгоритм" << endl;
        }
        if (key == 6)
        {            
            cout << "1. Алгоритм Хаффмана (HA)" << endl;           
            cout << "2. Кодирование длин серий (RLE)" << endl;
            cout << "3. Алгоритм Лемпеля-Зива (LZ78)" << endl;
            cout << "4. Преобразование Барроуза-Уиллера (BWT)" << endl;
            cout << "5. Преобразование MTF" << endl;
            cout << "6. Арифметическое кодирование (AC)" << endl;
            SetConsoleTextAttribute(descriptor, 2);
            cout << "7. PPM алгоритм" << endl;
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
        Huffman_alg();//Алгоритм Хаффмана (HA)
        break;
    case 1:
        RLE();//Кодирование длин серий (RLE)
        break;
    case 2:
        LZ78();//Алгоритм Лемпеля-Зива (LZ78)
        break;
    case 3:
        BWT();//Преобразование Барроуза-Уиллера (BWT)
        break;
    case 4:
        MTF();//Преобразование MTF
        break;
    case 5:
        ArithmeticCoding();//Арифметическое кодирование (AC)
        break;
    case 6:
        cout << "Not implenented yet" << endl;//PPM алгоритм
        break;
    default:
        cout << "invalid input" << endl;
        break;
    }
    system("pause");
}
