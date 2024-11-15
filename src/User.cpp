#include "User.h"

User::User(int _codigo_cartao, string _nome_jogador, string _cidade, int _idade)
{
    codigo_cartao = _codigo_cartao;
    nome_jogador = _nome_jogador;
    cidade = _cidade;
    idade = _idade;
    tempo_no_casino = 0;
    numero_de_ganhos = 0;
}

User::~User()
{

}

int User::getCodCartao() const
{
    return codigo_cartao;
}

string User::getNome() const
{
    return nome_jogador;
}

string User::getCidade() const
{
    return cidade;
}

int User::getIdade() const
{
    return idade;
}

int User::getTempo() const
{
    return tempo_no_casino;
}

int User::getGanhos() const
{
    return numero_de_ganhos;
}

