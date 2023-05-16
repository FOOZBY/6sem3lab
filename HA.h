#include "incudes.h"


class Node //класс узла для составления списка, по которому будет создана таблица для кодировки
{
public:
	int a = 0;
	char c = ' ';
	Node* left, * right;

	Node() { left = right = NULL; }

	Node(Node* L, Node* R)
	{
		left = L;
		right = R;
		a = L->a + R->a;
	}
};

struct MyCompare //компаратор для сортировки указателей на узлы в списке
{
	bool operator()(const Node* l, const Node* r) const { return l->a < r->a; }
};

vector<bool> code;//вектор для хранения кода символа, глобальный, так как используем рекурсию
map<char, vector<bool> > table;//таблица кодировки, где каждому символу соответсвует свой код, глобальная, так как используем в 2-х функциях

void BuildTable(Node* root)//функция для создания таблицы
{
	if (root->left != NULL)
	{
		code.push_back(0);
		BuildTable(root->left);
	}

	if (root->right != NULL)
	{
		code.push_back(1);
		BuildTable(root->right);
	}

	if (root->left == NULL && root->right == NULL)
		table[root->c] = code;

	
	if (code.size())
		code.pop_back();

	
}

void Huffman_alg()
{
	//создаём таблицу частот, где смотрим какой символ, сколько раз считывается
	cout << "Введите название файла (с расширением), если он в одной папке с программой, либо укажите полный путь до файла, включая расширение: ";
	string file;
	cin >> file;
	ifstream f(file);

	map<char, int> freq;
	char c;
	string str;
	while (!f.eof())
	{
		getline(f, str);
		for (int i = 0; i < str.length(); i++)
		{
			c = str[i];
			freq[c]++;
		}
	}
	cout << "файл считан" << endl;

	//создаём список из таблицы частот
	list<Node*> lst;
	for (map<char, int>::iterator itr = freq.begin(); itr != freq.end(); ++itr)
	{
		Node* p = new Node;
		p->c = itr->first;
		p->a = itr->second;
		lst.push_back(p);
	}
	cout << "список частот создан" << endl;

	//создаём дерево, по которому будем создавать таблицу кодировки
	while (lst.size() != 1)
	{
		lst.sort(MyCompare());

		Node* SonL = lst.front();
		lst.pop_front();
		Node* SonR = lst.front();
		lst.pop_front();

		Node* parent = new Node(SonL, SonR);
		lst.push_back(parent);

	}
	cout << "дерево создано" << endl;

	Node* root = lst.front();   //root - указатель на вершину дерева

	//создаём таблицу кодировки, сама таблица будет в глобальной переменной table
	BuildTable(root);
	cout << "таблица создана" << endl;
	cout << "записываем код в файл" << endl;
	//выводим коды в бинарный файл
	f.clear(); f.seekg(0); // перемещаем указатель снова в начало файла

	ofstream g("output.bin");

	int count = 0; 
	char buf = 0;
	while (!f.eof())
	{
		getline(f, str);
		for (int i = 0; i < str.length(); i++)
		{
			
			c = str[i];
			vector<bool> x = table[c];
			for (int n = 0; n < x.size(); n++)
			{
				buf = buf | x[n] << (7 - count);
				count++;
				if (count == 8) 
				{ 
					count = 0;   
					g << buf; 
					buf = 0; 
				}
			}
		}
	}
	

	//добавления таблицы кодов в конец закодированного файлаw
	/*for (map<char, vector<bool>>::iterator itr = table.begin(); itr != table.end(); ++itr)
	{
		g << "(" << itr->first << ':';
		for (int i = 0; i < itr->second.size(); i++)
		{
			g << itr->second[i];
		}
		g << ")";
	}*/

	f.close();
	g.close();
	cout << "сжатые данные записаны в файл 'output.bin'." << endl;


	//раскодирование файла обратно и вывод результата(должно совпадать с изначальным текстом)
	/*ifstream F("output.bin", ios::in | ios::binary);
	Node* p = root;
	count = 0; 
	char byte;
	byte = F.get();
	while (!F.eof())
	{
		bool b = byte & (1 << (7 - count));
		if (b)
			p = p->right; 
		else 
			p = p->left;
		if (p && (p->left == NULL && p->right == NULL)) 
		{ 
			cout << p->c; 
			p = root; 
		}
		count++;
 		if (count == 8) 
		{ 
			count = 0;
			byte = F.get(); 
		}
	}

	F.close();*/
}