#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <bits/stdc++.h> // BIBLIOTECA PARA FAZER A FUNÇÃO DO VALIDADOR DE DATA E HORA

using namespace std;

//Função para buscar e salvar base

// Salva todo o vetor 'voo' no arquivo (formato simplificado: um campo por linha)
void salvarBase(string nomeBaseDados, Passagem voo[], int qtdAssentos) {
    ofstream escritorArquivo;
    escritorArquivo.open(nomeBaseDados); 

    if (!escritorArquivo.is_open()) {
        cout << "\nERRO: Nao foi possivel abrir o arquivo para escrita.\n";
        return;
    }

    for (int i = 0; i < qtdAssentos; i++) {
        // Salva cada campo com uma quebra de linha
        escritorArquivo << voo[i].dataCompra << "\n"
                       << voo[i].dadosVoo << "\n"
                       << voo[i].nomePassageiro << "\n"
                       << voo[i].companhiaAerea << "\n"
                       << voo[i].numeroAssento << "\n"
                       << voo[i].valor << "\n";
    }

    escritorArquivo.close();
}

int buscarAssento(Passagem voo[], int qtdAssentos, int numeroAssento) {
    for (int i = 0; i < qtdAssentos; i++) {
        if (voo[i].numeroAssento == numeroAssento) {
            return i; // Assento encontrado no índice i
        }
    }
    return -1; // Não encontrado
}

//FUNÇÕES PARA VALIDAÇÃO:

// Função de validação de data/hora
bool validarFormatoDataHora(string dataHora) {
    // Validação simplificada: apenas verifica se tem 10 caracteres (AAAA-MM-DD)
    if (dataHora.size() != 10 || dataHora[4] != '-' || dataHora[7] != '-') {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(dataHora[i])) return false;
    }
    return true;
}

// Função auxiliar para colocar todos os nomes em maiusculos

string paraMaiusculo(string str) {
    for (char &c : str) {
        c = toupper(c);
    }
    return str;
}

// Opção 1: Entrada de Passagem (Inserir no vetor e no arquivo)

void entradaPassagem(string nomeBaseDados, Passagem voo[], int tamanho, int *qtdAssentos) {
    if (*qtdAssentos == tamanho) {
        cout << "Todos os assentos estão ocupados. Entrada negada.\n";
        return;
    }

    Passagem novaPassagem;
    int numeroAssento;
    string dataCompra;

    cout << "\n--- Cadastro de passagem ---\n";

    // 1. Validação do assento (1 a 40 e não duplicado)
    do {
        cout << "Digite o numero do assento (1 à 40): ";
        if (!(cin >> numeroAssento) || numeroAssento < 1 || numeroAssento > tamanho) {
            cout << "ERRO: Numero de assento invalido. Tente novamente.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (buscarAssento(voo, *qtdAssentos, numeroAssento) != -1) {
            cout << "ERRO: O Assento " << numeroAssento << " ja esta ocupado. Tente outro.\n";
        } else {
            novaPassagem.numeroAssento = numeroAssento;
            break;
        }
    } while (true);

    //Limpar o buffer para ler outra string com espaços
    cin.ignore(1000, '\n');

    //Coleta dos outros dados

    cout << "Digite o Nome completo do passageiro: ";
    getline(cin, novaPassagem.nomePassageiro);

    cout << "Companhia Aerea: ";
    getline(cin, novaPassagem.companhiaAerea);

    cout << "Dados do voo (origem e destino)";
    getline(cin, novaPassagem.dadosVoo);

    //Validação da data de compra (AAAA-MM-DD)

    do{
        cout << "Data de compra (AAAA-MM-DD): ";
        getline(cin, dataCompra);

        if (validarFormatoDataHora (dataCompra)){
            novaPassagem.dataCompra = dataCompra;
            break;
        }else{
            cout << "Formato invalido de data. Use AAAA-MM-DD e apenas numeros\n";
        }
    }while (true);

    //4 valor

    cout << "Digite o valor da passagem: ";
    cin >> novaPassagem.valor;

    //5 salva o vetor no arquivo

    voo[*qtdAssentos] = novaPassagem;
    *qtdAssentos += 1;

    salvarBase(nomeBaseDados, voo, *qtdAssentos);
    cout << "\n Passagem para" << novaPassagem.nomePassageiro << " no assento " << novaPassagem.numeroAssento << " Registrada com sucesso\n";
}

//OPÇÃO 2: LISTAR TODOS OS ASSENTOS

void listarAssentos(Passagem voo[], int qtdAssentos, int tamanho){
    cout << "\n--- Listagem de Assentos ---\n";
    if (qtdAssentos == 0){
        cout << "Nenhum assento vendido.\n";
        return;
    }
    for (int i = 0; i < qtdAssentos; i++){
        cout << "Assento: " << voo[i].numeroAssento
             << " | Cliente: " << voo[i].nomePassageiro
             << " | voo: " << voo[i].dadosVoo << endl;
    }
    cout << "---------------\n";
    cout << "Assentos ocupados: " << qtdAssentos << " de " << tamanho << endl;
}

// OPÇÃO 3: CANCELAMENTO

void cancelarPassagem(string nomeBaseDados, Passagem voo[], int *qtdAssentos){
    int assentoCancelar;
    
    cout << "\n--- CANCELAMENTO DE PASSAGEM ---\n";
    cout << "Digite o numero do assento a ser cancelado: ";
    cin >> assentoCancelar;

    int indice = buscarAssento(voo, *qtdAssentos, assentoCancelar);

    if (indice == -1){
        cout << "O assento " << assentoCancelar << " não está ocupado.\n";
        return;
    }

    //Move o ultimo assento ocupado para o lugar do assento cancelado
    voo[indice] = voo[*qtdAssentos];

    *qtdAssentos -= 1; //Reduz o total de assentos ocupados

    salvarBase(nomeBaseDados, voo, *qtdAssentos);

    cout << "Assento " << assentoCancelar << " cancelado com sucesso e liberado\n";
}

//OPÇÃO 4: PESQUISAR

void pesquisarPassagem(Passagem voo[], int qtdAssentos){
    string termoBusca;
    int assentoBusca = -1;

    cout << "\n ---PESQUISAR PASSAGEM---\n";
    cout << "Digite o nome do cliente ou numero do assento: ";
    cin.ignore(1000, '\n');
    getline (cin, termoBusca);

    bool encontrado = false;

    // Converte o termoBusca para maiusculo
    string termoBuscaUpper = paraMaiusculo(termoBusca);

    // Caso tenha digitado para pesquisar pelo numero do assento
    try {
        assentoBusca = stoi(termoBusca);
    } catch (...) {
        // Se caso for digitado um nome, o assentoBusca fica com -1
        assentoBusca = -1;
    }

    cout << "\n Resultado da pesquisa: \n";

    for (int i = 0; i < qtdAssentos; i++){
        // Converte o nome do passageiro para maiusculo
        string nomePassageiroUpper = paraMaiusculo(voo[i].nomePassageiro);

        // Busca pelo nome maiusculo
        bool buscaPorNome = (nomePassageiroUpper.find(termoBuscaUpper) != string::npos);

        // Busca por assento
        bool buscaPorAssento = (assentoBusca != -1 && voo[i].numeroAssento == assentoBusca);

        if (buscaPorNome || buscaPorAssento){
            cout << "========================\n";
            cout << "Assento: " << voo[i].numeroAssento
                 << " | Cliente: " << voo[i].nomePassageiro
                 << " | Voo: " << voo[i].dadosVoo
                 << " | Data da compra: " << voo[i].dataCompra
                 << " | Valor: R$ " << voo[i].valor << endl;
            encontrado = true;
        }
    }

    if (!encontrado){
        cout << "Nenhuma passagem encontrada '" << termoBusca << "'\n";
    }
}