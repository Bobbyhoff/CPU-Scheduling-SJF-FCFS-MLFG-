#include "process.h"
#include "scheduling.h"
using namespace std;

int main()
{
	static const int arr1b[] = { 4,5,3,5,4,6,4,5,2 };
	static const int arr1io[] = { 24,73,31,27,33,43,64,19 };

	static const int arr2b[] = { 18,19,11,18,19,18,17,19,10 };
	static const int arr2io[] = { 31,35,42,43,47,51,32 };

	static const int arr3b[] = { 6,4,7,4,5,7,8,6,5 };
	static const int arr3io[] = { 18,21,19,16,29,21,22,24 };

	static const int arr4b[] = { 17,19,20,17,15,12,15,14 };
	static const int arr4io[] = { 42,55,54,52,67,72,66 };

	static const int arr5b[] = { 5,4,5,3,5,4,3,4,3,5 };
	static const int arr5io[] = { 81,82,71,61,62,51,77,61,42 };

	static const int arr6b[] = { 10,12,14,11,15,13,11 };
	static const int arr6io[] = { 35,41,33,32,41,29 };

	static const int arr7b[] = { 21,23,24,22,21,20 };
	static const int arr7io[] = { 51,53,61,31,43 };

	static const int arr8b[] = { 11,14,15,17,16,12,13,15 };
	static const int arr8io[] = { 52,42,31,21,43,31,32, };

	vector<int> p1io(arr1io, arr1io + sizeof(arr1io) / sizeof(arr1io[0]));
	vector<int> p1b(arr1b, arr1b + sizeof(arr1b) / sizeof(arr1b[0]));

	vector<int> p2io(arr2io, arr2io + sizeof(arr2io) / sizeof(arr2io[0]));
	vector<int> p2b(arr2b, arr2b + sizeof(arr2b) / sizeof(arr2b[0]));

	vector<int> p3io(arr3io, arr3io + sizeof(arr3io) / sizeof(arr3io[0]));
	vector<int> p3b(arr3b, arr3b + sizeof(arr3b) / sizeof(arr3b[0]));

	vector<int> p4io(arr4io, arr4io + sizeof(arr4io) / sizeof(arr4io[0]));
	vector<int> p4b(arr4b, arr4b + sizeof(arr4b) / sizeof(arr4b[0]));

	vector<int> p5io(arr5io, arr5io + sizeof(arr5io) / sizeof(arr5io[0]));
	vector<int> p5b(arr5b, arr5b + sizeof(arr5b) / sizeof(arr5b[0]));

	vector<int> p6io(arr6io, arr6io + sizeof(arr6io) / sizeof(arr6io[0]));
	vector<int> p6b(arr6b, arr6b + sizeof(arr6b) / sizeof(arr6b[0]));

	vector<int> p7io(arr7io, arr7io + sizeof(arr7io) / sizeof(arr7io[0]));
	vector<int> p7b(arr7b, arr7b + sizeof(arr7b) / sizeof(arr7b[0]));

	vector<int> p8io(arr8io, arr8io + sizeof(arr8io) / sizeof(arr8io[0]));
	vector<int> p8b(arr8b, arr8b + sizeof(arr8b) / sizeof(arr8b[0]));

	Process P1(p1b, p1io, "P1");
	Process P2(p2b, p2io, "P2");
	Process P3(p3b, p3io, "P3");
	Process P4(p4b, p4io, "P4");
	Process P5(p5b, p5io, "P5");
	Process P6(p6b, p6io, "P6");
	Process P7(p7b, p7io, "P7");
	Process P8(p8b, p8io, "P8");
	Process temp[] = { P1,P2,P3,P4,P5,P6,P7,P8 };
	vector<Process> ReadyVec(temp, temp + sizeof(temp) / sizeof(Process));

	cout << "FCFS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
	exFCFS(ReadyVec);

	cout << "SJF>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
	SJF(ReadyVec);

	cout << "MLFQ>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
	MLFQ(ReadyVec);

	cin.get();
}