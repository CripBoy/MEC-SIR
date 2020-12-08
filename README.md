# Modelo Epidemiológico Computacional usando o sistema SIR
- Aluno
  * Guilherme Kaio Dantas de Carvalho
  
- Checkpoint 1:
  * Implementação do modelo SIR e saída no terminal
  * Leitura dos parâmetros iniciais de simulação à partir de um arquivo de texto
  * Implementação do modelo SIR com saída em arquivo de texto csv
  * Modificações para Checkpoint 2:
    * ?

## Compilação
- Método para a compilação via linha de comando: `gcc -o main main.c`

## Execução
- Por linha de comando: `main -i path\to\file.txt`

## Arquivo de entrada
- Formato: `S(0) I(0) R(0) h N_b T_b S_b0 I_b0 m_k n_k T_k T`
- Exemplo: `68 2 0 0.1 12 24 50 10 6 22 24 504`
