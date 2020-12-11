#include "data.h"
#include "scripts\model.c"
#include "scripts\archive.c"

int main(int argc, char *argv[]){
    int i, j, exe, image;
    Data_t Data0;
    DataAux_t auxData;
    char filename[50], exefilename[50], imagefilename[50];
    strcpy(filename,"saida");
    strcpy(exefilename,"chart-win.exe -i ");
    for (i = 1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'i' && argv[i][2] == '\0' ){
            
            if(getInitialParameters(argv[i+1], &Data0, &auxData, argc, argv))
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
            strcat(exefilename, filename);
            strcpy(imagefilename, filename);
            strcat(filename, ".csv");
            strcat(imagefilename, ".jpg");
            FILE *csv = fopen(filename, "w+");
            printCsv(csv, 1, Data0, Data0.interval);
            //printConsole(1, Data0,  Data0.interval);
            for (j = 1; j < (Data0.days / Data0.interval); j++){
                if(auxData.Case != 0 && auxData.timer == j){
                    if(auxData.Case == 1){
                        getB(&Data0.contagionFacility, auxData.N_b, auxData.T_b, auxData.S_b0, auxData.I_b0);
                    }
                    if(auxData.Case == 2){
                        getK(&Data0.recoveryProbability, auxData.m_k, auxData.n_k, auxData.T_k);
                    }
                }         
                getS(&saida[j].susceptible, j, &Data0, &saida[j-1]);
                getR(&saida[j].recovered, j, &Data0, &saida[j-1]);
                getI(&saida[j].infected, j, &Data0, &saida[j-1]);
                getInterval(&saida[j].interval, j, &Data0, &saida[j-1]);
                getDead(&saida[j].dead, saida[j].recovered);
                printCsv(csv, j + 1, saida[j], saida[j].interval);
                printConsole(j + 1, saida[j], saida[j].interval);
            }
            fclose(csv);
            free(saida);

            exe = system(exefilename);
            printf("%d",exe);
            image = system(imagefilename);
            printf("%d",image);
        }
    }

    return 0;
}

