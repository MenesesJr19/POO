#include "XMLWriter.h"

XMLWriter::XMLWriter()
{

}
XMLWriter::~XMLWriter()
{
    WriteEndDocument();
}
void XMLWriter::WriteStartDocument(string ficheiro)
{
    F.open(ficheiro);
}
void XMLWriter::WriteEndDocument()
{
    F.close();
}
void XMLWriter::WriteElementString(string el, string valor)
{
    F << "<" << el << ">" << valor << "</" << el << ">" << endl;
}
void XMLWriter::WriteStartElement(string el)
{
    F << Tabulacoes(LTags.size()) << "<" << el << ">" << endl;
    LTags.push_front(el);
}
void XMLWriter::WriteEndElement()
{
    string el = LTags.front();
    F << Tabulacoes(LTags.size()) << "</" << el << ">" << endl;
    LTags.pop_front();
}
