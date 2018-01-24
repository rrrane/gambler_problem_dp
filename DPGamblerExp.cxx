
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "rlglue/RL_glue.h"

#define	P_HEADS		0.25	/* Probability of heads */
#define	MIN_BET		0	/* Minimum capital that agent can stake (can be 0 or 1)*/
#define NUM_STATES	101	/* Total number of states */
#define GAMMA		0.9	/* Discounting factor */
#define SWEEPS		1	/* Number of sweeps */

void saveResults(double* data, int dataSize, const char* filename);

double p(int s, int a, int s_prime, int r); /* Environment dynamics function */

int main(int argc, char *argv[]) {

	srand(time(NULL));
	
	double 	pi[NUM_STATES]; /* Deterministic policy */
	double 	V[NUM_STATES]; 	/* State-Value function */

	double 	delta;
	double 	theta;

	//Initialize V and pi
	for(int s = 0; s < NUM_STATES; s++){
		pi[s] = (double)MIN_BET;
		V[s] = 0.0;
	}
	
	pi[0] = 0.0;
	pi[100] = 0.0;

	theta = 0.01;

	randInRange(100);	

	//Calculate State-Value function V*

	while(1){

		delta = 0;

		for(int i = 0; i < SWEEPS; i++){
			for(int s = 0; s < NUM_STATES; s++){
			
				double v = V[s];

				int limit = (s < 100 - s) ? s : 100-s;

				for(int a = MIN_BET; a <= limit; a++){
					double sum = 0.0;

					for(int s_prime = 0; s_prime < NUM_STATES; s_prime++){
						for(int r = 0; r < 2; r++)
							sum += p(s, a, s_prime, r) * (r + GAMMA * V[s_prime]);
					}

					V[s] = (V[s] < sum) ? sum : V[s];
					//pi[s] = (V[s] <= sum) ? (double)a : pi[s];
				}

				delta = (abs(v - V[s]) > delta) ? abs(v - V[s]) : delta;
			}
		}
		if(delta < theta) break;

	}

	//Obtain optimal policy
	
	for(int s = 1; s < NUM_STATES - 1; s++){
		
		int limit = (s < 100 - s) ? s : 100-s;

		int ties[limit];

		int count = 0;

		int max_act = MIN_BET;
		
		double max_sum = 0.0;

		double act_val[limit+1];

		for(int a = MIN_BET; a <= limit; a++){
			double sum = 0.0;
			
			for(int s_prime = 0; s_prime < NUM_STATES; s_prime++){
				for(int r = 0; r < 2; r++)
					sum += p(s, a, s_prime, r) * (r + GAMMA * V[s_prime]);
			}

			act_val[a] = sum;

			max_act = (max_sum < sum) ? a : max_act;
			max_sum = (max_sum < sum)? sum : max_sum;
		}

		for(int a = max_act; a <= limit; a++){
			if(act_val[a] == act_val[max_act])
				ties[count++] = a;
		}

		pi[s] = (double)ties[randInRange(count)];

	}
	
  
  	/* Save data to a file */
  	saveResults(V, NUM_STATES, "RL_EXP_OUT.dat");
	saveResults(pi, NUM_STATES, "RL_POLICY.dat");
  
  	return 0;
}

double p(int s, int a, int s_prime, int r){
	if(s > 0 && s < 100){
		if(s_prime == s + a && (r == 0 && s_prime < 100 || r == 1 && s_prime == 100))
			return P_HEADS;

		if(s_prime == s - a && r == 0 && s_prime >= 0)
			return (1 - P_HEADS);

		return 0.0;
	}

	return 0.0;
}

void saveResults(double* data, int dataSize, const char* filename) {
  FILE *dataFile;
  int i;
  dataFile = fopen(filename, "w");
  for(i = 0; i < dataSize; i++){
    fprintf(dataFile, "%lf\n", data[i]);
  }
  fclose(dataFile);
}
