#define _CRT_SECURE_NO_WARNINGS
#include "Cliente.h"
#include <cstring>

using namespace std;

// Construtor padrão
Cliente::Cliente() {
    id = 0;
    nome[0] = '\0';
    telefone[0] = '\0';
    morada[0] = '\0';
}

// Construtor com parâmetros (sem ID, que será gerenciado pela classe Loja)
Cliente::Cliente(char* nome, char* telefone, char* morada) {
    this->id = 0; // ID inicial 0, será definido pela classe Loja

    // Copiar nome com segurança
    strcpy(this->nome, nome);

    // Copiar telefone com segurança
    strcpy(this->telefone, telefone);

    // Copiar morada com segurança
    strcpy(this->morada, morada);
}

// Métodos de acesso (getters)
int Cliente::getId() {
    return id;
}

char* Cliente::getNome() {
    return nome;
}

char* Cliente::getTelefone() {
    return telefone;
}

char* Cliente::getMorada() {
    return morada;
}

// Métodos de modificação (setters)
void Cliente::setId(int id) {
    this->id = id;
}

void Cliente::setNome(char* nome) {
    strcpy(this->nome, nome);
}

void Cliente::setTelefone(char* telefone) {
    strcpy(this->telefone, telefone);
}

void Cliente::setMorada(char* morada) {
    strcpy(this->morada, morada);
}

