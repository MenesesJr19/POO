#include "Casino.h"

Casino::Casino(string nome)
{
    nome_casino = nome;
    max_jogadores = 0;
    hora_inicio = 0;
    hora_fim = 0;
}

Casino::~Casino()
{
    for (auto Maquina : Lista_Maquina) {
        delete Maquina;
    }

    for (auto User : Lista_User) {
        delete User;
    }
}

bool Casino::Load(const string &ficheiro)
{
    int numeroID = 0;

    ObjectoXML *XML = ObjectoXML::Processar_Parser(ficheiro);

    ObjectoXML *X = XML->GetNode("DEFINICOES");

    nome_casino = X->GetAtributo("NOME");
    max_jogadores = stoi(X->GetAtributo("MAX_JOG"));
    hora_inicio = stoi(X->GetAtributo("HORA_INICIO"));
    hora_fim = stoi(X->GetAtributo("HORA_FIM"));

    list<ObjectoXML *> lm;
            X=XML->GetNode("LISTA_MAQ");
            X->GetNodes("MAQUINA", lm);
            for (list<ObjectoXML *>::iterator it = lm.begin(); it != lm.end(); it++)
    {
        numeroID++;
        Maquina* Aux= adicionarNovaMaquina(numeroID, (*it)->GetAtributo("NOME"), stoi((*it)->GetAtributo("PROB_G")), stoi((*it)->GetAtributo("PROB_G")), stoi((*it)->GetAtributo("PREMIO")), stoi((*it)->GetAtributo("X")), stoi((*it)->GetAtributo("Y")), stoi((*it)->GetAtributo("TEMP_AVISO")));
        Lista_Maquina.push_back(Aux);
    }
    lm.clear();
    delete XML;

    return 0;
}

bool Casino::Add(User *ut)
{
    if(!ut){
        cout << "Ocorreu um erro ao adicionar o jogador!" << endl;
    } else {
        Lista_User.push_back(ut);
    }

    return 0;
}

bool Casino::Add(Maquina *m)
{
    if(!m){
        cout << "Ocorreu um erro ao adicionar a máquina!" << endl;
    } else {
        Lista_Maquina.push_back(m);
    }

    return 0;
}

int Casino::ContarMaquinas()
{
    return Lista_Maquina.size();
}

int Casino::ContarMaquinasEstado(Maquina::ESTADO_MAQUINA estado)
{
    int contador = 0;
    for (const Maquina* maquina : Lista_Maquina) {
        if (maquina->getEstado() == estado) {
            contador++;
        }
    }

    return contador;
}

void Casino::Listar(std::ostream &f)
{
        int numeroDeMaquinasOn = ContarMaquinasEstado(Maquina::ON);
        int numeroDeMaquinasOff = ContarMaquinasEstado(Maquina::OFF);
        int numeroDeMaquinasAvariadas = ContarMaquinasEstado(Maquina::AVARIADA);

        cout << "Estado atual do Casino: " << endl;
        cout << "Nome: " << nome_casino << endl;
        cout << "Total de máquinas: " << ContarMaquinas() << " - ON: [" << numeroDeMaquinasOn << "] OFF: [" << numeroDeMaquinasOff << "] AVARIADA: [" << numeroDeMaquinasAvariadas << "]" << endl;
        cout << "Número total de jogadores: " << Lista_User.size() << endl;

        for (auto Maquina : Lista_Maquina)
        {
            string estadoString = Maquina->estadoParaString();
            f << "ID: " << Maquina->getID() << " [" << Maquina->getNomeMaquina() << "] - [" << estadoString << "]" << " - POSIÇÃO: [X: " << Maquina->getX() << " Y: " << Maquina->getY() << "]" << endl;
        }
}

Maquina::ESTADO_MAQUINA Casino::Get_Estado(int id_maq)
{
     for (auto Maquina : Lista_Maquina) {
        if (Maquina->getID() == id_maq) {
            string estadoString = Maquina->estadoParaString();
            cout << "A máquina com o ID: " << id_maq << " [" << Maquina->getNomeMaquina() << "] encontra-se neste momento no estado: [" << estadoString << "]" << endl;
            return Maquina->getEstado();
        }
     }

     cout << "Máquina com ID " << id_maq << " não encontrada." << endl;
}

void Casino::Desligar(int id_maq)
{
    for (Maquina* maquina : Lista_Maquina) {
        if (maquina->getID() == id_maq) {
            maquina->setEstado(Maquina::OFF);
            cout << "Máquina com ID " << id_maq << " desligada com sucesso." << endl;
            return;
        }
    }

    cout << "Máquina com ID " << id_maq << " não encontrada." << endl;
}

int Casino::Memoria_Total()
{
    int memoriaMaquina = 0;
    int memoriaUser = 0;
    int tamanhoDaMemoria = 0;

    for (auto Maquina : Lista_Maquina) {
        memoriaMaquina += sizeof(Maquina);
    }

    for (auto User : Lista_User) {
        memoriaUser += sizeof(User);
    }

    tamanhoDaMemoria = memoriaMaquina + memoriaUser;

    return tamanhoDaMemoria;
}

list<Maquina *> Casino::Listar_Tipo(string Tipo, std::ostream &f)
{
    list<Maquina *> maquinasDoTipo;

    for (auto maquina : Lista_Maquina) {
        if (maquina->getNomeMaquina() == Tipo) {
            maquinasDoTipo.push_back(maquina);
        }
    }

    f << "Foram encontradas " << maquinasDoTipo.size() << " máquinas do tipo: " << Tipo << endl;
    for (auto maquina : maquinasDoTipo) {
        string estadoString = maquina->estadoParaString();
        f << "ID: " << maquina->getID() << ", Estado Atual: " << estadoString << endl;
    }

    return maquinasDoTipo;
}

bool Casino::LoadUser(const string &ficheiro)
{
    ifstream lerficheiro(ficheiro);
    if (lerficheiro.is_open())
    {
        string line;
        while (getline(lerficheiro, line))
        {
            stringstream ss(line);
            string cartao, nome, cidade, idade;
            int _idade, _cartao;

            if (getline(ss, cartao, '\t') && getline(ss, nome, '\t') && getline(ss, cidade, '\t') && getline(ss, idade, '\t'))
            {
                _cartao = stoi(cartao);
                _idade = stoi(idade);
                User *user = new User(_cartao, nome, cidade, _idade);
                Lista_User.push_back(user);
            }
        }
        lerficheiro.close();
    }
    else
    {
        cout << "Ocorreu um erro ao abrir/carregar os jogadores: " << ficheiro << " não existe!" << endl;
    }
}

void Casino::ListarUser(std::ostream &f)
{
       for (auto User : Lista_User)
        {
            f << "Cod: " << User->getCodCartao() << " " << User->getNome() << " " << User->getCidade() << " " << User->getIdade() << endl;
        }
}

void Casino::associarEJogar(list<User *> Lista_User, list<Maquina *> Lista_Maquina)
{
    // Verifica se ainda há jogadores disponíveis para jogar
    if (Lista_User.empty()) {
        std::cout << "Não há jogadores disponíveis para jogar." << std::endl;
        return;
    }

    // Filtra máquinas com estado ON
    list<Maquina *> maquinasFiltradas;
    for (auto maquina : Lista_Maquina) {
        if (maquina->getEstado() == Maquina::ON) {
            maquinasFiltradas.push_back(maquina);
        }
    }

    // Verifica se há máquinas no estado ON disponíveis para jogar
    if (maquinasFiltradas.empty()) {
        std::cout << "Não há máquinas no estado ON disponíveis para jogar." << std::endl;
        return;
    }

    // Seleciona um usuário aleatório da lista de usuários disponíveis
    auto userIt = Lista_User.begin();
    std::advance(userIt, rand() % Lista_User.size());

    // Seleciona uma máquina aleatória do filtro de máquinas ON
    auto maquinaIt = maquinasFiltradas.begin();
    std::advance(maquinaIt, rand() % maquinasFiltradas.size());

    // Simula uma jogada
    int resultadoJogada = rand() % 100 + 1;
    int resultadoAvaria = rand() % 1000 + 1;
    int resultadoTemperatura = rand() % 100 + 1;
    string reparar;
    if (resultadoJogada <= (*maquinaIt)->prob_ganhar) {
        if (resultadoTemperatura >= (*maquinaIt)->temperatura_aviso) {
            cout << "ATENÇÃO!: A máquina " << (*maquinaIt)->getNomeMaquina() << " [X: " << (*maquinaIt)->getX() << " Y: " << (*maquinaIt)->getY() << "] está com a temperatura no limite [" << resultadoTemperatura << "ºC de no máximo permitido " << (*maquinaIt)->getTemperatura() << "ºC]" << endl;
            Sleep(5000);
        }
        if (resultadoAvaria <= (*maquinaIt)->prob_avariar) {
            (*maquinaIt)->contar_avarias++;
            (*maquinaIt)->setEstado(Maquina::AVARIADA);
            cout << (*maquinaIt)->getNomeMaquina() << " avariou!" << endl;
            cout << "Deseja reparar esta máquina avariada? s/n" << endl;
            cin >> reparar;

            if (reparar == "s" || reparar == "S") {
                cout << "Máquina reparada com sucesso!" << endl;
                (*maquinaIt)->setEstado(Maquina::ON);
            } else {
                Run();
            }
        } else {
        (*userIt)->tempo_no_casino++;
        (*maquinaIt)->jogadas++;
        (*userIt)->numero_de_ganhos++;
        std::cout << (*userIt)->getNome() << " ganhou na máquina " << (*maquinaIt)->getNomeMaquina() << " [X: " << (*maquinaIt)->getX() << " Y: " << (*maquinaIt)->getY() << "] a máquina pagou com uma percentagem de " << resultadoJogada << "%, ficando igual ou abaixo da probabilidade de ganhar de " << (*maquinaIt)->prob_ganhar << "%." << std::endl;
        Sleep(5000);
        }
    } else {
        if (resultadoTemperatura >= (*maquinaIt)->temperatura_aviso) {
            cout << "ATENÇÃO!: A máquina " << (*maquinaIt)->getNomeMaquina() << " [X: " << (*maquinaIt)->getX() << " Y: " << (*maquinaIt)->getY() << "] está com a temperatura no limite [" << resultadoTemperatura << "ºC de no máximo permitido " << (*maquinaIt)->getTemperatura() << "ºC]" << endl;
            Sleep(5000);
        }
        if (resultadoAvaria <= (*maquinaIt)->prob_avariar) {
            (*maquinaIt)->contar_avarias++;
            (*maquinaIt)->setEstado(Maquina::AVARIADA);
            cout << (*maquinaIt)->getNomeMaquina() << " avariou!" << endl;
            cout << "Deseja reparar esta máquina avariada? s/n" << endl;
            cin >> reparar;

            if (reparar == "s" || reparar == "S") {
                cout << "Máquina reparada com sucesso!" << endl;
                (*maquinaIt)->setEstado(Maquina::ON);
            } else {
                Run();
            }
        } else {
        (*userIt)->tempo_no_casino++;
        (*maquinaIt)->jogadas++;
        std::cout << (*userIt)->getNome() << " não ganhou na máquina " << (*maquinaIt)->getNomeMaquina() << " [X: " << (*maquinaIt)->getX() << " Y: " << (*maquinaIt)->getY() << "] a máquina não pagou com uma percentagem de " << resultadoJogada << "%, para ganhar precisaria de ficar igual ou abaixo de " << (*maquinaIt)->prob_ganhar << "%." << std::endl;
        Sleep(5000);
        }
    }
}

void Casino::Listar(float X, std::ostream &f)
{
    for (auto Maquina : Lista_Maquina) {
        if (Maquina->getProbabilidade() > X) {
            f << "Máquina: " << Maquina->getNomeMaquina() << ", Probabilidade de Ganhar: " << Maquina->getProbabilidade() << "%." << std::endl;
        }
    }
}

list<Maquina*>* Casino::Ranking_Das_Mais_Trabalhadoras()
{
    list<Maquina*>* ranking = new list<Maquina*>(Lista_Maquina);

    // Ordenar a lista 'ranking' com base no número de jogadas (uso da máquina)
    ranking->sort([](const Maquina* a, const Maquina* b) {
        return a->getJogadas() > b->getJogadas(); // Ordena decrescentemente
    });

    // Retorne o ponteiro para a lista ordenada
    return ranking;
}

list<User *> * Casino::Jogadores_Mais_Frequentes()
{
    list<User*>* ranking = new list<User*>(Lista_User);

    ranking->sort([](const User* a, const User* b) {
        return a->getTempo() > b->getTempo(); // Ordena decrescentemente
    });

    return ranking;
}

list<User *> * Casino::Jogadores_Mais_Ganhos ()
{
    list<User*>* ranking = new list<User*>(Lista_User);

    ranking->sort([](const User* a, const User* b) {
        return a->getGanhos() > b->getGanhos(); // Ordena decrescentemente
    });

    return ranking;
}

list<string> * Casino::Ranking_Dos_Fracos()
{
    list<string> *ranking = new list<string>;

    list<Maquina *> fracos_lista = Lista_Maquina;

    fracos_lista.sort([](const Maquina* a, const Maquina* b) {
        return a->getAvaria() > b->getAvaria();
    });

    for (auto maquina : fracos_lista) {
        string string_maquina = "ID: " + to_string(maquina->getID()) + " [" + maquina->getNomeMaquina() + "], Total de avarias: " + to_string(maquina->getAvaria());
        ranking->push_back(string_maquina);
    }

    return ranking;
}

string Casino::getNome() const  {
    return nome_casino;
}

void Casino::Relatorio(string fich_xml)
{
    int numeroDeMaquinasOn = ContarMaquinasEstado(Maquina::ON);
    int numeroDeMaquinasOff = ContarMaquinasEstado(Maquina::OFF);
    int numeroDeMaquinasAvariadas = ContarMaquinasEstado(Maquina::AVARIADA);

    XMLWriter XML;
    XML.WriteStartDocument(fich_xml);
    XML.WriteStartElement("CASINO");
    XML.WriteStartElement("INFORMACOES");
    XML.WriteElementString("NOME_CASINO",this->getNome());
    XML.WriteStartElement("TOTAL_MAQUINAS");
    XML.WriteElementString("ON",to_string(numeroDeMaquinasOn));
    XML.WriteElementString("OFF",to_string(numeroDeMaquinasOff));
    XML.WriteElementString("AVARIADA",to_string(numeroDeMaquinasAvariadas));
    XML.WriteEndElement();
    XML.WriteEndElement();
    XML.WriteStartElement("MAQUINAS");
    for (list<Maquina*>::iterator it = Lista_Maquina.begin(); it != Lista_Maquina.end(); it++) {
    string estadoString = (*it)->estadoParaString();
    XML.WriteElementString("ID",to_string((*it)->getID()));
    XML.WriteElementString("NOME",(*it)->getNomeMaquina());
    XML.WriteElementString("ESTADO",estadoString);
    }
    XML.WriteEndElement();
    XML.WriteEndElement();
}

Maquina* Casino::adicionarNovaMaquina(int _id, string _nome_maquina, int _prob_ganhar, int _prob_avariar, int _premio, int _x, int _y, int _temperatura_aviso)
{
    if (_nome_maquina == "Blackjack") {
        return new Blackjack(_id, _nome_maquina, _prob_ganhar, _prob_avariar, _premio, _x, _y, _temperatura_aviso);
    }
    else if (_nome_maquina == "Roleta") {
        return new Roleta(_id, _nome_maquina, _prob_ganhar, _prob_avariar, _premio, _x, _y, _temperatura_aviso);
    }
    else if (_nome_maquina == "Craps") {
        return new Craps(_id, _nome_maquina, _prob_ganhar, _prob_avariar, _premio, _x, _y, _temperatura_aviso);
    }
    else if (_nome_maquina == "Classic Slots") {
        return new ClassicSlots(_id, _nome_maquina, _prob_ganhar, _prob_avariar, _premio, _x, _y, _temperatura_aviso);
    }
    else {
        return nullptr;
    }
}

void Casino::Run(bool Debug)
{
    std::cout << "Simulação em execução..." << std::endl;
    std::cout << "A hora do inicio da simulação é: " << hora_inicio << "h" << std::endl;
    std::cout << "A hora para terminar a simulação é: " << hora_fim << "h" << std::endl;

    double hora_atual = hora_inicio;

    while (Debug && hora_atual <= hora_fim) {
        // Gere uma nova simulação a cada iteração
        associarEJogar(Lista_User, Lista_Maquina);
        hora_atual += 0.5;

        if (_kbhit()) {
            int tecla = _getch();
            if (tecla == 77 || tecla == 109) {
                break; // Encerra o loop quando a tecla 'M' ou 'm' for pressionada
            }
        }
    }

    if(hora_atual > hora_fim) {
        std::cout << "O tempo da simulação chegou ao fim." << std::endl;
    } else {
        std::cout << "A simulação foi interrompida pelo gestor do casino." << std::endl;
    }
}

void Casino::textoMenu()
{
    cout << " .--.               _               .---.  .--.  .--." << endl;
    cout << ": .--'             :_;              : .; :: ,. :: ,. :" << endl;
    cout << ": :    .--.   .--. .-.,-.,-. .--.   :  _.': :: :: :: :" << endl;
    cout << ": :__ ' .; ; `._-.': :: ,. :' .; :  : :   : :; :: :; :" << endl;
    cout << "`.__.'`.__,_;`.__.':_;:_;:_;`.__.'  :_;   `.__.'`.__.'" << endl << endl ;
}

void Casino::Menu()
{
    Casino casinoPOO(nome_casino);
    casinoPOO.Load("casinoConfiguracao.xml");
    casinoPOO.LoadUser("pessoas.txt");

    srand(static_cast<unsigned>(time(nullptr)));

    int opcao;
    bool continuar = true;

    while (continuar) {
        textoMenu();
        cout << "Bem-vindo(a) ao gestor do " << casinoPOO.nome_casino << endl;

        std::cout << "\nMenu do Casino" << std::endl;
        std::cout << "1. Listar o estado atual do Casino" << std::endl;
        std::cout << "2. Pesquisar estado de uma máquina" << std::endl;
        std::cout << "3. Executar Simulação" << std::endl;
        std::cout << "4. Desligar Máquina" << std::endl;
        std::cout << "5. Memória total ocupada pela estrutura de dados" << std::endl;
        std::cout << "6. Pesquisar máquinas por tipo" << std::endl;
        std::cout << "7. Listar máquinas com probabilidade superior a X" << std::endl;
        std::cout << "8. Ranking das máquinas mais trabalhadoras" << std::endl;
        std::cout << "9. Ranking dos jogadores que mais tempo passaram a jogar" << std::endl;
        std::cout << "10. Ranking dos jogadores que mais PRÉMIOS ganharam no casino" << std::endl;
        std::cout << "11. Ranking das Maquinas que mais avariam" << std::endl;
        std::cout << "12. Relatório XML [Estado Casino]" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                std::cout << "[Listar o estado atual do Casino]:" << std::endl;
                casinoPOO.Listar();
                cout << "Voltando ao menu inicial em 5 segundos..." << endl;
                Sleep(5000);
                system("cls");
                break;
            case 2:
                std::cout << "[Pesquisar estado de uma máquina]:" << std::endl;
                int id_maq_pesquisar;
                cout << "Digite o ID da máquina que você deseja pesquisar: ";
                cin >> id_maq_pesquisar;

                casinoPOO.Get_Estado(id_maq_pesquisar);
                cout << "Voltando ao menu inicial em 5 segundos..." << endl;
                Sleep(5000);
                system("cls");
                break;
            case 3:
                std::cout << "Executar Simulação" << std::endl;
                casinoPOO.Run();
                cout << "Voltando ao menu inicial em 5 segundos..." << endl;
                Sleep(5000);
                system("cls");
                break;
            case 4:
                std::cout << "[Desligar Máquina]:" << std::endl;
                int id_maq;
                cout << "Digite o ID da máquina que você deseja desligar: ";
                cin >> id_maq;

                casinoPOO.Desligar(id_maq);
                cout << "Voltando ao menu inicial em 5 segundos..." << endl;
                Sleep(5000);
                system("cls");
                break;
            case 5:
                std::cout << "[Memória total ocupada pela estrutura de dados]:" << std::endl;
                cout << "O tamanho ocupado pela memória é: " << casinoPOO.Memoria_Total() << endl;
                cout << "Voltando ao menu inicial em 5 segundos..." << endl;
                Sleep(5000);
                system("cls");
                break;
            case 6: {
                std::cout << "[Pesquisar máquinas por tipo]:" << std::endl;
                string tipoDaMaquina;
                cout << "Digite o tipo de máquina que você deseja pesquisar: ";
                cin >> tipoDaMaquina;

                casinoPOO.Listar_Tipo(tipoDaMaquina);
                cout << "Voltando ao menu inicial em 5 segundos..." << endl;
                Sleep(5000);
                system("cls");
                break;
            }
            case 7: {
                std::cout << "[Listar máquinas com probabilidade superior a X]:" << std::endl;
                int prob;
                string guardar;
                string nomeF = "maquinasPesquisaProb.txt";
                cout << "Digite o probabilidadade [0-100]% da deseja pesquisar: ";
                cin >> prob;

                if (prob >= 0 && prob <= 100) {
                    casinoPOO.Listar(prob);
                    cout << "Deseja guardar a pesquisa em um ficheiro? - s/n" << endl;
                    cin >> guardar;


                    if (guardar == "s" || guardar =="S") {
                    ofstream ficheiro(nomeF);

                    if (ficheiro.is_open()) {
                        cout << "Gravando no ficheiro: " << nomeF << " as máquinas com probabilidade de ganhar maior a " << prob << "%." << endl;
                        casinoPOO.Listar(prob, ficheiro);
                    } else {
                        cout << "Ocorreu algum erro ao gravar o ficheiro!" << endl;
                    }
                    }
                } else {
                    cout << "Introduziu um número não válido!" << endl;
                }
                cout << "Voltando ao menu inicial em 5 segundos..." << endl;
                Sleep(5000);
                system("cls");
                break;
            }
            case 8: {
                std::cout << "[Ranking das máquinas mais trabalhadoras]:" << std::endl;
                std::list<Maquina*> *ranking = casinoPOO.Ranking_Das_Mais_Trabalhadoras();

                for (const Maquina* maquina : *ranking) {
                    std::cout << "ID: " << maquina->getID() << ", Nome: " << maquina->getNomeMaquina() << ", Jogadas: " << maquina->getJogadas() << std::endl;
                }
                cout << "Voltando ao menu inicial em 5 segundos..." << endl;
                Sleep(5000);
                system("cls");
                break;
            }
            case 9: {
                std::cout << "[Ranking dos jogadores que mais tempo passaram a jogar]:" << std::endl;
                std::list<User*> *ranking = casinoPOO.Jogadores_Mais_Frequentes();

                bool JogadorMaisTempo = false;

                for (const User* user : *ranking) {
                    if (user->getTempo() > 0) {
                        std::cout << "Nome: " << user->getNome() << ", Tempo jogado: " << user->getTempo() << std::endl;
                        JogadorMaisTempo = true;
                    }
                }

                if (!JogadorMaisTempo) {
                    std::cout << "Nenhum jogador esteve ainda a jogar." << std::endl;
                }

                cout << "Voltando ao menu inicial em 5 segundos..." << endl;
                Sleep(5000);
                system("cls");
                break;
            }
            case 10: {
                std::cout << "[Ranking dos jogadores que mais PRÉMIOS ganharam no casino]:" << std::endl;
                std::list<User*> *ranking = casinoPOO.Jogadores_Mais_Ganhos();

                bool JogadorComPremios = false;

                for (const User* user : *ranking) {
                    if (user->getGanhos() > 0) {
                        std::cout << "Nome: " << user->getNome() << ", Total de Prémios: " << user->getGanhos() << std::endl;
                        JogadorComPremios = true;
                    }
                }

                if (!JogadorComPremios) {
                    std::cout << "Nenhum jogador ganhou prémios." << std::endl;
                }

                std::cout << "Voltando ao menu inicial em 5 segundos..." << std::endl;
                Sleep(5000);
                system("cls");
                break;
            }
            case 11: {
                std::cout << "[Ranking das Maquinas que mais avariam]:" << std::endl;
                list<string> *rankingFracos = casinoPOO.Ranking_Dos_Fracos();

                for (const string& maquinaInfo : *rankingFracos) {
                    cout << maquinaInfo << endl;
                }
                cout << "Voltando ao menu inicial em 5 segundos..." << endl;
                Sleep(5000);
                system("cls");
                break;
            }
            case 12: {
                std::cout << "[Relatório XML [Estado Casino]]:" << std::endl;
                string nomeF = "relatorio.xml";
                casinoPOO.Relatorio(nomeF);
                cout << "Foi criado um relatório: " << nomeF << " com sucesso!" << endl;
                cout << "Voltando ao menu inicial em 5 segundos..." << endl;
                Sleep(5000);
                system("cls");
                break;
            }
            case 0:
                continuar = false;
                break;
            default:
                std::cout << "Opção inválida. Tente novamente." << std::endl;
                cout << "Voltando ao menu inicial em 5 segundos..." << endl;
                Sleep(5000);
                system("cls");
        }
    }
    std::cout << "Saindo do programa..." << std::endl;


}

