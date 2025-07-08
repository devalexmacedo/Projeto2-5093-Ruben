#pragma once
#include <string>
#include <iostream>     // Para std::cout, std::cin
#include <limits>       // Para std::numeric_limits
#include <sstream>      // Para std::stringstream
#include <algorithm>    // Para std::replace, std::equal
#include <cctype>       // Para std::isalpha, std::isdigit, std::tolower
#include <iomanip>      // Para std::fixed, std::setprecision

using namespace std;

// Declarações antecipadas das classes para evitar includes desnecessários
class Loja;
class Cliente;
class Produto;
class Venda;

/*
 * Configuração para leitura de teclado sem eco (para _getch)
 * Compatível com Windows (_getch) e Linux/macOS (implementação customizada)
 */
#ifdef _WIN32
#include <conio.h>
#define GETCH _getch
#else
#include <termios.h>
#include <unistd.h>
inline int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // Desativa modo canônico e eco
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#define GETCH getch
#endif

// --------------------------
// Funções utilitárias gerais
// --------------------------

/** Limpa o buffer de entrada para evitar problemas com entradas inválidas */
void limparBufferEntrada();

/** Trata erros de entrada padrão e limpa o buffer */
void tratarErroEntrada();

/** Obtém um valor inteiro do usuário com tratamento de erros */
int obterInt(const string& prompt);

/** Obtém um valor inteiro positivo do usuário com tratamento de erros */
int obterIntPositivo(const string& prompt);

/** Obtém um valor float do usuário com tratamento de erros */
float obterFloat(const string& prompt);

/** Obtém uma string do usuário (com espaços) */
string obterString(const string& prompt);

// Função auxiliar para formatar números com 2 casas decimais
string formatarDecimal(float valor);

/** Pausa a execução e espera por entrada do usuário */
void pausar();

/** Limpa a tela do console (implementação dependente do sistema) */
void limparTela();

// --------------------------------------------------
// Funções para obter entrada validada do usuário 
// (com loops de repetição até entrada válida)
// --------------------------------------------------

/** Obtém um nome válido do usuário com repetição até ser válido */
string obterNomeValido(const string& prompt);

/** Obtém um telefone válido do usuário com repetição até ser válido */
string obterTelefoneValido(const string& prompt);

/** Obtém uma morada válida do usuário com repetição até ser válida */
string obterMoradaValida(const string& prompt);

/** Obtém uma cidade válida do usuário com repetição até ser válida */
string obterCidadeValida(const string& prompt);

// --------------------------
// Funções auxiliares
// --------------------------

/** Compara duas strings ignorando diferenças de maiúsculas/minúsculas */
bool compararStringsIgnorarCase(const string& s1, const string& s2);

// --------------------------
// Funções de Menu
// --------------------------

/** Exibe e gerencia o menu de vendas */
void menuVendas(Loja& loja);

/** Exibe e gerencia o menu de clientes */
void menuClientes(Loja& loja);

/** Exibe e gerencia o menu de produtos */
void menuProdutos(Loja& loja);

/** Exibe e gerencia o menu de relatórios */
void menuRelatorios(Loja& loja);

