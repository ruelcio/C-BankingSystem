#include "ContaBancaria.hpp"
#include "cores.hpp"
#include <iostream>
#include <iomanip>

// Construtor
ContaBancaria::ContaBancaria(int numeroConta, const std::string& nomeCompleto,
                             const std::string& numeroBI, const std::string& nacionalidade,
                             const std::string& dataNascimento)
    : numeroConta(numeroConta), nomeCompleto(nomeCompleto), numeroBI(numeroBI),
      nacionalidade(nacionalidade), dataNascimento(dataNascimento), saldo(0.0)
{
    // Gerar IBAN simples
    iban = "AO" + std::string(10 - std::to_string(numeroConta).length(), '0') + std::to_string(numeroConta);
}

void ContaBancaria::setSaldo(double valor) {
    saldo = valor;
}

void ContaBancaria::setIban(const std::string& novoIban) {
    iban = novoIban;
}

int ContaBancaria::getNumeroConta() const { return numeroConta; }
std::string ContaBancaria::getNomeCompleto() const { return nomeCompleto; }
std::string ContaBancaria::getNumeroBI() const { return numeroBI; }
std::string ContaBancaria::getNacionalidade() const { return nacionalidade; }
std::string ContaBancaria::getDataNascimento() const { return dataNascimento; }
std::string ContaBancaria::getIban() const { return iban; }
double ContaBancaria::getSaldo() const { return saldo; }

// Método para mostrar todos os dados
void ContaBancaria::mostrarDados() const {
    setColor(11); // Ciano
    std::cout << "Conta: " << numeroConta << std::endl;
    setColor(14); // Amarelo
    std::cout << "Nome: " << nomeCompleto << std::endl;
    std::cout << "BI: " << numeroBI << std::endl;
    std::cout << "Nacionalidade: " << nacionalidade << std::endl;
    std::cout << "Nascimento: " << dataNascimento << std::endl;
    std::cout << "IBAN: " << iban << std::endl;
    setColor(10); // Verde
    std::cout << "Saldo: Kz " << std::fixed << std::setprecision(2) << saldo << std::endl;
    setColor(7); // Branco
}
