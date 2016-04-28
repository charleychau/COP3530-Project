#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define INT_MAX 2147483647

struct realmNode
{
	string charm;                                     //contains the string of realm (charm)
	int lis;                                          //contains LIS length value
	int sumLIS;                                       //contains sum of LIS
	vector<int> sumArr;                               //contains sums corresponding to LIS

	realmNode(string c, int l, int s) : charm(c), lis(l), sumLIS(s) {}  //constructor for realmNode
};


//computes and returns length of Longest Increasing Subsequence, the LIS total sum, and sum values corresponding to LIS set
//used to determine if possible to move to other realms
int sum;         //global variable sum holds sumLIS
int tempLength;  //global variable tempLength holds length of LIS
int *lisArr;     //global variable lisArr holds array of the LIS values
int LIS(int magiPowerOrder[], int MPOsize)
{
	int mpiLength = 0;
	tempLength = 0;
	mpiLength = MPOsize;

	int *temp = new int[mpiLength];   // create array to keep track of correct LIS
	int *temp2 = new int[mpiLength];  // create another array to keep track of possibly new LIS
	int sum2 = 0;                     // variable sum2 holds possibly new LIS sum
	sum = 0;                          // variable sum holds correct LIS sum
	bool change = false;              // change becomes true when a longer LIS is confirmed,
                                          //   if true, temp will become temp2 and sum will become sum2

	for (int k = 0; k < mpiLength; k++)  //traverse all magi to find LIS
	{
		if (k == 0)                                 //handle the first element in the magi array
		{
			temp[k] = magiPowerOrder[k];        //put first magi element in LIS list of temp
			temp2[k] = magiPowerOrder[k];       //  and temp2
			sum += magiPowerOrder[k];           //update sum value
			sum2 = sum;                         //  and sum2
		}
		else
		{
			if (temp2[tempLength] < magiPowerOrder[k])  //if new value larger than largest in LIS set
			{
				temp[++tempLength] = magiPowerOrder[k];   //append new value to temp set
				temp2[tempLength] = magiPowerOrder[k];    //  and temp2

				if (sum != sum2 && change == true)        //if update of LIS is needed
				{
					sum = sum2;                       //update sum value
					temp = temp2;                     //update temp array
				}

				sum += magiPowerOrder[k];                 //add new value to total sum
				sum2 = sum;                               //  update sum2
				change = false;                           //reset change
			}
			else if (temp[0] > magiPowerOrder[k])  //if new value less than smallest in LIS set
			{
				if (tempLength == 0)                     //if array only has one element
				{
					temp[0] = magiPowerOrder[k];     //replace element in temp
					temp2[0] = magiPowerOrder[k];    //  and temp2
					sum = temp[0];                   //update sum with value
				}
				else                                     //if array has more than one element
				{
					sum2 -= temp[0];                 //subtract first element from sum2 total
					temp2[0] = magiPowerOrder[k];    //replace first element with new smallest element
					sum2 += temp[0];                 //add new smallest value to sum2 total
				}
			}
			else  //binary search (nlogn) for where new element fits in list
			{
				int l = 0, m = 0, r = 0;
				r = tempLength;
				while (l <= r)                                 //while there is more to search
				{
					m = (l + r) / 2;
					if (temp[m] == magiPowerOrder[k])      //if element already in list
					{
						break;                         //break out of loop
					}
					else if (temp[m] < magiPowerOrder[k])  //if new value greater than middle value
					{
						l = m + 1;                     //update left
					}
					else //temp[m] > magiPowerOrder[k]     //if new value less than middle value
					{
						r = m - 1;                     //update right
					}
				}

				if (l <= r)  //if new element already in list
				{
					//magiPowerOrder[k] already in list
				}
				else  //if not found in list
				{
					sum2 -= temp[m];               //subtract old element from sum2 total
					temp2[m] = magiPowerOrder[k];  //replace first larger-than-new value with new value
					sum2 += temp[m];               //add new element to sim2 total

					if (m == tempLength)  //if new element replaces the old largest element in list
					{
						change = true;                //indicate the temp and sum updates need to occur
                                                temp[m] = magiPowerOrder[k];  //replace largest value in set with new largest value
					}
					else  //if new element is between smallest and largest values in temp set
					{
						change = false;  //ensure no unneeded update occurs
					}
				}
			}
		}
	}

	int *a = new int[tempLength + 1];            //create new array a to store sum values
	a[0] = temp[0];                              //set first element of array to sum of first element in temp
	for (int g = 1; g < tempLength + 1; g++)     //for all elements in temp
	{
		a[g] = a[g - 1] + temp[g];           //add temp element to previous sum total and store in current sum element
	}

	lisArr = a;  //set global array lisArr to equal a array
	return (tempLength + 1);  //return LIS
}

//used to find the minimum of three numbers
//c++11 has the ability to find the minimum of three numbers, but c++98 does not
int minimum(int x, int y, int z)
{
	return min(min(x, y), z);
}

//computes the edit distance of two different charms
//used to compare with LIS amount to determine if possible to move to other realms
int editDistance(string currCharm, string destCharm)
{
	vector<vector<int> > matrix(currCharm.length() + 1, vector<int>(destCharm.length() + 1)); //creates a 2D matrix of the minimum edit distances

	for (int i = 0; i < currCharm.length() + 1; i++)		//populates the first row with editDistance of the string and nothing
	{
		matrix[i][0] = i;
	}
	for (int j = 0; j < destCharm.length() + 1; j++)		//populates the first column with editDistance of nothing and the string
	{
		matrix[0][j] = j;
	}

	for (int i = 1; i <= currCharm.length(); i++)			//populates the rest of the 2D vector with minimum edit distances
	{
		for (int j = 1; j <= destCharm.length(); j++)
		{
			if (currCharm[i - 1] == destCharm[j - 1])		//if the letters are the same, take the minimum of the left cell + 1, top cell + 1, and diagonal
			{												//because if you are comparing sitting to kneeding, you only need to compare sitt and kneed
				matrix[i][j] = minimum(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1, matrix[i - 1][j - 1]);
			}
			else											//if the letters are not the same, take the minimum of the left cell + 1, top cell + 1, and diagonal cell + 1
			{
				matrix[i][j] = minimum(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1, matrix[i - 1][j - 1] + 1);
			}
		}
	}

	return matrix[currCharm.length()][destCharm.length()];	//returns the last cell of the 2D vector, which is the minimum edit distance
}

//compares LIS with minimum edit distance
//if LIS >= minimum edit distance, it is possible to travel to this realm
bool canTravel(int lis, int minEditDistance)
{
	if (lis >= minEditDistance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

struct graphNode
{
	int weight;
	int gems;
};

// Dijkstra's Algorithm 
/*
shortestPath - Calculates the shortest path between the realms
@ param - int *Graph - pointer to 2D array to hold the realms.
@ param - int numRealms - number of realms
@ param - int sourceVertex - source realm.
@ param - int destinationVertex - destination realm.
@ returns - int shortest path or -1 if no shortest path found.
*/
int numGems;  //global variable numGems contains total number of gems needed to traverse the shortest path
int shortestPath(graphNode *Graph[], int numRealms, int sourceVertex, int destinationVertex)
{
	int shortPath = 0;
	numGems = 0;  //reset to zero

	vector<int> dist(numRealms);

	vector<bool> vist(numRealms);

	vector<int> gems(numRealms);  //create vector of gems to hold total gems at each position

	for (int i = 0; i < numRealms; i++)
	{
		dist[i] = INT_MAX;      // Make all distance to realms inifinity 

		vist[i] = false;        // Make visited realms all false 

		gems[i] = 0;            //begin with each total gem value set to zero
	}

	dist[sourceVertex] = 0;     // Make distance from source vertex to itself zero
	gems[sourceVertex] = 0;     //set total gems to traverse to itself as zero
	int i = 0;

	for (i = 0; i < numRealms; i++)
	{
		int index = 0;
		int minValue = INT_MAX;

		for (int j = 0; j < numRealms; j++)
		{
			if (vist[j] == true)
			{
				continue;
			}

			if (dist[j] < minValue)
			{
				index = j;
				minValue = dist[j];
			}
		}

		vist[index] = true;

		if (index == destinationVertex)
		{
			shortPath = dist[index];
			numGems = gems[index];  //set numGems to total number of gems needed for shortest path traversal

			if (shortPath == INT_MAX)
				return -1;
			else
				return shortPath;
		}

		for (int j = 0; j < numRealms; j++)
		{
			int distance = 0;
			int ng = 0;  //temp holder of number of gems set to zero

			if (vist[j] == false && Graph[index][j].weight > 0)
			{

				distance = dist[index] + Graph[index][j].weight;
				ng = gems[index] + Graph[index][j].gems;  //update temp holder of number of gems to new total gems

				if (distance < dist[j])
				{
					dist[j] = distance;
					gems[j] = ng;  //update current total number of gems with new number if path is shorter
				}
			}
		}
	}

	return -1;
}

int main()
{
	int numRealms = 0, numMagi = 0;
	string charm = "", source = "", destination = "";

	cin >> numRealms;						//get number of realms
									  
	graphNode **Graph = new graphNode*[numRealms];			// Allocate 2D Graph array 

	for (int i = 0; i < numRealms; i++)
	{
		Graph[i] = new graphNode[numRealms];
	}

	vector<realmNode*> realms;                        		//vector containing all realms
	for (int i = 0; i < numRealms; i++)                		//for each realm
	{
		cin >> charm;                                   	//get charm associated with realm
		cin >> numMagi;                                 	//get the number of Magi that will be encountered

		int *MagiPowerOrder = new int[numMagi];			//create array for Magi

		for (int j = 0; j < numMagi; j++)                	//for each magi
		{
			cin >> MagiPowerOrder[j];                       //get rank of magi
		}
		int lis = LIS(MagiPowerOrder, numMagi);        		//compute Longest Increasing Substring (LIS)

		realms.push_back(new realmNode(charm, lis, sum));  	//create realm with charm, length of LIS, and total sum of gems
		for (int d = 0; d < tempLength + 1; d++)		//for each element in gem sum array
		{
			realms[i]->sumArr.push_back(lisArr[d]);		//add sum to vector in realmNode
		}
	}
	cin >> source >> destination;                     		//get source charm and destination charm

	for (int k = 0; k < realms.size(); k++)  //for each row
	{
		for (int l = 0; l < realms.size(); l++)  //for each col
		{
			if (k != l)  //if row != col
			{
				int ed = editDistance(realms[k]->charm, realms[l]->charm);  //get edit distance
				if (canTravel(realms[k]->lis, ed))                          //if LIS > edit distance
				{
					Graph[k][l].weight = ed; 			    //update corresponding graph weight
					Graph[k][l].gems = realms[k]->sumArr[ed - 1];       // and number of gems needed
				}
			}
		}
	}
	
	int s = 0, d = 0;
	for (int i = 0; i < realms.size() && (s == 0 || d == 0); i++)  //until source and destination realm values are found
	{
		if (source == realms[i]->charm)  //if source
		{
			s = i;
		}
		if (destination == realms[i]->charm)  //if destination
		{
			d = i;
		}
	}

	int path2 = shortestPath(Graph, numRealms, s, d);

	if (path2 > 0)
	{
		cout << path2 << " " << numGems << endl;
	}
	else
	{
		cout << "IMPOSSIBLE" << endl;
	}

	int path = shortestPath(Graph, numRealms, d, s);

	if (path > 0)
	{
		cout << path << " " << numGems << endl;
	}
	else
	{
		cout << "IMPOSSIBLE" << endl;
	}
	
	return 0;
}
