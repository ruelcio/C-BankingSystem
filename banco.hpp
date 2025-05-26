#ifndef BANCO_HPP
#define BANCO_HPP

#include <string>
#include <vector>
#include "ContaBancaria.hpp"
#include "persistencia.hpp"

class Banco {
private:
    std::string nomeArquivo;
    std::vector<ContaBancaria> contas;
    Persistencia persistencia;

public:
    Banco(const std::string& arquivo = "contas.txt");
    
    // Operações de conta
    void abrirConta();
    void listarContas() const;
    void depositar();
    void realizarLevantamento();
    void realizarTransferencia();
    void realizarPagamento();
    
    // Getters
    const std::vector<ContaBancaria>& getContas() const { return contas; }
    
    // Menu
    void exibirMenu() const;
};

#endif