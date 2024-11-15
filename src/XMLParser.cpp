#include "XMLParser.h"

XMLParser::XMLParser()
{
    //ctor
}

XMLParser::~XMLParser()
{
    XMLParserFimDocumento();
}

void XMLParser::XMLParserInicioDocumento(string ficheiro)
{
    F.open(ficheiro);
}

void XMLParser::XMLParserFimDocumento()
{
    F.close();
}

void XMLParser::XMLParserElementoString(string el, string valor)
{
    F << "<" << el << ">" << valor << "</" << el << ">" << endl;
}

void XMLParser::XMLParserInicioElemento(string el)
{
    F << Tabulacoes(LTags.size()) << "<" << el << ">" << endl;
    LTags.push_front(el);
}

void XMLParser::XMLParserFimElemento()
{
    string el = LTags.front();
    F << Tabulacoes(LTags.size()) << "</" << el << ">" << endl;
    LTags.pop_front();
}
