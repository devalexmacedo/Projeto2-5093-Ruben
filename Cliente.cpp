#define _CRT_SECURE_NO_WARNINGS
#include "Cliente.h"

// Construtor padrão
Cliente::Cliente() {
    id = 0;
    nome = "";
    telefone = "";
    morada = "";
}

// Construtor com parâmetros (sem ID, que será gerenciado automaticamente)
Cliente::Cliente(const std::string& nome, const std::string& telefone, const std::string& morada) {
    this->id = 0; // ID inicial 0, será definido pela classe Loja
    this->nome = nome;
    this->telefone = telefone;
    this->morada = morada;
}

// Métodos de acesso (getters)
int Cliente::getId() const {
    return id;
}

std::string Cliente::getNome() const {
    return nome;
}

std::string Cliente::getTelefone() const {
    return telefone;
}

std::string Cliente::getMorada() const {
    return morada;
}

// Métodos de modificação (setters)
void Cliente::setId(int id) {
    this->id = id;
}

void Cliente::setNome(const std::string& nome) {
    this->nome = nome;
}

void Cliente::setTelefone(const std::string& telefone) {
    this->telefone = telefone;
}

void Cliente::setMorada(const std::string& morada) {
    this->morada = morada;
}
