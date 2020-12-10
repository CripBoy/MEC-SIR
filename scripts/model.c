
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

int getDead(double *dead, double R){
    *dead = R * 0.02;
    return 0;
}