#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

// Funções utilitárias para validação de entrada
void limparBufferEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void tratarErroEntrada() {
    cout << "Entrada inválida. Por favor, tente novamente.\n";
    cin.clear(); // Limpa os flags de erro
    limparBufferEntrada(); // Descarta a entrada inválida
}

// Função para obter um float válido do usuário
float obterFloat(const string& prompt) {
    float valor;
    while (true) {
        cout << prompt;
        if (cin >> valor && valor > 0) {
            limparBufferEntrada();
            return valor;
        }
        else {
            tratarErroEntrada();
        }
    }
}

// Função para obter um int válido do usuário
int obterInt(const string& prompt) {
    int n;
    while (true) {
        cout << prompt;
        if (cin >> n) {
            limparBufferEntrada();
            return n;
        }
        else {
            tratarErroEntrada();
        }
    }
}

// Função para obter uma string do usuário
string obterString(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

// Função para limpar a tela (compatível com Windows e sistemas Unix-like)
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função para pausar a execução até que o usuário pressione uma tecla
void pausar() {
    cout << "\nPressione Enter para continuar...";
    cin.get();
}

// Função para converter uma string para minúsculas
string paraMinusculo(const string& str) {
    string resultado = str;
    for (char& c : resultado) {
        c = tolower(c);
    }
    return resultado;
}

// Função para calcular o preço de venda (custo + 30%)
float calcularPrecoVenda(float precoCusto) {
    return precoCusto * 1.3f;
}

// Função para calcular o IVA (23%)
float calcularIVA(float preco) {
    return preco * 0.23f;
}

// Função para verificar se uma venda é grátis (25% de chance)
bool verificarVendaGratis() {
    return (rand() % 4) == 0;
}

#endif // UTILITARIOS_H
