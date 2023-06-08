#include "incudes.h"


struct Segment
{
	long double left, right;
};


void ArithmeticCoding()
{
	cout << "Введите название файла (с расширением), если он в одной папке с программой, либо укажите полный путь до файла, включая расширение: ";
	string file;
	cin >> file;
	ifstream f(file);

	map<char, double>  freq;
	char c;
	string str, original_text="";
	double n = 0;//кол-во символов в тексте
	while (!f.eof())//создаём таблицу символ-кол-во его вхождений, сохраняем изначальный текст в original_text
	{
		getline(f, str);
		for (int i = 0; i < str.length(); i++)
		{
			c = str[i];
			freq[c]++;
			n++;
			original_text += c;
		}
	}



	for (map<char,double>::iterator itr = freq.begin(); itr != freq.end(); ++itr)//создаём таблицу вероятности вхождения буквы
	{
		
		itr->second = itr->second / n;
		cout << itr->first << ":" << itr->second << endl;
	}
	int num = -1;
	long factorial = 1.0;


	map<char, Segment> segments;//создаём таблицу сегментов, где каждый символ находится в отрезке от 0 до 1
	long double l = 0;
	for (map<char, double>::iterator itr = freq.begin(); itr != freq.end(); ++itr)
	{
		segments[itr->first].left = l;
		segments[itr->first].right = l + itr->second;
		l = segments[itr->first].right;
		cout<< setprecision(25) << itr->first << ":[" << segments[itr->first].left << ";" << segments[itr->first].right << ")" << endl;
	}
	ofstream g("output.bin");
	string result = "";
	long double left = 0, right = 1;//кодируем изначальную строку в некий код, представленный вещественным числом от 0 до 1
	for (int i = 0; i < original_text.size(); i++)
	{
		char ch = original_text[i];
		long double new_right = left + (right - left) * segments[ch].right;
		long double new_left = left + (right - left) * segments[ch].left;

		while (1)
		{
			if (new_right < 0.5)
			{
				result += '0';
				new_left *= 2;
				new_right *= 2;
			}
			else if (new_left >= 0.5)
			{
				result += '1';
				new_left = (new_left-0.5)*2;
				new_right = (new_right - 0.5) * 2;
			}
			else if (new_left < 0.5 && new_left >= 0.25 && new_right < 0.75 && new_right >= 0.5)
			{
				result += '1';
				new_left = (new_left - 0.25) * 2;
				new_right = (new_right - 0.25) * 2;
				break;
			}
			else
			{
				break;
			}
		}
		//right = new_right;
		//left = new_left;
		////cout << left << ";" << right << endl;
		//if (right == left)
		//{
		//	result = (left + right) / 2;
		//	cout << result << ';';
		//	g << result << ';';
		//	left = 0;
		//	right = 1;
		//}
	}
	cout << result << endl;
	g << result;
	g.close();
	//long double result = (left + right) / 2;
	//cout << "закодировано в " << result << endl;
	cout << "файл считан" << endl;

	cout << "Декодировать файл обратно?[Y(y)/N(n)]: ";
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		cout << "декодирование: " << endl;
		ifstream F("output.bin", ios::in | ios::binary);


		string decode = "";
		while (!F.eof())
		{
			string sub_str;
			getline(F, sub_str,'\n');
			cout << sub_str << endl;
			double low = 0, high = 1, value = 0;
			

			for (int i = 0; i < sub_str.length(); i++)
			{
				string temp = "";
				temp += sub_str[i];
				value = value * 2 + stoi(temp);
				double range = high - low;
				for (map<char, Segment>::iterator j = segments.begin(); j != segments.end(); j++)
				{
					long double sym_range = j->second.right - j->second.left;
					if (j->second.left<=(value-low)/range && (value - low) / range < j->second.right)
					{
						//decode += j->first;
						cout << j->first;
						high = low + sym_range * range;
						low = low + j->second.left * range;
						break;
					}
				}
			}

















			//cout << sub_str << endl;
			//double result = stod(sub_str);
			//cout << result << endl;
			//for (map<char, Segment>::iterator j = segments.begin(); j != segments.end(); j++)
			//{
			//	if (result >= j->second.left && result < j->second.right)
			//	{
			//		decode += j->first;
			//		result = (result - j->second.left) / (j->second.right - j->second.left);
			//		left = j->second.left;
			//		right = j->second.right;
			//		//cout << result;
			//		break;
			//	}
			//}
		}
		cout << decode << endl;
	}
}