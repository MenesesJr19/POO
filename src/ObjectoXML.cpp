#include "ObjectoXML.h"


int PartirString(const char *linhaSTR, char *StarTAG, char *TEX, char *EndTAG)
{
    //cout << "Linha = [" << linhaSTR << "]"<< endl;
    strcpy(StarTAG, "");
    strcpy(TEX, "");
    strcpy(EndTAG, "");
    int ret = sscanf(linhaSTR, "\t<%[^>]>%[^</]</%[^>]>",StarTAG, TEX, EndTAG);
    //cout << "RET = " << ret << endl;
    //cout << "StarTAG = ["<<StarTAG<<"]" << endl;
    //cout << "TEX = ["<<TEX<<"]" << endl;
    //cout << "EndTAG = ["<<EndTAG<<"]" << endl;
    return ret;
}
string ObjectoXML::Tabulacao(int n)
{
    string s = "";
    for (int i = 0; i < n; i++)
        s += "\t";
    return s;
}

ObjectoXML::~ObjectoXML()
{
    DADOS.clear();
    for (list<ObjectoXML *>::iterator it = LFilhos.begin(); it != LFilhos.end(); ++it)
        delete (*it);
    LFilhos.clear();
}
string ObjectoXML::GetAtributo(string tag)
{
    auto iter = DADOS.find(tag);
    if (iter != DADOS.end())
        return iter->second;
    return "";
}
ObjectoXML* ObjectoXML::GetNode(string tit)
{
    if (TITULO.compare(tit) == 0) return this;
    for (list<ObjectoXML *>::iterator it = LFilhos.begin(); it != LFilhos.end(); ++it)
    {
        ObjectoXML *F = *it;
        if (F->GetTitulo().compare(tit) == 0)
            return F;
    }
    return NULL;
}
int ObjectoXML::GetNodes(string tit, list<ObjectoXML *> &lnodes)
{
    if (TITULO.compare(tit) == 0) lnodes.push_back(this);
    else
    {
        for (list<ObjectoXML *>::iterator it = LFilhos.begin(); it != LFilhos.end(); ++it)
        {
            ObjectoXML *F = *it;
            if(!TITULO.compare(F->GetTitulo()))
            {
                if (F->GetTitulo().compare(tit) == 0)
                    lnodes.push_back(F);
            }
            F->GetNodes(tit, lnodes);
        }
    }
    return lnodes.size();
}
ObjectoXML* ObjectoXML::Processar_Parser(string fich)
{
    bool space=true;
    ifstream F(fich);
    if (!F.is_open()) return NULL;
    list<ObjectoXML *> Pilha;
    string Linha;
    char StartTAG[50];
    char EndTAG[50];
    char Conteudo[250];
    ObjectoXML *Raiz = NULL;
    ObjectoXML *Obj_Corrente = NULL;
    while (!F.eof())
    {
        space=true;
        getline(F, Linha);
        int res = PartirString(Linha.c_str(), StartTAG, Conteudo, EndTAG);

        for(int i=0; i<strlen(Conteudo);i++)
        {
            if(!isspace(Conteudo[i]))
                    space=false;
        }
        if(space)
            res=1;
        if (res == 1)
        {
            char *pch= strchr(StartTAG,'/');
            if (pch == NULL)
            {
                ObjectoXML *Filho = new ObjectoXML(StartTAG);
                if (Obj_Corrente)
                    Obj_Corrente->Add(Filho);
                else
                    Raiz = Filho;

                Obj_Corrente = Filho;
                Pilha.push_front(Obj_Corrente);
            }
            else
            {
                Pilha.pop_front();
                if(Pilha.size()>0)
                    Obj_Corrente = Pilha.front();
            }
        }
        else
            Obj_Corrente->Add(StartTAG, Conteudo);
    }
    Pilha.clear();
    F.close();
    return Raiz;
}
void ObjectoXML::Show(int ntab)
{
    string tab = Tabulacao(ntab);
    cout << tab << "[" << TITULO << "]" << endl;
    for(map<string, string>::const_iterator it = DADOS.begin(); it != DADOS.end(); ++it)
        cout << tab << "\t[" << it->first << "] = [" << it->second << "]" << endl;
    for (list<ObjectoXML *>::iterator it = LFilhos.begin(); it != LFilhos.end(); ++it)
        (*it)->Show(ntab + 1);
    cout << tab << "[" << TITULO << "]" << endl;
}
