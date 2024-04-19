# Trabalho 1 de Compiladores
## Autores
Augusto dos Santos Gomes Vaz - 800268
Gabriel Kusumota Nadalin - 819498

## Objetivo
Fazer um analisador léxico para a linguagem "Linguagem Algorítmica", identificando os tokens e informando erros, caso sejam identificados.\
O analisador vai ser um arquivo do código fonte e vai escrever todos os tokens identificados no arquivo de saída.\
Caso algum erro de sintaxe for identificado durante o processo, o programa irá informar neste mesmo arquivo e encerrar sua execução.

## Como rodar
1. Certifique-se que você tem o gcc instalado: ```gcc --version```\
Caso nenhuma mensagem informando a versão seja exibida, [instale o gcc](https://www.mingw-w64.org/downloads/)
2. Compile o código ```make --always-make```
2. Rode o programa ```./main arquivo_fonte arquivo_output```

## Considerações
Por se tratar de uma versão simplificada, o analisador tem algumas limitações.
1. Suporte de identificadores de tamanhos de até 200 caracteres
2. Suporte de strings de tamanho de até 200 caracteres
3. Identificação de erros com precisão de linhas somente
