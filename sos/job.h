#ifndef JOB_H
#define JOB_H
#include <iostream>
using namespace std;

// job class to store information received from sos.
class job
{
private:
    // job table information
    long jobnum;
    long jobsize;
    long entryTime;
    long cpuUsed;
    long maxCpu;
    long ioPending;
    long priority;
    bool blocked;
    bool latched;
    bool inCore;
    bool term;

public:
    // default constructor
    job()
    {
        jobnum = -1; // set to -1 to not interfere with any existing jobs.
        jobsize = 0;
        entryTime = 0;
        cpuUsed = 0;
        maxCpu = 0;
        ioPending = 0;
        priority = 0;
        blocked = false;
        latched = false;
        inCore = false;
        term = false;
    }

};

#endif // JOB_H
