#define _CRT_SECURE_NO_WARNINGS
#include "Venda.h"
#include <iostream>   // Para cout, cin
#include <iomanip>    // Para formatação de saída
#include <ctime>      // Para manipulação de data/hora
#include <string>     // Para uso de strings
#include <sstream>    // Para stringstream
#include <algorithm>  // Para max()

using namespace std;

// Constantes para configuração
const float MARGEM_LUCRO = 0.3f;   // Margem de 30% sobre o custo
const float TAXA_IVA = 0.23f;      // IVA de 23%

// Função auxiliar para calcular o comprimento visível de uma string,
// útil para alinhamento correto em consoles que usam UTF-8.
int getVisibleLength(const string& str) {
    int length = 0;
    for (char c : str) {
        // Conta bytes que iniciam um caractere UTF-8. Simplificação para alinhamento.
        if ((c & 0xC0) != 0x80) { // Se não for um byte de continuação (0x80-0xBF)
            length++;
        }
    }
    return length;
}

// Função auxiliar para formatar strings com largura fixa e alinhamento.
// Usada para construir o talão de forma organizada.
string formatarLinha(const string& conteudo, int largura, ios_base::fmtflags alinhamento, char preenchimento = ' ') {
    stringstream ss;
    ss << setfill(preenchimento);

    int conteudo_len = getVisibleLength(conteudo); // Comprimento real para alinhamento.
    int espacos_a_preencher = largura - conteudo_len;

    if (alinhamento == ios::left) {
        ss << left << setw(largura) << conteudo;
    }
    else if (alinhamento == ios::right) {
        ss << right << setw(largura) << conteudo;
    }
    else { // Centralizar
        int espacos_antes = espacos_a_preencher / 2;
        int espacos_depois = espacos_a_preencher - espacos_antes;
        ss << string(max(0, espacos_antes), preenchimento) << conteudo << string(max(0, espacos_depois), preenchimento);
    }
    return ss.str();
}

// Construtor padrão: inicializa membros e define a data/hora atual.
Venda::Venda() {
    numeroFatura = 0;
    numeroCliente = 0;
    totalSemIVA = 0.0f;
    totalIVA = 0.0f;
    totalComIVA = 0.0f;
    valorEntregue = 0.0f;
    troco = 0.0f;

    // Obtém e formata a data e hora atual.
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", timeinfo);
    data = buffer;
}

// Construtor com parâmetros: inicializa fatura, cliente e data/hora.
Venda::Venda(int numeroFatura, int numeroCliente) {
    this->numeroFatura = numeroFatura;
    this->numeroCliente = numeroCliente;
    totalSemIVA = 0.0f;
    totalIVA = 0.0f;
    totalComIVA = 0.0f;
    valorEntregue = 0.0f;
    troco = 0.0f;

    // Obtém e formata a data e hora atual.
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", timeinfo);
    data = buffer;
}

// Getters para acessar os atributos da venda.
int Venda::getNumeroFatura() const { return numeroFatura; }
int Venda::getNumeroCliente() const { return numeroCliente; }
int Venda::getNumItens() const { return static_cast<int>(itens.size()); }
size_t Venda::getNumItens_sizet() const { return itens.size(); } // Versão para size_t.
float Venda::getTotalSemIVA() const { return totalSemIVA; }
float Venda::getTotalIVA() const { return totalIVA; }
float Venda::getTotalComIVA() const { return totalComIVA; }
float Venda::getValorEntregue() const { return valorEntregue; }
float Venda::getTroco() const { return troco; }
string Venda::getData() const { return data; }

// Setters para modificar os atributos da venda.
void Venda::setNumeroFatura(int numeroFatura) { this->numeroFatura = numeroFatura; }
void Venda::setNumeroCliente(int numeroCliente) { this->numeroCliente = numeroCliente; }
void Venda::setData(const string& data) { this->data = data; }

// Adiciona um item à lista de itens da venda e recalcula os totais.
void Venda::adicionarItem(int idProduto, const string& nomeProduto, int quantidade, float precoCusto) {

    if (quantidade <= 0 || precoCusto <= 0) {
        cout << "ERRO: Quantidade ou preço inválidos!\n";
        return; // Sai sem adicionar o item
    }
    // Cálculo do preço (custo + 30% margem)
    float precoSemIVA = precoCusto * (1 + MARGEM_LUCRO);
    // Calcula IVA (23% sobre o preço com margem)
    float iva = precoSemIVA * TAXA_IVA;
    // Preço final (com margem + IVA)
    float precoUnitario = precoSemIVA + iva;
    //Valor total (Margem + IVA)
    float total = precoUnitario * quantidade;

        ItemVenda item; // Cria e preenche a estrutura ItemVenda.
    item.idProduto = idProduto;
    item.nomeProduto = nomeProduto;
    item.quantidade = quantidade;
    item.precoUnitario = precoUnitario;
    item.precoSemIVA = precoSemIVA;
    item.iva = iva;
    item.total = total;

    itens.push_back(item); // Adiciona o item ao vetor.
    calcularTotal(); // Recalcula os totais da venda.
}

// Recalcula os totais (sem IVA, IVA, com IVA) da venda somando todos os itens.
void Venda::calcularTotal() {
    totalSemIVA = 0.0f;
    totalIVA = 0.0f;
    totalComIVA = 0.0f;

    for (const auto& item : itens) { // Itera sobre todos os itens da venda.
        totalSemIVA += item.precoSemIVA * item.quantidade;
        totalIVA += item.iva * item.quantidade;
        totalComIVA += item.total;
    }
}

// Processa o pagamento, registrando o valor entregue e calculando o troco.
void Venda::processarPagamento(float valorEntregue) {
    this->valorEntregue = valorEntregue;
    this->troco = max(0.0f, valorEntregue - totalComIVA); // Garante que o troco não seja negativo.
}

// Exibe um resumo da venda (checkout) e pede confirmação ao usuário.
// Retorna true se a compra for confirmada, false se for cancelada.
bool Venda::exibirCheckout() const {
    if (itens.empty()) {
        cout << "🛒 Carrinho vazio! Adicione itens primeiro.\n";
        return false;
    }

    system("cls"); // Limpa a tela para o checkout.

    cout << "=========== Checkout ===========\n";
    for (const auto& item : itens) { // Lista cada item com seus detalhes.
        cout << "Produto: " << item.nomeProduto << "\n";
        cout << "Quantidade: " << item.quantidade << "\n";
        cout << "Preco Unitario: " << fixed << setprecision(2) << item.precoUnitario << " euros\n";
        cout << "Preco s/IVA: " << fixed << setprecision(2) << item.precoSemIVA << " euros\n";
        cout << "IVA (23%): " << fixed << setprecision(2) << item.iva << " euros\n";
        cout << "---------------------------------\n";
    }

    // Exibe os totais da venda.
    cout << "Subtotal s/IVA: " << fixed << setprecision(2) << totalSemIVA << " euros\n";
    cout << "Total IVA: " << fixed << setprecision(2) << totalIVA << " euros\n";
    cout << "Total c/IVA: " << fixed << setprecision(2) << totalComIVA << " euros\n\n";

    string input;
    char confirmacao;

    // Loop para obter uma confirmação válida (S/N).
    do {
        cout << "Confirmar compra (s - Sim) ou Desistir da venda (n - Nao)? ";
        getline(cin, input);
        if (!input.empty()) {
            confirmacao = input[0];
        }
        else {
            confirmacao = '\0'; // Entrada vazia.
        }
        if (confirmacao != 's' && confirmacao != 'n' && confirmacao != 'S' && confirmacao != 'N') {
            cout << "Opcao invalida! Digite apenas s (Sim) ou n (Nao).\n";
        }
    } while (confirmacao != 's' && confirmacao != 'n' && confirmacao != 'S' && confirmacao != 'N');

    return (confirmacao == 's' || confirmacao == 'S'); // Retorna a decisão do usuário.
}
// Imprime um talão formatado da venda, simulando um recibo de loja.
void Venda::imprimirTalao() const {
    system("cls"); // Limpa a tela.

    // Função auxiliar local para formatação decimal
    auto formatarDecimal = [](float valor) {
        stringstream ss;
        ss << fixed << setprecision(2) << valor;
        return ss.str();
        };

    // Códigos ANSI para cores no console (texto preto, fundo branco).
    const string fundoBrancoTextoPreto = "\033[30;47m";
    const string reset = "\033[0m"; // Reseta as cores.

    const int largura = 70; // Largura fixa do talão.

    // Desenha o cabeçalho do talão com informações da loja.
    cout << fundoBrancoTextoPreto; // Aplica cores.
    cout << "+" << string(largura - 2, '-') << "+\n";
    cout << "|" << formatarLinha("LOJA DE INFORMATICA", largura - 2, ios::internal) << "|\n";
    cout << "|" << formatarLinha("Rua da Tecnologia, 123", largura - 2, ios::internal) << "|\n";
    cout << "|" << formatarLinha("Tel: 123-456-789", largura - 2, ios::internal) << "|\n";
    cout << "|" << formatarLinha("NIF: 123456789", largura - 2, ios::internal) << "|\n";
    cout << "|" << formatarLinha("", largura - 2, ios::left) << "|\n";
    cout << "+" << string(largura - 2, '=') << "+\n";
    cout << "|" << formatarLinha("TALAO DE COMPRA", largura - 2, ios::internal) << "|\n";
    cout << "+" << string(largura - 2, '=') << "+\n";

    // Exibe informações da fatura, data e cliente.
    cout << "|" << formatarLinha("Fatura No: " + to_string(numeroFatura), largura - 2, ios::left) << "|\n";
    cout << "|" << formatarLinha("Data: " + data, largura - 2, ios::left) << "|\n";
    cout << "|" << formatarLinha("Cliente No: " + to_string(numeroCliente), largura - 2, ios::left) << "|\n";

    // Cabeçalho da tabela de itens.
    cout << "+" << string(largura - 2, '=') << "+\n";
    cout << "|" << formatarLinha("No  PRODUTO                          QTD   PRECO    TOTAL", largura - 2, ios::left) << "|\n";
    cout << "+" << string(largura - 2, '=') << "+\n";

    // Lista cada item da venda.
    for (size_t i = 0; i < itens.size(); i++) {
        const auto& item = itens[i];
        stringstream ss_item;
        string nomeTruncado = item.nomeProduto;
        if (getVisibleLength(nomeTruncado) > 27) { // Trunca nomes longos.
            nomeTruncado = nomeTruncado.substr(0, 27) + "...";
        }
        ss_item << setw(2) << (i + 1) << ". "
            << left << setw(30) << nomeTruncado
            << right << setw(6) << item.quantidade
            << right << setw(8) << fixed << setprecision(2) << item.precoUnitario << "EUR"
            << right << setw(8) << fixed << setprecision(2) << item.total << "EUR";

        cout << "|" << formatarLinha(ss_item.str(), largura - 2, ios::left) << "|\n";

        if (i < itens.size() - 1) { // Separador entre itens.
            cout << "|" << string(largura - 2, '*') << "|\n";
        }
    }

    // Exibe os totais e informações de pagamento.
    cout << "+" << string(largura - 2, '=') << "+\n";
    // Aqui, os valores são impressos diretamente com cout, que respeita fixed e setprecision.
    // Se fossem concatenados com to_string(), a precisão poderia ser perdida.
    cout << "|" << formatarLinha("Subtotal s/IVA: " + formatarDecimal(totalSemIVA) + "EUR", largura - 2, ios::right) << "|\n";
    cout << "|" << formatarLinha("IVA (23%): " + formatarDecimal(totalIVA) + "EUR", largura - 2, ios::right) << "|\n";
    cout << "+" << string(largura - 2, '=') << "+\n";
    cout << "|" << formatarLinha("TOTAL: " + formatarDecimal(totalComIVA) + "EUR", largura - 2, ios::right) << "|\n";
    cout << "+" << string(largura - 2, '=') << "+\n";
    cout << "|" << formatarLinha("", largura - 2, ios::left) << "|\n";
    cout << "|" << formatarLinha("Valor Pago: " + formatarDecimal(valorEntregue) + "EUR", largura - 2, ios::right) << "|\n";
    cout << "|" << formatarLinha("Troco: " + formatarDecimal(troco) + "EUR", largura - 2, ios::right) << "|\n";

    // Mensagens finais.
    cout << "+" << string(largura - 2, '=') << "+\n";
    cout << "|" << formatarLinha("", largura - 2, ios::left) << "|\n";
    cout << "|" << formatarLinha("OBRIGADO PELA SUA COMPRA!", largura - 2, ios::internal) << "|\n";
    cout << "|" << formatarLinha("VOLTE SEMPRE!", largura - 2, ios::internal) << "|\n";
    cout << "|" << formatarLinha("", largura - 2, ios::left) << "|\n";
    cout << "+" << string(largura - 2, '-') << "+" << reset << "                                                                                              " << "\n"; // Reset final.

    cout << "\n";
    system("pause"); // Pausa a execução para o usuário ver o talão.
}

// Verifica se a venda é "grátis" com base em uma chance aleatória (1 em 4).
bool Venda::verificarVendaGratis() const {
    return (rand() % 4) == 0; // 25% de chance.
}

// Retorna um ponteiro constante para um item específico da venda pelo índice.
const ItemVenda* Venda::getItem(int index) const {
    if (index >= 0 && index < static_cast<int>(itens.size())) {
        return &itens[index];
    }
    return nullptr; // Retorna nullptr se o índice for inválido.
}

// Sobrecarga de getItem para aceitar size_t como índice.
const ItemVenda* Venda::getItem(size_t index) const {
    if (index < itens.size()) {
        return &itens[index];
    }
    return nullptr; // Retorna nullptr se o índice for inválido.
}
