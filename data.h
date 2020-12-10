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