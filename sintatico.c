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

int tipo(token_type token){    
    if((strcmp(token.valor, "float") == 0) || (strcmp(token.valor, "char") == 0) || 
    (strcmp(token.tipo, "double") == 0) || (strcmp(token.tipo, "void") == 0) || (strcmp(token.tipo, "int") == 0)){
        return 1;
    } 
    return 0;        
}

void listaArg(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, &index);
    if (strcmp(token.valor, ",") == 0){
        listaArg(listaTokens, &index);
    } else if (tipo(token)){
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
    if (tipo(token))
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
    else if(tipo(token)) {
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

void expressaoOpcional(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
     if(strcmp(token.tipo,"identificador") == 0){
         voltarToken(&index);
         expressao(listaTokens, &index);
     }
     else voltarToken(&index);
}

void statementWhile(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor,"while") == 0){
        token = lerToken(listaTokens, &index);
        if(strcmp(token.valor,"(") == 0){
            expressao(listaTokens, &index);
            token = lerToken(listaTokens, &index);
            if(strcmp(token.valor,")") == 0){
                statement(listaTokens, &index);
            } 
            else deuPau(token, 14, listaTokens, &index);
        }
        else deuPau(token, 15, listaTokens, &index);
    }
    else deuPau(token, 16, listaTokens, &index);
}

void statementDoWhile(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor,"do") == 0){
        statementEscopo(listaTokens, &index);
        token = lerToken(listaTokens, &index);
        if(strcmp(token.valor,"while") == 0){
            token = lerToken(listaTokens, &index);
            if(strcmp(token.valor,"(") == 0){
                expressao(listaTokens, &index);
                token = lerToken(listaTokens, &index);
                if(!strcmp(token.valor,")") == 0){
                    deuPau(token, 17, listaTokens, &index);
                }
            }
            else deuPau(token, 18, listaTokens, &index);
        }
        else deuPau(token, 19, listaTokens, &index);
    }
    else deuPau(token, 20, listaTokens, &index);
}

void statementIf(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor,"if") == 0){
        token = lerToken(listaTokens, &index);
        if(strcmp(token.valor,"(") == 0){   
            expressao(listaTokens, &index);
            token = lerToken(listaTokens, &index);
            if(strcmp(token.valor,")") == 0){
                statement(listaTokens, &index);
                parteElse(listaTokens,&index);                
            } 
            else deuPau(token, 21, listaTokens, &index);
        }
        else deuPau(token, 21, listaTokens, &index);
    }
    else deuPau(token, 22, listaTokens, &index);
}

void parteElse(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor,"else") == 0){
        statement(listaTokens, &index);    
    }
    else voltarToken(&index);
}

void statementReturn(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor,";") == 0){
        voltarToken(&index);
        return;
    }
    if(strcmp(token.tipo,"identificador") == 0 || strcmp(token.tipo,"numero") == 0 || strcmp(token.tipo,"literal") == 0)
        return;

    deuPau(token, 23, listaTokens, &index);
}

void statementEscopo(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor,"{") == 0){
        listaStatement(listaTokens, &index);
        token = lerToken(listaTokens, &index);
            if(strcmp(token.valor,"}") == 0)
                return;
            else deuPau(token, 24, listaTokens, &index);    
    }
    else deuPau(token, 25, listaTokens, &index);
}

void listaStatement(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    statement(listaTokens, &index);
    listaStatementLinha(listaTokens, &index);
}

void listaStatementLinha(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor,"for") == 0 || strcmp(token.valor,"while") == 0 || strcmp(token.valor,"do") == 0 || tipo(token)
    || strcmp(token.valor,";") == 0 || strcmp(token.valor,"{") == 0 || strcmp(token.tipo,"identificador") == 0 ||
    strcmp(token.valor,"return") == 0 || strcmp(token.valor,"break") == 0 || strcmp(token.valor,"switch") == 0 ){
        voltarToken(&index);
        statement(listaTokens, &index);
        listaStatementLinha(listaTokens, &index);
        return;
    }
    voltarToken(&index);
}

void expressao(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.tipo,"identificador") == 0){
        expressao02(listaTokens, &index);
    }
    else if (comparacao(token) || strcmp(token.valor, "(") == 0 || strcmp(token.valor, "+") == 0 || 
    strcmp(token.valor, "-") == 0 || strcmp(token.valor, "\'") == 0 ||  strcmp(token.valor, "\"") == 0 || 
    strcmp(token.tipo, "identificador") == 0 || strcmp(token.tipo, "numero") == 0){
        voltarToken(&index);
        valorR(listaTokens, &index);
    }
    else deuPau(token, 25, listaTokens, &index);
}

void expressao02(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.tipo, "operador") == 0){
        expressao(listaTokens, &index);
        return;
    }
    deuPau(token, 26, listaTokens, &index);
}

void valorR(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(comparacao(token)){
        magnitude(listaTokens, &index);
        valorRlinha(listaTokens, &index);
        return;
    }
    if (strcmp(token.valor, "(") == 0 || strcmp(token.valor, "+") == 0 || 
    strcmp(token.valor, "-") == 0 || strcmp(token.valor, "\'") == 0 ||  strcmp(token.valor, "\"") == 0 || 
    strcmp(token.tipo, "identificador") == 0 || strcmp(token.tipo, "numero") == 0){
        voltarToken(&index);
        magnitude(listaTokens, &index);
        return;
    }
    deuPau(token, 27, listaTokens, &index); 
}

void valorRLinha(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(comparacao(token)){
        magnitude(listaTokens, &index);
        valorRlinha(listaTokens, &index);
        return;
    }
    voltarToken(&index);
}

int comparacao(token_type token){
    if (strcmp(token.valor, "==") == 0 || strcmp(token.valor, ">") == 0 || strcmp(token.valor, "<") == 0 || 
    strcmp(token.valor, "<=") == 0 || strcmp(token.valor, ">=") == 0 ||  strcmp(token.valor, "!=") == 0)
        return 1;
    return 0;    
}

void magnitude(token_type* listaTokens, int* index){
    termo(listaTokens, &index);
    magnitudeLinha(listaTokens, &index);

}

void termo(token_type* listaTokens, int* index){
    fator(listaTokens, &index);
    termoLinha(listaTokens, &index);
}

void magnitudeLinha(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor, "+") == 0 || strcmp(token.valor, "-") == 0){
        termo(listaTokens, &index);
        magnitudeLinha(listaTokens, &index);
        return;
    }
    voltarToken(*index);
}

void termoLinha(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor, "*") == 0 || strcmp(token.valor, "/") == 0 ){
        fator(listaTokens, &index);
        termoLinha(listaTokens, &index);
        return;
    } 
    voltarToken(&index);
}

void fator(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor, "(") == 0){
        expressao(listaTokens, &index);
        token = lerToken(listaTokens, &index);
        if(strcmp(token.valor, ")") == 0)
            return;
        else {
            deuPau(token, 28, listaTokens, &index); 
            return;       
        }   
    }
    
    if(strcmp(token.valor, "+") == 0 || strcmp(token.valor, "-") == 0){
        fator(listaTokens, &index);
        return;
    }

    if(strcmp(token.tipo, "identificador") == 0 || strcmp(token.tipo, "numero") == 0 || strcmp(token.valor, "\'") == 0 || strcmp(token.tipo, "\"") == 0){
        return;
    }
    
    deuPau(token, 29, listaTokens, &index); 
}

void switch01(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor, "switch") == 0){
        token = lerToken(listaTokens, &index);
        if(strcmp(token.valor, "(") == 0){
            switch02(listaTokens, &index);
            token = lerToken(listaTokens, &index);
            if(strcmp(token.valor, ")") == 0){
                token = lerToken(listaTokens, &index);
                if(strcmp(token.valor, "{") == 0){
                    listaCase(listaTokens, &index);
                      token = lerToken(listaTokens, &index);
                      if(strcmp(token.valor, "}") == 0)
                        return;
                      deuPau(token, 30, listaTokens, &index);         
                }
                deuPau(token, 31, listaTokens, &index); 
            }
            deuPau(token, 32, listaTokens, &index); 
            return;
        }
        deuPau(token, 33, listaTokens, &index); 
        return;
    }
    deuPau(token, 34, listaTokens, &index);
}

void switch02(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.tipo, "numero") == 0 || strcmp(token.tipo, "identificador") == 0 || strcmp(token.valor, "\"") == 0 || 
    strcmp(token.valor, "\'") == 0)
        return;

    deuPau(token, 35, listaTokens, &index);  
}

void listaCase(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor, "case") == 0){
        switch02(listaTokens, &index);
        token = lerToken(listaTokens, &index);
        if(strcmp(token.valor, ":") == 0){
            listaStatement(listaTokens, &index);
            listaCaseLinha(listaTokens, &index);
            return;
        }
        deuPau(token, 36, listaTokens, &index); 
        return;  
    }
    deuPau(token, 37, listaTokens, &index); 
    return;
}

void listaCaseLinha(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor, "case") == 0){
        switch02(listaTokens, &index);
        token = lerToken(listaTokens, &index);
        if(strcmp(token.valor, ":") == 0){
            listaStatement(listaTokens, &index);
            listaCaseLinha(listaTokens, &index);
            return;
        }
        deuPau(token, 36, listaTokens, &index); 
        return;  
    }
    else if(strcmp(token.valor, "default") == 0){
        token = lerToken(listaTokens, &index);
        if(strcmp(token.valor, ":") == 0){
            listaStatement(listaTokens, &index);
            return;
        }
        deuPau(token, 37, listaTokens, &index);
    }
    return;
}

void chamadaFuncao(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.tipo, "identificador") == 0){
        token = lerToken(listaTokens, &index);
        if(strcmp(token.valor, "(") == 0){
            listaArgChamadaFuncao(listaTokens, &index);
            token = lerToken(listaTokens, &index);
            if(strcmp(token.valor, ")") == 0){
                token = lerToken(listaTokens, &index);
                if(strcmp(token.valor, ";") == 0){
                    return;
                }
                deuPau(token, 38, listaTokens, &index);
                return;
            }
            deuPau(token, 39, listaTokens, &index);
            return;
        }
        deuPau(token, 40, listaTokens, &index);
        return;
    }
    deuPau(token, 41, listaTokens, &index);
        return;
}

void listaArgChamadaFuncao(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.tipo, "numero") == 0 || strcmp(token.tipo, "identificador") == 0 || strcmp(token.valor, "\"") == 0 || 
    strcmp(token.valor, "\'") == 0){
        voltarToken(&index);
        switch02(listaTokens, &index);
        listaArgChamadaFuncaoLinha(listaTokens, &index);
        return;
    }
}

void listaArgChamadaFuncaoLinha(token_type* listaTokens, int* index){
    token_type token = lerToken(listaTokens, &index);
    if(strcmp(token.valor, ",") == 0){
        switch02(listaTokens, &index);
        listaArgChamadaFuncaoLinha(listaTokens, &index);
        return;
    }
}



int main(int argc, char* argv[]){
    int tamanho = 0;
    FILE* arquivo = fopen(argv[1], "r");
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
    
   FILE* listtok = fopen("/home/lucas/Área de trabalho/TP - Compiladores/lexico_usar_esse/lexico-master/tokens.txt", "w");
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