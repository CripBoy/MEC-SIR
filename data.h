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
  double dead;
} Data_t;

typedef struct {
  double m_k;
  double n_k;
  double T_k;
  double N_b;
  double T_b;
  double S_b0;
  double I_b0;
  double timer;
  int Case;
} DataAux_t;