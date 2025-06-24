#define _CRT_SECURE_NO_WARNINGS
#include "Venda.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

// Construtor padrão
Venda::Venda() {
    numeroFatura = 0;
    numeroCliente = 0;
    totalSemIVA = 0.0;
    totalIVA = 0.0;
    totalComIVA = 0.0;
    valorEntregue = 0.0;
    troco = 0.0;
    
    // Obter data e hora atual
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", timeinfo);
    data = buffer;
}

// Construtor com parâmetros básicos
Venda::Venda(int numeroFatura, int numeroCliente) {
    this->numeroFatura = numeroFatura;
    this->numeroCliente = numeroCliente;
    totalSemIVA = 0.0;
    totalIVA = 0.0;
    totalComIVA = 0.0;
    valorEntregue = 0.0;
    troco = 0.0;
    
    // Obter data e hora atual
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", timeinfo);
    data = buffer;
}

// Métodos de acesso (getters)
int Venda::getNumeroFatura() const {
    return numeroFatura;
}

int Venda::getNumeroCliente() const {
    return numeroCliente;
}

int Venda::getNumItens() const {
    return itens.size();
}

float Venda::getTotalSemIVA() const {
    return totalSemIVA;
}

float Venda::getTotalIVA() const {
    return totalIVA;
}

float Venda::getTotalComIVA() const {
    return totalComIVA;
}

float Venda::getValorEntregue() const {
    return valorEntregue;
}

float Venda::getTroco() const {
    return troco;
}

std::string Venda::getData() const {
    return data;
}

// Métodos de modificação (setters)
void Venda::setNumeroFatura(int numeroFatura) {
    this->numeroFatura = numeroFatura;
}

void Venda::setNumeroCliente(int numeroCliente) {
    this->numeroCliente = numeroCliente;
}

void Venda::setData(const std::string& data) {
    this->data = data;
}

// Métodos adicionais
void Venda::adicionarItem(int idProduto, const std::string& nomeProduto, int quantidade, float precoCusto) {
    // Calcular preços
    float precoSemIVA = precoCusto * 1.3; // Preço de venda é custo + 30%
    float iva = precoSemIVA * 0.23; // IVA de 23%
    float precoUnitario = precoSemIVA + iva;
    float total = precoUnitario * quantidade;
    
    // Criar item de venda
    ItemVenda item;
    item.idProduto = idProduto;
    item.nomeProduto = nomeProduto;
    item.quantidade = quantidade;
    item.precoUnitario = precoUnitario;
    item.precoSemIVA = precoSemIVA;
    item.iva = iva;
    item.total = total;
    
    // Adicionar à lista de itens
    itens.push_back(item);
    
    // Recalcular totais
    calcularTotal();
}

void Venda::calcularTotal() {
    totalSemIVA = 0.0;
    totalIVA = 0.0;
    totalComIVA = 0.0;
    
    for (const auto& item : itens) {
        totalSemIVA += item.precoSemIVA * item.quantidade;
        totalIVA += item.iva * item.quantidade;
        totalComIVA += item.total;
    }
}

void Venda::processarPagamento(float valorEntregue) {
    this->valorEntregue = valorEntregue;
    this->troco = valorEntregue - totalComIVA;
}

void Venda::imprimirTalao() const {
    // Limpar a tela para garantir fundo branco
    system("cls");
    
    // Imprimir o talão com fundo branco e letra preta
    std::cout << "======= TALÃO DE COMPRAS =======\n";
    std::cout << "Fatura N: " << numeroFatura << "\n";
    std::cout << "Data: " << data << "\n";
    std::cout << "Cliente N: " << numeroCliente << "\n\n";
    std::cout << "----- Detalhes dos Produtos -----\n";
    
    for (const auto& item : itens) {
        std::cout << "Produto: " << item.nomeProduto << "\n";
        std::cout << "Quantidade: " << item.quantidade << "\n";
        std::cout << "Preço Unitário: " << std::fixed << std::setprecision(2) << item.precoUnitario << " euros\n";
        std::cout << "Preço s/IVA: " << std::fixed << std::setprecision(2) << item.precoSemIVA << " euros\n";
        std::cout << "IVA (23%): " << std::fixed << std::setprecision(2) << item.iva << " euros\n";
        std::cout << "---------------------------------\n";
    }
    
    std::cout << "Subtotal s/IVA: " << std::fixed << std::setprecision(2) << totalSemIVA << " euros\n";
    std::cout << "Total IVA: " << std::fixed << std::setprecision(2) << totalIVA << " euros\n";
    std::cout << "Total c/IVA: " << std::fixed << std::setprecision(2) << totalComIVA << " euros\n";
    std::cout << "Valor Pago: " << std::fixed << std::setprecision(2) << valorEntregue << " euros\n";
    std::cout << "Troco: " << std::fixed << std::setprecision(2) << troco << " euros\n";
    std::cout << "=====================================\n";
}

// Método para verificar se a venda foi sorteada como grátis (25% de chance)
bool Venda::verificarVendaGratis() const {
    // Gera um número aleatório entre 0 e 3
    // Se for 0 (25% de chance), a venda é grátis
    return (rand() % 4) == 0;
}
