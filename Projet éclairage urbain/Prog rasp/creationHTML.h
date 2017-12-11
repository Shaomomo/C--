#ifndef CREATIONHTML_H
#define CREATIONHTML_H

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <ctime>

using namespace std;

class CREATIONHTML
{
private :
    string numeroRue;
    struct tm date;
public:
    CREATIONHTML();

    int CreateRueFile();
    bool VerrifMessage(string message);
    string CheckTheDate();
};

#endif // HISTORIQUERUE_H
