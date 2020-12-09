#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  double recovered;
  double infected;
  double susceptible;
  double contagionFacility;
  double recoveryProbability;
  double interval;
  double days;
} Data_t;

int getInitialParameters(char *dest, Data_t *data, int argc, char *argv[]);
int getK(double *k, double m_k, double n_k, double T_k);
int getB(double *b, double N_b, double T_b, double S_b0, double I_b0);
double getS(int x, Data_t *zero, Data_t *previous);
double getI(int x, Data_t *zero, Data_t *previous);
double getR(int x, Data_t *zero, Data_t *previous);
double getInterval(int x, Data_t *zero, Data_t *previous);
int printCsv(FILE *file, int index, Data_t print, double interval);
int printConsole(int index, Data_t print, double interval);
int getNameFile(int argc, char *argv[], char *filename);

int main(int argc, char *argv[]){
    int i, j;
    Data_t Data0;
    char filename[50];
    strcpy(filename,"saida");
    for (i = 1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'i' && argv[i][2] == '\0' ){
            
            if(getInitialParameters(argv[i+1], &Data0, argc, argv))
            {
                printf("Por favor Insira um caminho para o arquivo de entrada apos o -i.");
                return 1;
            }
            Data_t *saida;

            saida = malloc(sizeof(Data_t) * (Data0.days / Data0.interval)+1);
            saida[0].infected = Data0.infected;
            saida[0].recovered = Data0.recovered;
            saida[0].susceptible = Data0.susceptible;
            saida[0].interval = Data0.interval;
            
            getNameFile(argc, argv, &filename);
            strcat(filename, ".csv");
            FILE *csv = fopen(filename, "w+");
            for (j = 1; j < (Data0.days / Data0.interval) + 1; j++){               
                saida[j].susceptible = getS(j, &Data0, &saida[j-1]);
                saida[j].recovered = getR(j, &Data0, &saida[j-1]);
                saida[j].infected = getI(j, &Data0, &saida[j-1]);
                printCsv(csv, j, saida[j], saida[j-1].interval);
                printConsole(j, saida[j], saida[j-1].interval);
                saida[j].interval = getInterval(j, &Data0, &saida[j-1]);
            }
            fclose(csv);
            free(saida);
        }
    }

    return 0;
}

double getS(int x, Data_t *zero, Data_t *previous){
    if( x == 0) return zero->susceptible;
    return previous->susceptible - (zero->interval * zero->contagionFacility * previous->susceptible * previous->infected);
}

double getI(int x, Data_t *zero, Data_t *previous){
    if( x == 0) return zero->infected;
    return previous->infected + (zero->interval * (zero->contagionFacility * previous->susceptible * previous->infected - zero->recoveryProbability * previous->infected));
}

double getR(int x, Data_t *zero, Data_t *previous){
    if( x == 0) return zero->recovered;
    return previous->recovered + (zero->interval * zero->recoveryProbability* previous->infected);
}

double getInterval(int x, Data_t *zero, Data_t *previous){
    if( x == 0) return zero->interval;
    return previous->interval + zero->interval;
}

int getB(double *b, double N_b, double T_b, double S_b0, double I_b0){
    *b = N_b/(T_b * S_b0 * I_b0);
    return 0;
}

int getK(double *k, double m_k, double n_k, double T_k){
    *k = m_k/(n_k * T_k);
    return 0;
}

int getInitialParameters(char *dest, Data_t *data, int argc, char *argv[]){
    int i = 0;
    FILE *input;
    input = fopen(dest, "r");
    char buff[1000], aux[12][10], *ret;
    if(input == NULL) return 1;
    fgets(buff, 1000, (FILE*)input);
    fclose(input);
    char *token = strtok(buff, " ");
    while(token != NULL) {
        strcpy(aux[i], token);
        token = strtok(NULL, " ");
        i++;
    }
    if(i != 12)return 1;
    int j;
    for ( j = 1; j < argc; j++)
    {
        if(argv[j][0] == '-' && argv[j][1] == 'S' && argv[j][2] == '0' && argv[j][3] == '\0' ){
            strcpy(aux[0], argv[j+1]);
        }
        if(argv[j][0] == '-' && argv[j][1] == 'I' && argv[j][2] == '0' && argv[j][3] == '\0' ){
            strcpy(aux[1], argv[j+1]);
        }
        if(argv[j][0] == '-' && argv[j][1] == 'R' && argv[j][2] == '0' && argv[j][3] == '\0' ){
            strcpy(aux[2], argv[j+1]);
        }
        if(argv[j][0] == '-' && argv[j][1] == 'h' && argv[j][2] == '\0' ){
            strcpy(aux[3], argv[j+1]);
        }
        if(argv[j][0] == '-' && argv[j][1] == 'N' && argv[j][2] == 'b' && argv[j][3] == '\0' ){
            strcpy(aux[4], argv[j+1]);
        }
        if(argv[j][0] == '-' && argv[j][1] == 'T' && argv[j][2] == 'b' && argv[j][3] == '\0' ){
            strcpy(aux[5], argv[j+1]);
        }
        if(argv[j][0] == '-' && argv[j][1] == 'S' && argv[j][2] == 'b' && argv[j][3] == '0' && argv[j][4] == '\0'){
            strcpy(aux[6], argv[j+1]);
        }
        if(argv[j][0] == '-' && argv[j][1] == 'I' && argv[j][2] == 'b' && argv[j][3] == '0' && argv[j][4] == '\0'){
            strcpy(aux[7], argv[j+1]);
        }
        if(argv[j][0] == '-' && argv[j][1] == 'm' && argv[j][2] == 'k' && argv[j][3] == '\0' ){
            strcpy(aux[8], argv[j+1]);
        }
        if(argv[j][0] == '-' && argv[j][1] == 'n' && argv[j][2] == 'k' && argv[j][3] == '\0' ){
            strcpy(aux[9], argv[j+1]);
        }
        if(argv[j][0] == '-' && argv[j][1] == 'T' && argv[j][2] == 'k' && argv[j][3] == '\0' ){
            strcpy(aux[10], argv[j+1]);
        }
        if(argv[j][0] == '-' && argv[j][1] == 'd' && argv[j][2] == '\0' ){
            strcpy(aux[11], argv[j+1]);
        }
    }
    data->susceptible = strtod(aux[0], &ret);
    data->infected = atoi(aux[1]);
    data->recovered = strtod(aux[2], &ret);
    data->interval = strtod(aux[3], &ret);
    if(getB(&data->contagionFacility, strtod(aux[4], &ret), strtod(aux[5], &ret), strtod(aux[6], &ret), strtod(aux[7], &ret)))return 1;
    if(getK(&data->recoveryProbability, strtod(aux[8], &ret), strtod(aux[9], &ret), strtod(aux[10], &ret)))return 1;
    data->days = strtod(aux[11], &ret);


    //S(0), I(0), R(0), h, N_b, T_b, S_b0, I_b0, m_k, n_k, T_k
    // 0     1     2    3   4    5    6     7     8    9   10
    return 0;
}

int printCsv(FILE *file, int index, Data_t print, double interval){
    if(index == 1){
        fprintf(file, "%s,", "x");
        fprintf(file, "%s,", "S(x)");
        fprintf(file, "%s,", "I(x)");
        fprintf(file, "%s,", "R(x)");
        fprintf(file, "%s\n", "Dias");
    }
    fprintf(file, "%d,", index);
    fprintf(file, "%.3f,", print.susceptible);
    fprintf(file, "%.4f,", print.infected);
    fprintf(file, "%.7f,", print.recovered);
    fprintf(file, "%.1f\n", interval);
    return 0;
}

int printConsole(int index, Data_t print, double interval){
    printf( "%d,", index);
    printf( "%.3f,", print.susceptible);
    printf( "%.4f,", print.infected);
    printf( "%.7f,", print.recovered);
    printf( "%.1f\n", interval);
}

int getNameFile(int argc, char *argv[], char *filename){
    int j;
    for ( j = 1; j < argc; j++)
    {
        if(argv[j][0] == '-' && argv[j][1] == 'o' && argv[j][2] == '\0' ){
            strcpy(filename, argv[j+1]);
        }
    }
    return 0;
}
