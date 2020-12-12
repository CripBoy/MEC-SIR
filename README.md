# Modelo Epidemiológico Computacional usando o sistema SIR
- Aluno
  * Guilherme Kaio Dantas de Carvalho
  
- Checkpoint 1:
  * Implementação do modelo SIR e saída no terminal
  * Leitura dos parâmetros iniciais de simulação à partir de um arquivo de texto
  * Implementação do modelo SIR com saída em arquivo de texto csv
- Checkpoint 2:
  * Implementação dos cenários
  * Plotagem do Gráfico
  * Encapsulamento
  * Correções Gerais

## Compilação
- Método para a compilação via linha de comando: `gcc -o main main.c`

## Execução
- Por linha de comando: `main -i path\to\file.txt`

## Arquivo de entrada
- Cenário 0
  * Formato: `S(0) I(0) R(0) h N_b T_b S_b0 I_b0 m_k n_k T_k T`
  * Exemplo: `68 2 0 0.1 12 24 50 10 6 22 24 504`
- Cenário 1
  * Formato: `S(0) I(0) R(0) h N_b T_b S_b0 I_b0 m_k n_k T_k T T_b1 T_1`
  * Exemplo: `68 2 0 0.1 12 24 50 10 6 22 24 504 48 300`
- Cenário 2
  * Formato: `S(0) I(0) R(0) h N_b T_b S_b0 I_b0 m_k n_k T_k T T_k2 T_2`
  * Exemplo: `68 2 0 0.1 12 24 50 10 6 22 24 504 10 300`

## Flags
- E/S
  * `-i path\to\file.txt`: Informa ao programa um arquivo de com os parâmetros iniciais (obrigatório).
  * `-o nome`: Altera o nome do documento de saida, padrão: `saida.csv`.
- Cenários
  * `-c1`: Altera para o cenário 1.
  * `-c2`: Altera para o cenário 2.
- Parâmetros
  * `-S0 valor`: Altera o valor inicial de indivíduos suscetíveis.  
  * `-I0 valor`: Altera o valor inicial de indivíduos infectados.
  * `-R0 valor`: Altera o valor inicial de indivíduos removidos.
  * `-h valor`: Altera o intervalo de tempo entre cada simulação.
  * `-Nb valor`: Altera o valor correspondente ao número de pessoas suscetíveis que se infectaram em um intervalo de tempo.
  * `-Tb valor`: Altera o intervalo de tempo utilizado na calculo de facilidade de contágio de um indivíduo.
  * `-Sb0 valor`: Altera o valor correspondente ao número de pessoas suscetíveis no início da observação.
  * `-Ib0 valor`: Altera o valor correspondente ao número de pessoas infectadas no início da observação.
  * `-mk valor`: Altera o valor correspondente ao número de indivíduos que se recuperaram utilizado no calculo de probabilidade de recuperação do indivíduo.
  * `-nk valor`: Altera o valor correspondente ao número total de indivíduos utilizado no calculo de probabilidade de recuperação do indivíduo.
  * `-Tk valor`: Altera o intervalo de tempo utilizado no calculo de probabilidade de recuperação do indivíduo.
  * `-d valor`: Altera o a quantidade de dias simulados.
