#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <locale>

using std::cin;
using std::cout;
using std::string;

class Game
{
protected:
	std::vector<string> buf;
	double total;
	enum ACT
	{
		num = '1',
		plus = '+',
		doubl = '�',
		delPrev = '�'
	};
public:
	void insert()
	{
		cout << "������ �������� ����� ����� (�������: 5 2 � � +) " << std::endl;
		string input;
		std::getline(cin, input);
		std::istringstream stream(input);

		std::string value;
		while (stream >> value) { buf.push_back(value); }

		if (check() != true) return;

		action();

		cout << "Գ������� ���������: " << std::endl;
		cout << total << std::endl;
	}

	void action()
	{
		int getInt = 0;
		char getCase = 0;

		int numRes = 0;
		int plusRes = 0;
		int doublRes = 0;
		int delPrevRes = 0;

		int back0 = 0; // ���������� ��� ��� �������� ����� ���������� ��� ���� � ���������� �����
		int back1 = 0; // ���������� ��� + 1 ( ������ �� ���� ������ )


		for (int i = 0; i < buf.size(); ++i)
		{
			if (digCheck(buf, i) == true)
			{
				getInt = convetToInt(buf, i);
				getCase = '1';
			}
			else if (buf[i][0] == '-' && subDigCheck(i) == true)
			{
				getInt = convetToInt(buf, i);
				getCase = '1';
			}
			else getCase = buf[i][0];

			switch (getCase)
			{
			case num: // �����
				numRes = getInt;
				total += numRes;
				back1 = back0;
				back0 = numRes;
				break;
			case plus: //+
				plusRes = (back0 + back1);
				total += plusRes;
				back1 = back0;
				back0 = plusRes;
				break;
			case doubl: // �
				doublRes = (back0 * 2);
				total += doublRes;
				back1 = back0;
				back0 = doublRes;
				break;
			case delPrev: // c
				delPrevRes = (back0);
				total -= delPrevRes;
				back0 = back1;
				break;
			default:
				break;
			}
		}
	}

	bool check() // �������� ������� �� ������������ ����� ������ false - �� ���������, ture - ���������
	{
		int temp = 0;
		int bufIndex = buf.size();
		for (int i = 0; i < bufIndex; ++i)
		{
			if (digCheck(buf, i) == true)
			{
				temp = convetToInt(buf, i);
				if (temp > 333 || temp < -333)
				{
					cout << "������� ���������� ��������: " << temp << std::endl;
					return false;
				}
			}
			else if (buf[i][0] == '-' && subDigCheck(i) == true) //�������������� �������� ��� ������������� �������� �����
			{
				temp = convetToInt(buf, i);
				if (temp > 333 || temp < -333)
				{
					cout << "������� ���������� ��������: " << temp << std::endl;
					return false;
				}
			}
			else if (buf[i].length() > 1)
			{
				cout << "������� ���������� ��������: " << buf[i] << std::endl;
				return false;
				break;
			}
			else if (buf[i] != "�" && buf[i] != "�" && buf[i] != "+")
			{
				cout << "������� ���������� ��������: " << buf[i] << std::endl; 
				return false;
				break;
			}
			else if (buf[i] == "+" && i < 2)
			{
				cout << "������� ���������� �������� (+)" << std::endl;
				cout << "��� ��������� �������� (+) �� ���� ���������� ��� �������� �����." << std::endl;
				return false;
			}
			else if (buf[i] == "�" && i < 1)
			{
				cout << "������� ���������� ��������: "<<buf[i] << std::endl;
				cout << "��� ��������� ��������: "<<buf[i]<< " �� ���� ���������� ���� ��������� ������." << std::endl;
				return false;
			}
			else if (buf[i] == "�" && i < 1)
			{
				cout << "������� ���������� ��������: " << buf[i] << std::endl;
				cout << "��� ��������� ��������: " << buf[i] << " �� ���� ���������� ���� ��������� ������." << std::endl;
				return false;
			}
		}
		return true;
	}
	bool digCheck(const std::vector<string>& one, int index) //�������� ������ �� �����
	{
		for (char ch : one[index])
		{
			if (!isdigit(static_cast<unsigned char>(ch), std::locale())) return false; //false �� �����
		}
		return true;
	}
	bool subDigCheck(int index) //�������������� �������� ����� �� ����� ��� ������������� ��������
	{
		string subStr = buf[index].substr(1);
		for (char ch : subStr)
		{
			if (!isdigit(static_cast<unsigned char>(ch), std::locale())) return false;
		}
		return true;
	}
	int convetToInt(const std::vector<string>& one, int index) //������� string � int
	{
		int convInt = 0;
		if (one[index].length() > 1)
		{
			if (one[index][0] == '-')
			{
				convInt = std::stoi(one[index]);
				convInt = -convInt;
			}
		}
		convInt = std::stoi(one[index]);
		return convInt;
	}
};

int main()
{
	system("chcp 1251");

	Game p;

	p.insert();

	return 0;
}