import matplotlib.pyplot as plt
import re 
import sys
import numpy as np

#Round Robin sceduler -- #tasks: 1000; seed value: 3141
#average waiting time  y axis 2000000 250000 3000000 350000 4000000 450000
#dispatch overhead x axis 0 5 15 20 25


#Round Robin sceduler -- #tasks: 1000; seed value: 3141
#average turnaround time 2000000 250000 3000000 350000 4000000 450000
#dispatch overhead x axis 0 5 15 20 25
    

def main():


    tasks = float(sys.argv[1])
    quantum = [50, 100, 250, 500]
    dispatch = [0, 5, 10, 15, 20, 25]
    find = []
    totalwait = []  
    totalturn = []
    wait50 = []
    wait100 = []
    wait250 = []
    wait500 = []
    turn50 = []
    turn100 = []
    turn250 = []
    turn500 = []

    for q in quantum:
        for d in dispatch:
            
            with open('outputq50d0.txt',encoding ="utf8", errors='ignore') as f:
                file = f.read()
            #file = open('outputq50d0.txt' , 'r')

            total_waittime = 0
            total_turnaround = 0

            for line in file:
                if 'EXIT' in line: 
                    find = re.findall(r"\d+\.\d+", line)
                    w = find[0]
                    ta = find[1]
                    total_waittime += float(w)
                    total_turnaround += float(ta)
                    w = 0
                    ta =0
            
            f.close()

            avg_waittime = total_waittime/tasks
            avg_turnaround = total_turnaround/tasks

            #totals.append[avg_waittime, avg_turnaround]
            totalwait.append([avg_waittime])
            totalturn.append([avg_turnaround])

            avg_turnaround = 0
            avg_waittime = 0



    fig,(totalw,totalt) = plt.subplots(2)

    #make graphs
    totalw.set_title('Round robin scheduler -- # tasks: 1000;seed value:3141')

    x = [0, 5, 10, 15, 20, 25]
    y = [2000000, 250000, 3000000, 350000, 4000000, 450000]
    #totalwait
   # totalw.ylabel('Average waiting time')
   # totalw.xlabel('Dispatch overhead')
    totalw.set_xticks(x)
    totalw.set_yticks(y)

    
    for avg_waittime in range(0,6):
        wait50.append([avg_waittime])
    
    totalw.plot(x, wait50, label = "q=50")
    
    for avg_waittime in range(6,12):
       wait100.append([avg_waittime])
    
    totalw.plot(x, wait100, label = "q=100")
   
    for avg_waittime in range(12,18):
        wait250.append([avg_waittime])
    
    totalw.plot(x, wait250, label = "q=250")
   
    for avg_waittime in range(18,24):
        wait500.append([avg_waittime])
   
    totalw.plot(x, wait500, label = "q=500")

    totalw.set_ylabel('Average waiting time')
    totalw.set_xlabel('Dispatch overhead')

#totalturn 

    #graph 2 
    totalt.set_title('Round robin scheduler -- # tasks: 1000;seed value:3141')
    
  #  y = np.array([0, 5, 10, 15, 20, 25])
   # x = np.array([2000000, 250000, 3000000, 350000, 4000000, 450000])
    totalt.set_ylabel('Average turnaround time')
    totalt.set_xlabel('Dispatch overhead')
    totalt.set_xticks(x)
    totalt.set_yticks((2000000, 250000, 3000000, 350000, 4000000, 450000))


    for avg_waittime in range(0,6):
        turn50.append([avg_waittime])
    
    totalt.plot(x, turn50, label = "q=50")
    
    for avg_waittime in range(6,12):
       turn100.append([avg_waittime])
    
    totalt.plot(x, turn100, label = "q=100")
   
    for avg_waittime in range(12,18):
        turn250.append([avg_waittime])
    
    totalt.plot(x, turn250, label = "q=250")
   
    for avg_waittime in range(18,24):
        turn500.append([avg_waittime])
   
    totalt.plot(x, turn500, label = "q=500")
 
    #save both graphs to files
    plt.tight_layout()
    plt.show()

    plt.savefig("graph_waiting.pdf")

if __name__ == '__main__':
	main()
