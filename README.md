# Analisador-Sintatico
<div style="text-align: justify"> 
O Analisador Sintático recebe uma lista de tokens de um arquivo e retorna os erros sintáticos presentes no código.
O código foi baseado na seguinte gramática livre de contexto: <br> https://lookaside.fbsbx.com/file/glc.txt?token=AWxIPu_BTmIMJVkghBWahr44-Z-BmE6po3XZHE78HVr1oGT_Qa8SUgjZhmBcqm7UN7R_XBjUnMwwprxUyECsUYk4uKBjj5FsMiWVoD1djz_V1-fG5az1GUk4Tdwl4Xl-zdC4huI1sAA26JMQcKYZHRhBycsuAjiVDD851mI82Yw2zg

Para compilar:<br>
make clean <br>
make

Para executar:<br>
./sintatico arquivo_com_a_lista_de_tokens.txt (use o nome tokens.txt para rodar no exemplo contido nesse repositório)

Infelizmente o código contém erros não identificados na implementação da gramática. Muitas vezes ele dá erros de fim de escopo inválidos em situações em que não necessariamente deveria haver um fim de escopo. Porém, o código se mostrou eficiente para encontrar erros de ponto e vírgula, parenteses em laços e ifs e erros em declarações de funções.


</div>
