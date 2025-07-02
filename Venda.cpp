#define _CRT_SECURE_NO_WARNINGS
#include "Venda.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

// Construtor padrão da classe Venda
Venda::Venda() {
    numeroFatura = 0;
    numeroCliente = 0;
    totalSemIVA = 0.0f;
    totalIVA = 0.0f;
    totalComIVA = 0.0f;
    valorEntregue = 0.0f;
    troco = 0.0f;

    // Obtém a data e hora atual do sistema
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", timeinfo);
    data = buffer;
}

// Construtor da classe Venda com parâmetros
Venda::Venda(int numeroFatura, int numeroCliente) {
    this->numeroFatura = numeroFatura;
    this->numeroCliente = numeroCliente;
    totalSemIVA = 0.0f;
    totalIVA = 0.0f;
    totalComIVA = 0.0f;
    valorEntregue = 0.0f;
    troco = 0.0f;

    // Obtém a data e hora atual do sistema
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", timeinfo);
    data = buffer;
}

// Retorna o número da fatura
int Venda::getNumeroFatura() const {
    return numeroFatura;
}

// Retorna o ID do cliente
int Venda::getNumeroCliente() const {
    return numeroCliente;
}

// Retorna o número de itens na venda
int Venda::getNumItens() const {
    return static_cast<int>(itens.size());
}

// Versão alternativa para compatibilidade com size_t
size_t Venda::getNumItens_sizet() const {
    return itens.size();
}

// Retorna o total sem IVA
float Venda::getTotalSemIVA() const {
    return totalSemIVA;
}

// Retorna o total de IVA
float Venda::getTotalIVA() const {
    return totalIVA;
}

// Retorna o total com IVA
float Venda::getTotalComIVA() const {
    return totalComIVA;
}

// Retorna o valor entregue pelo cliente
float Venda::getValorEntregue() const {
    return valorEntregue;
}

// Retorna o troco a ser devolvido
float Venda::getTroco() const {
    return troco;
}

// Retorna a data da venda
string Venda::getData() const {
    return data;
}

// Define o número da fatura
void Venda::setNumeroFatura(int numeroFatura) {
    this->numeroFatura = numeroFatura;
}

// Define o ID do cliente
void Venda::setNumeroCliente(int numeroCliente) {
    this->numeroCliente = numeroCliente;
}

// Define a data da venda
void Venda::setData(const string& data) {
    this->data = data;
}

// Adiciona um item à venda e recalcula os totais
void Venda::adicionarItem(int idProduto, const string& nomeProduto, int quantidade, float precoCusto) {
    // Calcula o preço de venda com margem de 30%
    float precoSemIVA = precoCusto * 1.3f;
    // Calcula o IVA de 23%
    float iva = precoSemIVA * 0.23f;
    float precoUnitario = precoSemIVA + iva;
    float total = precoUnitario * quantidade;

    ItemVenda item;
    item.idProduto = idProduto;
    item.nomeProduto = nomeProduto;
    item.quantidade = quantidade;
    item.precoUnitario = precoUnitario;
    item.precoSemIVA = precoSemIVA;
    item.iva = iva;
    item.total = total;

    itens.push_back(item);
    calcularTotal();
}

// Recalcula os totais da venda
void Venda::calcularTotal() {
    totalSemIVA = 0.0f;
    totalIVA = 0.0f;
    totalComIVA = 0.0f;

    for (const auto& item : itens) {
        totalSemIVA += item.precoSemIVA * item.quantidade;
        totalIVA += item.iva * item.quantidade;
        totalComIVA += item.total;
    }
}

// Processa o pagamento e calcula o troco
void Venda::processarPagamento(float valorEntregue) {
    this->valorEntregue = valorEntregue;
    this->troco = valorEntregue - totalComIVA;
}

// Exibe o checkout e pede confirmação do cliente
bool Venda::exibirCheckout() const {
    if (itens.empty()) {
        cout << "Não há itens na venda para checkout.\n";
        return false;
    }

    system("cls");

    cout << "=========== Checkout ===========\n";

    for (const auto& item : itens) {
        cout << "Produto: " << item.nomeProduto << "\n";
        cout << "Quantidade: " << item.quantidade << "\n";
        cout << "Preço Unitário: " << fixed << setprecision(2) << item.precoUnitario << " euros\n";
        cout << "Preço s/IVA: " << fixed << setprecision(2) << item.precoSemIVA << " euros\n";
        cout << "IVA (23%): " << fixed << setprecision(2) << item.iva << " euros\n";
        cout << "---------------------------------\n";
    }

    cout << "Subtotal s/IVA: " << fixed << setprecision(2) << totalSemIVA << " euros\n";
    cout << "Total IVA: " << fixed << setprecision(2) << totalIVA << " euros\n";
    cout << "Total c/IVA: " << fixed << setprecision(2) << totalComIVA << " euros\n\n";

    string input;
    char confirmacao;

    do {
        cout << "Confirmar compra (s - Sim) ou Desistir da venda (n - Não)? ";
        getline(cin, input);
        if (!input.empty()) {
            confirmacao = input[0];
        } else {
            confirmacao = '\0';
        }
        if (confirmacao != 's' && confirmacao != 'n' && confirmacao != 'S' && confirmacao != 'N') {
            cout << "Opção inválida! Digite apenas s (Sim) ou n (Não).\n";
        }
    } while (confirmacao != 's' && confirmacao != 'n' && confirmacao != 'S' && confirmacao != 'N');

    return (confirmacao == 's' || confirmacao == 'S');
}

// Imprime o talão da venda com aparência de talão de mercado
void Venda::imprimirTalao() const {
    // Limpa a tela
    system("cls");
    
    // Obtém o handle da console de saída padrão
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Define a cor do texto para preto (0) e o fundo para branco (15)
    SetConsoleTextAttribute(hConsole, 0 | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    
    // Cria o talão com fundo branco completo (50 caracteres de largura)
    string linha(50, ' ');
    string separador(50, '-');
    
    cout << linha << "\n";
    cout << "                LOJA DE INFORMÁTICA               " << "\n";
    cout << "             Rua da Tecnologia, 123              " << "\n";
    cout << "              Tel: 123-456-789                   " << "\n";
    cout << "                NIF: 123456789                   " << "\n";
    cout << linha << "\n";
    cout << separador << "\n";
    cout << "              TALÃO DE COMPRA                    " << "\n";
    cout << separador << "\n";
    cout << " Fatura Nº: " << left << setw(32) << numeroFatura << " " << "\n";
    cout << " Data: " << left << setw(37) << data << " " << "\n";
    cout << " Cliente Nº: " << left << setw(30) << numeroCliente << " " << "\n";
    cout << separador << "\n";
    cout << " PRODUTO                   QTD   PREÇO    TOTAL  " << "\n";
    cout << separador << "\n";
    
    // Lista os produtos de forma organizada com separadores
    for (size_t i = 0; i < itens.size(); i++) {
        const auto& item = itens[i];
        string nomeTruncado = item.nomeProduto.substr(0, 20);
        cout << " " << left << setw(20) << nomeTruncado
             << right << setw(6) << item.quantidade
             << right << setw(8) << fixed << setprecision(2) << item.precoUnitario << "€"
             << right << setw(8) << fixed << setprecision(2) << item.total << "€"
             << "      " << "\n";
        
        // Adiciona separador entre itens (exceto no último)
        if (i < itens.size() - 1) {
            string separadorItem(50, '*');
            cout << separadorItem << "\n";
        }
    }
    
    cout << separador << "\n";
    cout << " Subtotal s/IVA: " << right << setw(25) << fixed << setprecision(2) << totalSemIVA << "€ " << "\n";
    cout << " IVA (23%): " << right << setw(30) << fixed << setprecision(2) << totalIVA << "€ " << "\n";
    cout << separador << "\n";
    cout << " TOTAL: " << right << setw(34) << fixed << setprecision(2) << totalComIVA << "€ " << "\n";
    cout << separador << "\n";
    cout << "                                                  " << "\n";
    cout << " Valor Pago: " << right << setw(29) << fixed << setprecision(2) << valorEntregue << "€ " << "\n";
    cout << " Troco: " << right << setw(34) << fixed << setprecision(2) << troco << "€ " << "\n";
    cout << separador << "\n";
    cout << "                                                  " << "\n";
    cout << "            OBRIGADO PELA SUA COMPRA!            " << "\n";
    cout << "               VOLTE SEMPRE!                     " << "\n";
    cout << "                                                  " << "\n";
    cout << linha << "\n";
    
    // Preenche o resto da tela com fundo branco (aproximadamente 15 linhas extras)
    for (int i = 0; i < 15; i++) {
        cout << linha << "\n";
    }
    
    // Restaura as cores padrão do console
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
    cout << "\n";
}

// Verifica se a venda foi sorteada como grátis (25% de chance)
bool Venda::verificarVendaGratis() const {
    return (rand() % 4) == 0;
}

// Retorna um ponteiro para um item específico da venda
const ItemVenda* Venda::getItem(int index) const {
    if (index >= 0 && index < static_cast<int>(itens.size())) {
        return &itens[index];
    }
    return nullptr;
}

// Sobrecarga para compatibilidade com size_t
const ItemVenda* Venda::getItem(size_t index) const {
    if (index < itens.size()) {
        return &itens[index];
    }
    return nullptr;
}

