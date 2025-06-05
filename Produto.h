#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <locale.h> // Para permitir caracteres especiais
#include <conio.h> // Interrompe limpezas de tela for de hora esperando um input do user
#include <vector>
#include <algorithm> // adicionador para verificar a igualdade entre strings: transform e tolower
#include <limits> // Necessário para as funções de validações

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS, necessario para usar o localtime


using namespace std;

class Produto {
private:
    int id;                 // ID único do produto
    char nome[50];          // Nome do produto
    int quantidade;         // Quantidade em estoque
    double precoCusto;      // Preço de custo
    double precoVenda;      // Preço de venda (custo + 30%)

public:
    // Construtor padrão
    Produto();

    // Construtor com parâmetros
    Produto(int id, char* nome, int quantidade, double precoCusto);

    // Métodos de acesso (getters)
    int getId() const;
    char* getNome() const;
    int getQuantidade() const;
    double getPrecoCusto() const;
    double getPrecoVenda() const;

    // Métodos de modificação (setters)
    void setId(int id);
    void setNome(char* nome);
    void setQuantidade(int quantidade);
    void setPrecoCusto(double precoCusto);

    // Métodos adicionais
    void calcularPrecoVenda();     // Calcula o preço de venda (custo + 30%)
    void adicionarEstoque(int quantidade);  // Adiciona quantidade ao estoque
    void removerEstoque(int quantidade);    // Remove quantidade do estoque
    bool temEstoqueSuficiente(int quantidade);  // Verifica se há estoque suficiente
};

class ProdutoManager {
private:
    vector<Produto> produtos;  // Vetor para armazenar os produtos
    int nextId;                // Gerador automático de IDs

public:
    // Construtor: inicia nextId com 1 (ou outro valor inicial desejado)
    ProdutoManager() : nextId(1) {}

   
    void adicionarProduto(const char *nome, int quantidade, double precoCusto);
    bool adicionarEstoque(int id, int quantidade);
    bool eliminarProduto(int id);
    void listarProdutos() const;
    void relatorioEstoqueTotal() const;
    bool simularVenda(int id, int quantidade);
        void atualizarEstoqueAutomatico();
    };
