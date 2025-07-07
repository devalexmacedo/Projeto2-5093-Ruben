#define _CRT_SECURE_NO_WARNINGS
#include "Venda.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <windows.h>
#include <sstream>
#include <locale>
#include <codecvt>
#include <cwchar>

using namespace std;

// Função para calcular o comprimento visível de uma string, considerando caracteres multibyte (UTF-8)
// Esta versão tenta ser mais pragmática para caracteres comuns que causam problemas de alinhamento.
int getVisibleLength(const string& str) {
    int length = 0;
    for (char c : str) {
        // Caracteres ASCII ocupam 1 unidade de largura
        if ((c & 0x80) == 0) {
            length++;
        }
        else if ((c & 0xE0) == 0xC0) { // 2-byte UTF-8 character
            // Para caracteres como 'º' e '€', que são 2 ou 3 bytes em UTF-8 mas 1 caractere visual
            // Esta é uma simplificação. Em um ambiente de console Windows, eles geralmente ocupam 1 célula.
            // Se for um caractere de início de sequência multibyte, incrementa o comprimento.
            // Assumimos que a maioria dos caracteres multibyte comuns ocupam 1 célula visual.
            length++;
        }
        else if ((c & 0xF0) == 0xE0) { // 3-byte UTF-8 character
            length++;
        }
        else if ((c & 0xF8) == 0xF0) { // 4-byte UTF-8 character
            length++;
        }
    }
    return length;
}

// Função auxiliar genérica para formatar strings com largura fixa, alinhamento e caractere de preenchimento
string formatarLinha(const string& conteudo, int largura, ios_base::fmtflags alinhamento, char preenchimento = ' ') {
    stringstream ss;
    ss << setfill(preenchimento);

    int conteudo_len = getVisibleLength(conteudo);

    // Calcula os espaços a preencher com base no comprimento visível
    int espacos_a_preencher = largura - conteudo_len;

    if (alinhamento == ios::left) {
        ss << left << setw(largura) << conteudo;
    }
    else if (alinhamento == ios::right) {
        ss << right << setw(largura) << conteudo;
    }
    else { // ios::internal para centralizar
        int espacos_antes = espacos_a_preencher / 2;
        int espacos_depois = espacos_a_preencher - espacos_antes;
        ss << string(max(0, espacos_antes), preenchimento) << conteudo << string(max(0, espacos_depois), preenchimento);
    }
    return ss.str();
}

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
    this->troco = max(0.0f, valorEntregue - totalComIVA);
}

// Exibe o checkout e pede confirmação do cliente
bool Venda::exibirCheckout() const {
    if (itens.empty()) {
        cout << "Nao ha itens na venda para checkout.\n";
        return false;
    }

    system("cls");

    cout << "=========== Checkout ===========\n";

    for (const auto& item : itens) {
        cout << "Produto: " << item.nomeProduto << "\n";
        cout << "Quantidade: " << item.quantidade << "\n";
        cout << "Preco Unitario: " << fixed << setprecision(2) << item.precoUnitario << " euros\n";
        cout << "Preco s/IVA: " << fixed << setprecision(2) << item.precoSemIVA << " euros\n";
        cout << "IVA (23%): " << fixed << setprecision(2) << item.iva << " euros\n";
        cout << "---------------------------------\n";
    }

    cout << "Subtotal s/IVA: " << fixed << setprecision(2) << totalSemIVA << " euros\n";
    cout << "Total IVA: " << fixed << setprecision(2) << totalIVA << " euros\n";
    cout << "Total c/IVA: " << fixed << setprecision(2) << totalComIVA << " euros\n\n";

    string input;
    char confirmacao;

    do {
        cout << "Confirmar compra (s - Sim) ou Desistir da venda (n - Nao)? ";
        getline(cin, input);
        if (!input.empty()) {
            confirmacao = input[0];
        }
        else {
            confirmacao = '\0';
        }
        if (confirmacao != 's' && confirmacao != 'n' && confirmacao != 'S' && confirmacao != 'N') {
            cout << "Opcao invalida! Digite apenas s (Sim) ou n (Nao).\n";
        }
    } while (confirmacao != 's' && confirmacao != 'n' && confirmacao != 'S' && confirmacao != 'N');

    return (confirmacao == 's' || confirmacao == 'S');
}

// Imprime o talao da venda com aparencia de talao de mercado
void Venda::imprimirTalao() const {
    // Limpa a tela
    system("cls");

    const string fundoBrancoTextoPreto = "\033[30;47m"; // Texto preto (30), fundo branco (47)
    const string reset = "\033[0m";

    const int largura = 70; // Largura fixa do talao

    string linhaTopo = "+" + string(largura - 2, '-') + "+";
    string linhaFundo = "+" + string(largura - 2, '=') + "+";

    // Cabeçalho com fundo branco
    cout << fundoBrancoTextoPreto;
    cout << linhaTopo << "\n";
    cout << "|" << formatarLinha("LOJA DE INFORMATICA", largura - 2, ios::internal) << "|\n";
    cout << "|" << formatarLinha("Rua da Tecnologia, 123", largura - 2, ios::internal) << "|\n";
    cout << "|" << formatarLinha("Tel: 123-456-789", largura - 2, ios::internal) << "|\n";
    cout << "|" << formatarLinha("NIF: 123456789", largura - 2, ios::internal) << "|\n";
    cout << "|" << formatarLinha("", largura - 2, ios::left) << "|\n";
    cout << linhaFundo << "\n";
    cout << "|" << formatarLinha("TALAO DE COMPRA", largura - 2, ios::internal) << "|\n";
    cout << linhaFundo << "\n";

    stringstream ss_fatura;
    ss_fatura << "Fatura No: " << numeroFatura;
    cout << "|" << formatarLinha(ss_fatura.str(), largura - 2, ios::left) << "|\n";

    stringstream ss_data;
    ss_data << "Data: " << data;
    cout << "|" << formatarLinha(ss_data.str(), largura - 2, ios::left) << "|\n";

    stringstream ss_cliente;
    ss_cliente << "Cliente No: " << numeroCliente;
    cout << "|" << formatarLinha(ss_cliente.str(), largura - 2, ios::left) << "|\n";

    cout << linhaFundo << "\n";
    cout << "|" << formatarLinha("No  PRODUTO                          QTD   PRECO    TOTAL", largura - 2, ios::left) << "|\n";
    cout << linhaFundo << "\n";

    for (size_t i = 0; i < itens.size(); i++) {
        const auto& item = itens[i];
        stringstream ss_item;
        string nomeTruncado = item.nomeProduto;
        if (getVisibleLength(nomeTruncado) > 27) {
            nomeTruncado = nomeTruncado.substr(0, 27) + "...";
        }
        ss_item << setw(2) << (i + 1) << ". "
            << left << setw(30) << nomeTruncado
            << right << setw(6) << item.quantidade
            << right << setw(8) << fixed << setprecision(2) << item.precoUnitario << "EUR"
            << right << setw(8) << fixed << setprecision(2) << item.total << "EUR";

        cout << "|" << formatarLinha(ss_item.str(), largura - 2, ios::left) << "|\n";

        if (i < itens.size() - 1) {
            cout << "|" << string(largura - 2, '*') << "|\n";
        }
    }

    cout << linhaFundo << "\n";

    stringstream ss_subtotal;
    ss_subtotal << "Subtotal s/IVA: " << fixed << setprecision(2) << totalSemIVA << "EUR";
    cout << "|" << formatarLinha(ss_subtotal.str(), largura - 2, ios::right) << "|\n";

    stringstream ss_iva;
    ss_iva << "IVA (23%): " << fixed << setprecision(2) << totalIVA << "EUR";
    cout << "|" << formatarLinha(ss_iva.str(), largura - 2, ios::right) << "|\n";

    cout << linhaFundo << "\n";

    stringstream ss_total;
    ss_total << "TOTAL: " << fixed << setprecision(2) << totalComIVA << "EUR";
    cout << "|" << formatarLinha(ss_total.str(), largura - 2, ios::right) << "|\n";

    cout << linhaFundo << "\n";
    cout << "|" << formatarLinha("", largura - 2, ios::left) << "|\n";

    stringstream ss_valor_pago;
    ss_valor_pago << "Valor Pago: " << fixed << setprecision(2) << valorEntregue << "EUR";
    cout << "|" << formatarLinha(ss_valor_pago.str(), largura - 2, ios::right) << "|\n";

    stringstream ss_troco;
    ss_troco << "Troco: " << fixed << setprecision(2) << troco << "EUR";
    cout << "|" << formatarLinha(ss_troco.str(), largura - 2, ios::right) << "|\n";

    cout << linhaFundo << "\n";
    cout << "|" << formatarLinha("", largura - 2, ios::left) << "|\n";
    cout << "|" << formatarLinha("OBRIGADO PELA SUA COMPRA!", largura - 2, ios::internal) << "|\n";
    cout << "|" << formatarLinha("VOLTE SEMPRE!", largura - 2, ios::internal) << "|\n";
    cout << "|" << formatarLinha("", largura - 2, ios::left) << "|\n";
    cout << linhaTopo << reset << "                                                                                              " << "\n"; // Reset final

    cout << "\n";
    system("pause");
}

// Verifica se a venda foi sorteada como gratis (25% de chance)
bool Venda::verificarVendaGratis() const {
    return (rand() % 4) == 0;
}

// Retorna um ponteiro para um item especifico da venda
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