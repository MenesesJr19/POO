#ifndef OBJECTOXML_H
#define OBJECTOXML_H
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
#include <fstream>
#include <list>
#include <map>
#include <conio.h>

int PartirString(const char *linhaSTR, char *StarTAG, char *TEX, char *EndTAG);

class ObjectoXML
{
    string TITULO;
    map<string, string> DADOS;
    list<ObjectoXML *> LFilhos;
    string Tabulacao(int n);
    public:
        ObjectoXML(string tit){TITULO = tit;}
        void Add(ObjectoXML *X){LFilhos.push_back(X);}
        void Add(string tag, string valor){DADOS[tag] = valor;}
        string GetAtributo(string tag);
        virtual ~ObjectoXML();
        string GetTitulo() { return TITULO; }
        ObjectoXML *GetNode(string tit);
        int GetNodes(string tit, list<ObjectoXML *> &lnodes);
        static ObjectoXML *Processar_Parser(string fich);
        void Show(int ntab = 0);

    protected:

    private:
};

#endif // OBJECTOXML_H
