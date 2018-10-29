# CPU-Scheduling-SJF-FCFS-MLFG-
#include "process.h"
#include <queue>
#include <iomanip>
#include <fstream>
#include <xiosbase>
#include <iostream>
#include <ios>
using namespace std;

void exFCFS(vector<Process>);
void SJF(vector<Process>);
void MLFQ(vector<Process>);

deque<Process>initReadyQueue(vector<Process>);

void readyToRunning(deque<Process> &, Process &);
void readyToRunning(vector<Process> &, Process &);
void minSort(vector <Process>&);
int minInsert(vector<Process>&, Process);
void ioVecAge(deque<Process> &, vector<Process> &, int);
void ioVecAge(vector<Process> &, vector<Process> &, int);
void ioVecAge(vector<Process> &, vector<Process> &, vector<Process> &, vector<Process> &, int);
void ageRunning(Process &, vector<Process> &, vector<Process> &, deque<Process>, int);
void ageRunning(Process &, vector<Process> &, vector<Process> &, vector<Process>, int);
void ageRunning(Process &, vector<Process> &, vector<Process> &, vector<Process>, vector<Process> &,vector<Process> &, int &, int);
void PrintCSStatsFCFS(deque<Process>, vector<Process>, vector<Process>, Process, int);
void PrintCSStatsSJF(vector<Process>, vector<Process>, vector<Process>, Process, int);
void PrintCSMLFQ(vector<Process>, vector<Process>, vector<Process>,vector<Process>, vector<Process>, Process, int);

int preempt(Process &, vector<Process> &, vector<Process> &, int);
void printStatsSJF(vector<Process>, int);


inline void exFCFS(vector<Process> ReadyVec)
{
	deque<Process> Ready = initReadyQueue(ReadyVec);
	
	vector<Process> IoVec,fin;
	Process Running;
	int currentTime = 0;

	Running = Ready.front();
	Ready.pop_front();
	Running.editStatus('R');

	while (fin.size() != ReadyVec.size())
	{
		if (!IoVec.empty())
		{
			ioVecAge(Ready, IoVec, currentTime);
		}
		if (Running.getStatus() == 'N'&& Ready.size() != 0)
		{
			readyToRunning(Ready, Running);
		}
		if (Running.getStatus() == 'R')
		{
			for (deque<Process>::iterator i = Ready.begin(); i != Ready.end() ; i++)
			{
				i->AgeProcess(currentTime);
			}
			ageRunning(Running, IoVec, fin, Ready, currentTime);

		}
		currentTime++;
	}
	printStatsSJF(fin, currentTime);
}

inline void SJF(vector<Process> ReadyVec)
{
	vector<Process> Ready = ReadyVec;
	vector<Process> IoVec;
	vector<Process> fin;
	
	Process Running;
	int currentTime = 0;
	minSort(Ready);
	Ready[Ready.size() - 1].editStatus('R');
	Running = Ready[Ready.size() - 1];
	Ready.pop_back();

	while (fin.size() < ReadyVec.size())
	{
		if (!IoVec.empty())
		{
			ioVecAge(Ready, IoVec, currentTime);
		}
		if (Running.getStatus() == 'N' && Ready.size() != 0)
		{
			readyToRunning(Ready, Running);
		}
		if (Running.getStatus() == 'R')
		{
			for (vector<Process>::iterator i = Ready.begin(); i != Ready.end(); i++)
			{
				i->AgeProcess(currentTime);
			}
			ageRunning(Running, IoVec, fin, Ready, currentTime);
		}
		currentTime++;
	}
	cout << "SJF\n---\n";
	printStatsSJF(fin, currentTime);
}



inline deque<Process>initReadyQueue(vector<Process> ReadyVec)
{
	deque<Process> Ready;
	for (int i = 0; i < ReadyVec.size(); i++)
	{
		Ready.push_back(ReadyVec[i]);
	}
	return Ready;
}

inline void readyToRunning(deque<Process> &Ready, Process &Running)
{
	Running = Ready.front();
	Running.editStatus('R');
	Ready.pop_front();
}

inline void readyToRunning(vector<Process> &Ready, Process &Running)
{
	Running = Ready[Ready.size() - 1];
	Running.editStatus('R');
	Ready.pop_back();
}

inline void minSort(vector<Process> &sJFQ)
{
	for (int j = 0; j < 0; j++)
	{
		for (unsigned int i = 0; i < sJFQ.size() - 1; i++)
		{
			if (sJFQ[i].getCpuBurst() <= sJFQ[i + 1].getCpuBurst())
			{
				Process temp = sJFQ[i];
				sJFQ[i] = sJFQ[i + 1];
				sJFQ[i + 1] = temp;
			}
		}
	}
}

inline int minInsert(vector<Process> &sJFQ, Process insert)
{
	int flag = 0;
	int j = 0;
	for (int i = 0; i < sJFQ.size(); i++)
	{
		if (sJFQ[i].getCpuBurst() <= insert.getCpuBurst())
		{
			sJFQ.insert(sJFQ.begin() + i, insert);
			flag = 1;
			return 0;
		}
	}
	if (flag == 0)
	{
		sJFQ.push_back(insert);
	}
	return 0;
}

inline void ageRunning(Process &Running, vector<Process> &IoVec, vector<Process> &fin, deque<Process> Ready, int currentTime)
{
	int contextOrReady = 0;
	contextOrReady = Running.AgeProcess(currentTime);
	switch (contextOrReady)
	{
	case 1:
		PrintCSStatsFCFS(Ready, IoVec, fin, Running, currentTime);
	case 3:
		Running.editStatus('F');
		Running.popCpuBurst();
		fin.push_back(Running);
		Running.editStatus('N');
		break;
	default:
		break;
	}
}

inline void ageRunning(Process &Running, vector<Process> &IoVec, vector<Process> &fin, vector<Process> Ready, int currentTime)
{
	int contextOrReady = 0;
	contextOrReady = Running.AgeProcess(currentTime);
	switch (contextOrReady)
	{
	case 1:
		PrintCSStatsSJF(Ready, IoVec, fin, Running, currentTime);
		Running.editStatus('I');
		Running.popCpuBurst();
		IoVec.push_back(Running);
		Running.editStatus('N');
		break;
	case 3:
		Running.editStatus('F');
		Running.popCpuBurst();
		fin.push_back(Running);
		Running.editStatus('N');
		break;
	default:
		break;

	}

}

inline void ageRunning(Process &Running, vector<Process> &IoVec, vector<Process>&fin, vector<Process>readyRR1, vector<Process>&readyRR2, vector<Process>&readyFCFS, int &tq, int currentTime)
{
	int contextOrReady = 0;
	contextOrReady = Running.AgeProcess(currentTime);
	if (contextOrReady == 1)
	{
		Running.popCpuBurst();
		PrintCSMLFQ(readyRR1, readyRR2, readyFCFS, IoVec, fin, Running, currentTime);
		Running.editStatus('I');
		IoVec.push_back(Running);
		Running.editStatus('N');
	}
	else if (contextOrReady == 0 && (tq = 1) == 0)
	{
		Running.incrementPStatus();
		Running.editStatus('W');
		Running.decrementWaitTime();
		if (Running.getPStatus() == 2)
		{
			readyRR2.insert(readyRR2.end(), Running);

		}
		else if (Running.getPStatus() == 3)
		{
			readyFCFS.insert(readyFCFS.end(), Running);
		}
		Running.editStatus('N');
	}
	else if (contextOrReady == 3)
	{
		Running.popCpuBurst();
		Running.editStatus('F');
		fin.push_back(Running);
		Running.editStatus('N');
	}
	else if (tq != 0 && contextOrReady == 0)
	{
		tq--;
	}
}
inline void MLFQ(vector<Process> ReadyVec)
{
	vector<Process> readyRR1 = ReadyVec;
	vector<Process> readyRR2;
	vector<Process> readyFCFS;
	vector<Process> IoVec;
	vector<Process> fin;

	Process Running;
	int tq = 0, currentTime = 0, contextOrReady = 0;
	tq = 6;
	Running = readyRR1[0];
	Running.editStatus('R');
	readyRR1.erase(readyRR1.begin());

	while (fin.size() != ReadyVec.size())
	{
		if (!IoVec.empty())
		{
			ioVecAge(readyRR1, readyRR2, readyFCFS, IoVec, currentTime);
		}
		if (Running.getStatus() == 'N')
		{
			if (readyRR1.size() != 0)
			{
				readyRR1[0].editStatus('R');
				Running = readyRR1[0];
				readyRR1.erase(readyRR1.begin());
				tq = 6;
			}
			else if (readyRR2.size() != 0)
			{
				readyRR2[0].editStatus('R');
				Running = readyRR2[0];
				readyRR2.erase(readyRR2.begin());
				tq = 11;
			}
			else if (readyFCFS.size() != 0)
			{
				readyFCFS[0].editStatus('R');
				Running = readyFCFS[0];
				readyFCFS.erase(readyFCFS.begin());
			}
		}
		if (Running.getStatus() != 'N')
		{
			switch (Running.getPStatus())
			{
			case 1:
				ageRunning(Running, IoVec, fin, readyRR1, readyRR2, readyFCFS, tq, currentTime);
				break;
			case 2:
				if (readyRR1.size() != 0)
				{
					tq = preempt(Running, readyRR1, readyRR2, 6);
					ageRunning(Running, IoVec, fin, readyRR1, readyRR2, readyFCFS, tq, currentTime);
				}
				else
				{
					ageRunning(Running, IoVec, fin, readyRR1, readyRR2, readyFCFS, tq, currentTime);
				}
				break;
			case 3:
				if (readyRR1.size() != 0)
				{
					tq = preempt(Running, readyRR1, readyFCFS, 6);
					ageRunning(Running, IoVec, fin, readyRR1, readyRR2, readyFCFS, tq, currentTime);
				}
				else if (readyRR2.size() != 0)
				{
					tq = preempt(Running, readyRR2, readyFCFS, 11);
					ageRunning(Running, IoVec, fin, readyRR1, readyRR2, readyFCFS, tq, currentTime);
				}
				else
				{
					tq = 23;
					ageRunning(Running, IoVec, fin, readyRR1, readyRR2, readyFCFS, tq, currentTime);
				}
				break;
			default:
				break;
			}

		}

		for (int i = 0; i < readyRR1.size(); i++)
		{
			readyRR1[i].AgeProcess(currentTime);
		}
		for (int i = 0; i < readyRR2.size(); i++)
		{
			readyRR2[i].AgeProcess(currentTime);
		}
		for (int i = 0; i < readyFCFS.size(); i++)
		{
			readyFCFS[i].AgeProcess(currentTime);
		}
		currentTime++;


		cout << "MLFQ\n---\n";
		printStatsSJF(fin, currentTime);
	}
}

inline void ioVecAge(vector<Process> &Ready, vector<Process> &IoVec, int currentTime)
{
	int ioFlag = 0, index = 0;

	while (index < IoVec.size())
	{
		ioFlag = IoVec[index].AgeProcess(currentTime);
		if (ioFlag == 2)
		{
			IoVec[index].editStatus('W');
			IoVec[index].popIoBurst();
			minInsert(Ready, IoVec[index]);
			IoVec.erase(IoVec.begin() + index);
		}
		else
		{
			index++;
		}
		ioFlag = 0;
	}
}

inline void ioVecAge(deque<Process> &Ready, vector<Process> &IoVec, int currentTime)
{
	int ioFlag = 0, index = 0;
	
	while (index < IoVec.size())
	{
		ioFlag = IoVec[index].AgeProcess(currentTime);
		if (ioFlag == 2)
		{
			IoVec[index].editStatus('W');
			IoVec[index].popIoBurst();
			Ready.push_back(IoVec[index]);
			IoVec.erase(IoVec.begin() + index);
		}
		else
		{
			index++;
		}
		ioFlag = 0;
	}
}

inline void ioVecAge(vector<Process> &readyRR1, vector<Process> &readyRR2, vector<Process> &readyFCFS, vector<Process> &IoVec, int currentTime)
{
	int index = 0, ioFlag;

	while (index < IoVec.size())
	{
		ioFlag = IoVec[index].AgeProcess(currentTime);
		if (ioFlag == 2)
		{
			IoVec[index].editStatus('W');
			IoVec[index].popIoBurst();
			if (IoVec[index].getPStatus() == 1)
			{
				readyRR1.push_back(IoVec[index]);
			}
			else if (IoVec[index].getPStatus() == 2)
			{
				readyRR2.push_back(IoVec[index]);
			}
			else if (IoVec[index].getPStatus() == 3)
			{
				readyFCFS.push_back(IoVec[index]);
			}
			IoVec.erase(IoVec.begin() + index);
		}
		else
		{
			index++;
		}
		ioFlag = 0;

	}
}

inline void PrintCSStatsSJF(vector<Process> Ready, vector<Process> ioVec, vector<Process> fin, Process Running, int currentTime)
{
	ofstream output;
	output.open("output.txt", ios_base::app);
	output << "[SJF] Current Time is [" << currentTime << "]\n";
	output << "[Running Process is " << Running.getName() << "]\n-------------------------------------\nProcesses in Ready list\n---------------------\n";
	for (int i = Ready.size(); i > 0; i--)
	{
		output << "Process  " << Ready[i - 1].getName() << "; [CPU Burst Time] = " << Ready[i - 1].getCpuBurst() << "\n";
	}
	output << "-----------------\nProcesses in I/O-------------------\n";
	for (int i = 0; i < ioVec.size(); i++)
	{
		output << "Process " << ioVec[i].getName() << "; [I/O Burst Time] = " << ioVec[i].getIOBurst() << "\n";
	}
	output << "---------------------\nFinished Processes\n--------------------------\n";
	for (int i = 0; i < fin.size(); i++)
	{
		cout << "Process " << fin[i].getName() << "\n";
	}
	cout << "\n\n--------------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "Current Time is " << currentTime << "\n";
	cout << "[Running Process is " << Running.getName() << "]\n----------------------------------\nProcesses in Ready list\n----------------\n";
	for (int i = Ready.size(); i > 0; i--)
	{
		cout << "Process " << Ready[i - 1].getName() << "; [CPU Burst Time] = " << Ready[i - 1].getCpuBurst() << "\n";
	}
	cout << "--------------\nProcesses in I/O\n----------------\n";
	for (int i = 0; i < ioVec.size(); i++)
	{
		cout << "Process " << ioVec[i].getName() << "; [I/O Burst TIme] = " << ioVec[i].getIOBurst() << "\n";
	}
	cout << "--------------\n Finished Processes\n-------------------------------------\n";

	for (int i = 0; i < fin.size(); i++)
	{
		cout << "Process " << fin[i].getName() << "\n";
	}
	cout << "\n\n-------------------------------------------------------------------------------------------------------\n";								
}

inline void PrintCSStatsFCFS(deque<Process> Ready, vector<Process> ioVec, vector<Process> fin, Process Running, int currentTime)
{
	ofstream output;
	output.open("output.txt", ios_base::app);
	output << "[FCFS] Current Time is [" << currentTime << "]\n";
	output << "[Running Process is " << Running.getName() << "] \n------------------\nProcess in Ready List\n-----------------\n";
	for (int i = Ready.size(); i > 0; i--)
	{
		output << "Process " << Ready[i - 1].getName() << "; [CPU Burst time] = " << Ready[i - 1].getCpuBurst() << "\n";
	}
	output << "-----------------\nProcesses in I/O\n-------------------\n";
	for (int i = 0; i < ioVec.size(); i++)
	{
		output << "Process " << ioVec[i].getName() << "; [I/O Burst Time] = " << ioVec[i].getIOBurst() << "\n";
	}
	output << "---------------------\nFinished Processes\n--------------------------\n";
	for (int i = 0; i < fin.size(); i++)
	{
		cout << "Process " << fin[i].getName() << "\n";
	}
	cout << "\n\n--------------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "Current Time is " << currentTime << "\n";
	cout << "[Running Process is " << Running.getName() << "]\n----------------------------------\nProcesses in Ready list\n----------------\n";
	for (int i = Ready.size(); i > 0; i--)
	{
		cout << "Process " << Ready[i - 1].getName() << "; [CPU Burst Time] = " << Ready[i - 1].getCpuBurst() << "\n";
	}
	cout << "--------------\nProcesses in I/O\n----------------\n";
	for (int i = 0; i < ioVec.size(); i++)
	{
		cout << "Process " << ioVec[i].getName() << "; [I/O Burst TIme] = " << ioVec[i].getIOBurst() << "\n";
	}
	cout << "--------------\n Finished Processes\n-------------------------------------\n";

	for (int i = 0; i < fin.size(); i++)
	{
		cout << "Process " << fin[i].getName() << "\n";
	}
	cout << "\n\n-------------------------------------------------------------------------------------------------------\n";
}

inline void PrintCSMLFQ(vector<Process> readyRR1, vector<Process> readyRR2, vector<Process> FCFS, vector<Process> ioVec, vector<Process> fin, Process Running, int currentTime)
{
	ofstream output;
	output.open("output.txt", ios_base::app);
	output << "[MLFQ] Current Time is [" << currentTime << "]\n";
	output << "[Running Process is " << Running.getName() << "] \n------------------\nProcess in Ready List\n-----------------\n";

	for (int i = 0; i < readyRR1.size(); i++)
	{
		output << "Process " << readyRR1[i].getName() << "; [CPU Burst Time] = " << readyRR1[i].getCpuBurst() << "\n";
	}
	output << "-------------------------------\nProcesses in Ready LIst Medium Priority\n----------------------\n";
	for (int i = 0; i < readyRR2.size(); i++)
	{
		output << "Process " << readyRR2[i].getName() << "; [CPU Burst Time] = " << readyRR2[i].getCpuBurst() << "\n";
	}
	output << "---------------------------\nProcesses in Ready List low priority\n-----------------------\n";
	for (int i = 0; i < FCFS.size(); i++)
	{
		output << "Process " << FCFS[i].getName() << "; [CPU Burst Time] = " << FCFS[i].getCpuBurst() << "\n";
	}
	output << "------------\nProcesses in I/O\n----------------------------\n";
	for (int i = 0; i < ioVec.size(); i++)
	{
		output << "Process " << ioVec[i].getName() << "; [I/O Burst Time] = " << ioVec[i].getIOBurst() << "\n";
	}
	output << "-----------\nFinished Processes\n---------------------\n";

	for (int i = 0; i < fin.size(); i++)
	{
		output << "Process " << fin[i].getName() << "\n";
	}
	output << "\n\n------------------------------------------------------------------------------------\n";

	cout << "Current Time is [" << currentTime << "]\n";
	cout << "[Running Process is " << Running.getName() << "]\n-----------------------\nProcesses in Ready List High Priority\n---------------------------\n";
	
	for (int i = 0; i < readyRR1.size(); i++)
	{
		cout << "Process " << readyRR1[i].getName() << "; [CPU Burst Time] = " << readyRR1[i].getCpuBurst() << "\n";
	}
	cout << "-------------------------------\nProcesses in Ready LIst Medium Priority\n----------------------\n";
	for (int i = 0; i < readyRR2.size(); i++)
	{
		cout << "Process " << readyRR2[i].getName() << "; [CPU Burst Time] = " << readyRR2[i].getCpuBurst() << "\n";
	}
	cout << "---------------------------\nProcesses in Ready List low priority\n-----------------------\n";
	for (int i = 0; i < FCFS.size(); i++)
	{
		cout << "Process " << FCFS[i].getName() << "; [CPU Burst Time] = " << FCFS[i].getCpuBurst() << "\n";
	}
	cout << "------------\nProcesses in I/O\n----------------------------\n";
	for (int i = 0; i < ioVec.size(); i++)
	{
		cout << "Process " << ioVec[i].getName() << "; [I/O Burst Time] = " << ioVec[i].getIOBurst() << "\n";
	}
	cout << "-----------\nFinished Processes\n---------------------\n";
	for (int i = 0; i < fin.size(); i++)
	{
		cout << "Process " << fin[i].getName() << "\n";
	}
	cout << "\n\n------------------------------------------------------------------------------------\n";
}

inline int preempt(Process &Running, vector<Process> &highPrio, vector<Process> &lowPrio, int tq)
{
	Running.editStatus('W');
	lowPrio.insert(lowPrio.begin(), Running);
	Running.editStatus('N');
	highPrio[0].editStatus('R');
	Running = highPrio[0];
	highPrio.erase(highPrio.begin());
	return tq;
}

inline void printStatsSJF(vector <Process> fin, int currentTime)
{
	int finishTime = currentTime;
	int cpuActiveTime = 0;
	int totWaitTime = 0;
	int totWaitTIme = 0;
	int totRT = 0;
	int totTT = 0;
	for (int i = 0; i < fin.size(); i++)
	{
		cpuActiveTime += fin[i].getCpuActiveTime();
		totWaitTime += fin[i].getWaitTime();
		totRT += fin[i].getResponseTime();
		totTT += fin[i].getTT();
	}
	double avgWait = totWaitTime / fin.size();
	double avgRT = totRT / fin.size();
	double avgTT = totTT / fin.size();
	double cpuUtil = cpuActiveTime * 100 / currentTime;
	for (int i = 0; i < fin.size(); i++)
	{
		cout << "[" << fin[i].getName() << "] : {WT= " << fin[i].getWaitTime() << "; TT= " << fin[i].getTT() << "; RT= " << fin[i].getResponseTime() << "}\n";
	}
	cout << "[CPU Util] = " << cpuUtil << "%; [AVG WT]= " << avgWait << "; [AVG TT] = " << avgTT << "; [AVG RT] = " << avgRT << "; [RT] = " << currentTime << "\n\n\n";
}
