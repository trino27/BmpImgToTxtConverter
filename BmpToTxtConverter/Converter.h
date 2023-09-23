#pragma once

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

class Converter
{
private:
	short BlackIND = 105;
	short WhiteIND = 50;
	short Chars = 1;
protected:
	// Масив для заміни кольорових пікселів 
	const unsigned char CharsA[3][6][3] = { { { '.', 'r', 'U' }, { ':', '?', 'P' }, { '"', ')', 'h' }, { '!', '7', 'O' }, { ';', 'Y', 'd' }, { '/', 'e', '9' } },
											{ { '-', 'v', 'E' }, { '_', 'T', 'X' }, { '^', '(', 'H' }, { '*', 'z', '6' }, { '>', 'l', 'q' }, { '=', '4', 'R' } },
											{ { '\'', 'L', 'a' }, { ',', 'c', 'A' }, { '~', '|', 'm' }, { '<', 'x', 'b' }, { '\\', '5', 'p' }, { '+', 'S', 'G' } } };


	const unsigned char CharsB[3][6][3] = { { { 'r', 'T', 'R' }, { 'z', 'u', 'y' }, { 'f', '[', 'g' }, { 'c', 's', 'q' }, { 'x', 'h', 'b' }, { 'a', 'l', 'p' } },
										   { { '-', '~', '{' }, { 'v', 'U', 'Y' }, { 'e', 'O', 'G' }, { 'd', 'C', 'Q' }, { 'w', 'H', 'B' }, { 'j', 'L', 'P' } },
										   { { '2', 't', '6' }, { '`', 'F', 'i' }, { '0', 'o', '>' }, { '^', '*', '&' }, { ',', '|', '/' }, { '.', '+', ';' } } };

	// Масив для заміни чорно-білих пікселів
	const unsigned char Chars2[25] = { '@', '%', '#' };

public:
	
    
    short GetBlackIND()
    {
        return BlackIND;
    }
    short GetWhiteIND()
    {
        return WhiteIND;
    }
    short GetChars()
    {
        return Chars;
    }
    void SetBlackIND(short value)
    {
        BlackIND = value;
    }
    void SetWhiteIND(short value)
    {
        WhiteIND = value;
    }
    void SetChars(short value)
    {
        Chars = value;
    }

	Converter() {}
	void Convert(RGBTRIPLE**& Map, char**& ASCII, int Width, int Height);
	void Max_Min(RGBTRIPLE Pixel, int& Max, int& Min);
	void Read(RGBTRIPLE**& Map, BITMAPFILEHEADER& BFH, BITMAPINFOHEADER& BIH, FILE* f);
	void Print_file(char**& ASCII, int Width, int Height);
	void Print_cmd(char**& ASCII, int Width, int Height);
};
