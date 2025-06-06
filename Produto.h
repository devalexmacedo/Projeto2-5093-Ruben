// Produto.h - Definição da classe Produto
#pragma once

class Produto {
private:
    int id;                 // ID único do produto (gerenciado pela classe Loja)
    char nome[50];          // Nome do produto
    int quantidade;         // Quantidade em estoque
    double precoCusto;      // Preço de custo
    double precoVenda;      // Preço de venda (custo + 30%)

public:
    // Construtor padrão
    Produto();

    // Construtor com parâmetros (sem ID, que será gerenciado pela classe Loja)
    Produto(char* nome, int quantidade, double precoCusto);

    // Métodos de acesso (getters)
    int getId();
    char* getNome();
    int getQuantidade();
    double getPrecoCusto();
    double getPrecoVenda();

    // Métodos de modificação (setters)
    void setId(int id);  // Usado apenas internamente pela classe Loja
    void setNome(char* nome);
    void setQuantidade(int quantidade);
    void setPrecoCusto(double precoCusto);

    // Métodos adicionais
    void calcularPrecoVenda();     // Calcula o preço de venda (custo + 30%)
    void adicionarEstoque(int quantidade);  // Adiciona quantidade ao estoque
    void removerEstoque(int quantidade);    // Remove quantidade do estoque
    bool temEstoqueSuficiente(int quantidade);  // Verifica se há estoque suficiente
};

