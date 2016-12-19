#include <iostream>
#include <vector>
#include <queue>
#include "job.h"
#include "memory.h"

using namespace std;

// global variables
vector<job> joblist; // a vector to store jobs coming from sos.
long runningJob; // holds the location of the running job on the vector.
memory memory; // create the memory
queue<long>ioQueue;
long doingio; // holds the number for the job that is currently doing I/O

// findNextJob function definition
job job::findNextJob(){
    vector<job>::iterator it;
    for(it=joblist.begin();it<joblist.end();++it){
        if(memory.findfreespace(*it.getjobsize())!=-1&&!*it.isInCore()){
            return *it;
        }
    }
return NULL;
}

// function prototypes
void bookkeeper(long); // book keeping function - keeps track of time.

// channel commands from the simulator.
void siodisk(long jobnum);
void siodrum(long jobnum, long jobsize, long coreaddress, long direction);
    // direction: 1 - core to drum, 0 - drum to core.

// for debugging use.
void ontrace();
void offtrace();

void startup()
{
    // initializes the system.
    // called once at startup.
    ontrace();
    runningJob = -1; // initialize at -1 == no job running since joblist[0] can have a job in it.
    doingio= -1; 
}

//--------------------//
// interrupt handlers //
//--------------------//

void Crint(long &a, long p[])
{
    // indicates arrival of new job on drum.

    bookkeeper(p[5]); // updates the time.

    // push job onto joblist
    joblist.push_back(job(p[1], p[2], p[3], p[4], p[5]));
}

void Dskint(long &a, long p[])
{
     // The disk has finished an I/O operation. I/O has been finished for job at top of I/O queue.
    getJob();
    bookkeeper(p[5]); // updates the current time
    ioQueue.pop(); // remove job from the queue
    joblist[doingio].setIOpending(joblist[doingio].getIOpending()-1); // decrement the amount of pending jobs.

    if(!joblist[doingio].getIOpending()){ // if there is no more pending io
        joblist[doingio].setLatched(false); // unlatch
        joblist[doingio].setBlocked(false); // unblock

        if(joblist[doingio].isTerm()){ // erases job from memory
            memory.removejob(joblist[doingio].getLocation());
            joblist.erase(joblist.begin()+ doingio);
        }
    }

    if(!ioQueue.empty()){ // if there aren't anymore jobs in the io queue
    getJob();
    siodisk(joblist[doingio].getjobnum());
    }
    
    startJob(a,p);
    return;
    
}

void Drmint(long &a, long p[])
{
    // drum interrupt.
    a=1;
    bookkeeper(p[5]);
    scheduler(&a, p[], false, false);
    a=2;
    return;
}

void Tro(long &a, long p[])
{
    a=1;
    bookkeeper(p[5]);
    scheduler(&a, p[], true, false);
    a=2;
    return;
}

void Svc(long &a, long p[])
{
    bookkeeper(p[5]); //bookmark current time
    if(a==5){ //There is a request to terminate
        if(!joblist[runningJob].getIOpending())
            {//If there is no pending io operations, then terminate the running job
            joblist[runningJob].setTerm(true); // Terminates the running job

            } 
            }else if (a==6){ // requesting another disk io operation
            if(ioQueue.empty())
                { // if the queue is empty
                    siodisk(joblist[runningJob].getjobnum()); // get the job number from sos
                    ioQueue.push(joblist[runningJob].getjobnum()); // adds job number to the queue
                }
            }else if (a==7){ // request to block
                if(joblist[runningJob].ioPending()){ // if there is pending io for the running job
                        joblist[runningJob].setBlocked(true);

                }
            }
    
    }
    // user program supervisor call.
}
//Dispatcher
void startJob(long &a, long p[])
{
    if(!joblist[runningJob].isInMemory() || joblist[runningJob].isBlocked()){ // cannot run job if not in memory or if job is blocked
        a = 1;
        return;
    } else{
    
    a=2;
    p[2]= joblist[runningJob].getLocation();
    p[3]= joblist[runningJob].getjobsize();
    p[4]= joblist[runningJob].getMaxCpuTime();
    joblist[runningJob].setEntryTime(p[5]);
    joblist[runningJob].setInCore(true);
    }
    return;
}
void getJob()
{
     for(long i=0; i < joblist.size(); i++){ // get the job index
        if(joblist[i].getjobnum()== ioQueue.front())
            runningJob= i;
    }
}

//--------------------------//
// any additional functions //
//--------------------------//

void bookkeeper(long time)
{
    // keeps track of time for the currently running job
    // called before every interrupt to update the timer.
    if (runningJob != -1)
    {
        // updates the CPU used time using the current time and the time the job entered the system.
        long t;
        t = time - joblist[runningJob].getEntryTime();
        joblist[runningJob].setCpuUsedTime(t);
    }
}

void scheduler(long &a, long p[], bool rem, bool kill){

    // removes finished jobs from memory and terminates the running job if expired/asked
    if(rem){
        swapper(runningjob, memory.findjob(runningjob.getjobnum()), 1);
        if(runningjob.getCpuUsedTime()==runningjob.getMaxCpuTime()||kill){
            runningjob.setTerm(true);
        }
    }

    // next job to run
    long torun;
    torun=memory.roundrobin();
    vector<job>::iterator it;
    for(it=joblist.begin();it<joblist.end();++it){
            if(*it.getjobnum()==torun){
                    p[2]=memory.findjob(torun);
                    p[3]=*it.getjobsize();
                    p[4]=3;
            }
    }

    // moves jobs from drum to memory, repeating if there's enough space
    bool repeat=true;
    while(repeat){
        job toMem = joblist.findNextJob();
        if(toMem!=NULL){
            swapper(toMem, memory.findfreespace(toMem.getjobsize()), 0);
        }
        else repeat=false;
    }

    return;
}

// moves jobs from core to drum and from drum to core, depending on direction
void swapper(job swapjob, long address, long direction){
    vector<job>::iterator it;
    for(it=joblist.begin();it<joblist.end();++it){
            if(*it.getjobnum()==swapjob.getjobnum()){
                if(direction==0) {
                        *it.setInCore(true);
                        memory.addjob(swapjob.getjobnum(), swapjob.getjobsize);
                }
                else if(direction==1) {
                        *it.setInCore(false);
                        memory.removejob(swapjob.getjobnum());
                }
                break;
            }
    }
    siodrum(swapjob.getjobnum(), swapjob.getjobsize(), address, direction);
    return;
}
