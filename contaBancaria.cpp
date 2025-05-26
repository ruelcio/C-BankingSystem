#include "ContaBancaria.hpp"
#include <iomanip>
#include <sstream>

// Construtor
ContaBancaria::ContaBancaria(int numeroConta, const std::string& nomeCompleto,
                             const std::string& numeroBI, const std::string& nacionalidade,
                             const std::string& dataNascimento)
    : numeroConta(numeroConta), nomeCompleto(nomeCompleto), numeroBI(numeroBI),
      nacionalidade(nacionalidade), dataNascimento(dataNascimento), saldo(0.0)
{
    // Gerar IBAN simples
    std::ostringstream oss;
    oss << "AO" << std::setw(10) << std::setfill('0') << numeroConta;
    iban = oss.str();
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
    std::cout << "Conta: " << numeroConta << "\n"
              << "Nome: " << nomeCompleto << "\n"
              << "BI: " << numeroBI << "\n"
              << "Nacionalidade: " << nacionalidade << "\n"
              << "Nascimento: " << dataNascimento << "\n"
              << "IBAN: " << iban << "\n"
              << "Saldo: Kz " << std::fixed << std::setprecision(2) << saldo << "\n";
}
