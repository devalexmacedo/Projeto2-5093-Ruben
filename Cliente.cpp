#include "Cliente.h"
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

// Construtor padrão
Cliente::Cliente() : id(0) {}

// Construtor com parâmetros
Cliente::Cliente(const string& nome, const string& telefone, const string& morada, const string& cidade)
    : nome(nome), telefone(telefone), morada(morada), cidade(cidade), id(0) {}

// Retorna o ID do cliente
int Cliente::getId() const {
    return id;
}

// Retorna o nome do cliente
string Cliente::getNome() const {
    return nome;
}

// Retorna o telefone do cliente
string Cliente::getTelefone() const {
    return telefone;
}

// Retorna a morada do cliente
string Cliente::getMorada() const {
    return morada;
}

// Retorna a cidade do cliente
string Cliente::getCidade() const {
    return cidade;
}

// Define o ID do cliente
void Cliente::setId(int newId) {
    id = newId;
}

// Define o nome do cliente
void Cliente::setNome(const string& newNome) {
    // Verifica se o nome é vazio ou contém apenas espaços em branco
    // Se for, atribui "Cliente Desconhecido"
    if (newNome.empty() || all_of(newNome.begin(), newNome.end(), [](unsigned char c){ return isspace(c); })) {
        cout << "Nome do cliente não pode ser vazio. Atribuindo 'Cliente Desconhecido'." << endl;
        nome = "Cliente Desconhecido";
    } else {
        // Se o nome for válido, atribui o novo nome
        cout << "Nome do cliente alterado para: " << newNome << endl;
    }
    nome = newNome;
}

// Define o telefone do cliente
void Cliente::setTelefone(const string& newTelefone) {
    if (newTelefone.empty() || all_of(newTelefone.begin(), newTelefone.end(), [](unsigned char c){ return isspace(c); })) {
        cout << "Telefone do cliente não pode ser vazio. Atribuindo 'Telefone Desconhecido'." << endl;
        telefone = "Telefone Desconhecido";
    } else {
        cout << "Telefone do cliente alterado para: " << newTelefone << endl;
    }
    telefone = newTelefone;
}

// Define a morada do cliente
void Cliente::setMorada(const string& newMorada) {
    if (newMorada.empty() || all_of(newMorada.begin(), newMorada.end(), [](unsigned char c){ return isspace(c); })) {
        cout << "Morada do cliente não pode ser vazia. Atribuindo 'Morada Desconhecida'." << endl;
        morada = "Morada Desconhecida";
    } else {
        cout << "Morada do cliente alterada para: " << newMorada << endl;
    }
    morada = newMorada;
}

// Define a cidade do cliente
void Cliente::setCidade(const string& newCidade) {
    if (newCidade.empty() || all_of(newCidade.begin(), newCidade.end(), [](unsigned char c){ return isspace(c); })) {
        cout << "Cidade do cliente não pode ser vazia. Atribuindo 'Cidade Desconhecida'." << endl;
        cidade = "Cidade Desconhecida";
    } else {
        cout << "Cidade do cliente alterada para: " << newCidade << endl;
    }
    cidade = newCidade;
}



