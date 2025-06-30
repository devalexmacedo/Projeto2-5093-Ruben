#define _CRT_SECURE_NO_WARNINGS
#include "Cliente.h"
#include <iostream>

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
    if (nome.empty()) { // Verifica se o nome não é vazio
        std::cout << "Nome não pode ser vazio. Atribuindo 'Cliente Desconhecido'." << std::endl;
        this->nome = "Cliente Desconhecido";
        return;
    }
    this->nome = nome;
}

void Cliente::setTelefone(const std::string& telefone) {
    if (telefone.empty()) { // Verifica se o telefone não é vazio
        std::cout << "Telefone não pode ser vazio. Atribuindo 'Telefone Desconhecido'." << std::endl;
        this->telefone = "Telefone Desconhecido";
        return;
    }
    this->telefone = telefone;
}

void Cliente::setMorada(const std::string& morada) {
    if (morada.empty()) { // Verifica se a morada não é vazia
        std::cout << "Morada não pode ser vazia. Atribuindo 'Morada Desconhecida'." << std::endl;
        this->morada = "Morada Desconhecida";
        return;
    }
    this->morada = morada;
}
