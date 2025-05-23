#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h> // Para getch()

#define MAX_USUARIO 50
#define MAX_SENHA 50
#define MAX_CLIENTES 100
#define MAX_NOME 100

typedef struct {
    char nomeResponsavel[MAX_NOME];
    char nomeEmpresa[MAX_NOME];
    char cnpj[20];
    char cidade[100];
    char estado[3]; // Ex: "SP"
    char cep[10];   // Ex: "12345-678"
    float residuosMensais[12];
    float custoMensal[12];
} Cliente;

Cliente clientes[MAX_CLIENTES];
int totalClientes = 0;

// Função para criptografar/descriptografar usando XOR
void criptografar(char *str, char chave) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] ^= chave;
    }
}

// Função para entrada escondida de senha
void entradaSenha(char *senha) {
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r') { // '\r' é Enter
        if (ch == '\b') { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b"); // Apaga o último caractere
            }
        } else if (i < MAX_SENHA - 1) {
            senha[i++] = ch;
            printf("*");
        }
    }
    senha[i] = '\0';
}

// Função para salvar clientes em arquivo CSV
void salvarClientesCSV() {
    FILE *file = fopen("clientes.csv", "w");
    if (file == NULL) {
        printf("Erro ao salvar os dados dos clientes no formato CSV!\n");
        return;
    }
    fprintf(file, "NomeEmpresa,CNPJ,Cidade,Estado,CEP,ResiduosMensais,CustosMensais\n");
    for (int i = 0; i < totalClientes; i++) {
        fprintf(file, "%s,%s,%s,%s,%s",
                clientes[i].nomeEmpresa,
                clientes[i].cnpj,
                clientes[i].cidade,
                clientes[i].estado,
                clientes[i].cep);
        for (int j = 0; j < 12; j++) {
            fprintf(file, ",%.2f,%.2f",
                    clientes[i].residuosMensais[j],
                    clientes[i].custoMensal[j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Clientes salvos no formato CSV com sucesso!\n");
}

// Função para cadastrar cliente
void cadastrarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Limite maximo de clientes atingido!\n");
        return;
    }
    Cliente novoCliente;
    printf("Digite o nome do responsavel: ");
    fgets(novoCliente.nomeResponsavel, MAX_NOME, stdin);
    novoCliente.nomeResponsavel[strcspn(novoCliente.nomeResponsavel, "\n")] = '\0';

    printf("Digite o nome da empresa: ");
    fgets(novoCliente.nomeEmpresa, MAX_NOME, stdin);
    novoCliente.nomeEmpresa[strcspn(novoCliente.nomeEmpresa, "\n")] = '\0';

    printf("Digite o CNPJ: ");
    fgets(novoCliente.cnpj, 20, stdin);
    novoCliente.cnpj[strcspn(novoCliente.cnpj, "\n")] = '\0';

    printf("Digite a cidade: ");
    fgets(novoCliente.cidade, 100, stdin);
    novoCliente.cidade[strcspn(novoCliente.cidade, "\n")] = '\0';

    printf("Digite o estado: ");
    fgets(novoCliente.estado, 3, stdin);
    novoCliente.estado[strcspn(novoCliente.estado, "\n")] = '\0';

    printf("Digite o CEP: ");
    fgets(novoCliente.cep, 10, stdin);
    novoCliente.cep[strcspn(novoCliente.cep, "\n")] = '\0';

    for (int i = 0; i < 12; i++) {
        novoCliente.residuosMensais[i] = 0.0;
        novoCliente.custoMensal[i] = 0.0;
    }

    clientes[totalClientes++] = novoCliente;
    salvarClientesCSV();
    printf("Cliente cadastrado com sucesso!\n");
}

// Função para atualizar resíduos e custos
void atualizarResiduos() {
    char cnpj[20];
    printf("Digite o CNPJ do cliente: ");
    fgets(cnpj, 20, stdin);
    cnpj[strcspn(cnpj, "\n")] = '\0';

    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].cnpj, cnpj) == 0) {
            int mes;
            printf("Digite o mes (1-12): ");
            scanf("%d", &mes);
            getchar(); // Limpa o buffer
            if (mes < 1 || mes > 12) {
                printf("Mes invalido! Escolha entre 1 e 12.\n");
                return;
            }
            printf("Digite a quantidade de residuos tratados: ");
            scanf("%f", &clientes[i].residuosMensais[mes - 1]);
            getchar();
            printf("Digite o custo do mes: ");
            scanf("%f", &clientes[i].custoMensal[mes - 1]);
            getchar();
            salvarClientesCSV();
            printf("Dados atualizados com sucesso!\n");
            return;
        }
    }
    printf("Cliente com CNPJ %s nao encontrado!\n", cnpj);
}

// Função para gerar relatórios
void gerarRelatorio() {
    for (int i = 0; i < totalClientes; i++) {
        printf("Cliente: %s\n", clientes[i].nomeEmpresa);
        printf("Resíduos tratados e custos por mes:\n");
        for (int j = 0; j < 12; j++) {
            printf("Mês %d: Residuos %.2f, Custo R$%.2f\n",
                   j + 1, clientes[i].residuosMensais[j], clientes[i].custoMensal[j]);
        }
        printf("---------------------------------\n");
    }
}

// Menu principal
void menuPrincipal() {
    int opcao;
    do {
        printf("\n=== Seja Bem-Vindo, ao Sistema de Gerenciamento de Residuos e Gastos Mensais ===\n");
        printf("\n=== Menu Principal ===\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Atualizar Residuos\n");
        printf("3. Gerar Relatorio\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer
        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                atualizarResiduos();
                break;
            case 3:
                gerarRelatorio();
                break;
            case 4:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);
}

// Função principal
int main() {
    char usuarioPadrao[MAX_USUARIO] = "admin";
    char senhaPadrao[MAX_SENHA] = "1234";
    char usuario[MAX_USUARIO], senha[MAX_SENHA];
    char chaveCriptografia = 'X';

    criptografar(senhaPadrao, chaveCriptografia);

    printf("============= Gerenciamento de Residuos e Gastos Mensais ========== \n" );
    printf("=== Login do Sistema ===\n");
    printf("Usuario: ");
    fgets(usuario, MAX_USUARIO, stdin);
    usuario[strcspn(usuario, "\n")] = '\0';

    printf("Senha: ");
    entradaSenha(senha);
    criptografar(senha, chaveCriptografia);

    if (strcmp(usuario, usuarioPadrao) == 0 && strcmp(senha, senhaPadrao) == 0) {
        printf("\nLogin bem-sucedido!\n");
        menuPrincipal();
    } else {
        printf("\nUsuario ou senha incorretos!\n");
    }

    return 0;
}
