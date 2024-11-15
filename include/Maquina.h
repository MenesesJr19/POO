#ifndef MAQUINA_H
#define MAQUINA_H

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <limits>

#include "User.h"

using namespace std;

class Maquina
{
    public:
        enum ESTADO_MAQUINA {
            ON,
            OFF,
            AVARIADA
        };

        int id;
        int prob_ganhar;
        int prob_avariar;
        int premio;
        int x;
        int y;
        int temperatura_aviso;
        int jogadas;
        int contar_avarias;
        string nome_maquina;
        ESTADO_MAQUINA estado;

        Maquina(int _id, string _nome_maquina, int _prob_ganhar, int _prob_avariar, int _premio, int _x, int _y, int _temperatura_aviso);
        virtual ~Maquina();
        ESTADO_MAQUINA getEstado() const;
        int getID() const;
        int getProbabilidade() const;
        int getJogadas() const;
        int getAvaria() const;
        string getNomeMaquina() const;
        string estadoParaString() const;
        void setEstado(ESTADO_MAQUINA novoEstado);
        void Show_maquina();
        int getX() const;
        int getY() const;
        int getTemperatura() const;

    protected:

    private:
};

class Blackjack : public Maquina
{
    public:
        Blackjack(int _id, string _nome_maquina, int _prob_ganhar, int _prob_avariar, int _premio, int _x, int _y, int _temperatura_aviso);
        virtual ~Blackjack();
};

class Roleta : public Maquina
{
    public:
        Roleta(int _id, string _nome_maquina, int _prob_ganhar, int _prob_avariar, int _premio, int _x, int _y, int _temperatura_aviso);
        virtual ~Roleta();
};

class Craps : public Maquina
{
    public:
        Craps(int _id, string _nome_maquina, int _prob_ganhar, int _prob_avariar, int _premio, int _x, int _y, int _temperatura_aviso);
        virtual ~Craps();
};

class ClassicSlots : public Maquina
{
    public:
        ClassicSlots(int _id, string _nome_maquina, int _prob_ganhar, int _prob_avariar, int _premio, int _x, int _y, int _temperatura_aviso);
        virtual ~ClassicSlots();
};

#endif // MAQUINA_H
