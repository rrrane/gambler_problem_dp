
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rlglue/Environment_common.h" /* Required for RL-Glue interface*/


static gsl_vector* local_observation;
static reward_observation_terminal_t this_reward_observation;

void env_init() 
{
	//NOT USED

	return;
}

const observation_t* env_start()
{
	//NOT USED
	
  	return this_reward_observation.observation;
}

const reward_observation_terminal_t *env_step(const action_t *this_action)
{
	//NOT USED
  
  	return &this_reward_observation;
}


void env_cleanup()
{
  gsl_vector_free(local_observation);
}

const char* env_message(const char* inMessage) 
{
  if(strcmp(inMessage,"what is your name?")==0)
  return "my name is skeleton_environment!";
  
  /* else */
  return "I don't know how to respond to your message";
}
