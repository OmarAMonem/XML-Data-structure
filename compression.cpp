#include<iostream>
#include <string>
#include <map>
#include<vector>
#include<fstream>
using namespace std;

void comprese(string& str)
{
	ofstream fout("my_output.txt");
	if (fout.fail())
	{
		cout << "Can't open the file.\n";
		return;
	}

	map<pair<int, string>, string> mp;
	int n = str.length();
	for (int i = 0; i < n;)
	{
		if (str[i] == '<')
		{
			int j;
			if (str[i + 1] == '/')
			{
				for (j = i + 2; str[j] != '>'; j++);
				mp[{i + 2, str.substr(i + 2, j - (i + 2))}] = static_cast<char>((char)(str[j - 1]) - (char)(str[i + 2]) + 15);
				fout << mp[{i + 2, str.substr(i + 2, j - (i + 2))}];
				i = j + 1;
			}
			else
			{
				for (j = i + 1; str[j] != '>'; j++);
				mp[{i + 1, str.substr(i + 1, j - (i + 1))}] = static_cast<char>((char)(str[j - 1]) - (char)(str[i + 1]) + 15);
				fout << mp[{i + 1, str.substr(i + 1, j - (i + 1))}];
				i = j + 1;
			}
			
		}
		else
		{
			fout << str[i];
			i++;
		}
	}
	fout.close();
	for (const pair<pair<int, string>, string> item : mp)
		cout << item.first.first << " , " << item.first.second << " - " << item.second << endl;
}

int main()
{
	// string str = "<note><to>Tove</to><from>Jani</from><note><heading>Reminder</heading><body>Don't forget me this weekend!</body></note>";
	string str;
	string path = "notes.txt";
	fstream file_handler(path.c_str());
	if (file_handler.fail())
	{
		cout << "Can't open the file.\n";
		return 0;
	}
	string line;
	while (getline(file_handler, line))
		str = line;
	file_handler.close();
	comprese(str);

	return 0;
}