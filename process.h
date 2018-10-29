#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Process
{
private:
	vector<int> cpuBurst;
	vector<int> ioBurst;

	char status;
	int pStatus;

	int waitTime, finishTime, responseTime, cpuActiveTime;
	bool firstTimeFlag;
	string pname;

public:
	Process();
	Process(vector<int>,vector<int>,string);
	int AgeProcess(int);

	char getStatus();
	string getName();
	void editStatus(char);
	Process&operator= (const Process&);
	int getWaitTime();
	int getFinishTime();
	int getResponseTime();
	int getCpuActiveTime();
	int getTT();
	int getCpuBurst();
	int getIOBurst();
	int getPStatus();
	bool getFirstTimeFlag();
	void decrementWaitTime();
	void decrementResponseTime();
	void incrementPStatus();
	void editFirstTimeFlag();
	void editPStatus(int);
	void popCpuBurst();
	void popIoBurst();

};

Process::Process()
{
	status = 'W';
	pStatus = 1;
	pname = "";
	waitTime = 0;
	finishTime = 0;
	responseTime = 0;
	cpuActiveTime = 0;
	firstTimeFlag = false;
}

Process::Process(vector<int> cpuBursts, vector<int> ioBursts, string processNumber)
{
	status = 'W';
	pStatus = 1;
	pname = processNumber;
	cpuBurst = cpuBursts;
	ioBurst = ioBursts;
	waitTime = 0;
	finishTime = 0;
	responseTime = 0;
	cpuActiveTime = 0;
	firstTimeFlag = false;
}

int Process::AgeProcess(int currentTime)
{
	int contextOrReady = 0;

	switch (status)
	{
	case 'W':
		waitTime++;
		break;
	case 'R':
		if (firstTimeFlag == false)
		{
			firstTimeFlag = true;
			responseTime = currentTime;
		}
		cpuBurst[0]--;
		cpuActiveTime++;

		if (cpuBurst[0] <= 0)
		{
			status = 'I';
			if (ioBurst.empty())
			{
				status = 'F';
				finishTime = currentTime + 1;
				contextOrReady += 2;
			}
			contextOrReady += 1;
			break;
		}
		break;
	case 'I':
		if (ioBurst[0] != 0)
		{
			ioBurst[0]--;
		} else {
			status = 'W';
			contextOrReady = 2;
			break;
		}
		break;
	default :
		break;
	}
	return contextOrReady;
}

void Process::editStatus(char newStat)
{
	status = newStat;
}
string Process::getName()
{
	return pname;
}
char Process::getStatus()
{
	return status;
}
int Process::getPStatus()
{
	return pStatus;
}
int Process::getWaitTime()
{
	return waitTime;
}
int Process::getFinishTime()
{
	return finishTime;
}
int Process::getResponseTime()
{
	return responseTime;
}
int Process::getCpuBurst()
{
	return cpuBurst[0];
}
int Process::getIOBurst()
{
	return ioBurst[0];
}
int Process::getTT()
{
	return finishTime;
}
int Process::getCpuActiveTime()
{
	return cpuActiveTime;
}
void Process::editPStatus(int newPStatus)
{
	pStatus = newPStatus;
}
void Process::popCpuBurst()
{
	cpuBurst.erase(cpuBurst.begin());
}
void Process::decrementWaitTime()
{
	waitTime--;
}
void Process::decrementResponseTime()
{
	responseTime--;
}
void Process::popIoBurst()
{
	ioBurst.erase(ioBurst.begin());
}
void Process::incrementPStatus()
{
	if (pStatus != 3)
	{
		pStatus++;
	}
}

Process& Process::operator= (const Process &pSource)
{
	status = pSource.status;
	waitTime = pSource.waitTime;
	finishTime = pSource.finishTime;
	responseTime = pSource.responseTime;
	firstTimeFlag = pSource.firstTimeFlag;
	cpuActiveTime = pSource.cpuActiveTime;
	pStatus = pSource.pStatus;
	pname = pSource.pname;
	cpuBurst.clear();
	ioBurst.clear();
	cpuBurst.reserve(pSource.cpuBurst.size());
	ioBurst.reserve(pSource.ioBurst.size());
	copy(pSource.cpuBurst.begin(), pSource.cpuBurst.end(), back_inserter(cpuBurst));
	copy(pSource.ioBurst.begin(), pSource.ioBurst.end(), back_inserter(ioBurst));
	return *this;
}
