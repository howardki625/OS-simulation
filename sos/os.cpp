#include <iostream>
#include <vector>
#include <queue>
#include "job.h"

using namespace std;

// global variables
vector<job> joblist; // a vector to store jobs coming from sos.

// function prototypes

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
}

//--------------------//
// interrupt handlers //
//--------------------//

void Crint(long &a, long p[])
{
    // indicates arrival of new job on drum.

    // push job onto joblist
    joblist.push_back(job(p[1], p[2], p[3], p[4], p[5]));
}

void Dskint(long &a, long p[])
{
    // disk interrupt.
}

void Drmint(long &a, long p[])
{
    // drum interrupt.
}

void Tro(long &a, long p[])
{
    // timer-run-out.
}

void Svc(long &a, long p[])
{
    // user program supervisor call.
}

//--------------------------//
// any additional functions //
//--------------------------//
