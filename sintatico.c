#include "sintatico.h"


void sintatico(token_type* listaTokens, int *index, int tamanho){
    while(*index < tamanho)
        funcao(listaTokens, &index);
}


void funcao(token_type* listaTokens, int *index){
    funcao(listaTokens, &index);
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.tipo, "identificador") == 0){
        token = lerToken(listaTokens, &index);
        if(strcmp(token.valor, "(") == 0){
            listaArg(listaTokens, &index);
            token = lerToken(listaTokens, &index);
            if(strcmp(token.valor, ")") == 0)
                statementEscopo(listaTokens, &index);                            
            else deuPau(token, 0, listaTokens, &index);    
        } else deuPau(token, 1, listaTokens, &index);
    } else deuPau(token, 2, listaTokens, &index);
}

int tipo(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, &index);
    
    if(!((strcmp(token.valor, "float") == 0) || (strcmp(token.valor, "char") == 0) || (strcmp(token.tipo, "double") == 0) (strcmp(token.tipo, "void") == 0) || (strcmp(token.tipo, "int") == 0))){
        deuPau(token, 3, listaTokens, &index);
        return 0;
    } 
    
    return 1;        
}

void listaArg(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, &index);
    if (strcmp(token.valor, ",") == 0){
        listaArg(listaTokens, &index);
    } else if (tipo(listaTokens, &index)){
        arg(listaTokens, &index);
    } else 
        voltarToken(&index);         
}

void arg(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, &index);
    if (!(strcmp(token.tipo,"identificador") == 0))
        deuPau(token, 4, listaTokens, &index);
}

void declaracao(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, &index);
    if (tipo(listaTokens, &index))
        listaIdentificadores(listaTokens, &index);
    else
        voltarToken(&index);
}

void listaIdentificadores(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, &index);
    if (!(strcmp(token.tipo,"identificador") == 0))
        deuPau(token, 5, listaTokens, &index);
    else{
        token = lerToken(listaTokens, &index);
        if (!(strcmp(token.tipo,",") == 0))
            voltarToken(&index);
        else
            listaIdentificadores(listaTokens, &index);
    }        
}

void statement(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, &index);
    if (strcmp(token.valor,"for") == 0){
        voltarToken(&index);
        statementFor(listaTokens, &index);
        return;
    }        
    else if (strcmp(token.valor,"while") == 0) {
        voltarToken(&index);
        statementWhile(listaTokens, &index);
        return;
    }    
    else if(tipo(listaTokens, &index)) {
        voltarToken(&index);
        declaracao(listaTokens, &index);
        return;
    }  
    else if (strcmp(token.valor,"if") == 0){
        voltarToken(&index);
        statementIf(listaTokens, &index);
        return;
    }
    else if (strcmp(token.valor,"{") == 0){
        voltarToken(&index);
        statementEscopo(listaTokens, &index);
        return;
    }
    else if(strcmp(token.tipo,"identificador") == 0){
        voltarToken(&index);
        expressao(listaTokens, &index);
        return;
    }
    else if(strcmp(token.valor,"do") == 0){
        voltarToken(&index);
        statementDoWhile(listaTokens, &index);
        return;
    }
    else if(strcmp(token.valor,"return") == 0){
        statementReturn(listaTokens, &index);
        token = lerToken(listaTokens, &index);
        if (!(strcmp(token.valor,";") == 0)){
            deuPau(token, 6, listaTokens, &index);
        }
        return;
    }
    else if(strcmp(token.valor,"break") == 0){
        token = lerToken(listaTokens, &index);
        if (!(strcmp(token.valor,";") == 0)){
            deuPau(token, 7, listaTokens, &index);
        }
        return;
    }
    else if(strcmp(token.valor,"switch") == 0){
        voltarToken(&index);
        switch01(listaTokens, &index);
        return;
    }
    else if (!(strcmp(token.valor,";") == 0)){
            deuPau(token, 8, listaTokens, &index);
            return;
        }   
}

void statementFor(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor,"for") == 0){
        token = lerToken(listaTokens, &index);
        if(strcmp(token.valor,"(") == 0){
            expressao(listaTokens, &index);
            token = lerToken(listaTokens, &index);
            if (strcmp(token.valor,";") == 0){
                expressaoOpcional(listaTokens, &index);
                token = lerToken(listaTokens, &index);
                if ((strcmp(token.valor,";") == 0)){
                    expressaoOpcional(listaTokens, &index);
                    token = lerToken(listaTokens, &index);
                    if(strcmp(token.valor,")") == 0){
                        statement(listaTokens, &index);
                    }
                    else deuPau(token, 9, listaTokens, &index);
                } 
                else deuPau(token, 10, listaTokens, &index);                
            } 
            else deuPau(token, 11, listaTokens, &index);
        }
        else deuPau(token, 12, listaTokens, &index);
    }
    else deuPau(token, 13, listaTokens, &index);
}



int main(){
    int tamanho = 0;
    FILE* arquivo = fopen("/home/lucasrezende/Área de trabalho/TP COMPILADORES/lexico-master/tokens.txt", "r");
    if (arquivo == NULL) 
    { 
        printf("Could not open file.\n"); 
        return 0; 
    } 
     for (char c = getc(arquivo); c != EOF; c = getc(arquivo)) 
        if (c == '\n') // Increment count if this character is newline 
            tamanho++; 

    tamanho /= 4;
    
    fseek(arquivo, 0, SEEK_SET);
    printf("%d\n", tamanho);
    token_type* tokens = lerArquivo(arquivo, tamanho);
    fclose(arquivo);
    
   FILE* listtok = fopen("token.txt", "w");
    for(int i = 0; i < tamanho; i++){
       /* printf("%s ", tokens[i].tipo);
        printf("%s ", tokens[i].valor);
        printf("%d", tokens[i].linha);
        printf("%d\n", tokens[i].coluna);*/
        fprintf(listtok, "%s\n%s\n%d\n%d\n", tokens[i].tipo, tokens[i].valor, tokens[i].linha, tokens[i].coluna);
    }

    fclose(listtok);

    return 0;
}