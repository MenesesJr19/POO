#include "Maquina.h"

Maquina::Maquina(int _id, string _nome_maquina, int _prob_ganhar, int _prob_avariar, int _premio, int _x, int _y, int _temperatura_aviso)
{
    id = _id;
    nome_maquina = _nome_maquina;
    prob_ganhar = _prob_ganhar;
    prob_avariar = _prob_avariar;
    premio = _premio;
    x = _x;
    y = _y;
    temperatura_aviso = _temperatura_aviso;
    jogadas = 0;
    contar_avarias = 0;
    estado = ON; // A máquina começa no estado ON
}


Maquina::~Maquina()
{
    cout << "Maquina com ID: " << id << " foi destruida com sucesso!" << endl;
}

Blackjack::Blackjack(int _id, string _nome_maquina, int _prob_ganhar, int _prob_avariar, int _premio, int _x, int _y, int _temperatura_aviso) : Maquina(_id, _nome_maquina, _prob_ganhar, _prob_avariar, _premio, _x, _y, _temperatura_aviso)
{

}

Blackjack::~Blackjack() {

}

Roleta::Roleta(int _id, string _nome_maquina, int _prob_ganhar, int _prob_avariar, int _premio, int _x, int _y, int _temperatura_aviso) : Maquina(_id, _nome_maquina, _prob_ganhar, _prob_avariar, _premio, _x, _y, _temperatura_aviso)
{

}

Roleta::~Roleta() {

}

Craps::Craps(int _id, string _nome_maquina, int _prob_ganhar, int _prob_avariar, int _premio, int _x, int _y, int _temperatura_aviso) : Maquina(_id, _nome_maquina, _prob_ganhar, _prob_avariar, _premio, _x, _y, _temperatura_aviso)
{

}

Craps::~Craps() {

}

ClassicSlots::ClassicSlots(int _id, string _nome_maquina, int _prob_ganhar, int _prob_avariar, int _premio, int _x, int _y, int _temperatura_aviso) : Maquina(_id, _nome_maquina, _prob_ganhar, _prob_avariar, _premio, _x, _y, _temperatura_aviso)
{

}

ClassicSlots::~ClassicSlots() {

}

Maquina::ESTADO_MAQUINA Maquina::getEstado() const  {
    return estado;
}

Maquina::getID() const  {
    return id;
}

Maquina::getProbabilidade() const  {
    return prob_ganhar;
}

Maquina::getJogadas() const  {
    return jogadas;
}

Maquina::getAvaria() const  {
    return contar_avarias;
}

string Maquina::getNomeMaquina() const  {
    return nome_maquina;
}

void Maquina::setEstado(ESTADO_MAQUINA novoEstado) {
    estado = novoEstado;
}

string Maquina::estadoParaString() const {
    if (estado == ESTADO_MAQUINA::ON) {
            return "ON";
        } else if (estado == ESTADO_MAQUINA::OFF) {
            return "OFF";
        } else {
            return "AVARIADO";
        }
}

void Maquina::Show_maquina() {
    cout << "ID " << id << endl;
}

Maquina::getX() const  {
    return x;
}

Maquina::getY() const  {
    return y;
}

Maquina::getTemperatura() const  {
    return temperatura_aviso;
}

