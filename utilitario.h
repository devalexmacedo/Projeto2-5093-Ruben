#ifndef UTILITARIO_H
#define UTILITARIO_H

#include <string>

// Funções utilitárias
void limparBufferEntrada();
void tratarErroEntrada();
int obterInt(const std::string& prompt);
int obterIntPositivo(const std::string& prompt);
float obterFloat(const std::string& prompt);
std::string obterString(const std::string& prompt);
void pausar();
void limparTela();

// Para _getch no Windows
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
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#define GETCH getch
#endif

// Funções de Menu
class Loja;
void menuClientes(Loja& loja);
void menuProdutos(Loja& loja);
void menuVendas(Loja& loja);
void menuRelatorios(Loja& loja);

// Funções de Validação
bool validarNome(const std::string& nome);
bool validarTelefone(const std::string& telefone);
bool validarMorada(const std::string& morada);
bool validarCidade(const std::string& cidade);

#endif // UTILITARIO_H




bool compararStringsIgnorarCase(const std::string& s1, const std::string& s2);




// Funções para obter entrada válida com loops de validação
std::string obterNomeValido(const std::string& prompt);
std::string obterTelefoneValido(const std::string& prompt);
std::string obterMoradaValida(const std::string& prompt);
std::string obterCidadeValida(const std::string& prompt);


