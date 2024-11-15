#ifndef CASINO_H
#define CASINO_H

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <limits>
#include <list>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "User.h"
#include "Maquina.h"
#include "XMLParser.h"
#include "ObjectoXML.h"
#include "XMLWriter.h"

using namespace std;

class Casino
{
    public:
        list<User *> Lista_User;
        list<Maquina *> Lista_Maquina;
        std::list<User*> jogadores_disponiveis;
        std::list<Maquina*> maquinas_disponiveis;

        string nome_casino;
        int max_jogadores;
        int hora_inicio;
        int hora_fim;

        Casino(string nome);
        virtual ~Casino();
        bool Load(const string &ficheiro);
        bool Add(User *ut);
        bool Add(Maquina *m);
        void Listar(ostream &f = std::cout);
        Maquina::ESTADO_MAQUINA Get_Estado(int id_maq);
        void Menu();
        int ContarMaquinas();
        int ContarMaquinasEstado(Maquina::ESTADO_MAQUINA estado);
        void Desligar(int id_maq);
        int Memoria_Total();
        list<Maquina *> Listar_Tipo(string Tipo, ostream &f = std::cout);
        bool LoadUser(const string &ficheiro);
        void ListarUser(ostream &f = std::cout);
        void associarEJogar(list<User *> Lista_User, list<Maquina *> Lista_Maquina);
        void Listar(float X, ostream &f = std::cout);
        list<string> * Ranking_Dos_Fracos();
        list<Maquina*>* Ranking_Das_Mais_Trabalhadoras();
        list<User *> * Jogadores_Mais_Frequentes();
        list<User *> * Jogadores_Mais_Ganhos ();
        string getNome() const;
        void Relatorio(string fich_xml);
        void Run(bool Debug = true);
        void textoMenu();
        Maquina* adicionarNovaMaquina(int _id, string _nome_maquina, int _prob_ganhar, int _prob_avariar, int _premio, int _x, int _y, int _temperatura_aviso);

    protected:

    private:
};

#endif // CASINO_H
