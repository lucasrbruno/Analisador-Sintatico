#include "sintatico.h"



token_type* lerArquivo(FILE *arquivo, int tamanho){
    int i = 0;
    token_type* listaTokens = (token_type*) malloc (tamanho * sizeof (token_type));
    char palavra[MAX_STRINGS];
   
    while(!feof(arquivo)){
        fgets(palavra, MAX_STRINGS,arquivo);  
        if (palavra[strlen(palavra) - 1] == '\n')
            palavra[strlen(palavra) - 1] = '\0';
        printf("TIPO %s\n", palavra);
        token_type token;
        strcpy(token.tipo, palavra);
        fgets(palavra, MAX_STRINGS,arquivo);
        if (palavra[strlen(palavra) - 1] == '\n')
            palavra[strlen(palavra) - 1] = '\0';
        strcpy(token.valor, palavra);
        printf("Valor %s\n", token.valor);
        fgets(palavra, MAX_STRINGS,arquivo);
        if (palavra[strlen(palavra) - 1] == '\n')
            palavra[strlen(palavra) - 1] = '\0';
        token.linha = atoi(palavra);
        printf("LINHA %s\n", palavra);
        //printf("%s\n", palavra);
        fgets(palavra, MAX_STRINGS,arquivo);
        if (palavra[strlen(palavra) - 1] == '\n')
            palavra[strlen(palavra) - 1] = '\0';
        //printf("%s\n", palavra);
        token.coluna = atoi(palavra);
        printf("COLUNA %s\n", palavra);
        listaTokens[i++] = token;         
    }
   
   return listaTokens;
}


token_type lerToken(token_type* listaTokens, int *index){
    return listaTokens[*index++];
}

void voltarToken(int *index){
    *index--;
}