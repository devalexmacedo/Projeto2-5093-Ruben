#include "Produto.h" // Inclui o cabeçalho da classe Produto

using namespace std; // Usa o namespace padrão para facilitar o acesso a string, vector, etc.

// Construtor padrão da classe Produto.
// Inicializa todos os membros de dados com valores padrão ou zero.
// O ID é inicializado com 0, e o preço de venda é calculado.
Produto::Produto() : id(0), nome(""), quantidade(0), precoCusto(0.0f), precoVenda(0.0f) {
    calcularPrecoVenda(); // Garante que o preço de venda seja calculado mesmo com valores iniciais zero.
}

// Construtor com parâmetros da classe Produto.
// Inicializa o nome, quantidade e preço de custo com os valores fornecidos.
// O ID é inicializado com 0 (será atribuído pela Loja).
// O preço de venda é calculado automaticamente com base no preço de custo.
Produto::Produto(const string& nome, int quantidade, float precoCusto)
    : nome(nome), quantidade(quantidade), precoCusto(precoCusto), id(0) {
    calcularPrecoVenda(); // Calcula o preço de venda assim que o preço de custo é definido.
}

// Método privado para calcular o preço de venda.
// Define o preço de venda como 130% do preço de custo (margem de 30%).
// Este método é chamado internamente pelos construtores e pelo setter de precoCusto.
void Produto::calcularPrecoVenda() {
    precoVenda = precoCusto * 1.30f; // 30% de margem sobre o preço de custo.
}

// Método de acesso (getter) para o ID do produto.
// Retorna o ID único do produto.
int Produto::getId() const {
    return id;
}

// Método de acesso (getter) para o nome do produto.
// Retorna o nome descritivo do produto.
string Produto::getNome() const {
    return nome;
}

// Método de acesso (getter) para a quantidade em estoque do produto.
// Retorna o número de unidades do produto disponíveis.
int Produto::getQuantidade() const {
    return quantidade;
}

// Método de acesso (getter) para o preço de custo do produto.
// Retorna o preço pelo qual o produto foi adquirido.
float Produto::getPrecoCusto() const {
    return precoCusto;
}

// Método de acesso (getter) para o preço de venda do produto.
// Retorna o preço pelo qual o produto será vendido ao cliente.
float Produto::getPrecoVenda() const {
    return precoVenda;
}

// Método de modificação (setter) para o ID do produto.
// Define o ID único do produto. Usado pela classe Loja.
void Produto::setId(int newId) {
    id = newId;
}

// Método de modificação (setter) para o nome do produto.
// Define um novo nome para o produto.
void Produto::setNome(const string& newNome) {
    nome = newNome;
}

// Método de modificação (setter) para o preço de custo do produto.
// Define um novo preço de custo e recalcula automaticamente o preço de venda.
void Produto::setPrecoCusto(float newPrecoCusto) {
    precoCusto = newPrecoCusto;
    calcularPrecoVenda(); // Recalcula o preço de venda sempre que o custo é alterado.
}

// Adiciona uma quantidade especificada ao estoque do produto.
// A quantidade deve ser positiva.
void Produto::adicionarEstoque(int qtd) {
    if (qtd > 0) {
        quantidade += qtd;
    }
}

// Remove uma quantidade especificada do estoque do produto.
// Retorna 'true' se a remoção for bem-sucedida (há estoque suficiente), 'false' caso contrário.
bool Produto::removerEstoque(int qtd) {
    if (qtd > 0 && quantidade >= qtd) {
        quantidade -= qtd;
        return true;
    }
    return false; // Não há estoque suficiente ou quantidade inválida.
}

// Verifica se há estoque suficiente para uma determinada quantidade.
// Retorna 'true' se a quantidade solicitada for menor ou igual à quantidade em estoque, 'false' caso contrário.
bool Produto::temEstoqueSuficiente(int qtd) const {
    return quantidade >= qtd;
}
