#define _CRT_SECURE_NO_WARNINGS
#include "Produto.h"
#include <cstring>

using namespace std;

// Construtor padrão
Produto::Produto() {
    id = 0;
    nome[0] = '\0';
    quantidade = 0;
    precoCusto = 0.0;
    precoVenda = 0.0;
}

// Construtor com parâmetros (sem ID, que será gerenciado pela classe Loja)
Produto::Produto(char* nome, int quantidade, double precoCusto) {
    this->id = 0; // ID inicial 0, será definido pela classe Loja
    strcpy(this->nome, nome);
    this->quantidade = quantidade;
    this->precoCusto = precoCusto;
    calcularPrecoVenda();
}

// Métodos de acesso (getters)
int Produto::getId() {
    return id;
}

char* Produto::getNome() {
    return nome;
}

int Produto::getQuantidade() {
    return quantidade;
}

double Produto::getPrecoCusto() {
    return precoCusto;
}

double Produto::getPrecoVenda() {
    return precoVenda;
}

// Métodos de modificação (setters)
void Produto::setId(int id) {
    this->id = id;
}

void Produto::setNome(char* nome) {
    strcpy(this->nome, nome);
}

void Produto::setQuantidade(int quantidade) {
    this->quantidade = quantidade;
}

void Produto::setPrecoCusto(double precoCusto) {
    this->precoCusto = precoCusto;
    calcularPrecoVenda();
}

// Métodos adicionais
void Produto::calcularPrecoVenda() {
    // Preço de venda é o preço de custo + 30%
    precoVenda = precoCusto * 1.3;
}

void Produto::adicionarEstoque(int quantidade) {
    if (quantidade > 0) {
        this->quantidade += quantidade;
    }
}

void Produto::removerEstoque(int quantidade) {
    if (quantidade > 0 && this->quantidade >= quantidade) {
        this->quantidade -= quantidade;
    }
}

bool Produto::temEstoqueSuficiente(int quantidade) {
    return this->quantidade >= quantidade;
}

