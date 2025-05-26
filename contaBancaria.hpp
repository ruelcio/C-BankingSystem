#ifndef CONTABANCARIA_HPP
#define CONTABANCARIA_HPP

#include <string>
#include <iostream>

class ContaBancaria {
private:
    int numeroConta;
    std::string nomeCompleto;
    std::string numeroBI;
    std::string nacionalidade;
    std::string dataNascimento;
    double saldo;
    std::string iban;

public:
    ContaBancaria(int numeroConta, const std::string& nomeCompleto,
                  const std::string& numeroBI, const std::string& nacionalidade,
                  const std::string& dataNascimento);

    // Getters
    int getNumeroConta() const;
    std::string getNomeCompleto() const;
    std::string getNumeroBI() const;
    std::string getNacionalidade() const;
    std::string getDataNascimento() const;
    double getSaldo() const;
    std::string getIban() const;

    void setSaldo(double valor);
    void setIban(const std::string& novoIban);

    // Método para mostrar todos os dados da conta
    void mostrarDados() const;
};

#endif
