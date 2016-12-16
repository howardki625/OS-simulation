#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
using namespace std;

// representation of the memory
// 0 = free space
// # = jobnum
class memory
{
private:
    // memory is an array of size 100
    // each box of the array is 1k of addresses
    // each box of the array has the number of the job that is taking up the address
    long mem[100];
    long roundrobinlong=0;

public:
    // constructor
    // goes thru all the addresses and set them all to 0
    // to show that they are not in use since job# starts at 1
    FST()
    {
        for (long i=0; i<100; i++)
        {
            mem[i] = 0;
        }
    }

    // resets the memory if needed to for whatever reason
    void resetmem()
    {
        for (long i=0; i<100; i++)
        {
            mem[i] = 0;
        }
    }

    // given the starting address of a free space
    // see if a job can fit into it
    bool jobfits(long address, long jobsize)
    {
        // looping thru the addresses
        // if the address is free, add 1 to freespace counter
        long freespace = 0;
        for (long i=address; i<address+jobsize; i++)
        {
            if (mem[i] == 0)
            {
                freespace++;
            }
        }
        // if the # of freespace >= job size, return true
        // else return false
        bool fits = false;
        if (freespace >= jobsize)
        {
            fits = true;
        }

        return fits;
    }

    // find a freespace that fits the jobsize
    // returns the starting address of that space
    long findfreespace(long jobsize)
    {
        long address = -1;  // initialize the address to -1 to indicate no freespace available
        for (long i=0; i<100-jobsize; i++)
        {
            if (jobfits(mem[i], jobsize))
            {
                address = i;
            }
        }

        return address;
    }

    // add a job
    void addjob(long jobnum, long jobsize)
    {
        // look for a freespace
        long address = findfreespace(jobsize);
        // if there is freespace, add the job
        if (address != -1)
        {
            // from starting address to the size of the job
            // change the array to reflect the job that is using the memory
            for (long i=address; address<address+jobsize; i++)
            {
                if (mem[i] != 0)
                {
                    // another layer of insurance to protect the other jobs
                    // mostly for debugging use
                    cout<< "ERROR!! WRITING ONTO ANOTHER JOB!!!\n";
                } else
                {
                    mem[i] = jobnum;
                }
            }
        }
        return;
    }

    // remove a job
    // goes through memory and for each block of address associated with that job
    // change the job number to 0 to indicate that there is no job there
    void removejob(long jobnum)
    {
        for (long i=0; i<100; i++)
        {
            if (mem[i] == jobnum)
            {
                mem[i] = 0;
            }
        }
    }

    // find the starting address of a job
    long findjob(long jobnum)
    {
        bool found = false;
        long address = -1;
        for (long i=0; i<100; i++)
        {
            if (mem[i] == jobnum && found == false)
            {
                found = true;   // we don't want the starting address to get overwritten
                address = i;
            }
        }
        return address;
    }

    // Determine next job to run through round robin
    // returns jobnum
    long roundrobin()
    {
        long i=roundrobinlong;
        ++roundrobinlong;
        while(roundrobinlong!=i){
            if(mem[roundrobinlong]!=0) return roundrobinlong;
            if(roundrobinlong!=99) ++roundrobinlong
            else roundrobinlong=0;
        }
        return 0;
    }

};

#endif // MEMORY_H
