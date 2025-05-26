#ifndef CONTA_BANCARIA_HPP
#define CONTA_BANCARIA_HPP

#include <string>
#include <iostream>

class ContaBancaria {
private:
    int numeroConta;
    std::string nome;
    std::string bi;
    std::string nacionalidade;
    std::string nascimento;
    std::string iban;
    double saldo;

    void gerarIBAN();

public:
    ContaBancaria(int numero, const std::string& nome, const std::string& bi,
                 const std::string& nacionalidade, const std::string& nascimento);

    // Getters
    int getNumeroConta() const;
    std::string getNomeCompleto() const;
    std::string getNumeroBI() const;
    std::string getNacionalidade() const;
    std::string getDataNascimento() const;
    double getSaldo() const;
    std::string getIban() const;

    void setSaldo(double novoSaldo);
    void setIban(const std::string& novoIban);

    // Método para mostrar todos os dados da conta
    void mostrarDados() const;
};

#endif
