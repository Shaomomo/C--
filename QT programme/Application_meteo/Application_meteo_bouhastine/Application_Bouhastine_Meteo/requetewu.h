#ifndef REQUETEWU_H
#define REQUETEWU_H
#include<string>
using namespace std;

class RequeteWU
{
private:
    string ville;
    string pays;
    string cle;
public:
    RequeteWU();
    void modifierVille(string uneville);
    void modifierPays(string unpays);
    string afficherVille();
    string afficherPays();
    string creerRequeteWU();
};

#endif // REQUETEWU_H
