#ifndef SNIR_H
#define SNIR_H
#include <string>
#include <fstream>
#include <sstream>
//refaire à la main ToFloat (mantisse...)
using namespace std;
class SNIR
{	public:
	static unsigned int ChaineHexaVersInt(char ChaineHexa[20],int NbCar);
	static string FloatToString(float nb,int nbdecimales);
	static string FloatToStringAvecExp(float nb,int nbdecimales);
	static float StringToFloat(string s);
	static int StringDecToInt(string s);
	static unsigned int StringHexToUnsignedInt(string s);
	static signed int StringHexToSignedInt(string s,int NbOctets);
	static long long StringDecToLongLong(string s);
	static string DecToString(int nb);
	static string UnsignedDecToString(unsigned int nb);
	static string HexToString(char nb);
	static string HexToString(short nb);
	static string HexToString(int nb);
	static string BinToString(char nb);
	static string BinToString(short nb);
	static string BinToString(int nb);
	static string FileToString(string chemin);
#ifdef VCL_H
	static UnicodeString ToUnicodeString(string s);
	static string ToString(UnicodeString us);
#endif  // VCL_H
};
#endif  //SNIR_H
