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
    long cpuUsedTime;
    long maxCpuTime;
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
        cpuUsedTime = 0;
        maxCpuTime = 0;
        ioPending = 0;
        priority = 0;
        blocked = false;
        latched = false;
        inCore = false;
        term = false;
    }

    // constructor with parameters from p[]
    job(long jobnum, long priority, long jobsize, long maxCpuTime, long entryTime)
    {
        this->jobnum = jobnum;
        this->jobsize = jobsize;
        this->entryTime = entryTime;
        cpuUsedTime = 0;
        this->maxCpuTime = maxCpuTime;
        ioPending = 0;
        this->priority = priority;
        blocked = false;
        latched = false;
        inCore = false;
        term = false;
    }

    // member functions
    long getjobnum()
    {
        return jobnum;
    }

    long getjobsize()
    {
        return jobsize;
    }

    long getEntryTime()
    {
        return entryTime;
    }

    long getCpuUsedTime()
    {
        return cpuUsedTime;
    }

    long getMaxCpuTime()
    {
        return maxCpuTime;
    }

    long getIOpending()
    {
        return ioPending;
    }

    long getPriority()
    {
        return priority;
    }

    bool isBlocked()
    {
        return blocked;
    }

    bool isLatched()
    {
        return latched;
    }

    bool isInCore()
    {
        return inCore;
    }

    bool isTerm()
    {
        return term;
    }

};

#endif // JOB_H
