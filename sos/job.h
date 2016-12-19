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
    bool inMemory;

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
        inMemory= false;
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
        inMemory= false;
    }

    // member functions to access the variables
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

    void setCpuUsedTime(long time)
    {
        this->cpuUsedTime = time;
    }

    long getMaxCpuTime()
    {
        return maxCpuTime;
    }

    long getIOpending()
    {
        return ioPending;
    }

    void setIOpending(long io)
    {
        this->ioPending = io;
    }

    long getPriority()
    {
        return priority;
    }

    bool isBlocked()
    {
        return blocked;
    }

    void setBlocked(bool flag)
    {
        this->blocked = flag;
    }

    bool isLatched()
    {
        return latched;
    }

    void setLatched(bool flag)
    {
        this->latched = flag;
    }

    bool isInCore()
    {
        return inCore;
    }

    void setInCore(bool flag)
    {
        this->inCore = flag;
    }

    bool isTerm()
    {
        return term;
    }

    void setTerm(bool flag)
    {
        this->term = flag;
    }
    bool isInMemory(bool flag)
    {
        return inMemory;
        
    }
    void setInMemory(bool flag)
    {
        this->inMemory = flag;
    }

    // Checks to find the first job not in core that can fit into core
    // loops thru the joblist and check if it fits criteria
    job findNextJob();

    // print function - for debugging use.
    void printInfo()
    {
        cout << "\nJob Info:";
        cout << "\nJob#: " << jobnum;
        cout << "\nSize: " << jobsize;
        cout << "\nTime arrived: " << entryTime;
        cout << "\nCPU time used: " << cpuUsedTime;
        cout << "\nMax CPU time: " << maxCpuTime;
        cout << "\nI/O Pending: " << ioPending;
        cout << "\nPriority: " << priority;
        cout << "\nBlocked: " << blocked;
        cout << "\nLatched: " << latched;
        cout << "\nIn Core: " << inCore;
        cout << "\nTerm: " << term;
        cout << "\n";
    }

};

#endif // JOB_H
