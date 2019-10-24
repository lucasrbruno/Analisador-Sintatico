#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_STRINGS 256
#define NUM_LEXEMAS_RESERVADAS 26
#define NUM_LEXEMAS_SEPARADORES 13
#define NUM_LEXEMAS_OP_ARITMETICOS 12
#define NUM_LEXEMAS_OP_LOGICOS 10
#define MAX_TOKENS 12000

typedef struct tok{
    char tipo[MAX_STRINGS];
    char valor[MAX_STRINGS];
    int linha;
    int coluna;
} token_type;

token_type* lerArquivo(FILE *arquivo, int tamanho);
token_type lerToken(token_type* listaTokens, int *index);
void listaDiretivas(token_type* listaTokens, int *index);
void sintatico(token_type* listaTokens, int *index, int tamanho);
void funcao(token_type* listaTokens, int *index);
int tipo(token_type* listaTokens, int *index);
void listaArg(token_type* listaTokens, int *index);
void arg(token_type* listaTokens, int *index);
void declaracao(token_type* listaTokens, int *index);
void listaIdentificadores(token_type* listaTokens, int *index);
void statement(token_type* listaTokens, int *index);
void statementFor(token_type* listaTokens, int *index);
void expressaoOpcional(token_type* listaTokens, int *index);
void statementWhile(token_type* listaTokens, int *index);
void statementDoWhile(token_type* listaTokens, int *index);
void parteElse(token_type* listaTokens, int *index);
void statementReturn(token_type* listaTokens, int *index);
void statementEscopo(token_type* listaTokens, int *index);
void listaStatement(token_type* listaTokens, int *index);
void listaStatementLinha(token_type* listaTokens, int *index);
void expressao(token_type* listaTokens, int *index);
void expressao02(token_type* listaTokens, int *index);
void valorR(token_type* listaTokens, int *index);
void valorRlinha(token_type* listaTokens, int *index);
void comparacao(token_type* listaTokens, int *index);
void magnitude(token_type* listaTokens, int *index);
void termo(token_type* listaTokens, int *index);
void termoLinha(token_type* listaTokens, int *index);
void fator(token_type* listaTokens, int *index);
void aritmetica(token_type* listaTokens, int *index);
void aritmeticaOperadorDuplicado(token_type* listaTokens, int *index);
void aritmeticaOperadorIgualComposto(token_type* listaTokens, int *index);
void switch01(token_type* listaTokens, int *index);
void fecha_chaves(token_type* listaTokens, int *index);
void switch02(token_type* listaTokens, int *index);
void listaCase(token_type* listaTokens, int *index);
void listaCaseLinha(token_type* listaTokens, int *index);
void chamadaFuncao(token_type* listaTokens, int *index);
void listaArgChamadaFuncao(token_type* listaTokens, int *index);
void listaArgChamadaFuncaoLinha(token_type* listaTokens, int *index);
void deuPau(token_type token, int erro_numero, token_type* listaTokens, int *index);
void voltarToken(int *index);
void statementIf(token_type* listaTokens, int *index);