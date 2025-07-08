#include "Produto.h" // Inclui o cabeçalho da classe Produto
#include "constantes.h"

using namespace std; // Usa o namespace padrão para facilitar o acesso a string, vector, etc.

// Construtor padrão da classe Produto.
Produto::Produto() : id(), nome(""), quantidade(0), precoCusto(0.0f), precoVenda(0.0f) {
    calcularPrecoVenda(); // Garante que o preço de venda seja calculado mesmo com valores iniciais zero.
}

// Construtor com parâmetros da classe Produto.
Produto::Produto(const string& nome, int quantidade, float precoCusto)
    : nome(nome), quantidade(quantidade), precoCusto(precoCusto), id(0) {
    calcularPrecoVenda(); // Calcula o preço de venda assim que o preço de custo é definido.
}

// Método privado para calcular o preço de venda.
void Produto::calcularPrecoVenda() {
    precoVenda = precoCusto * (1 + MARGEM_LUCRO); // 30% de margem sobre o preço de custo.
}

// Método de acesso (getter) para o ID do produto.
// Retorna o ID único do produto.
int Produto::getId() const {
    return id;
}

// Método de acesso (getter) para o nome do produto.
string Produto::getNome() const {
    return nome;
}

// Método de acesso (getter) para a quantidade em estoque do produto.
int Produto::getQuantidade() const {
    return quantidade;
}

// Método de acesso (getter) para o preço de custo do produto.
float Produto::getPrecoCusto() const {
    return precoCusto;
}

// Método de acesso (getter) para o preço de venda do produto.
float Produto::getPrecoVenda() const {
    return precoVenda;
}

// Método de modificação (setter) para o ID do produto.
void Produto::setId(int newId) {
    id = newId;
}

// Método de modificação (setter) para o nome do produto.
void Produto::setNome(const string& newNome) {
    nome = newNome;
}

// Método de modificação (setter) para o preço de custo do produto.
void Produto::setPrecoCusto(float newPrecoCusto) {
    precoCusto = newPrecoCusto;
    calcularPrecoVenda(); // Recalcula o preço de venda sempre que o custo é alterado.
}

// Adiciona uma quantidade especificada ao estoque do produto.
void Produto::adicionarEstoque(int qtd) {
    if (qtd > 0) {
        quantidade += qtd;
    }
}

// Remove uma quantidade especificada do estoque do produto.
bool Produto::removerEstoque(int qtd) {
    if (qtd > 0 && quantidade >= qtd) {
        quantidade -= qtd;
        return true;
    }
    return false; // Não há estoque suficiente ou quantidade inválida.
}

// Verifica se há estoque suficiente para uma determinada quantidade.
bool Produto::temEstoqueSuficiente(int qtd) const {
    return quantidade >= qtd;
}
