// produto.h - Definição da classe Produto
#pragma once  // Garante que o arquivo só será incluído uma vez

#include <string>
using namespace std;

// Representa um produto do sistema com controle de estoque e preços
class Produto {
private:
    int id;             // Código único do produto
    string nome;        // Nome do produto
    int quantidade;     // Quantidade em estoque
    float precoCusto;   // Preço de compra
    float precoVenda;   // Preço de venda (calculado automaticamente)

    // Atualiza o preço de venda baseado no custo (margem fixa de 30%)
    void calcularPrecoVenda();

public:
    // Construtores
    Produto();  // Cria produto vazio
    Produto(const string& nome, int quantidade, float precoCusto);  // Cria produto com dados básicos

    // Consultas (getters)
    int getId() const;            // Retorna ID
    string getNome() const;       // Retorna nome
    int getQuantidade() const;    // Retorna quantidade em estoque
    float getPrecoCusto() const;  // Retorna preço de custo
    float getPrecoVenda() const;  // Retorna preço de venda

    // Alterações (setters)
    void setId(int newId);                    // Define ID
    void setNome(const string& newNome);      // Altera nome
    void setPrecoCusto(float newPrecoCusto);  // Atualiza preço de custo e recalcula venda

    // Operações de estoque
    void adicionarEstoque(int qtd);           // Adiciona quantidade ao estoque
    bool removerEstoque(int qtd);             // Remove do estoque (retorna sucesso)
    bool temEstoqueSuficiente(int qtd) const; // Verifica se há estoque disponível
};