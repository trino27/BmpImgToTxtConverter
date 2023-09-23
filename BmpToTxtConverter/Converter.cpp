#include "Converter.h"
using namespace std;

void Converter::Convert(RGBTRIPLE**& Map, char**& ASCII, int Width, int Height)
{
	int Hue = 0;    // Змінна для збереження відтінку
	int Max, Min;   // Змінні для збереження максимальної та мінімальної інтинсивності кольору в стрктурі RGBTRIPLE
	int Saturation; // Змінна для збереження насиченості кольору

	
	ASCII = new char* [Height];
	for (int i = 0; i < Height; i++)
	{
		ASCII[i] = new char[Width];
	}

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			Max_Min(Map[i][j], Max, Min); 

			// Змінну Max приймємо за яскравість
			//Якщо яскравість пікселя нульова або максимальна
			//змінюємо значення відповідної комірки масиву та переходимо до наступного пікселя

			if (Max / this->BlackIND == 0) { ASCII[i][j] = '@'; continue; }// 105 == 0 -> black
			if (Max / 5 >= this->WhiteIND) { ASCII[i][j] = ' '; continue; }//50 >= 50 -> white

			//Якщо значення максимальної та мінімальної інтинсивності кольору в стрктурі RGBTRIPLE однакові
			//це означає що піксель чорно білий
			if (Max == Min) {
				ASCII[i][j] = Chars2[(Max / 50) - 2];
				continue;
			}


			//обчислюємо відтінок пікселя
			//залежно від переважной інтенсивності червоного синього або зеленого кольорів у пікселі
			if (Max == Map[i][j].rgbtRed && Map[i][j].rgbtGreen >= Map[i][j].rgbtBlue)
			{
				Hue = (int)(60 * (Map[i][j].rgbtGreen - Map[i][j].rgbtBlue) / (Max - Min));
			}
			else if (Max == Map[i][j].rgbtRed && Map[i][j].rgbtGreen < Map[i][j].rgbtBlue)
			{
				Hue = (int)(60 * (Map[i][j].rgbtGreen - Map[i][j].rgbtBlue) / (Max - Min)); // 360
			}
			else if (Max == Map[i][j].rgbtGreen)
			{
				Hue = (int)(60 * (Map[i][j].rgbtBlue - Map[i][j].rgbtRed) / (Max - Min)); //120

			}
			else if (Max == Map[i][j].rgbtBlue)
			{
				Hue = (int)(60 * (Map[i][j].rgbtRed - Map[i][j].rgbtBlue) / (Max - Min));
			}


			Saturation = 100 - (int)(((float)Min / (float)Max) * 100); // обчислюємо насиченість кольору пікселя

			if (this->Chars == 1)ASCII[i][j] = CharsA[(Max / 50) - 2][Hue / 60][Saturation / 33];
			if (this->Chars == 2)ASCII[i][j] = CharsB[(Max / 50) - 2][Hue / 60][Saturation / 33];// змінюємо значення відповідної комірки масиву
		}
	}
}
void Converter::Max_Min(RGBTRIPLE Pixel, int& Max, int& Min) {
	if (Pixel.rgbtRed > Pixel.rgbtGreen && Pixel.rgbtRed > Pixel.rgbtBlue) {
		Max = Pixel.rgbtRed;
	}
	else if (Pixel.rgbtGreen > Pixel.rgbtRed && Pixel.rgbtGreen > Pixel.rgbtBlue) {
		Max = Pixel.rgbtGreen;
	}
	else if (Pixel.rgbtBlue > Pixel.rgbtRed && Pixel.rgbtBlue > Pixel.rgbtGreen) {
		Max = Pixel.rgbtBlue;
	}
	else {
		Max = Pixel.rgbtBlue;
		Min = Pixel.rgbtBlue;
		return;
	}

	if (Pixel.rgbtRed < Pixel.rgbtGreen && Pixel.rgbtRed < Pixel.rgbtBlue) {
		Min = Pixel.rgbtRed;
	}
	else if (Pixel.rgbtGreen < Pixel.rgbtRed && Pixel.rgbtGreen < Pixel.rgbtBlue) {
		Min = Pixel.rgbtGreen;
	}
	else if (Pixel.rgbtBlue < Pixel.rgbtRed && Pixel.rgbtBlue < Pixel.rgbtGreen) {
		Min = Pixel.rgbtBlue;
	}
}
void Converter::Read(RGBTRIPLE**& Map, BITMAPFILEHEADER& BFH, BITMAPINFOHEADER& BIH, FILE* f) {

	fread(&BFH, sizeof(BITMAPFILEHEADER), 1, f);
	fread(&BIH, sizeof(BITMAPINFOHEADER), 1, f);

	int sep = 4 - (BIH.biWidth * 3) % 4;


	Map = new RGBTRIPLE * [BIH.biHeight];
	for (int i = 0; i < BIH.biHeight; i++) {
		Map[i] = new RGBTRIPLE[BIH.biWidth];
	}


	for (int i = BIH.biHeight - 1; i >= 0; i--) {
		for (int j = 0; j < BIH.biWidth; j++) {
			Map[i][j].rgbtBlue = fgetc(f);
			Map[i][j].rgbtGreen = fgetc(f);
			Map[i][j].rgbtRed = fgetc(f);
		}
		for (int j = 0; j < sep; j++) fgetc(f);
	}
}
void Converter::Print_file(char**& ASCII, int Width, int Height)
{
	string out_file;
	cout << "Example -> C:\\Programming_Projects\\BmpImage\\Image\n";
	cout << "Enter path to output: ";
	cin >> out_file;
	ofstream out(out_file + ".txt");

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			out << ASCII[i][j]; out << ASCII[i][j];
		}
		out << endl;
	}

}
void Converter::Print_cmd(char**& ASCII, int Width, int Height) {
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			cout << ASCII[i][j] << ASCII[i][j];
		}
		cout << endl;
	}
}
