#include "incudes.h"


class Node //����� ���� ��� ����������� ������, �� �������� ����� ������� ������� ��� ���������
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

struct MyCompare //���������� ��� ���������� ���������� �� ���� � ������
{
	bool operator()(const Node* l, const Node* r) const { return l->a < r->a; }
};

vector<bool> code;//������ ��� �������� ���� �������, ����������, ��� ��� ���������� ��������
map<char, vector<bool> > table;//������� ���������, ��� ������� ������� ������������ ���� ���, ����������, ��� ��� ���������� � 2-� ��������

void BuildTable(Node* root)//������� ��� �������� �������
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
	//������ ������� ������, ��� ������� ����� ������, ������� ��� �����������
	cout << "������� �������� ����� (� �����������), ���� �� � ����� ����� � ����������, ���� ������� ������ ���� �� �����, ������� ����������: ";
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
	cout << "���� ������" << endl;

	//������ ������ �� ������� ������
	list<Node*> lst;
	for (map<char, int>::iterator itr = freq.begin(); itr != freq.end(); ++itr)
	{
		Node* p = new Node;
		p->c = itr->first;
		p->a = itr->second;
		lst.push_back(p);
	}
	cout << "������ ������ ������" << endl;

	//������ ������, �� �������� ����� ��������� ������� ���������
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
	cout << "������ �������" << endl;

	Node* root = lst.front();   //root - ��������� �� ������� ������

	//������ ������� ���������, ���� ������� ����� � ���������� ���������� table
	BuildTable(root);
	cout << "������� �������" << endl;
	cout << "���������� ��� � ����" << endl;
	//������� ���� � �������� ����
	f.clear(); f.seekg(0); // ���������� ��������� ����� � ������ �����

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
	

	//���������� ������� ����� � ����� ��������������� �����w
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
	cout << "������ ������ �������� � ���� 'output.bin'." << endl;


	//�������������� ����� ������� � ����� ����������(������ ��������� � ����������� �������)
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