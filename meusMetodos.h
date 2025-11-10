#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <bits/stdc++.h> // BIBLIOTECA PARA FAZER A FUNÇÃO DO VALIDADOR DE DATA E HORA

using namespace std;

int buscarAssento(Passagem voo[], int qtdAssentos, int numeroAssento) {
    for (int i = 0; i < qtdAssentos; i++) {
        if (voo[i].numeroAssento == numeroAssento) {
            return i; // Assento encontrado no índice i
        }
    }
    return -1; // Não encontrado
}

// 2. FUNÇÕES DO MENU DA GARAGEM

// Opção 1: Entrada de Passagem (Inserir no vetor e no arquivo)

void entradaPassagem(string nomeBaseDados, Passagem voo[], int tamanho, int *qtdAssentos) {
    if (*qtdAssentos == tamanho) {
        cout << "Todos os assentos estão ocupados. Entrada negada.\n";
        return;
    }

    Passagem novaPassagem;
    int numeroAssento;
    string dataEntrada;

    cout << "\n--- Entrada de Veiculo ---\n";

    // 1. VALIDAÇÃO DO ASSENTO (Placa com 7 caracteres e não duplicada)
    do {
        cout << "Digite o numero do assento (1 à 40): ";
        cin >> numeroAssento;

        if (numeroAssento <= 40) {
            // Verifica se o numero do assento já está ocupado (em memória)
            if (buscarAssento(voo, *qtdAssentos, numeroAssento) != -1) {
                cout << "ERRO: o Assento já está ocupado. Tente novamente.\n";
            } else {
                novaPassagem.numeroAssento = numeroAssento;
                break; // Sai do loop do assento
            }
        } else {
            cout << "ERRO: o número do assento é maior que o número suportado. Tente novamente.\n";
        }
    } while (true);