
int getS(double *S, int x, Data_t *zero, Data_t *previous){
    if( x == 0) return zero->susceptible;
    *S = previous->susceptible - (zero->interval * zero->contagionFacility * previous->susceptible * previous->infected);
    return 0;
}

int getI(double *I, int x, Data_t *zero, Data_t *previous){
    if( x == 0) return zero->infected;
    *I = previous->infected + (zero->interval * (zero->contagionFacility * previous->susceptible * previous->infected - zero->recoveryProbability * previous->infected));
    return 0;
}

int getR(double *R, int x, Data_t *zero, Data_t *previous){
    if( x == 0) return zero->recovered;
    *R = previous->recovered + (zero->interval * zero->recoveryProbability* previous->infected);
    return 0;
}

int getInterval(double *interval, int x, Data_t *zero, Data_t *previous){
    if( x == 0) return zero->interval;
    *interval = previous->interval + zero->interval;
    return 0;
}

int getB(double *b, double N_b, double T_b, double S_b0, double I_b0){
    *b = N_b/(T_b * S_b0 * I_b0);
    return 0;
}

int getK(double *k, double m_k, double n_k, double T_k){
    *k = m_k/(n_k * T_k);
    return 0;
}

int getDead(double *dead, double R){
    *dead = R * 0.02;
    return 0;
}