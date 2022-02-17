//  OS Practical 8: c) Implementation of SRTF scheduling
#include <iostream>
using namespace std;

#define PId 0       //column 0 store PId
#define AvT 1       //column 1 store Arrival Time
#define BT 2        //column 2 store Burst Time
#define CT 3        //column 3 store Completion Time
#define WT 4        //column 4 store Waiting Time
#define TaT 5       //column 5 store Turnaround Time


//Program to print detail of processes in matrix 
void printPDetailTable(int mat[][6], int totalProcesses,  int uptoColumn=6)
{
    for (int i = 0; i < totalProcesses; i++)
    {
        cout<<"| P";
        for (int j = 0; j < uptoColumn; j++)
        {
            if(j==0)
            {
                cout<<mat[i][j]<<"\t\t|";
            }
            else
            {
                cout<<"|\t"<<mat[i][j]<<"\t|";
            }
            
        }
		cout<<endl;
	}
}

//Function to take input of details of processes
void getJobDetails(int mat[][6], int totalProcesses)
{
    cout<<endl;
    cout<<endl<< "Enter the process Details "<<endl<<endl;
	for (int i = 0; i < totalProcesses; i++)
    {
		cout << "For Process " << i + 1 << " : "<<endl;
		cout << "Enter Process Id: ";
		cin >> mat[i][PId];
		cout << "Enter Arrival Time: ";
		cin >> mat[i][AvT];
		cout << "Enter Burst Time: ";
		cin >> mat[i][BT];
		cout<<endl;
	}
    cout<<endl;
}

//function to swap value of two given variables
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//Function to sort Matrix according to Process ID number
void sortMat(int mat[][6], int totalProcesses)
{
    for(int i=0;i<totalProcesses;i++)
	{		
		for(int j=i+1;j<totalProcesses;j++)
		{
			if(mat[i][PId]>mat[j][PId])
            {
                for(int k=0;k<6;k++)
                {
                    swap(mat[i][k],mat[j][k]);
                }
            }
        }
	}
}

//Function to arrange arrangeArrival time in ascending order
void arrangeArrival(int mat[][6], int totalProcesses)
{
	for (int i = 0; i < totalProcesses; i++) {
		for (int j = 0; j < totalProcesses - i - 1; j++) {
			if (mat[j][AvT] > mat[j + 1][AvT]) {
				for (int k = 0; k < 5; k++) {
					swap(mat[j][k], mat[j + 1][k]);
				}
			}
		}
	}
}

//Function to calculate average Waiting Time
float avgWaitingTime(int mat[][6], int totalProcesses)
{
    int sum = 0;
    for (int i = 0; i < totalProcesses; i++)
    {
        sum+=mat[i][WT];
    }
    return ((float)sum/(float)totalProcesses);
}

//Function to calculate average Turn Around Time
float avgTurnAroundTime(int mat[][6], int totalProcesses)
{
    int sum = 0;
    for (int i = 0; i < totalProcesses; i++)
    {
        sum+=mat[i][TaT];
    }
    return ((float)sum/(float)totalProcesses);
}

void copyColumnToArray(int mat[][6], int totalProcesses, int columnNumber, int destination[])
{
    for (int i = 0; i < totalProcesses; i++)
    {
        destination[i]= mat[i][columnNumber];
    }
}

//Function to calculate Completion, Waiting and TurnAround Time
void calculate_time(int mat[][6], int totalProcesses)
{
    int processesCompleted = 0;
    int burst[totalProcesses+1]={0};
	copyColumnToArray(mat, totalProcesses, BT, burst);
    burst[totalProcesses] = 10000;
    int smallestBurstIndex;
    for(int time=0; processesCompleted!=totalProcesses; time++)
    {
        smallestBurstIndex =totalProcesses;

        for(int i=0; i<totalProcesses; i++)
        {
            if(mat[i][AvT] <= time && burst[i] < burst[smallestBurstIndex] && burst[i]>0)
            {
                smallestBurstIndex = i;
            }
        }
        burst[smallestBurstIndex]--;
        if(burst[smallestBurstIndex]==0)
        {
            processesCompleted++;
            mat[smallestBurstIndex][CT]=time+1;
            mat[smallestBurstIndex][TaT]= mat[smallestBurstIndex][CT]- mat[smallestBurstIndex][AvT];
            mat[smallestBurstIndex][WT]= mat[smallestBurstIndex][TaT]- mat[smallestBurstIndex][BT];
        }
    }
}

//Main function for execution of program
int main()
{
    int totalProcesses;
	
	cout<<endl<<"Enter Total Number of Processes: ";
    cin>>totalProcesses;

    int mat[totalProcesses][6] = {0};
    
    getJobDetails(mat, totalProcesses);
    arrangeArrival(mat, totalProcesses);
	calculate_time(mat, totalProcesses);
	sortMat(mat, totalProcesses);

   
	cout<<endl<< "\nFinal Result : \n\n";

	cout<<"   Process ID\t   Arrival Time\t    Burst Time     Completion Time   Waiting Time     Turnaround Time"<<endl;
	printPDetailTable(mat, totalProcesses, 6);

    cout<<endl<<endl<<"Average Waiting Time = "<<avgWaitingTime(mat, totalProcesses);
    cout<<endl<<"Average Turn Around Time = "<<avgTurnAroundTime(mat, totalProcesses);



    return 0;
}
