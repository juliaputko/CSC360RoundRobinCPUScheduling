# Julia Putko V00889506
## Description of makegraphs.py
* used python and matplotlib to create graph
### Calculations
* for every quantum length given 
    * for each quantum loop through every dispatch length 
        * do the following:
        * open the file which contains the output from rrsim.c 
        * read it line by line 
        * for each line:
        * gather the waiting time and turnaround time given at each EXIT line 
        * add the waiting time to previously gathered waiting times 
        * add the turnaround time to previously gathered turnaround times 
        * reset variable to 0 so that previous variables stored there are erased 
        for the next iteration of the loop
        * go to the next dispatch length for this quantum length until we are done with all the dispatch lengths 
        * once we are done with all the dispatch length we go on to the next quantum length and loop through all 
        the dispatch lengths with that quantum 
        * repeat until we are done with all the quantum lengths 
* once we have looped through the 20 combinations of quantum lengths and dispatch lengths:
    * calculate the average wait time and the average turnaround time by dividing the total 
    wait time and the total turnaround time by the number of tasks 
### Building graphs 
* created 2 subplots 
* assigned values for x and y axis 
* create plots on graph by grouping together avgerage wait times into groups of 6:
    * first 6 numbers create point at dispatch 0 
    * next 6 create point at dispatch 5
    * etc. 
* same idea for turnaround time graph 

## Problems encountered
    * labels on the y axis did not show up on the graph produced
    * labels for each quantum length were put in but did not appear in graph produced
## Probems encountered in rrsim.c
* unable to find a way for program to check if anything new was ready to be put on the 
ready_q from the event_list when ticks increased, especially when previous task has leftovers, because program put leftovers on the ready_q immediately, and then when tasks were being run, the loop did not stop to check the event_list in between running tasks on ready_q queue:

* possible ways to fix this: add event_list check in between runs on ready_q (tried this but caused program to go into infinite loop) 
* have program only run 1 thing on the ready_q at a time, and then go back up and check the event_list -- this would require major tweaking of my current program, and unfortunately I ran out of time  
