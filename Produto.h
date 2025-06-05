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

    // Adiciona um novo produto
    // quantidade e precoCusto são os dados necessários para criar o produto.
    void adicionarProduto(const char *nome, int quantidade, double precoCusto) {
        // Cria um novo produto com o id atual e os dados passados.
        
        Produto novo(nextId, const_cast<char*>(nome), quantidade, precoCusto);
        novo.calcularPrecoVenda();  // Calcula o preço de venda com base no custo
        produtos.push_back(novo);
        cout << "Produto adicionado com sucesso! (ID: " << nextId << ")" << "\n";
        nextId++;
    }

    // Acrescenta estoque a um produto identificado pelo id
    bool adicionarEstoque(int id, int quantidade) {
        for (auto &produto : produtos) {
            if (produto.getId() == id) {
                produto.adicionarEstoque(quantidade);
                cout << "Estoque atualizado para o produto " << produto.getNome() << "\n";
                return true;
            }
        }
        cout << "Produto não encontrado." << "\n";
        return false;
    }

    // Elimina o produto com o id informado, removendo-o do vetor (sem deixar "buracos")
    bool eliminarProduto(int id) {
        for (auto it = produtos.begin(); it != produtos.end(); ++it) {
            if (it->getId() == id) {
                produtos.erase(it);
                cout << "Produto removido com sucesso." << "\n";
                return true;
            }
        }
        cout << "Produto não encontrado." << "\n";
        return false;
    }

    // Lista todos os produtos cadastrados com seus dados
    void listarProdutos() const {
        if (produtos.empty()) {
            cout << "Nenhum produto cadastrado." << "\n";
            return;
        }
        for (const auto &produto : produtos) {
            cout << "ID: " << produto.getId()
                 << " | Nome: " << produto.getNome()
                 << " | Quantidade: " << produto.getQuantidade()
                 << " | Preço de Custo: " << produto.getPrecoCusto()
                 << " | Preço de Venda: " << produto.getPrecoVenda() << "\n";
        }
    }

    // Gera um relatório do estoque total (soma das quantidades de todos os produtos)
    void relatorioEstoqueTotal() const {
        int total = 0;
        for (const auto &produto : produtos) {
            total += produto.getQuantidade();
        }
        cout << "Estoque total de produtos: " << total << "\n";
    }

    // Simula uma venda para o produto com id informado, removendo a quantidade do estoque
    bool simularVenda(int id, int quantidade) {
        for (auto &produto : produtos) {
            if (produto.getId() == id) {
                if (produto.temEstoqueSuficiente(quantidade)) {
                    produto.removerEstoque(quantidade);
                    cout << "Venda realizada para o produto: " << produto.getNome() << "\n";
                    return true;
                } else {
                    cout << "Estoque insuficiente para o produto: " << produto.getNome() << "\n";
                    return false;
                }
            }
        }
        cout << "Produto não encontrado." << "\n";
        return false;
    }

    // Atualiza automaticamente o estoque dos produtos: se a quantidade for menor que 5, adiciona 10 unidades
    void atualizarEstoqueAutomatico() {
        for (auto &produto : produtos) {
            if (produto.getQuantidade() < 5) {
                produto.adicionarEstoque(10);
                cout << "Estoque do produto " << produto.getNome()
                     << " atualizado automaticamente (adicionado 10 unidades)." << "\n";
            }
        }
    }
};

