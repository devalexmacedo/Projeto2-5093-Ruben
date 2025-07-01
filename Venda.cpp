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
    if (valorEntregue < totalComIVA) {
        std::cout << "Valor entregue é menor que o total com IVA. Pagamento não processado." << std::endl;
        this->valorEntregue = 0.0;
        this->troco = 0.0;
        return;
    }
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

// Função auxiliar para centralizar texto dentro de uma largura específica
void printCentered(const std::string& text, int width) {
    if (width <= text.length()) {
        cout << text << "\n";
        return;
    }
    int padding = width - text.length();
    int padLeft = padding / 2;
    int padRight = padding - padLeft;
    cout << string(padLeft, ' ') << text << string(padRight, ' ') << "\n";
}


// Imprime o talão da venda com aparência de talão de mercado
void Venda::imprimirTalao() const {
    system("cls"); // Limpa a tela

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Define a cor do texto para preto (0) e o fundo para branco (15)
    SetConsoleTextAttribute(hConsole, 0 | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

    // Definir uma largura consistente para o talão (50 caracteres), com base nas suas imagens
    const int talaoWidth = 50;
    string emptyWhiteLine = string(talaoWidth, ' '); // Linha de espaços com fundo branco
    string separatorLine = string(talaoWidth, '-'); // Linha de traços
    string starSeparatorLine = string(talaoWidth, '*'); // Linha de asteriscos

    // Cabeçalho da loja
    cout << starSeparatorLine << "\n"; // Linha de asteriscos
    printCentered("LOJA DE INFORMÁTICA", talaoWidth);
    printCentered("Rua da Tecnologia, 123", talaoWidth);
    printCentered("Tel: 123-456-789", talaoWidth);
    printCentered("NIF: 123456789", talaoWidth);
    cout << starSeparatorLine << "\n"; // Linha de asteriscos

    // Título do Talão
    cout << emptyWhiteLine << "\n"; // Linha vazia com fundo branco
    printCentered("TALÃO DE COMPRA", talaoWidth);
    cout << emptyWhiteLine << "\n"; // Linha vazia com fundo branco
    cout << separatorLine << "\n"; // Linha de traços

    // Informações da fatura
    // Garante que o texto + valor preencham a largura total
    // Ex: "Fatura Nº: " (11 caracteres)
    cout << left << " Fatura Nº: " << setw(talaoWidth - string(" Fatura Nº: ").length()) << numeroFatura << "\n";
    cout << left << " Data: " << setw(talaoWidth - string(" Data: ").length()) << data << "\n";
    cout << left << " Cliente Nº: " << setw(talaoWidth - string(" Cliente Nº: ").length()) << numeroCliente << "\n";
    cout << separatorLine << "\n";

    // Cabeçalho da tabela de itens
    // As larguras somam 66: DESCRIÇÃO (40) + QTD (5) + PREÇO (9) + TOTAL (12) = 66
    const int descColWidth = 30;
    const int qtdColWidth = 5;
    const int precoColWidth = 9; // Ajustado para 9 para "XXX.YY€"
    const int totalColWidth = 12; // Ajustado para 12 para "XXXX.YY€"

    cout << left << setw(descColWidth) << " PRODUTO" // Use " PRODUTO" para combinar com suas imagens recentes
        << right << setw(qtdColWidth) << "QTD"
        << setw(precoColWidth) << "PREÇO"
        << setw(totalColWidth) << "TOTAL" << "\n";
    cout << separatorLine << "\n";

    // Lista os produtos de forma organizada
    for (const auto& item : itens) {
        string nomeTruncado = item.nomeProduto;
        // Trunca o nome do produto se for muito longo para caber na coluna, adicionando "..."
        if (nomeTruncado.length() > descColWidth - 3) {
            nomeTruncado = nomeTruncado.substr(0, descColWidth - 3) + "...";
        }

        cout << left << " " << setw(descColWidth - 1) << nomeTruncado // -1 para o espaço inicial
            << right << setw(qtdColWidth) << item.quantidade
            << setw(precoColWidth - 1) << fixed << setprecision(2) << item.precoUnitario << "€" // -1 para o '€'
            << setw(totalColWidth - 1) << fixed << setprecision(2) << item.total << "€" << "\n"; // -1 para o '€'
    }

    cout << separatorLine << "\n";

    // Totais (Subtotal, IVA, TOTAL, Valor Entregue, Troco)
    // Largura para a etiqueta dos totais (ex: "Subtotal s/IVA: ")
    // Largura para o valor e o símbolo "€" (ex: "1234.56€")
    const int labelColTotalWidth = 35;
    const int valueColTotalWidth = talaoWidth - labelColTotalWidth; // 50 - 35 = 15

    cout << left << setw(labelColTotalWidth) << " Subtotal s/IVA: " // Adicionado espaço inicial para alinhamento
        << right << setw(valueColTotalWidth - 1) << fixed << setprecision(2) << totalSemIVA << "€" << "\n";
    cout << left << setw(labelColTotalWidth) << " IVA (23%): " // Adicionado espaço inicial para alinhamento
        << right << setw(valueColTotalWidth - 1) << fixed << setprecision(2) << totalIVA << "€" << "\n";
    cout << starSeparatorLine << "\n"; // Usar separador de asteriscos para o total, como na imagem
    cout << left << setw(labelColTotalWidth) << " TOTAL: " // Adicionado espaço inicial para alinhamento
        << right << setw(valueColTotalWidth - 1) << fixed << setprecision(2) << totalComIVA << "€" << "\n";
    cout << starSeparatorLine << "\n"; // Usar separador de asteriscos

    // Valor Pago e Troco
    cout << left << setw(labelColTotalWidth) << " Valor Pago: " // Adicionado espaço inicial para alinhamento
        << right << setw(valueColTotalWidth - 1) << fixed << setprecision(2) << valorEntregue << "€" << "\n";
    cout << left << setw(labelColTotalWidth) << " Troco: " // Adicionado espaço inicial para alinhamento
        << right << setw(valueColTotalWidth - 1) << fixed << setprecision(2) << troco << "€" << "\n";
    cout << starSeparatorLine << "\n"; // Usar separador de asteriscos

    // Mensagens Finais
    cout << emptyWhiteLine << "\n"; // Linha vazia com fundo branco
    printCentered("OBRIGADO PELA SUA COMPRA!", talaoWidth);
    printCentered("VOLTE SEMPRE!", talaoWidth);
    cout << emptyWhiteLine << "\n"; // Uma linha vazia final para espaçamento controlado
    cout << starSeparatorLine; // Final com asteriscos

    // Restaura as cores padrão do console
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

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

