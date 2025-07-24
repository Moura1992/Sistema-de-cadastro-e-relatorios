# Sistema de Gerenciamento de Resíduos e Custos Mensais

Este projeto é um sistema simples em linguagem C para gerenciamento de clientes, controle de resíduos tratados e custos mensais. Ele permite o cadastro de empresas, atualização de dados mensais e geração de relatórios, com autenticação de acesso.

## 📋 Funcionalidades

- Login com usuário e senha (criptografados com XOR)
- Cadastro de clientes com dados como:
  - Nome do responsável
  - Nome da empresa
  - CNPJ, cidade, estado e CEP
- Atualização mensal de:
  - Quantidade de resíduos tratados
  - Custo mensal
- Geração de relatórios com os dados de todos os clientes
- Exportação dos dados para um arquivo `clientes.csv`

## 🛠️ Estrutura do Código

- `Cliente`: estrutura que armazena os dados de cada empresa
- `criptografar`: função para criptografar/descriptografar senhas
- `entradaSenha`: entrada de senha com ocultação dos caracteres
- `cadastrarCliente`: coleta e armazena dados de um novo cliente
- `atualizarResiduos`: atualiza resíduos e custos de um cliente por mês
- `gerarRelatorio`: exibe os dados de todos os clientes
- `salvarClientesCSV`: salva os dados em formato CSV
- `menuPrincipal`: interface de navegação do sistema

## ▶️ Como Compilar

Use um compilador C como `gcc`:

```bash
gcc -o sistema sistema.c
./sistema

