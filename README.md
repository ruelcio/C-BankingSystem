# Sistema Bancário - UmaBanking

Este é um sistema bancário simples desenvolvido em C++ que permite gerenciar contas bancárias com várias funcionalidades como abertura de conta, depósito, levantamento, transferências e pagamentos de serviços.

---

## Requisitos

- Compilador C++ (recomendado: `g++`)
- Sistema operacional compatível com terminal (Windows, Linux ou macOS)

---

## Como Compilar

Abra o terminal na pasta do projeto e execute:

```
g++ -o umaBanking main.cpp banco.cpp contaBancaria.cpp persistencia.cpp -Wall
```

---

## Como Executar

Após a compilação, execute o programa com:

```
./umaBanking
```

Ou no Windows:

```
.\umaBanking.exe
```

---

## Funcionalidades

### 1. Abrir Conta
- Solicita nome completo, número do BI, nacionalidade e data de nascimento
- Gera número de conta e IBAN automaticamente

### 2. Depositar
- Digite o número da conta
- Informe o valor do depósito
- Confirmação com novo saldo

### 3. Levantar
- Digite o número da conta
- Informe o valor a levantar
- Verifica saldo suficiente antes da operação
- Confirmação com novo saldo

### 4. Consultar Contas
- Lista todas as contas cadastradas
- Mostra detalhes completos de cada conta

### 5. Transferir
- Digite o número da sua conta e da conta destino
- Informe o valor da transferência
- Verifica saldo suficiente
- Atualiza e mostra os saldos de ambas as contas

### 6. Pagar Serviços
- Escolha um serviço para pagar: Água, Luz ou Internet
- Digite o valor a ser pago
- Verifica saldo suficiente
- Confirmação com novo saldo

---

## Estrutura do Código

- `main.cpp`: Arquivo principal com o menu e a lógica de interação
- `banco.hpp/.cpp`: Gerencia operações bancárias como depósito, levantamento e transferência
- `contaBancaria.hpp/.cpp`: Representa os dados e operações de uma conta bancária
- `persistencia.hpp/.cpp`: Lida com leitura e gravação de dados em arquivo

---

## Arquivo de Dados

- **contas.txt**: Armazena as contas em formato texto  
  - Cada conta ocupa uma linha  
  - Campos separados por ponto e vírgula (`;`)  
  - Formato dos campos:  
    `numero;nome;bi;nacionalidade;nascimento;iban;saldo`
