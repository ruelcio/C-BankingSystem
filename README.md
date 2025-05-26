# Sistema Bancário UmaBanking

Este é um sistema bancário simples desenvolvido em C++ que permite gerenciar contas bancárias com várias funcionalidades.

## Requisitos

- Compilador C++ (g++ recomendado)
- Sistema operacional Windows (para as cores do terminal)

## Como Compilar

1. Abra o terminal na pasta do projeto
2. Execute o comando:
```bash
g++ -o umaBanking main.cpp banco.cpp contaBancaria.cpp persistencia.cpp -Wall
```

## Como Executar

1. Após compilar, execute o programa:
```bash
./umaBanking
```

## Funcionalidades

1. **Abrir Conta**
   - Solicita nome completo
   - Número do BI
   - Nacionalidade
   - Data de nascimento
   - Gera número de conta e IBAN automaticamente

2. **Depositar**
   - Digite o número da conta
   - Informe o valor do depósito
   - Confirmação com novo saldo

3. **Levantar**
   - Digite o número da conta
   - Informe o valor do levantamento
   - Verifica saldo suficiente
   - Confirmação com novo saldo

4. **Consultar Contas**
   - Lista todas as contas cadastradas
   - Mostra detalhes completos de cada conta

5. **Transferir**
   - Digite sua conta
   - Digite a conta destino
   - Informe o valor
   - Verifica saldo suficiente
   - Confirmação com novos saldos

6. **Pagar Serviços**
   - Escolha o serviço (Água, Luz, Internet)
   - Digite o valor
   - Verifica saldo suficiente
   - Confirmação com novo saldo

## Estrutura do Código

- `main.cpp`: Arquivo principal com o menu e loop do programa
- `banco.hpp/cpp`: Classe que gerencia todas as operações bancárias
- `contaBancaria.hpp/cpp`: Classe que representa uma conta bancária
- `persistencia.hpp/cpp`: Classe que gerencia a leitura/escrita em arquivo
- `cores.hpp`: Funções para colorir a interface do terminal

## Arquivos de Dados

- `contas.txt`: Arquivo que armazena os dados das contas
  - Formato: número;nome;bi;nacionalidade;nascimento;iban;saldo
  - Cada conta em uma linha
  - Separador: ponto e vírgula (;) 