#include "contaBancaria.hpp"
#include <iostream>
#include <iomanip>

// Construtor
ContaBancaria::ContaBancaria(int numero, const std::string& nome, const std::string& bi,
                           const std::string& nacionalidade, const std::string& nascimento)
    : numeroConta(numero), nome(nome), bi(bi), nacionalidade(nacionalidade),
      nascimento(nascimento), saldo(0.0) {
    gerarIBAN();
}

void ContaBancaria::gerarIBAN() {
    std::ostringstream oss;
    oss << "AO06" << "1000" << std::setw(16) << std::setfill('0') << numeroConta;
    iban = oss.str();
}

void ContaBancaria::setSaldo(double novoSaldo) {
    saldo = novoSaldo;
}

void ContaBancaria::setIban(const std::string& novoIban) {
    iban = novoIban;
}

int ContaBancaria::getNumeroConta() const {
    return numeroConta;
}

std::string ContaBancaria::getNomeCompleto() const {
    return nome;
}

std::string ContaBancaria::getNumeroBI() const {
    return bi;
}

std::string ContaBancaria::getNacionalidade() const {
    return nacionalidade;
}

std::string ContaBancaria::getDataNascimento() const {
    return nascimento;
}

std::string ContaBancaria::getIban() const {
    return iban;
}

double ContaBancaria::getSaldo() const {
    return saldo;
}

// Método para mostrar todos os dados
void ContaBancaria::mostrarDados() const {
    std::cout << "Numero da Conta: " << numeroConta << std::endl;
    std::cout << "Nome: " << nome << std::endl;
    std::cout << "BI: " << bi << std::endl;
    std::cout << "Nacionalidade: " << nacionalidade << std::endl;
    std::cout << "Data de Nascimento: " << nascimento << std::endl;
    std::cout << "IBAN: " << iban << std::endl;
    std::cout << "Saldo: Kz " << std::fixed << std::setprecision(2) << saldo << std::endl;
}
