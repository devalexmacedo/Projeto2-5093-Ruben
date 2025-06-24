#define _CRT_SECURE_NO_WARNINGS
#include "Produto.h"
#include <iostream>
using namespace std;
// Construtor padrão
Produto::Produto() {
    id = 0;
    nome = "";
    quantidade = 0;
    precoCusto = 0.0;
}

// Construtor com parâmetros (sem ID, que será gerenciado automaticamente)
Produto::Produto(const std::string& nome, int quantidade, float precoCusto) {
    this->id = 0; // ID inicial 0, será definido pela classe Loja
    this->nome = nome;
    this->quantidade = quantidade;
    this->precoCusto = precoCusto;
}

// Métodos de acesso (getters)
int Produto::getId() const {
    return id;
}

std::string Produto::getNome() const {
    return nome;
}

int Produto::getQuantidade() const {
    return quantidade;
}

float Produto::getPrecoCusto() const {
    return precoCusto;
}

float Produto::getPrecoVenda() const {
    // Preço de venda é o preço de custo + 30% + 23% do IVA em cima do valor final.
    return (precoCusto * 1.3) * 1.23;
}

// Métodos de modificação (setters)
void Produto::setId(int id) {
    this->id = id;
}

void Produto::setNome(const std::string& nome) {
    this->nome = nome;
}

void Produto::setQuantidade(int quantidade) {
    // Verifica se a quantidade é não negativa antes de atribuir
    if (quantidade >= 0) { // Verifica se a quantidade é não negativa
       cout << "Quantidade não pode ser negativa. Atribuindo 0." << endl;
       quantidade = 0;
    } 
    this->quantidade = quantidade;
}

void Produto::setPrecoCusto(float precoCusto) {
    if (precoCusto < 0) { // Verifica se o preço de custo é não negativo
        cout << "Preço de custo não pode ser negativo. Atribuindo 0." << endl;
        precoCusto = 0.0;
    }   
    this->precoCusto = precoCusto;
}

// Métodos adicionais
void Produto::adicionarEstoque(int quantidade) {
    if (quantidade > 0) {
        this->quantidade += quantidade;
    }
}

void Produto::removerEstoque(int quantidade) {
    // Verifica se a quantidade é positiva e se há estoque suficiente
     if (quantidade < 0) { // Verifica se a quantidade não é negativa
        cout << "Quantidade a remover não pode ser negativa." << endl;
        return;
    }
    if (quantidade > 0 && this->quantidade >= quantidade) {
        this->quantidade -= quantidade;
    }
}

bool Produto::temEstoqueSuficiente(int quantidade) const {
    return this->quantidade >= quantidade;
}
