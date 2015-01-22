/*
==============================================
AUTHOR - JULES MANALANG
PROJECT - DECOY - drone.c
EMAIL - julesman@buffalo.edu
==============================================
*/

/*
==============================================
Libraries used. Semaphore is used to mark a
drone landing/takeoff position is taken.
==============================================
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>


/*
==============================================
Incoming Drone definitions. Please see documentation
for finite state diagrams. Used in switch statement
==============================================
*/
# define LDA 0 //Incoming drone arrival
# define LDH 1 //Incoming drone hovering or waiting for available landing stop
# define LDM 2 //Incoming drone moves into position
# define LDL 3 //Incoming drone lands
# define LDP 4 //Incoming drone landing confirmation
# define LDC 5 //Incoming drone assesses collision
# define COM 6 //Incoming drone completes its lifespan

/*
==============================================
Departing Drone definitions. Please see documentation
for finite state diagrams. Used in switch statement
==============================================
*/
# define TDR 10 //Departing drone registers with  control
# define TDH 11 //Departing drone moves to take-off area if empty
# define TDI 12 //Departing drone initialize for take off
# define TDT 13 //Departing drone takes off
# define TDS 14 //Departing drone successfully takes off and is leaving
# define TDU 15 //Departing drone leaves control and is unregistered
# define TDC 16 //Departing drone assesses collisions
# define DON 17 //Departing drone completes its lifespan

/*
==============================================
Variable initializations. Used throughout
==============================================
*/
int loop0, loop1, col_chance;
int collision(int col_chance);
sem_t run;
void *landing(void *threadarg);
void *takeoff(void *threadarg1);

/*
==============================================
Structs for Incoming and Departing drones.
Contains the drone's lifespan, it's ID number
and collision data
==============================================
*/
struct drone_takeoff{
	int thread_collision_take;
	int thread_id_take;
	int thread_state_take;
};

struct drone_land{
	int thread_collision_land;
	int thread_id_land;
	int thread_state_land;
};

/*
==============================================
The following detects if there is a collision 
that going to happen. There's a 1 in 10 chance
collision will occur. Using a random number from
1 to 10 and seeing if the result is a number 5
results in a collision.
==============================================
*/

int collision(int col_chance) {
	int x;
	x = rand() % 10 + 1;
	if(x == 5) {
		col_chance = 0;
		return col_chance;
	}else {
		col_chance = 1;
		return col_chance;
	}
}


 
/*
==============================================
Landing method for Incoming Drones
-Uses switch cases to change the drone's state 
-Calls for collision checks at certain states
-Uses Semaphores to indicate that the landing
	area is currently occupied by a drone.
==============================================
*/
void *landing(void *threadarg) {
	int lid, lstate, lflag, LDCcounter;
	int x = 0;
	struct drone_land *land_data;
	land_data = (struct drone_land *) threadarg;
	lid = land_data->thread_id_land;
	lstate = land_data->thread_state_land;
	lflag = land_data->thread_collision_land;
	lstate = LDA;
	LDCcounter = 1234;
	while(lstate != 6) {
		switch(lstate) {
			case LDA: { printf("Incoming Drone: %d is approaching station.\n", lid);
					  lflag = collision(x);
					  if(lflag == 1) {  
						  lstate = LDH;
					  } else {
						  printf("WARNING Incoming Drone: %d detects something in the way.\n" , lid);
						  LDCcounter = 1;
						  lstate = LDC;
					  }
				  }
				  break; 
			case LDH: { printf("Incoming Drone: %d is waiting to land. \n", lid);
					  sem_wait(&run); 	//indicates that the take-off/landing area is in use by an incoming drone. 
					  lflag = collision(x);
					  if(lflag == 1) {  
						  lstate = LDM;
					  } else {
						  printf("WARNING Incoming Drone: %d picks up something abnormal with its sensors \n", lid);
						  LDCcounter = 2;
						  lstate = LDC;
					  }
				  }
				  break;
			case LDM: { printf("Incoming Drone: %d is landing... \n", lid);
					  lflag = collision(x);
					  if(lflag  == 1) {  
						  lstate = LDL;
					  } else {
						  printf("WARNING Incoming Drone: %d recognizes an obstacle while landing \n", lid);
						  LDCcounter = 3;
						  lstate = LDC;
					  }
				  }
				  break;
			case LDL: { printf("Incoming Drone: %d has landed and moving to receiving area\n", lid);
					  lstate = LDP;
				  }
				  break;
			
			case LDC: { if(LDCcounter == 1) {
					  int inRand = rand() % 3 + 1;
					  if(inRand == 1){
						printf("ACTION Incoming Drone: %d takes evasive maneuvers \n" , lid);
					  }
					  if(inRand == 2){
						printf("ACTION Incoming Drone: %d sees that the object has moved and does nothing \n" , lid);
					  }
					  if(inRand == 3){
						printf("ACTION Incoming Drone: %d decides that hitting the object will not damage itself and continues\n" , lid);
					  }
					  lstate = LDH;
				  } else if (LDCcounter == 2) {
					  int inRand = rand() % 3 + 1;
					  if(inRand == 1){
						printf("ACTION Incoming Drone: %d dodges the object while waiting to land \n" , lid);
					  }
					  if(inRand == 2){
						printf("ACTION Incoming Drone: %d sees that the object has moved and continues waiting to land \n" , lid);
					  }
					  if(inRand == 3){
						printf("ACTION Incoming Drone: %d decides that object will not cause damage if it hits and remains in place.\n" , lid);
					  }
					  lstate = LDM;
				  } else if (LDCcounter == 3) {
					  int inRand = rand() % 3 + 1;
					  if(inRand == 1){
						printf("ACTION Incoming Drone: %d reroutes and continues to a receiving area\n" , lid);
					  }
					  if(inRand == 2){
						printf("ACTION Incoming Drone: %d sees that the object has moved continues on its path \n" , lid);
					  }
					  if(inRand == 3){
						printf("ACTION Incoming Drone: %d decides that hitting the object will not damage itself and does not reroute.\n" , lid);
					  }
					  lstate = LDL;
				  }
				  }
				  break;
			case LDP: { printf("SUCCESS Incoming Drone: %d has touched down and left the landing area\n", lid);
					  sem_post(&run);	// the drone has touched down and the landing area is free again.
					  pthread_exit(NULL);	//end of the drone's life. end this pthread
					  lstate = COM; //exits the switch case statement
				  }
				  break;
		}
	} 		
}

/*
==============================================
Take-off method for Departing Drones
-Uses switch cases to change the drone's state 
-Calls for collision checks at certain states
-Uses Semaphores to indicate that the landing
	area is currently occupied by a drone.
-Essentially the same as landing but starts
	at the landing area
==============================================
*/

void *takeoff(void *threadarg1) {
	int tid,tstate, tflag, TDCcounter;
	int x = 0;
	struct drone_takeoff *take_data;
	take_data = (struct drone_takeoff *) threadarg1;
	tid = take_data->thread_id_take;
	tstate = take_data->thread_state_take;

	tflag= take_data->thread_collision_take;
	tstate = TDR;

	TDCcounter = 1234;
	tflag = 3;

	while(tstate != 17) {
		switch(tstate) {
			case TDR: { printf("Departing Drone: %d is registering with control \n", tid);	
					  tflag = collision(x);
					  if(tflag == 1) {  
						  tstate = TDH;
					  } else {
						  printf("WARNING Departing Drone: %d is detecting a problem while registering with   control\n", tid);
						  TDCcounter = 1;
						  tstate = TDC;
					  }
				  }
				  break; 
			case TDH: { printf("Departing Drone: %d is waiting to depart\n", tid);
					  sem_wait(&run);  //indicates that take-off/landing area is in use
					  tstate = TDI;
				  }
				  break;
			case TDI:{ printf("Departing Drone: %d has performed last minute checks and is taking off \n", tid);
					 tstate = TDT;
				 }
				 break;
			case TDT: { printf("Departing Drone: %d has taken off successfully\n", tid);
					  sem_post(&run); //drone has left the take-off/landing area and is open once again
					  tflag = collision(x);
					  if(tflag == 1) { 
						  tstate = TDS;
					  } else {
						  printf("WARNING Departing Drone: %d detects an object in the way while leaving control \n", tid);
						  TDCcounter = 2;
						  tstate = TDC;
					  }
				  }
				  break;
			case TDS: { printf("Departing Drone: %d is going to its destination and is leaving control\n", tid);
					  tflag = collision(x);
					  if(tflag == 1) {
						  tstate = TDU;
					  } else {
						  printf("WARNING Departing Drone: %d picks up something on its sensors while leaving.\n", tid);
						  TDCcounter = 3;
						  tstate = TDC;
					  }
				  }
				  break;
	
			case TDC: { if(TDCcounter == 1) {
					  int inRand = rand() % 3 + 1;
					  if(inRand == 1){
						printf("ACTION Departing Drone: %d waits until workers have have cleared the area\n" , tid);
					  }
					  if(inRand == 2){
						printf("ACTION Departing Drone: %d is suffering interference and waits until clear connection is met\n" , tid);
					  }
					  if(inRand == 3){
						printf("ACTION Departing Drone: %d is requesting refuelling or repairs.\n" , tid);
					  }
					  tstate = TDH;
				  } else if (TDCcounter == 2) {
					  int inRand = rand() % 3 + 1;
					  if(inRand == 1){
						printf("ACTION Departing Drone: %d detects and obstacle and evades it while leaving\n" , tid);
					  }
					  if(inRand == 2){
						printf("ACTION Departing Drone: %d notices the obstacle has moved and continues\n" , tid);
					  }
					  if(inRand == 3){
						printf("ACTION Departing Drone: %d decides that the obstacle does will not interfere and continues\n" , tid);
					  }
					  tstate = TDS;
				  } else if (TDCcounter == 3) {
					  int inRand = rand() % 3 + 1;
					  if(inRand == 1){
						printf("ACTION Departing Drone: %d takes evasive maneuvers \n" , tid);
					  }
					  if(inRand == 2){
						printf("ACTION Departing Drone: %d sees that the object has moved and does nothing \n" , tid);
					  }
					  if(inRand == 3){
						printf("ACTION Departing Drone: %d decides that hitting the object will not damage itself and does not reroute.\n" , tid);
					  }
					  tstate = TDU;
				  }
				  }
				  break;
			case TDU: { printf("SUCCESS Departing Drone: %d has successfully departed and is unregistered from control\n", tid);
					  tstate = DON;
					  pthread_exit(NULL); 	// terminate the pthread as we reach this case
					  break;
				  }
		}
	}				  
}

//main method assigns ID, number of drones per task, all within a pthread.

int main(int argc, char *argv[]){
	int  my_t_state, my_l_state, my_t_collision, my_l_collision, takeoffs, landings, spot;
	
	takeoffs = atoi(argv[1]);  
	landings = atoi(argv[2]);  
	spot = atoi(argv[3]);
	
	pthread_t taker[takeoffs], lander[landings];
	sem_init(&run, 0, spot);
	srand(time(NULL));
	
	struct drone_takeoff takeoff_array[takeoffs];
	struct drone_land landing_array[landings];
	
	for(loop0 = 1; loop0 <= takeoffs; loop0++) {
		takeoff_array[loop0].thread_id_take = loop0; //struct gives ID
		takeoff_array[loop0].thread_state_take = my_t_state;
		takeoff_array[loop0].thread_collision_take = my_t_collision;
		pthread_create(&taker[loop0], NULL, takeoff,(void *) &takeoff_array[loop0]); 

	}
	for(loop1 = 1; loop1 <= landings; loop1++) {
		landing_array[loop1].thread_id_land = loop1;
		landing_array[loop1].thread_state_land = my_l_state;
		landing_array[loop1].thread_collision_land = my_l_collision;
		pthread_create(&lander[loop1], NULL, landing, (void *) &landing_array[loop1]);	
	}
	pthread_exit(NULL);
	return 0;
}
