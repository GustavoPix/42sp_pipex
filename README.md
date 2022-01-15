# Pipex

Sexto projeto da 42sp, o projeto é um programa no qual lê um arquivo, passa este arquivo para uma aplicação e o resultado para outra aplicação e a saida deste programa para um arquivo.

## Execução

`./pipex file_in "cmd" "cmd" file_out`

- `file_in` -> Arquivo de texto de entrada
- `cmd` -> comando para processar o dado anterior (ex: `grep abc`)
- `file_out` -> arquivo de texto para imprimir a saida (pode ser um arquivo existente ou um novo arquivo)

## Mandatório

No mandatório só é possível executar 2 comandos

## Compilação

`make` compila o projeto (mandatório com 2 cmds)
`make clean` apaga os arquivos compilados
`make fclean` apaga os arquivos e o programa

## Requisitos

Possuir um arquivo de texto para a leitura do programa

## Libft

Como a Libft é proibida neste projeto, foi utilizado algumas funções da mesma na pasta da Libft.
