// Venda.cpp - Implementação da classe Venda
#define _CRT_SECURE_NO_WARNINGS
#include "Venda.h"
#include <string.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

using namespace std;

// String vazia estática para retorno seguro
static char stringVazia[1] = { '\0' };

// Construtor padrão
Venda::Venda() {
    numeroFatura = 0;
    numeroCliente = 0;
    numItens = 0;
    totalComIVA = 0.0;
    valorEntregue = 0.0;
    troco = 0.0;
    data[0] = '\0';

    // Inicializar arrays
    for (int i = 0; i < 100; i++) {
        linhas[i] = 0;
        produtos[i][0] = '\0';
        quantidades[i] = 0;
        precosSemIVA[i] = 0.0;
        ivas[i] = 0.0;
    }
}

// Construtor com parâmetros básicos
Venda::Venda(int numeroFatura, int numeroCliente, char* data) {
    this->numeroFatura = numeroFatura;
    this->numeroCliente = numeroCliente;
    numItens = 0;
    totalComIVA = 0.0;
    valorEntregue = 0.0;
    troco = 0.0;

    // Copiar data com segurança
    strcpy(this->data, data);

    // Inicializar arrays
    for (int i = 0; i < 100; i++) {
        linhas[i] = 0;
        produtos[i][0] = '\0';
        quantidades[i] = 0;
        precosSemIVA[i] = 0.0;
        ivas[i] = 0.0;
    }
}

// Métodos de acesso (getters)
int Venda::getNumeroFatura() {
    return numeroFatura;
}

int Venda::getNumeroCliente() {
    return numeroCliente;
}

int Venda::getNumItens() {
    return numItens;
}

double Venda::getTotalComIVA() {
    return totalComIVA;
}

char* Venda::getData() {
    return data;
}

// Métodos de modificação (setters)
void Venda::setNumeroFatura(int numeroFatura) {
    this->numeroFatura = numeroFatura;
}

void Venda::setNumeroCliente(int numeroCliente) {
    this->numeroCliente = numeroCliente;
}

void Venda::setData(char* data) {
    strcpy(this->data, data);
}

// Métodos adicionais
void Venda::adicionarItem(int linha, char* nomeProduto, int quantidade, double precoSemIVA) {
    if (numItens < 100) {
        linhas[numItens] = linha;

        // Copiar nome do produto com segurança
        strcpy(produtos[numItens], nomeProduto);

        quantidades[numItens] = quantidade;
        precosSemIVA[numItens] = precoSemIVA;
        ivas[numItens] = precoSemIVA * 0.23; // IVA de 23%

        numItens++;
        calcularTotal();
    }
}

void Venda::calcularTotal() {
    totalComIVA = 0.0;

    for (int i = 0; i < numItens; i++) {
        totalComIVA += (precosSemIVA[i] + ivas[i]) * quantidades[i];
    }
}

void Venda::processarPagamento(double valorEntregue) {
    this->valorEntregue = valorEntregue;
    this->troco = valorEntregue - totalComIVA;
}

// Nova função de checkout
bool Venda::checkout() {
    double somaIVA = 0.0;
    char confirmacao;
    string input;

    system("cls");

    cout << "=========== Checkout ===========\n";
    for (int i = 0; i < numItens; ++i) {
        cout << "Produto: " << produtos[i] << "\n";
        cout << "Quantidade: " << quantidades[i] << "\n";
        cout << "Preço Unitário: " << fixed << setprecision(2) << precosSemIVA[i] + ivas[i] << " euros\n";
        cout << "Preço s/IVA: " << fixed << setprecision(2) << precosSemIVA[i] << " euros\n";
        cout << "IVA (23%): " << fixed << setprecision(2) << ivas[i] << " euros\n";
        cout << "---------------------------------\n";

        somaIVA += ivas[i] * quantidades[i];
    }

    cout << "Subtotal s/IVA: " << fixed << setprecision(2) << totalComIVA - somaIVA << " euros\n";
    cout << "Total IVA: " << fixed << setprecision(2) << somaIVA << " euros\n";
    cout << "Total c/IVA: " << fixed << setprecision(2) << totalComIVA << " euros\n\n";

    while (true) {
        do {
            cout << "Confirmar compra (Y - Sim) ou Desistir da venda (N - Não)? ";
            getline(cin, input);
            if (!input.empty()) {
                confirmacao = input[0];
            }
            else {
                confirmacao = '\0';
            }
        } while (confirmacao != 'y' && confirmacao != 'n' && confirmacao != 'Y' && confirmacao != 'N');

        if (confirmacao == 'y' || confirmacao == 'Y') {
            cout << "Compra confirmada.\n";
            return true; // Retorna true se a compra for confirmada
        }
        else {
            cout << "Venda cancelada no checkout.\n";
            return false; // Retorna false se a venda for cancelada
        }
    }
    return false;
}

void Venda::imprimirTalao() {
    double somaIVA = 0.0;
    for (int i = 0; i < numItens; i++) {
        somaIVA += ivas[i] * quantidades[i];
    }

    time_t t = time(nullptr);
    tm* dataAtual = localtime(&t);

    system("cls"); // Limpa a tela para o talão branco com letras pretas

    cout << "======= TALÃO DE COMPRAS =======\n";
    cout << "Fatura N: " << numeroFatura << "\n";
    cout << "Data: " << put_time(dataAtual, "%d/%m/%Y %H:%M") << "\n";
    cout << "Cliente N: " << numeroCliente << "\n\n";
    cout << "----- Detalhes dos Produtos -----\n";

    for (int i = 0; i < numItens; i++) {
        cout << "Produto: " << produtos[i] << "\n";
        cout << "Quantidade: " << quantidades[i] << "\n";
        cout << "Preço Unitário: " << fixed << setprecision(2) << precosSemIVA[i] + ivas[i] << " euros\n";
        cout << "Preço s/IVA: " << fixed << setprecision(2) << precosSemIVA[i] << " euros\n";
        cout << "IVA (23%): " << fixed << setprecision(2) << ivas[i] * quantidades[i] << " euros\n";
        cout << "---------------------------------\n";
    }

    cout << "Subtotal s/IVA: " << fixed << setprecision(2) << totalComIVA - somaIVA << " euros\n";
    cout << "Total IVA: " << fixed << setprecision(2) << somaIVA << " euros\n";
    cout << "Total c/IVA: " << fixed << setprecision(2) << totalComIVA << " euros\n";
    cout << "Valor Pago: " << fixed << setprecision(2) << valorEntregue << " euros\n";
    cout << "Troco: " << fixed << setprecision(2) << troco << " euros\n";
    cout << "=====================================\n";
}

// Métodos para acesso aos itens
int Venda::getLinha(int indice) {
    if (indice >= 0 && indice < numItens) {
        return linhas[indice];
    }
    return -1;
}

char* Venda::getNomeProduto(int indice) {
    if (indice >= 0 && indice < numItens) {
        return produtos[indice];
    }
    return stringVazia;
}

int Venda::getQuantidade(int indice) {
    if (indice >= 0 && indice < numItens) {
        return quantidades[indice];
    }
    return 0;
}

double Venda::getPrecoSemIVA(int indice) {
    if (indice >= 0 && indice < numItens) {
        return precosSemIVA[indice];
    }
    return 0.0;
}

double Venda::getIVA(int indice) {
    if (indice >= 0 && indice < numItens) {
        return ivas[indice];
    }
    return 0.0;
}

double Venda::getValorEntregue() {
    return valorEntregue;
}

double Venda::getTroco() {
    return troco;
}