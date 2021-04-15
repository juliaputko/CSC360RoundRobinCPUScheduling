#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include <math.h>

#define MAX_BUFFER_LEN 80

taskval_t *event_list = NULL;	//contains tasks loaded in from command line

void print_task(taskval_t *t, void *arg) {
    printf("id=%05d req=%.2f used= %.2f\n",
        t->id,
        t->cpu_request,
        t->cpu_used
    );  
}

void print_task_exit(taskval_t *t, void *arg){
    printf("id=%05d EXIT w=%.2f ta=%.2f\n",
		    t->id,((t->finish_time - t->arrival_time) - t->cpu_request)-1, 
		    (double)(t->finish_time - t->arrival_time)-1);
}

void increment_count(taskval_t *t, void *arg) {
    int *ip;
    ip = (int *)arg;
    (*ip)++;
}



void run_simulation(int qlen, int dlen) {
    //taskval_t *ready_q = NULL;		//holding queued tasks
	
    taskval_t *ready_q = NULL; //** note : moving a task from the incoming event 
    int tick = 0;
    int is_end = 0; 	//changed to 1 if we have reached the end of our event_list
    int is_endq = 0;	//changed to 1 if we have reached the end of our readyq, still dunno if its relevant we'll see i guess
    int exited = 0;
    int leftover = 0;
    int go_back_top = 0;
   // int new;
    taskval_t *front = NULL;
    taskval_t *temp = NULL;
    taskval_t *run = NULL; 
    taskval_t *rem = NULL; 
    taskval_t *left =NULL;
    taskval_t *temp2 = NULL;

    

    for (;;){ //keep checking if a task has arrived and put it on the ready queue 
      
	if (qlen ==0){
		break; 		//to avoid infinite loop
	}
	    // front = peek_front(event_list);
       	front = peek_front(event_list);
	
	if (front == NULL && ready_q == NULL|| is_end == 1 && ready_q == NULL){ //event list is empty
		break; 
	}
        for(;;){ //keep doing this until there are no more arrived tasks on the event list 
            front = peek_front(event_list);
	    if (front ==NULL || is_end == 1){ //front == NULL: nothing more on the event list, break and check the ready queue
                break;
            }
	    
            else if (front->arrival_time <= tick){ //task has arrived, we can add it to the readyq
             //	front = peek_front(event_list);
	     //	new = 0;
	  //     	printf("im here\n");
		temp = event_list;
		if (event_list->next != NULL){
			event_list = event_list->next;
			
		}
		else{
			is_end = 1; //we've reached the end of the event_list
		}
		temp = peek_front(temp);
		ready_q = add_end(ready_q, temp);
	

		temp = NULL;
		front = peek_front(event_list);

		if(leftover == 1){
			ready_q = add_end(ready_q, left);
			left = NULL;
			leftover = 0;
		}
	
	
            }
	    else if (leftover == 1){
	    	//there was something leftover from another run that we have to add to the ready_q too  
		ready_q = add_end(ready_q, left);
		
		left == NULL;
		leftover = 0; //set back to default
	    }
			
	  
            else{  // arrival time > tick, so no task on the event list have arrived yet,  break and check the ready queue
	//	printf("arrival time not there yet\n");
		break;
            }//end else
        }//end inner infinite for 
        //now we have something on the ready_q hopefully 
	
        run = peek_front(ready_q);
	
	if (run != NULL){

       //	if (run != NULL){ //something to run 
		is_endq = 0; //make sure is set to 0, aka nothing has exited 	
           // so lets run it
        	for (int i = 0; i<dlen; i++){
        		printf("[%05d] ", tick);
                	tick++;
                	printf("DISPATCHING\n");
		}

		for (int l = 0; l<qlen;l++){//will break either when we reach the end of quantum or we exit and break 
			printf("[%05d] ", tick);
                	tick++;                 
                
                	if ((ceil)(run->cpu_request) - run->cpu_used == 0 ){    //we have reached the end exit and break out of for loop 
			//none left over, exit 
                        	run->finish_time = tick;
                        //	tick++; no tick increment for exit
				tick = tick-1;
                        	print_task_exit(run, NULL);
				
                        	is_endq= 1;
                        	break; 		//where does it go, do I have to add a condition to skip the enxt bit? 
                	}	
                	print_task(run, NULL);
                	run->cpu_used++;
		} // end qlen for loop
		

	    //make sure exit hasnt happened 
		if (is_endq != 1){
		//something is left over --> deal with it  
        		if (run->next != NULL){	
		//		printf("add to the end of a nonempty list \n");
		    		rem = run;
                    		run = run->next;  //if it's not NULL, can run the next thing in the readyq
                    		run = add_end(run, rem); 
		    		ready_q = run;    //next thing in ready_q will be run
		    		rem = NULL; 
            		}//end if   

			else{
				leftover = 1;
				left = run;
				run = remove_front(run);
				ready_q = run;
			}//end else
//check again if something has come into the event list 


	    	}//end if check

							//if it has exited should we remove the front
		else{ 				//is _end1 == 1 which means we have exited, so I dont think we need this  	 
			run = remove_front(run);	 //remove what we just ran 
			ready_q = run; 			//now ready_q is just null
	    
		}	 
							//go back to the top and test 
	     //	new = 1; 
		front = peek_front(event_list);
		// front = peek_front(event_list);// make sure nothing has come in
		/////copy and past event_list check

//		if (front->arrival_time <= tick){
			
 
    	}//end if run != NULL
	else{ // (run ==NULL){// run does == NULL 
	
	  	printf("[%05d] ", tick);
                tick++;
                printf("IDLE\n");;
	}//end check if run == NULL

			//else{ //run  == NULL,nothing in the readyQ, 
			//sim is idle  idle until something else is ready on the event list 
			//nothing on the ready queue to run, so we hae to wait until our ticks increase 
        		//we will go back up to the for loop and 
        
    }//end outer for loop
}


int main(int argc, char *argv[]) {
    char   input_line[MAX_BUFFER_LEN];
    int    i;
    int    task_num;
    int    task_arrival;
    float  task_cpu;
    int    quantum_length = -1;
    int    dispatch_length = -1;

    taskval_t *temp_task;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--quantum") == 0 && i+1 < argc) {
            quantum_length = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "--dispatch") == 0 && i+1 < argc) {
            dispatch_length = atoi(argv[i+1]);
        }
    }

    if (quantum_length == -1 || dispatch_length == -1) {
        fprintf(stderr, 
            "usage: %s --quantum <num> --dispatch <num>\n",
            argv[0]);
        exit(1);
    }


    while(fgets(input_line, MAX_BUFFER_LEN, stdin)) {
        sscanf(input_line, "%d %d %f", &task_num, &task_arrival,
            &task_cpu);
        temp_task = new_task();
        temp_task->id = task_num;
        temp_task->arrival_time = task_arrival;
        temp_task->cpu_request = task_cpu;
        temp_task->cpu_used = 0.0;
        event_list = add_end(event_list, temp_task);
    }

#ifdef DEBUG
    int num_events;
    apply(event_list, increment_count, &num_events);
    printf("DEBUG: # of events read into list -- %d\n", num_events);
    printf("DEBUG: value of quantum length -- %d\n", quantum_length);
    printf("DEBUG: value of dispatch length -- %d\n", dispatch_length);
#endif

    run_simulation(quantum_length, dispatch_length);

    return (0);
}
