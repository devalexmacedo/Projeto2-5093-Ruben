#include "Produto.h"
#include <iostream>

using namespace std;
// Construtor padrão
Produto::Produto() : id(0), quantidade(0), precoCusto(0.0f), precoVenda(0.0f) {}

// Construtor com parâmetros
Produto::Produto(const string& nome, int quantidade, float precoCusto)
    : nome(nome), quantidade(quantidade), precoCusto(precoCusto), id(0) {
    calcularPrecoVenda();
}

// Calcula o preço de venda com base no custo (margem de 30%)
void Produto::calcularPrecoVenda() {
    precoVenda = precoCusto * 1.3f;
}

// Retorna o ID do produto
int Produto::getId() const {
    return id;
}

// Retorna o nome do produto
string Produto::getNome() const {
    return nome;
}

// Retorna a quantidade em estoque
int Produto::getQuantidade() const {
    return quantidade;
}

// Retorna o preço de custo
float Produto::getPrecoCusto() const {
    return precoCusto;
}

// Retorna o preço de venda
float Produto::getPrecoVenda() const {
    return precoVenda;
}

// Define o ID do produto
void Produto::setId(int newId) {
    id = newId;
}

// Define o nome do produto
void Produto::setNome(const string& newNome) {
    nome = newNome;
}

// Define o preço de custo e recalcula o preço de venda
void Produto::setPrecoCusto(float newPrecoCusto) {
    precoCusto = newPrecoCusto;
    calcularPrecoVenda();
}

// Adiciona quantidade ao estoque
void Produto::adicionarEstoque(int qtd) {
    if (qtd > 0) {
        quantidade += qtd;
    }
    this->quantidade += quantidade;
}

// Remove quantidade do estoque
bool Produto::removerEstoque(int qtd) {
    if (qtd > 0 && quantidade >= qtd) {
        quantidade -= qtd;
        return true;
    }
    return false;
}

// Verifica se há estoque suficiente
bool Produto::temEstoqueSuficiente(int qtd) const {
    return quantidade >= qtd;
}

