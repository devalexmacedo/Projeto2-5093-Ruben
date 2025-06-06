// Loja.h - Definição da classe Loja
#pragma once

#include "Produto.h"
#include "Cliente.h"
#include "Venda.h"

class Loja {
private:
    Produto produtos[100];      // Array de produtos
    Cliente clientes[100];      // Array de clientes
    Venda vendas[100];          // Array de vendas (limitado a 100)
    int numProdutos;            // Número atual de produtos
    int numClientes;            // Número atual de clientes
    int numVendas;              // Número atual de vendas
    int proximoIdProduto;       // Próximo ID para produto
    int proximoIdCliente;       // Próximo ID para cliente
    int proximoNumeroFatura;    // Próximo número de fatura

public:
    // Construtor
    Loja();

    // Métodos para gestão de produtos
    void adicionarProduto(char* nome, int quantidade, double precoCusto);
    void atualizarEstoque(int idProduto, int quantidade);
    void eliminarProduto(int idProduto);
    Produto* buscarProdutoPorId(int idProduto);
    Produto* buscarProdutoPorNome(char* nome);
    void listarProdutos();

    // Métodos para gestão de clientes
    void adicionarCliente(char* nome, char* telefone, char* morada);
    void eliminarCliente(int idCliente);
    void alterarNomeCliente(int idCliente, char* novoNome);
    Cliente* buscarClientePorId(int idCliente);
    void listarClientes();

    // Métodos para vendas
    void iniciarVenda(int idCliente);
    void adicionarItemVenda(int idProduto, int quantidade);
    bool checkoutVenda(); 
    void finalizarVenda(double valorEntregue);

    // Métodos para relatórios
    void relatorioEstoque();
    void relatorioVendasPorProduto(char* nomeProduto);
    void relatorioTotalVendas();

    // Método para inicializar a loja com dados predefinidos
    void inicializarDadosPredefinidos();
};


