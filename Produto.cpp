#include "Produto.h"
#include <iostream>

using namespace std;
<<<<<<< HEAD

=======
>>>>>>> 9e5aa59e7d5bbcc663b3049ceb76b1c86b0e3cdc
// Construtor padrão
Produto::Produto() : id(0), quantidade(0), precoCusto(0.0f), precoVenda(0.0f) {}

// Construtor com parâmetros
Produto::Produto(const string& nome, int quantidade, float precoCusto)
    : nome(nome), quantidade(quantidade), precoCusto(precoCusto), id(0) {
    calcularPrecoVenda();
}

<<<<<<< HEAD
// Calcula o preço de venda com base no custo (margem de 30%)
void Produto::calcularPrecoVenda() {
    precoVenda = precoCusto * 1.3f;
=======
// Construtor com parâmetros (sem ID, que será gerenciado automaticamente)
Produto::Produto(const std::string& nome, int quantidade, float precoCusto) {
    this->id = 0; 
    this->nome = nome;
    this->quantidade = quantidade;
    this->precoCusto = precoCusto;
>>>>>>> 9e5aa59e7d5bbcc663b3049ceb76b1c86b0e3cdc
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

<<<<<<< HEAD
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
=======
void Produto::setNome(const std::string& nome) {
    if (nome.empty()) { // Verifica se o nome não é vazio
        cout << "Nome não pode ser vazio. Atribuindo 'Produto Desconhecido'." << endl;
        this->nome = "Produto Desconhecido";
        return;
    }
    this->nome = nome;
}

void Produto::setQuantidade(int quantidade) {
    // Verifica se a quantidade não é negativa antes de atribuir
    if (quantidade < 0) { // Verifica se a quantidade não é negativa
       cout << "Quantidade não pode ser negativa. Atribuindo 0." << endl;
       quantidade = 0;
    } else if (quantidade == 0) { // Verifica se a quantidade é zero
        cout << "Quantidade não pode ser zero. Atribuindo 1." << endl;
        quantidade = 1; // Atribui 1 se a quantidade for zero
    }
    this->quantidade = quantidade;
}

void Produto::setPrecoCusto(float precoCusto) {
    if (precoCusto < 0) { // Verifica se o preço de custo é não negativo
        cout << "Preço de custo não pode ser negativo. Atribuindo 0." << endl;
        precoCusto = 0.0;
    } else {
        this->precoCusto = precoCusto;
    }  
}
// Métodos adicionais
void Produto::adicionarEstoque(int quantidade) {
    if (quantidade <= 0) { // Verifica se a quantidade é positiva e diferente de zero
        cout << "Quantidade a adicionar deve ser positiva e diferente de zero." << endl;
        return;
>>>>>>> 9e5aa59e7d5bbcc663b3049ceb76b1c86b0e3cdc
    }
    this->quantidade += quantidade;
}

<<<<<<< HEAD
// Remove quantidade do estoque
bool Produto::removerEstoque(int qtd) {
    if (qtd > 0 && quantidade >= qtd) {
        quantidade -= qtd;
        return true;
    }
    return false;
=======
void Produto::removerEstoque(int quantidade) {
    // Verifica se a quantidade é positiva e se há estoque suficiente
     if (quantidade < 0) { // Verifica se a quantidade não é negativa
        cout << "Quantidade a remover não pode ser negativa." << endl;
        return;
    }
    if (quantidade == 0) {
        cout << "Quantidade a remover não pode ser zero." << endl;
        return;
    }
    if (quantidade > this->quantidade) {
        cout << "Estoque insuficiente para remover " << quantidade << " unidades." << endl;
        return;
    }
    this->quantidade -= quantidade;
>>>>>>> 9e5aa59e7d5bbcc663b3049ceb76b1c86b0e3cdc
}

// Verifica se há estoque suficiente
bool Produto::temEstoqueSuficiente(int qtd) const {
    return quantidade >= qtd;
}

