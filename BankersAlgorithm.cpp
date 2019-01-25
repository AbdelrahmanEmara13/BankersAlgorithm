#include <iostream>
#include <string>
#include <vector>
using namespace std;


vector<vector<int>> createMatrix(int rows, int cols);                                          //creates allocation and max matricies
vector<vector<int>> getNeed(const vector<vector<int>> &alloc, const vector<vector<int>> &max); // calculates need matrix
vector<int> fillVec(int cols);                                                                 // creates the available and request vectors
bool needLessWork(vector<int> &work, vector<int> &need);                                       // true if need is less than work

bool is_safe(vector<int> &available, vector<vector<int>> &allocation, vector<vector<int>> &need);                                       // returns true if the system in a safe state and prints the safe seqence
bool requestAlgo(vector<int> &request, int procIndex, vector<int> &available, vector<vector<int>> &allocation, vector<vector<int>> &need); // returns true if the new request can be granted
void printMatrix(const vector<vector<int>> &matrix);                                                                                          //utility function to print matrix
bool isTrue(vector<bool> &vec);                                                                                                            //check if the finish vector elements are all true

int main(int argc, char const *argv[])
{

    int rows, cols;
    cout << "Rows?  ";
    cin >> rows;
    cout << "cols?  ";
    cin >> cols;

    cout << "allocation Matrix Values: \n";
    vector<vector<int>> allocation =  createMatrix(rows, cols);
    printMatrix(allocation);

    cout << "Max Matrix Values: \n";
    vector<vector<int>> maxMatrix =   createMatrix(rows, cols);
    printMatrix(maxMatrix);

    cout << "Need Matrix Values: \n";
    vector<vector<int>> needMatrix = getNeed(allocation, maxMatrix);
    printMatrix(needMatrix);

    cout << "fill available : \n";
    vector<int> availableVector = fillVec(cols);

    //cout << needLessWork(availableVector, needMatrix[0]) << "\n";
    is_safe(availableVector, allocation, needMatrix);
    cout << "fill reqest : \n";
    vector<int> request = fillVec(availableVector.size());
    cout << "process index  : ";
    int procIndex;
    cin >> procIndex;
    requestAlgo(request, procIndex, availableVector, allocation, needMatrix);
    return 0;
}

vector<vector<int>> createMatrix(int rows, int cols)
{
    int val;
    vector<vector<int>> matrix;
    for (int i = 0; i < rows; i++)
    {
        vector<int> tempRow;
        for (int j = 0; j < cols; j++)
        {
            cout << "Matrix[" << i << "][" << j << "]: ";
            cin >> val;
            tempRow.push_back(val);
        }
        matrix.push_back(tempRow);
    }

    return matrix;
}

void printMatrix(const vector<vector<int>> &matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {

            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
}

vector<vector<int>> getNeed(const vector<vector<int>> &alloc, const vector<vector<int>> &max)
{
    vector<vector<int>> needMatrix;
    int val;
    for (int i = 0; i < alloc.size(); i++)
    {
        vector<int> tempRow;
        for (int j = 0; j < alloc[i].size(); j++)
        {
            val = max[i][j] - alloc[i][j];
            tempRow.push_back(val);
        }
        needMatrix.push_back(tempRow);
    }
    return needMatrix;
}

vector<int> fillVec(int cols)
{
    vector<int> vec;
    int val;
    for (int j = 0; j < cols; j++)
    {
        cout << "vec " << j + 1 << "th value : ";
        cin >> val;
        vec.push_back(val);
    }
    return vec;
}

bool is_safe(vector<int> &available, vector<vector<int>> &allocation, vector<vector<int>> &need)
{
    vector<bool> finishVec = {false};
    vector<int> work = available;

    vector<int> safSeq;

    while (safSeq.size() < need.size())

    {
        bool flag = false;

        for (int i = 0; i < need.size(); i++)
        {
            if (finishVec[i] == false)
            {
                if (needLessWork(work, need[i]))
                {
                    finishVec[i] = true;
                    safSeq.push_back(i);
                    for (int j = 0; j < work.size(); j++)
                    {

                        work[j] = work[j] + allocation[i][j];
                    }
                    flag = true;
                }
            }
        }
        if (flag == false)
        {
            cout << "NOT SAFE! :(\n";
            return false;
        }
    }

    cout << "IS SAFE \n< ";
    for (int j = 0; j < safSeq.size(); j++)
    {
        cout << "P" << safSeq[j] << ",";
    }
    cout << " >\n";
    return true;
}

bool requestAlgo(vector<int> &request, int procIndex, vector<int> &available, vector<vector<int>> &allocation, vector<vector<int>> &need)
{
    if (request <= need[procIndex])
    {
        if (request <= available)
        {
            vector<int> newAvailable;

            vector<int> newAllocation;

            vector<int> newNeed;

            for (int i = 0; i < request.size(); i++)
            {
                newAvailable.push_back(available[i] - request[i]);
            }
            for (int i = 0; i < request.size(); i++)
            {
                newAllocation.push_back(allocation[procIndex][i] + request[i]);
            }
            for (int i = 0; i < request.size(); i++)
            {
                newNeed.push_back(need[procIndex][i] - request[i]);
            }
            //create
            cout << "request!\n";
            for (int i = 0; i < newNeed.size(); i++)
            {
                need[procIndex][i] = need[procIndex][i] - need[procIndex][i] + newNeed[i];
            }

            for (int i = 0; i < newAllocation.size(); i++)
            {
                allocation[procIndex][i] = allocation[procIndex][i] - allocation[procIndex][i] + newAllocation[i];
            }
            //vector<vector<int>> updatedNeed = updateMatrix(need, newNeed, procIndex);

            /*   for (int i = 0; i < newAvailable.size(); i++)
            {
                cout << newAvailable[i] << ",";
            }*/
            vector<vector<int>> newNeedMatrix = need;
            vector<vector<int>> NewAllocation = allocation;
            cout << "New Allocation Matrix\n";
            printMatrix(NewAllocation);
            cout << "New Need Matrix\n";
            printMatrix(newNeedMatrix);
            cout << "New availabe Matrix\n";

            for (int i = 0; i < newAvailable.size(); i++)
            {
                cout << newAvailable[i] << " ";
            }
            cout << "\n";
            if (is_safe(newAvailable, NewAllocation, newNeedMatrix))
            {
                cout << "CAN BE GRANTED! :)\n";
                return true;
            }
            else
            {
                cout << "CANT BE GRANTED :(\n";
                return false;
            }
        }
        else
        {

            cout << "CANT BE GRANTED, Request > Available! :(\n";
            ;
            return false;
        }
    }
    else
    {
        cout << "CANT BE GRANTED, Rquest > Need! :(\n";
        return false;
    }
}

bool needLessWork(vector<int> &work, vector<int> &need)
{
    for (int i = 0; i < work.size(); i++)
    {
        if (need[i] > work[i])
        {
            return false;
        }
    }
    return true;
}

bool isTrue(vector<bool> &vec)
{
    for (int j = 0; j < vec.size(); j++)
    {
        if (vec[j] == false)
        {
            return false;
        }
    }
    return true;
}
