#include "Produto.h"

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
    // Preço de venda é o preço de custo + 30%
    return precoCusto * 1.3;
}

// Métodos de modificação (setters)
void Produto::setId(int id) {
    this->id = id;
}

void Produto::setNome(const std::string& nome) {
    this->nome = nome;
}

void Produto::setQuantidade(int quantidade) {
    this->quantidade = quantidade;
}

void Produto::setPrecoCusto(float precoCusto) {
    this->precoCusto = precoCusto;
}

// Métodos adicionais
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

bool Produto::temEstoqueSuficiente(int quantidade) const {
    return this->quantidade >= quantidade;
}
