#include "data.h"
#include "scripts\model.c"
#include "scripts\archive.c"

int main(int argc, char *argv[]){
    int i, j, exe;
    Data_t Data0;
    char filename[50], ifilename[50];
    strcpy(filename,"saida");
    strcpy(ifilename,"chart-win.exe -i ");
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
            saida[0].dead = Data0.dead;
            
            getNameFile(argc, argv, &filename);
            strcat(ifilename, filename);
            strcat(filename, ".csv");
            FILE *csv = fopen(filename, "w+");
            printCsv(csv, 1, Data0, Data0.interval);
            printConsole(1, Data0,  Data0.interval);
            for (j = 1; j < (Data0.days / Data0.interval); j++){               
                saida[j].susceptible = getS(j, &Data0, &saida[j-1]);
                saida[j].recovered = getR(j, &Data0, &saida[j-1]);
                saida[j].infected = getI(j, &Data0, &saida[j-1]);
                saida[j].interval = getInterval(j, &Data0, &saida[j-1]);
                getDead(&saida[j].dead, saida[j].recovered);
                printCsv(csv, j + 1, saida[j], saida[j].interval);
                printConsole(j + 1, saida[j], saida[j].interval);
            }
            fclose(csv);
            free(saida);

            exe = system(ifilename);
            printf("%d",exe);
        }
    }

    return 0;
}

