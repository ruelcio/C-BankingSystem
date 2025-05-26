#ifndef PERSISTENCIA_HPP
#define PERSISTENCIA_HPP

#include <vector>
#include <string>
#include "ContaBancaria.hpp"

class Persistencia {
public:
    // Salva todas as contas no arquivo
    void salvarContasEmArquivo(const std::vector<ContaBancaria>& contas, const std::string& nomeArquivo);
    
    // Carrega as contas do arquivo
    std::vector<ContaBancaria> carregarContas(const std::string& nomeArquivo);
};

#endif
