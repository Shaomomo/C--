#ifndef RETURNWU_H
#define RETURNWU_H

#include <string>

using namespace std;

class ReturnWU
{
private:
    string ville;
    string pays;
    string cle;
public:
    ReturnWU();
    void modifierVille(string uneville);
    void modifierPays(string unpays);
    string afficherVille();
    string afficherPays();
    string creerRequeteWU();
};

#endif // RETURNWU_H
