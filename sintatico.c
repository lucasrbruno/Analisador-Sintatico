#include "sintatico.h"


void sintatico(token_type* listaTokens, int *index, int tamanho){
    while(*index < tamanho)
        funcao(listaTokens, *index);
}


void funcao(token_type* listaTokens, int *index){
    funcao(listaTokens, *index);
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.tipo, "identificador") == 0){
        token = lerToken(listaTokens, *index);
        if(strcmp(token.valor, "(") == 0){
            listaArg(listaTokens, *index);
            token = lerToken(listaTokens, *index);
            if(strcmp(token.valor, ")") == 0)
                statementEscopo(listaTokens, *index);                            
                return;
            deuPau(token, 0, listaTokens, *index);    
        } 
        deuPau(token, 1, listaTokens, *index);
    } 
    deuPau(token, 2, listaTokens, *index);
}

int tipo(token_type token){    
    if((strcmp(token.valor, "float") == 0) || (strcmp(token.valor, "char") == 0) || 
    (strcmp(token.valor, "double") == 0) || (strcmp(token.valor, "void") == 0) || (strcmp(token.valor, "int") == 0)){
        return 1;
    } 
    return 0;        
}

void listaArg(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if (strcmp(token.valor, ",") == 0){
        listaArg(listaTokens, *index);
    } else if (tipo(token)){
        arg(listaTokens, *index);
    } else 
        voltarToken(*index);         
}

void arg(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if (!(strcmp(token.tipo,"identificador") == 0))
        deuPau(token, 4, listaTokens, *index);
}

void declaracao(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if (tipo(token))
        listaIdentificadores(listaTokens, *index);
    else
        voltarToken(*index);
}

void listaIdentificadores(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if (!(strcmp(token.tipo,"identificador") == 0))
        deuPau(token, 5, listaTokens, *index);
    else{
        token = lerToken(listaTokens, *index);
        if (!(strcmp(token.valor,",") == 0))
            voltarToken(*index);
        else
            listaIdentificadores(listaTokens, *index);
    }        
}

void statement(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if (strcmp(token.valor,"for") == 0){
        voltarToken(*index);
        statementFor(listaTokens, *index);
        return;
    }        
    else if (strcmp(token.valor,"while") == 0) {
        voltarToken(*index);
        statementWhile(listaTokens, *index);
        return;
    }    
    else if(tipo(token)) {
        voltarToken(*index);
        declaracao(listaTokens, *index);
        return;
    }  
    else if (strcmp(token.valor,"if") == 0){
        voltarToken(*index);
        statementIf(listaTokens, *index);
        return;
    }
    else if (strcmp(token.valor,"{") == 0){
        voltarToken(*index);                            
        statementEscopo(listaTokens, *index);
        return;
    }
    else if(strcmp(token.tipo,"identificador") == 0){
        voltarToken(*index);
        expressao(listaTokens, *index);
        return;
    }
    else if(strcmp(token.valor,"do") == 0){
        voltarToken(*index);
        statementDoWhile(listaTokens, *index);
        return;
    }
    else if(strcmp(token.valor,"return") == 0){
        statementReturn(listaTokens, *index);
        token = lerToken(listaTokens, *index);
        if (!(strcmp(token.valor,";") == 0)){
            deuPau(token, 6, listaTokens, *index);
        }
        return;
    }
    else if(strcmp(token.valor,"break") == 0){
        token = lerToken(listaTokens, *index);
        if (!(strcmp(token.valor,";") == 0)){
            deuPau(token, 7, listaTokens, *index);
        }
        return;
    }
    else if(strcmp(token.valor,"switch") == 0){
        voltarToken(*index);
        switch01(listaTokens, *index);
        return;
    }
    else if (!(strcmp(token.valor,";") == 0)){
            deuPau(token, 8, listaTokens, *index);
            return;
        }   
}

void statementFor(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor,"for") == 0){
        token = lerToken(listaTokens, *index);
        if(strcmp(token.valor,"(") == 0){
            expressao(listaTokens, *index);
            token = lerToken(listaTokens, *index);
            if (strcmp(token.valor,";") == 0){
                expressaoOpcional(listaTokens, *index);
                token = lerToken(listaTokens, *index);
                if ((strcmp(token.valor,";") == 0)){
                    expressaoOpcional(listaTokens, *index);
                    token = lerToken(listaTokens, *index);
                    if(strcmp(token.valor,")") == 0){
                        statement(listaTokens, *index);
                    }
                    else deuPau(token, 9, listaTokens, *index);
                } 
                else deuPau(token, 10, listaTokens, *index);                
            } 
            else deuPau(token, 11, listaTokens, *index);
        }
        else deuPau(token, 12, listaTokens, *index);
    }
    else deuPau(token, 13, listaTokens, *index);
}

void expressaoOpcional(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
     if(strcmp(token.tipo,"identificador") == 0){
         voltarToken(*index);
         expressao(listaTokens, *index);
     }
     else voltarToken(*index);
}

void statementWhile(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor,"while") == 0){
        token = lerToken(listaTokens, *index);
        if(strcmp(token.valor,"(") == 0){
            expressao(listaTokens, *index);
            token = lerToken(listaTokens, *index);
            if(strcmp(token.valor,")") == 0){
                statement(listaTokens, *index);
            } 
            else deuPau(token, 14, listaTokens, *index);
        }
        else deuPau(token, 15, listaTokens, *index);
    }
    else deuPau(token, 16, listaTokens, *index);
}

void statementDoWhile(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor,"do") == 0){
        statementEscopo(listaTokens, *index);
        token = lerToken(listaTokens, *index);
        if(strcmp(token.valor,"while") == 0){
            token = lerToken(listaTokens, *index);
            if(strcmp(token.valor,"(") == 0){
                expressao(listaTokens, *index);
                token = lerToken(listaTokens, *index);
                if(!strcmp(token.valor,")") == 0){
                    deuPau(token, 17, listaTokens, *index);
                }
            }
            else deuPau(token, 18, listaTokens, *index);
        }
        else deuPau(token, 19, listaTokens, *index);
    }
    else deuPau(token, 20, listaTokens, *index);
}

void statementIf(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor,"if") == 0){
        token = lerToken(listaTokens, *index);
        if(strcmp(token.valor,"(") == 0){   
            expressao(listaTokens, *index);
            token = lerToken(listaTokens, *index);
            if(strcmp(token.valor,")") == 0){
                statement(listaTokens, *index);
                parteElse(listaTokens,*index);                
            } 
            else deuPau(token, 21, listaTokens, *index);
        }
        else deuPau(token, 3, listaTokens, *index);
    }
    else deuPau(token, 22, listaTokens, *index);
}

void parteElse(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor,"else") == 0){
        statement(listaTokens, *index);    
    }
    else voltarToken(*index);
}

void statementReturn(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor,";") == 0){
        voltarToken(*index);
        return;
    }
    if(strcmp(token.tipo,"identificador") == 0 || strcmp(token.tipo,"numero") == 0 || strcmp(token.tipo,"literal") == 0)
        return;

    deuPau(token, 23, listaTokens, *index);
}

void statementEscopo(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor,"{") == 0){
        listaStatement(listaTokens, *index);
        token = lerToken(listaTokens, *index);
            if(strcmp(token.valor,"}") == 0)
                return;
            else deuPau(token, 24, listaTokens, *index);    
    }
    else deuPau(token, 25, listaTokens, *index);
}

void listaStatement(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    statement(listaTokens, *index);
    listaStatementLinha(listaTokens, *index);
}

void listaStatementLinha(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor,"for") == 0 || strcmp(token.valor,"while") == 0 || strcmp(token.valor,"do") == 0 || tipo(token)
    || strcmp(token.valor,";") == 0 || strcmp(token.valor,"{") == 0 || strcmp(token.tipo,"identificador") == 0 ||
    strcmp(token.valor,"return") == 0 || strcmp(token.valor,"break") == 0 || strcmp(token.valor,"switch") == 0 ){
        voltarToken(*index);
        statement(listaTokens, *index);
        listaStatementLinha(listaTokens, *index);
        return;
    }
    voltarToken(*index);
}

void expressao(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.tipo,"identificador") == 0){
        expressao02(listaTokens, *index);
    }
    else if (comparacao(token) || strcmp(token.valor, "(") == 0 || strcmp(token.valor, "+") == 0 || 
    strcmp(token.valor, "-") == 0 || strcmp(token.valor, "\'") == 0 ||  strcmp(token.valor, "\"") == 0 || 
    strcmp(token.tipo, "identificador") == 0 || strcmp(token.tipo, "numero") == 0){
        voltarToken(*index);
        valorR(listaTokens, *index);
    }
    else deuPau(token, 26, listaTokens, *index);
}

void expressao02(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.tipo, "operador") == 0){
        expressao(listaTokens, *index);
        return;
    }
    deuPau(token, 27, listaTokens, *index);
}

void valorR(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(comparacao(token)){
        magnitude(listaTokens, *index);
        valorRlinha(listaTokens, *index);
        return;
    }
    if (strcmp(token.valor, "(") == 0 || strcmp(token.valor, "+") == 0 || 
    strcmp(token.valor, "-") == 0 || strcmp(token.valor, "\'") == 0 ||  strcmp(token.valor, "\"") == 0 || 
    strcmp(token.tipo, "identificador") == 0 || strcmp(token.tipo, "numero") == 0){
        voltarToken(*index);
        magnitude(listaTokens, *index);
        return;
    }
    deuPau(token, 28, listaTokens, *index); 
}

void valorRLinha(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(comparacao(token)){
        magnitude(listaTokens, *index);
        valorRlinha(listaTokens, *index);
        return;
    }
    voltarToken(*index);
}

int comparacao(token_type token){
    if (strcmp(token.valor, "==") == 0 || strcmp(token.valor, ">") == 0 || strcmp(token.valor, "<") == 0 || 
    strcmp(token.valor, "<=") == 0 || strcmp(token.valor, ">=") == 0 ||  strcmp(token.valor, "!=") == 0)
        return 1;
    return 0;    
}

void magnitude(token_type* listaTokens, int *index){
    termo(listaTokens, *index);
    magnitudeLinha(listaTokens, *index);

}

void termo(token_type* listaTokens, int *index){
    fator(listaTokens, *index);
    termoLinha(listaTokens, *index);
}

void magnitudeLinha(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor, "+") == 0 || strcmp(token.valor, "-") == 0){
        termo(listaTokens, *index);
        magnitudeLinha(listaTokens, *index);
        return;
    }
    voltarToken(*index);
}

void termoLinha(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor, "*") == 0 || strcmp(token.valor, "/") == 0 ){
        fator(listaTokens, *index);
        termoLinha(listaTokens, *index);
        return;
    } 
    voltarToken(*index);
}

void fator(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor, "(") == 0){
        expressao(listaTokens, *index);
        token = lerToken(listaTokens, *index);
        if(strcmp(token.valor, ")") == 0)
            return;
        else {
            deuPau(token, 29, listaTokens, *index); 
            return;       
        }   
    }
    
    if(strcmp(token.valor, "+") == 0 || strcmp(token.valor, "-") == 0){
        fator(listaTokens, *index);
        return;
    }

    if(strcmp(token.tipo, "identificador") == 0 || strcmp(token.tipo, "numero") == 0 || strcmp(token.valor, "\'") == 0 ||
     strcmp(token.valor, "\"") == 0){
        return;
    }
    
    deuPau(token, 30, listaTokens, *index); 
}

void switch01(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor, "switch") == 0){
        token = lerToken(listaTokens, *index);
        if(strcmp(token.valor, "(") == 0){
            switch02(listaTokens, *index);
            token = lerToken(listaTokens, *index);
            if(strcmp(token.valor, ")") == 0){
                token = lerToken(listaTokens, *index);
                if(strcmp(token.valor, "{") == 0){
                    listaCase(listaTokens, *index);
                      token = lerToken(listaTokens, *index);
                      if(strcmp(token.valor, "}") == 0)
                        return;
                      deuPau(token, 31, listaTokens, *index);         
                }
                deuPau(token, 32, listaTokens, *index); 
            }
            deuPau(token, 33, listaTokens, *index); 
            return;
        }
        deuPau(token, 34, listaTokens, *index); 
        return;
    }
    deuPau(token, 35, listaTokens, *index);
}

void switch02(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.tipo, "numero") == 0 || strcmp(token.tipo, "identificador") == 0 || strcmp(token.valor, "\"") == 0 || 
    strcmp(token.valor, "\'") == 0)
        return;

    deuPau(token, 36, listaTokens, *index);  
}

void listaCase(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor, "case") == 0){
        switch02(listaTokens, *index);
        token = lerToken(listaTokens, *index);
        if(strcmp(token.valor, ":") == 0){
            listaStatement(listaTokens, *index);
            listaCaseLinha(listaTokens, *index);
            return;
        }
        deuPau(token, 37, listaTokens, *index); 
        return;  
    }
    deuPau(token, 38, listaTokens, *index); 
    return;
}

void listaCaseLinha(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor, "case") == 0){
        switch02(listaTokens, *index);
        token = lerToken(listaTokens, *index);
        if(strcmp(token.valor, ":") == 0){
            listaStatement(listaTokens, *index);
            listaCaseLinha(listaTokens, *index);
            return;
        }
        deuPau(token, 39, listaTokens, *index); 
        return;  
    }
    else if(strcmp(token.valor, "default") == 0){
        token = lerToken(listaTokens, *index);
        if(strcmp(token.valor, ":") == 0){
            listaStatement(listaTokens, *index);
            return;
        }
        deuPau(token, 40, listaTokens, *index);
        return;
    }
    deuPau(token, 41, listaTokens, *index);
}

void chamadaFuncao(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.tipo, "identificador") == 0){
        token = lerToken(listaTokens, *index);
        if(strcmp(token.valor, "(") == 0){
            listaArgChamadaFuncao(listaTokens, *index);
            token = lerToken(listaTokens, *index);
            if(strcmp(token.valor, ")") == 0){
                token = lerToken(listaTokens, *index);
                if(strcmp(token.valor, ";") == 0){
                    return;
                }
                deuPau(token, 42, listaTokens, *index);
                return;
            }
            deuPau(token, 43, listaTokens, *index);
            return;
        }
        deuPau(token, 44, listaTokens, *index);
        return;
    }
    deuPau(token, 45, listaTokens, *index);
        return;
}

void listaArgChamadaFuncao(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.tipo, "numero") == 0 || strcmp(token.tipo, "identificador") == 0 || strcmp(token.valor, "\"") == 0 || 
    strcmp(token.valor, "\'") == 0){
        voltarToken(*index);
        switch02(listaTokens, *index);
        listaArgChamadaFuncaoLinha(listaTokens, *index);
        return;
    }
}

void listaArgChamadaFuncaoLinha(token_type* listaTokens, int *index){
    token_type token = lerToken(listaTokens, *index);
    if(strcmp(token.valor, ",") == 0){
        switch02(listaTokens, *index);
        listaArgChamadaFuncaoLinha(listaTokens, *index);
        return;
    }
}

void deuPau(token_type token, int erro_numero, token_type* listaTokens, int *index){
    switch (erro_numero)
    {
    case 0:
        printf("ERRO no token %s(%d, %d): Funcao sem abre parenteses.\n", token.valor, token.linha, token.coluna);
        break;

    case 1:
        printf("ERRO no token %s(%d, %d): Funcao sem fecha parenteses.\n", token.valor, token.linha, token.coluna);
        break;

    case 2:
        printf("ERRO no token %s(%d, %d): Funcao sem identificador.\n", token.valor, token.linha, token.coluna);
        break;

     case 3:
        printf("ERRO no token %s(%d, %d): If sem abre parenteses.\n", token.valor, token.linha, token.coluna);
        break;
    
    case 4:
        printf("ERRO no token %s(%d, %d): argumento sem identificador.\n", token.valor, token.linha, token.coluna);
        break;

    case 5:
        printf("ERRO no token %s(%d, %d): Token nao e identificador.\n", token.valor, token.linha, token.coluna);
        break;

    case 6:
        printf("ERRO no token %s(%d, %d): Return sem ponto e virgula.\n", token.valor, token.linha, token.coluna);
        break;

    case 7:
        printf("ERRO no token %s(%d, %d): Break sem ponto e virgula.\n", token.valor, token.linha, token.coluna);
        break;

    case 8:
        printf("ERRO no token %s(%d, %d): Statement invalido.\n", token.valor, token.linha, token.coluna);
        break;

    case 9:
        printf("ERRO no token %s(%d, %d): Falta de fecha parenteses no for.\n", token.valor, token.linha, token.coluna);
        break;

    case 10:
        printf("ERRO no token %s(%d, %d): Falta do segundo ponto e virgula no for.\n", token.valor, token.linha, token.coluna);
        break;

    case 11:
        printf("ERRO no token %s(%d, %d): Falta do primeiro ponto e virgula no for.\n", token.valor, token.linha, token.coluna);
        break;

    case 12:
        printf("ERRO no token %s(%d, %d): For sem abrir parenteses.\n", token.valor, token.linha, token.coluna);
        break;

    case 13:
        printf("ERRO no token %s(%d, %d): For sem for?.\n", token.valor, token.linha, token.coluna);
        break;

    case 14:
        printf("ERRO no token %s(%d, %d): While sem fecha parenteses.\n", token.valor, token.linha, token.coluna);
        break;

    case 15:
        printf("ERRO no token %s(%d, %d): While sem abre parenteses.\n", token.valor, token.linha, token.coluna);
        break;

    case 16:
        printf("ERRO no token %s(%d, %d): While sem while?.\n", token.valor, token.linha, token.coluna);
        break;

    case 17:
        printf("ERRO no token %s(%d, %d): While do Do While sem fecha parenteses.\n", token.valor, token.linha, token.coluna);
        break;

    case 18:
        printf("ERRO no token %s(%d, %d): While do Do While sem abre parenteses.\n", token.valor, token.linha, token.coluna);
        break;

    case 19:
        printf("ERRO no token %s(%d, %d): Do While sem while.\n", token.valor, token.linha, token.coluna);
        break;

    case 20:
        printf("ERRO no token %s(%d, %d): Do While sem Do?.\n", token.valor, token.linha, token.coluna);
        break;

    case 21:
        printf("ERRO no token %s(%d, %d): If sem fecha parenteses.\n", token.valor, token.linha, token.coluna);
        break;

    case 22:
        printf("ERRO no token %s(%d, %d): If sem if?.\n", token.valor, token.linha, token.coluna);
        break;

    case 23:
        printf("ERRO no token %s(%d, %d): Return invalido.\n", token.valor, token.linha, token.coluna);
        break;

    case 24:
        printf("ERRO no token %s(%d, %d): Escopo sem fecha chaves.\n", token.valor, token.linha, token.coluna);
        break;

    case 25:
        printf("ERRO no token %s(%d, %d): Escopo sem abre chaves.\n", token.valor, token.linha, token.coluna);
        break;

    case 26:
        printf("ERRO no token %s(%d, %d): Expressao invalida.\n", token.valor, token.linha, token.coluna);
        break;

    case 27:
        printf("ERRO no token %s(%d, %d): Expressao sem operador.\n", token.valor, token.linha, token.coluna);
        break;

    case 28:
        printf("ERRO no token %s(%d, %d): Expressao com comeco invalido.\n", token.valor, token.linha, token.coluna);
        break;

    case 29:
        printf("ERRO no token %s(%d, %d): Expressao com abre parenteses mas sem fecha parenteses.\n", token.valor, token.linha, token.coluna);
        break;

    case 30:
        printf("ERRO no token %s(%d, %d): Fator invalido.\n", token.valor, token.linha, token.coluna);
        break;

    case 31:
        printf("ERRO no token %s(%d, %d): Switch sem fecha chaves.\n", token.valor, token.linha, token.coluna);
        break; 

    case 32:
        printf("ERRO no token %s(%d, %d): Switch sem abre chaves.\n", token.valor, token.linha, token.coluna);
        break;

    case 33:
        printf("ERRO no token %s(%d, %d): Switch sem fecha parenteses.\n", token.valor, token.linha, token.coluna);
        break;

    case 34:
        printf("ERRO no token %s(%d, %d): Switch sem abre parenteses.\n", token.valor, token.linha, token.coluna);
        break;

    case 35:
        printf("ERRO no token %s(%d, %d): Switch sem switch?.\n", token.valor, token.linha, token.coluna);
        break;

    case 36:
        printf("ERRO no token %s(%d, %d): Valor dentro do switch invalido.\n", token.valor, token.linha, token.coluna);
        break;

    case 37:
        printf("ERRO no token %s(%d, %d): Case sem dois pontos.\n", token.valor, token.linha, token.coluna);
        break;

    case 38:
        printf("ERRO no token %s(%d, %d): switch sem case.\n", token.valor, token.linha, token.coluna);
        break;

    case 39:
        printf("ERRO no token %s(%d, %d): case_ sem dois pontos.\n", token.valor, token.linha, token.coluna);
        break;

    case 40:
        printf("ERRO no token %s(%d, %d): Default sem dois pontos.\n", token.valor, token.linha, token.coluna);
        break;

    case 41:
        printf("ERRO no token %s(%d, %d): Case sem case ou default.\n", token.valor, token.linha, token.coluna);
        break;

    case 42:
        printf("ERRO no token %s(%d, %d): Chamada de funcao sem ponto e virgula.\n", token.valor, token.linha, token.coluna);
        break;

    case 43:
        printf("ERRO no token %s(%d, %d): Chamada de funcao sem fecha parenteses.\n", token.valor, token.linha, token.coluna);
        break;

    case 44:
        printf("ERRO no token %s(%d, %d): Chamada de funcao sem abre parenteses.\n", token.valor, token.linha, token.coluna);
        break;  

    case 45:
        printf("ERRO no token %s(%d, %d): Chamada de funcao sem identificador.\n", token.valor, token.linha, token.coluna);
        break;      
                                            
    
    default:
        printf("ERRO no token %s(%d, %d): Erro desconhecido.\n", token.valor, token.linha, token.coluna);
        break;
    }

    while(!(strcmp(token.valor, ";") == 0 || strcmp(token.valor, "}") == 0))
        token = lerToken(listaTokens, *index);
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
    token_type* listaTokens = lerArquivo(arquivo, tamanho);
    fclose(arquivo);
    int index = 0;
    
    sintatico(listaTokens, &index, tamanho);

    return 0;
}