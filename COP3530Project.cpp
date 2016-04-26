#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define INT_MAX 2147483647

struct realmNode
{
	string charm;                                     //contains the string of realm (charm)
	int lis;                                          //contains LIS value
	int sumLIS;
	vector<realmNode*> accessibleRealms;              //vector containing all accessible realms

	realmNode(string c, int l, int s) : charm(c), lis(l), sumLIS(s) {}  //constructor for realmNode

	void addAcessibleRealm(realmNode* aR)             //add accessible realm
	{
		accessibleRealms.push_back(aR);
	}

	int numAccessibleRealms()                         //get number of accessible realms
	{
		return accessibleRealms.size();
	}
};


//computes the Longest Increasing Subsequence
//used to determine if possible to move to other realms
int sum;  //global variable sum holds sumLIS
int LIS(int magiPowerOrder[], int MPOsize)
{
	int longest = 0, mpiLength = 0, tempLength = 0;
	mpiLength = MPOsize;

	int *temp = new int[mpiLength];   // create array to keep track of LSI

									  //int temp[mpiLength];                             //create array to keep track of LSI
	int sum2 = 0;
	sum = 0;
	bool change = false;

	for (int k = 0; k < mpiLength; k++)               //traverse magi
	{
		if (k == 0)
		{
			temp[k] = magiPowerOrder[k];                //Put first element in LSI list
			sum += magiPowerOrder[k];
			sum2 = sum;
		}
		else
		{
			if (temp[tempLength] < magiPowerOrder[k])  //if new value larger than largest in set
			{
				temp[++tempLength] = magiPowerOrder[k];   //append new value to set
				if (sum != sum2 && change == true)
				{
					sum = sum2;
				}
				sum += magiPowerOrder[k];
				sum2 = sum;
				change = false;
			}
			else if (temp[0] > magiPowerOrder[k])      //if new value less than smallest in set
			{
				if (tempLength == 0)
				{
					temp[0] = magiPowerOrder[k];
					sum = temp[0];
				}
				else
				{
					sum2 -= temp[0];
					temp[0] = magiPowerOrder[k];              //replace smallest value with new value
					sum2 += temp[0];
				}
			}
			else                                        //binary search (nlogn)
			{
				int l = 0, m = 0, r = 0;
				r = tempLength;
				while (l <= r)
				{
					m = (l + r) / 2;
					if (temp[m] == magiPowerOrder[k])
					{
						break; //break out of loop
					}
					else if (temp[m] < magiPowerOrder[k])
					{
						l = m + 1;
					}
					else //temp[m] > magiPowerOrder[k]
					{
						r = m - 1;
					}
				}

				if (l <= r)
				{
					//magiPowerOrder[k] already in list
				}
				else
				{
					sum2 -= temp[m];
					temp[m] = magiPowerOrder[k];  //replace first larger-than-new-value with new value
					sum2 += temp[m];
					if (m == tempLength)
					{
						change = true;
					}
					else
					{
						change = false;
					}
				}
			}
		}
	}
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
			{
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


int shortestPath(int *Graph[], int numRealms, int sourceVertex, int destinationVertex);    // Dijkstra Algorithm 
/*
shortestPath - Calculates the shortest path between the realms
@ param - int *Graph - pointer to 2D array to hold the realms.
@ param - int numRealms - number of realms
@ param - int sourceVertex - source realm.
@ param - int destinationVertex - destination realm.
@ returns - int shortest path or -1 if no shortest path found.
*/
int shortestPath(int *Graph[], int numRealms, int sourceVertex, int destinationVertex)
{
	int shortPath = 0;

	vector<int> dist(numRealms);

	vector<bool> vist(numRealms);

	for (int i = 0; i < numRealms; i++)
	{
		dist[i] = INT_MAX;      // Make all distance to realms inifinity 

		vist[i] = false;        // Make visited realms all false 
	}

	dist[sourceVertex] = 0;     // Make distance from source vertex to itself zero

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
			}
		}

		vist[index] = true;

		if (index == destinationVertex)
		{
			shortPath = dist[index];

			if (shortPath == INT_MAX)
				return -1;
			else
				return shortPath;
		}

		for (int j = 0; j < numRealms; j++)
		{
			int distance = 0;

			if (vist[j] == false && Graph[index][j] > 0)
			{

				distance = dist[index] + Graph[index][j];

				if (distance < dist[j])
				{
					dist[j] = distance;
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

	cin >> numRealms;                                 //get number of realms

	//numRealms = 4;

	// Allocate 2D Graph array 
	int **Graph = new int*[numRealms];

	for (int i = 0; i < numRealms; i++)
	{
		Graph[i] = new int[numRealms];
	}

	// TODO:  Shane needs to populate this array 



	vector<realmNode*> realms;                        //vector containing all realms
	for (int i = 0; i < numRealms; i++)                //for each realm
	{
	cin >> charm;                                   //get charm associated with realm
	cin >> numMagi;                                 //get the number of Magi that will be encountered

	int *MagiPowerOrder = new int[numMagi];

	//int MagiPowerOrder[numMagi];                    //create array
	for (int j = 0; j < numMagi; j++)                //for each magi
	{
	cin >> MagiPowerOrder[j];                     //get rank of magi
	}
	int lis = LIS(MagiPowerOrder, numMagi);         //compute Longest Increasing Substring (LIS)
	realms.push_back(new realmNode(charm, lis, sum));  //create realm with charm and LIS
	}
	cin >> source >> destination;                     //get source charm and destination charm


	for (int k = 0; k < realms.size(); k++)            //FOR TESTING, outputs realm charm, LIS, and sumLIS
	{
	  cout << realms[k]->charm << " LIS:" << realms[k]->lis << " sumLIS:" << realms[k]->sumLIS << endl;
          for (int l = 0; l < realms.size(); l++)
          {
            if( k != l )
            {
              int ed = editDistance( realms[k]->charm, realms[l]->charm ); 
              if( canTravel( realms[k]->lis, ed ) )
              {
                Graph[k][l] = ed;
                cout << "Graph[" << k << "][" << l << "] = " << ed << endl;
              }
            }
          }
          cout << endl;
	}
	cout << "Source: " << source << "  Destination: " << destination << endl;




	//need to connect realms to other accessible realms using canTravel and editDistance functions

	//need to find shortest path from source realm to destination realm (Algorithm 3)

	// Input 1 

	//Graph[0][1] = 4;
	//Graph[0][2] = 2;
	//Graph[1][2] = 3;
	//Graph[1][3] = 3;
	//Graph[2][0] = 2;
	//Graph[3][1] = 3;
	//Graph[3][2] = 3;

	// Input 2

	//Graph[0][1] = 4;
	//Graph[1][0] = 4;
	//Graph[1][2] = 4;

	// NOTE - When you do your part Shane this is how the graph should be realized 
	// Source realm = row index
	// Destination realm = column index

	int path2 = shortestPath(Graph, numRealms, 2, 0);

	int path = shortestPath(Graph, numRealms, 0, 2);

	if (path2 > 0)
	{
		cout << path2 << endl << endl;
	}
	else
	{
		cout << "IMPOSSIBLE" << endl;
	}

	if (path > 0)
	{
		cout << path << endl << endl;
	}
	else
	{
		cout << "IMPOSSIBLE" << endl;
	}

	//system("pause");

	return 0;
}
