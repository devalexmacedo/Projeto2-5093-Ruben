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
    int getId();
    char* getNome();
    int getQuantidade();
    double getPrecoCusto();
    double getPrecoVenda();

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
