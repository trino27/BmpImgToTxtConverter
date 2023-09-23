#pragma warning(disable : 4996)

#include "main.h"

using namespace std;

void WorckModOneFile(Converter& converter)
{
	BITMAPFILEHEADER FHeader;
	BITMAPINFOHEADER IHeader;
	RGBTRIPLE** Map;
	short key = -1;
	
		char file_name[255];
		cout << "Example -> C:\\Programming_Projects\\BmpImage\\Image.bmp\n";
		cout << "Enter image path: ";
		cin.getline(file_name, 255, '\n');
		
		FILE* f = fopen(file_name, "rb");
		if (!file_name)
		{
			cout << "Can`t open file. (Or file isn`t exist.)\n" << endl;
			exit(1);
		}
		else cout << "Success!\n";

		converter.Read(Map, FHeader, IHeader, f);

		char** ASCII;

		converter.Convert(Map, ASCII, IHeader.biWidth, IHeader.biHeight);

		cout << "1 - To file" << endl;
		cout << "2 - To console" << endl;
		cout << "3 - Back" << endl;
		cout << "0 - End" << endl;
		cout << "->";
		cin >> key;
		if (key == 1)  converter.Print_file(ASCII, IHeader.biWidth, IHeader.biHeight);
		if (key == 2)  converter.Print_cmd(ASCII, IHeader.biWidth, IHeader.biHeight);
		cin.ignore();
	
}
void WorckModSettings(Converter& converter)
{
	short SetMod;
	cout << " Change black index  - 1\n Change white index - 2\n Back - 3\n";
	cin >> SetMod;
	if (SetMod == 1)
	{
		cout << "Enter from 1 to 255 (default: 105) ->";
		int blackIND;
		cin >> blackIND;
		converter.SetWhiteIND(blackIND);
		if (converter.GetBlackIND() < 1 || converter.GetBlackIND() > 255)
		{
			cout << "Input error, reset black to 105 points" << endl;
			converter.SetBlackIND(105);
		}
	}
	if (SetMod == 2)
	{
		cout << "Enter from 1 to 51 (default: 50) ->";
		int whiteIND;
		cin >> whiteIND;
		converter.SetWhiteIND(whiteIND);
		if (converter.GetWhiteIND() < 1 || converter.GetWhiteIND() > 51)
		{
			cout << "Input error, reset white to 50 points" << endl;
			converter.SetWhiteIND(50);
		}
	}
	if (SetMod == 3)
	{
	}
	if (SetMod < 1 || SetMod > 3)
	{
		cout << "Input Error!";
	}
}

int main() {
	cout << "I am on!\n";
	setlocale(LC_ALL, "Ukrainian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	short WorckMod = -1;
	Converter converter;

	do
	{
		cout << "Palette selection:\n 1 - A\n 2 - B\n 3 - end\n";
		short charValue;
		cin >> charValue;
	    converter.SetChars(charValue);
		if (converter.GetChars() == 3)
		{
			return 0;
		}
	} while (converter.GetChars() != 1 && converter.GetChars() != 2);

	while (WorckMod != 0)
	{
		cout << "Mod:\n Convert - 1\n Settings - 2\n Exit - 0\n";
		cin >> WorckMod;
		cin.ignore();
		switch (WorckMod)
		{
		case 1:
		{
			WorckModOneFile(converter);
		}  break;
		case 2:
		{
			WorckModSettings(converter);
		} break;
		case 0:   break;
		default: cout << "Input Error!";
		}
	}
	return 0;
}