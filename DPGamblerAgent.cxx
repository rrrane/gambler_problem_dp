#include <stdio.h>
#include <string.h>


#include "rlglue/Agent_common.h" /* Required for RL-Glue */

static gsl_vector* local_action;
static action_t* this_action;
static gsl_vector* last_observation;

void agent_init()
{
  //NOT USED
}

const action_t *agent_start(const observation_t *this_observation) {
 	
  //NOT USED
  
  return this_action;
}

const action_t *agent_step(double reward, const observation_t *this_observation) {
  

  	//NOT USED
  
  	return this_action;
}


void agent_end(double reward) {
  /* final learning update at end of episode */
}

void agent_cleanup() {
  /* clean up mememory */
  gsl_vector_free(local_action);
  gsl_vector_free(last_observation);
}

const char* agent_message(const char* inMessage) {
  /* might be useful to get information from the agent */
  if(strcmp(inMessage,"what is your name?")==0)
  return "my name is skeleton_agent!";
  
  /* else */
  return "I don't know how to respond to your message";
}
