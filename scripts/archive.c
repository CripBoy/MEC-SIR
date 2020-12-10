
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
    data->dead = data->recovered * 0.02;


    //S(0), I(0), R(0), h, N_b, T_b, S_b0, I_b0, m_k, n_k, T_k
    // 0     1     2    3   4    5    6     7     8    9   10
    return 0;
}

int printCsv(FILE *file, int index, Data_t print, double interval){
    if(index == 1){
        fprintf(file, "%s,", "x");
        fprintf(file, "%s,", "S");
        fprintf(file, "%s,", "I");
        fprintf(file, "%s,", "R");
        fprintf(file, "%s,", "Mortos");
        fprintf(file, "%s\n", "Dias");
    }
    fprintf(file, "%d,", index);
    fprintf(file, "%.3f,", print.susceptible);
    fprintf(file, "%.4f,", print.infected);
    fprintf(file, "%.7f,", print.recovered);
    fprintf(file, "%.7f,", print.dead);
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