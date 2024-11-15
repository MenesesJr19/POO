#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <list>

class XMLParser
{
    ofstream F;
    list<string> LTags;
    string Tabulacoes(int N)
    {
        string s = "";
        for (int i = 0; i < N; i++)
            s = s + "\t";
        return s;
    }
    public:
        XMLParser();
        virtual ~XMLParser();
        void XMLParserInicioDocumento(string ficheiro);
        void XMLParserFimDocumento();
        void XMLParserElementoString(string el, string valor);
        void XMLParserInicioElemento(string el);
        void XMLParserFimElemento();

    protected:

    private:
};

#endif // XMLPARSER_H
