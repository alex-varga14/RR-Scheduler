// Author: Alexander Varga
// date: 01/12/2021
#include "round-robin-cpu.h"
#include "common.h"
#include <vector>

/* NOT FULLY OPTIMZED!!! THERE EXISTS BETTER ROUND ROBIN SCHEDULERS */
void simulate_rr(
    int64_t quantum, 
    int64_t max_seq_len,
    std::vector<Process> & processes,
    std::vector<int> & seq
) {
    seq.clear();
	//Variables to keep track of current state of the simulation 
	//Int to keep track of current time
	int64_t curr_time = 0;
	//Int to keep track of remaining time for slice
	int64_t remaining_slice = quantum;
	//job index
	int cpu = -1;
	//Ready queue, job queue, and remaining bursts vectors
	std::vector<int> rq, jq;
	std::vector<int64_t> remaining_bursts;
	
	//loop through processes and copy burst sizes and push jobs into queue
	for(auto i = 0; i < (int)processes.size(); i++)
	{
		remaining_bursts.push_back(processes[i].burst);
		jq.push_back(processes[i].id);
	}
	//set int as jobs size which will end up being the breaking factor for the loop as jobs are finished
	int jobs = jq.size();
	while(1)
	{
		//if all jobs are done break;
		if(jobs == 0) break;
		
		//if cpu not idle and remaining_bursts == 0 i.e cpu has process thats finished
		if(cpu != -1 && remaining_bursts[cpu] == 0)
		{
			//reset quantum
			remaining_slice = quantum;
			//set process finish time
			processes[cpu].finish_time = curr_time;
			//reset cpu as idle
			cpu = -1;
			//delete a job
			jobs--;
			//erase job from ready queue
			rq.erase(rq.begin());
			//check to see if all jobs are done
			if(jobs == 0) break;
		}
		//if cpu is not idle but slice is over
		if(cpu != -1 && remaining_slice == 0)
		{
			//push back current job onto ready queue
			rq.push_back(cpu);
			rq.erase(rq.begin());
			//set cpu to first job in rq
			cpu = rq.front();
			//check to see if job has already been worked on, if not set start time
			if(processes[cpu].start_time == -1)
			{
				processes[cpu].start_time = curr_time;
			}
			//reset quantum
			remaining_slice = quantum;
		}
		
		//loop through job queue
		for(int job : jq)
		{
			//if the current time is equal to an arrival time, push job onto ready queue
			if(curr_time == processes[job].arrival_time)
				rq.push_back(job);
		}
		//if cpu is idle but ready queue is not empty
		if(cpu == -1 && !rq.empty())
		{
			//assign cpu to first job in queue
			cpu = rq.front();
			//check to see if job has already been worked on, if not set start time
			if(processes[cpu].start_time == -1)
				processes[cpu].start_time = curr_time;
			//reset quantum
			remaining_slice = quantum;
		} 
		//if cpu not idle, perform time actions
		if(cpu != -1)
		{
			remaining_bursts[cpu]--;
			remaining_slice--;
		}
		//push back job into sequence if it is not the same as the previous pushed job and not exceeding max sequence length
		if ((seq.back() != cpu || seq.empty()) && (int)seq.size() < max_seq_len) 
			seq.push_back(cpu);
		curr_time++;
	}
}