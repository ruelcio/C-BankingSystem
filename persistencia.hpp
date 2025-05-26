#ifndef PERSISTENCIA_HPP
#define PERSISTENCIA_HPP

#include <vector>
#include "ContaBancaria.hpp"

// Salva todas as contas no arquivo
void salvarContasEmArquivo(const std::vector<ContaBancaria>& contas, const std::string& nomeArquivo);

// Carrega as contas do arquivo
void carregarContasDoArquivo(std::vector<ContaBancaria>& contas, const std::string& nomeArquivo);

void realizarTransferencia(std::vector <ContaBancaria>& contas, const std::string& nomeArquivo);

#endif
