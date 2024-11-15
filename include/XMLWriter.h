#ifndef XMLWRITER_H
#define XMLWRITER_H
#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <list>


class XMLWriter
{
    ofstream F;
    list<string> LTags;
    string Tabulacoes(int N)
    {
        string s = "";
        for (int i = 0; i < N; i++)
             s= s + "\t";
        return s;
    }

    public:
        XMLWriter();
        virtual ~XMLWriter();
        void WriteStartDocument(string ficheiro);
        void WriteEndDocument();
        void WriteElementString(string el, string valor);
        void WriteStartElement(string el);
        void WriteEndElement();
};

#endif // XMLWRITER_H
