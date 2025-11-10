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

#define TAM 40

using namespace std;

#include "struct.cpp"
#include "meusMetodos.h"


// FUNÇÃO DO MENU PRINCIPAL

void menuPassagem(string baseDados, Passagem voo[], int tamanho, int numeroAssento, int qtdAssentos) {
    int opcao;
    
    // As chamadas para as opções 1 e 3 estão criadas no arquivo meusMetodos.h
    do {
        system("cls"); // Limpa a tela (infelizmente não funciona)
        cout << "\n================================\n";
        cout << "        MENU GARAGEM\n";
        cout << "================================\n";
        cout << "1) Cadastrar passagem\n";
        cout << "2) Listagem de assentos\n";
        cout << "3) Cancelamento\n";
        cout << "4) sair\n";
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1: 
            entradaPassagem(baseDados, voo, tamanho, &qtdAssentos); // CHAMADA DA FUNÇÃO
            // cout << "\n[Opcao 1] - Logica de Entrada de Passagem
            break;
        
        // Pausa no console para visualização
        if (opcao != 4) {
            cout << "\nPressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }

        default:
            cout << "Opcao invalida. Tente novamente.\n";
            break;
        }
        
    } while (opcao != 4);
}

int main() {
    Passagem voo[TAM];
    int qtdAssentos = 0;
    string baseDados = "voo.csv";

    menuPassagem(baseDados, voo, TAM, numeroAssento, qtdAssentos);
    
    return 0; // retornar 0
}