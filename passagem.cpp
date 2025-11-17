/*SISTEMA PARA COMPRA DE PASSAGENS

    MENU
1 - Cadastrar
2 - Listar
3 - Remover
4 - Pesquisar
5 - Sair
Opção
*/

#include <iostream>
#include <string>
#include <fstream> 
#include <sstream> // Para funções de string se necessário

using namespace std;

#include "struct.h"
#include "meusMetodos.h"


// FUNÇÃO DO MENU PRINCIPAL

void menuPassagem(string baseDados, Passagem voo[], int tamanho, int *qtdAssentos) {
    int opcao;
    
    // As chamadas para as opções 1 e 4 estão criadas no arquivo meusMetodos.h
    do {
        //system("cls"); // Limpa a tela (infelizmente não funciona)
        cout << "\n================================\n";
        cout << "        MENU PASSAGENS\n";
        cout << "================================\n";
        cout << "1) Cadastrar passagem\n";
        cout << "2) Listagem de assentos\n";
        cout << "3) Cancelamento\n";
        cout << "4) Pesquisar\n";
        cout << "5) sair\n";
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1: 
            entradaPassagem(baseDados, voo, tamanho, qtdAssentos); //Chamada da função
            break;
        case 2:
            listarAssentos(voo, *qtdAssentos, tamanho);
            break;
        case 3: 
            cancelarPassagem(baseDados, voo, qtdAssentos);
            break;
        case 4:
            pesquisarPassagem(voo, *qtdAssentos);
            break;
        case 5:
            cout << "Programa encerrado.\n";
            break;

        default:
            cout << "Opcao invalida. Tente novamente.\n";
            break;
        }

        // Pausa no console para visualização
        if (opcao != 4) {
            cout << "\nPressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (opcao != 5);
}

//FUNÇÃO PARA CARREGAR NA BASE DE ARQUIVOS

//Função de leitura para carregar o voo.csv no vetor

int carregarBasePassagens(string nomeBaseDados, Passagem voo[], int tamanho) {
    ifstream procuradorArquivo;
    procuradorArquivo.open(nomeBaseDados);

    if (!procuradorArquivo.is_open()) {
        cout << "AVISO: Arquivo '" << nomeBaseDados << "' nao encontrado. Iniciando vazio.\n";
        return 0; 
    }
    
    int qtdAssentos = 0;
    string campo;
    
    // O loop tenta ler todos os 4 campos de uma vez.
    // Se falhar em qualquer um, significa que o arquivo acabou.
    while (qtdAssentos < tamanho && 
           getline(procuradorArquivo, voo[qtdAssentos].dataCompra) &&
           getline(procuradorArquivo, voo[qtdAssentos].dadosVoo) &&
           getline(procuradorArquivo, voo[qtdAssentos].nomePassageiro) &&
           getline(procuradorArquivo, voo[qtdAssentos].companhiaAerea) &&
           getline(procuradorArquivo, campo)) // Lê o número do assento como string
    {
        // CONVERSÃO SIMPLIFICADA (DE STRING PARA NÚMERO)
        try {
            voo[qtdAssentos].numeroAssento = stoi(campo);
            // Tenta ler o valor (último campo)
            if (getline(procuradorArquivo, campo)) {
                 voo[qtdAssentos].valor = stof(campo);
                 qtdAssentos++; // SÓ INCREMENTA SE AMBOS CAMPOS NUMÉRICOS FORAM LIDOS
            }
        } catch (...) {
            cout << "AVISO: Linha ignorada devido a erro de formato numerico no arquivo.\n";
        }
    }

    procuradorArquivo.close();
    cout << "Base de dados carregada. Total de assentos ocupados: " << qtdAssentos << ".\n";
    return qtdAssentos;
}

int main() {
    Passagem voo[TAM];
    int qtdAssentos = 0;
    string baseDados = "voo.csv";

    //Carrega a base de dados ao iniciar
    qtdAssentos = carregarBasePassagens(baseDados, voo, TAM);

    //Carrega o menu
    menuPassagem(baseDados, voo, TAM, &qtdAssentos);
    
    return 0;
}