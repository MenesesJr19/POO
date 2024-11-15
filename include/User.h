#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <ctime>

using namespace std;

class User
{
    public:
        int codigo_cartao;
        string nome_jogador;
        string cidade;
        int idade;
        int tempo_no_casino;
        int numero_de_ganhos;

        User(int _codigo_cartao, string _nome_jogador, string _cidade, int _idade);
        virtual ~User();
        int getCodCartao() const;
        string getNome() const;
        string getCidade() const;
        int getTempo() const;
        int getIdade() const;
        int getGanhos() const;

    protected:

    private:
};

#endif // USER_H
