#pragma once

class Venda {
private:
    int numeroFatura;           // Número único da fatura
    int numeroCliente;          // ID do cliente que realizou a compra
    int linhas[100];            // Número de linha de cada item
    char produtos[100][50];     // Nome dos produtos
    int quantidades[100];       // Quantidade de cada produto
    double precosSemIVA[100];   // Preço sem IVA de cada produto
    double ivas[100];           // IVA de cada produto
    double totalComIVA;         // Total com IVA
    double valorEntregue;       // Valor pago pelo cliente
    double troco;               // Troco a devolver
    char data[20];              // Data da venda
    int numItens;               // Número de itens na venda

public:
    // Construtor padrão
    Venda();-

    // Construtor com parâmetros básicos
    Venda(int numeroFatura, int numeroCliente, const char* data);

    // Métodos de acesso (getters)
    int getNumeroFatura() const;
    int getNumeroCliente() const;
    int getNumItens() const;
    double getTotalComIVA() const;
    const char* getData() const;

    // Métodos de modificação (setters)
    void setNumeroFatura(int numeroFatura);
    void setNumeroCliente(int numeroCliente);
    void setData(const char* data);

    // Métodos adicionais
    void adicionarItem(int linha, const char* nomeProduto, int quantidade, double precoSemIVA);
    void calcularTotal();
    void processarPagamento(double valorEntregue);
    void imprimirTalao() const;

    // Métodos para acesso aos itens
    int getLinha(int indice) const;
    const char* getNomeProduto(int indice) const;
    int getQuantidade(int indice) const;
    double getPrecoSemIVA(int indice) const;
    double getIVA(int indice) const;
    double getValorEntregue() const;
    double getTroco() const;
};