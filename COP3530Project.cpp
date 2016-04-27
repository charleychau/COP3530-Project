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
        int *sumArr;

	realmNode(string c, int l, int s, int sa[]) : charm(c), lis(l), sumLIS(s), sumArr(sa) {}  //constructor for realmNode
};


//computes the Longest Increasing Subsequence
//used to determine if possible to move to other realms
int sum;  //global variable sum holds sumLIS
int tempLength;
int *lisArr;
int LIS(int magiPowerOrder[], int MPOsize)
{
	int longest = 0, mpiLength = 0;
        tempLength = 0;
	mpiLength = MPOsize;

	int *temp = new int[mpiLength];   // create array to keep track of LSI
int *sums = new int[mpiLength];
int *sums2 = new int[mpiLength];
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
sums[k] = magiPowerOrder[k];
			sum2 = sum;
sums2[k] = magiPowerOrder[k];
		}
		else
		{
			if (temp[tempLength] < magiPowerOrder[k])  //if new value larger than largest in set
			{
				temp[++tempLength] = magiPowerOrder[k];   //append new value to set
				if (sum != sum2 && change == true)
				{
					sum = sum2;
sums = sums2;
				}
				sum += magiPowerOrder[k];
sums[tempLength] = sums[tempLength-1] + magiPowerOrder[k];
				sum2 = sum;
sums2[tempLength] = sums2[tempLength-1] + magiPowerOrder[k];
				change = false;
			}
			else if (temp[0] > magiPowerOrder[k])      //if new value less than smallest in set
			{
				if (tempLength == 0)
				{
					temp[0] = magiPowerOrder[k];
					sum = temp[0];
sums[0] = sum;
sums2[0] = sum;
				}
				else
				{
					sum2 -= temp[0];
					temp[0] = magiPowerOrder[k];              //replace smallest value with new value
					sum2 += temp[0];
sums2[0] = sum2;
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
for(int t=1; t < m+1; t++)
{
  sums2[t] = sums2[t-1] + temp[t];
}
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
lisArr = sums;
//cout << lisArr[tempLength] << endl;
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

struct graphNode
{
  int weight;
  int gems;
};

int shortestPath(graphNode *Graph[], int numRealms, int sourceVertex, int destinationVertex);    // Dijkstra Algorithm 
/*
shortestPath - Calculates the shortest path between the realms
@ param - int *Graph - pointer to 2D array to hold the realms.
@ param - int numRealms - number of realms
@ param - int sourceVertex - source realm.
@ param - int destinationVertex - destination realm.
@ returns - int shortest path or -1 if no shortest path found.
*/
int numGems;
int shortestPath(graphNode *Graph[], int numRealms, int sourceVertex, int destinationVertex)
{
	int shortPath = 0;
numGems = 0;

	vector<int> dist(numRealms);

	vector<bool> vist(numRealms);

vector<int> gems(numRealms);

	for (int i = 0; i < numRealms; i++)
	{
		dist[i] = INT_MAX;      // Make all distance to realms inifinity 

		vist[i] = false;        // Make visited realms all false 

gems[i] = 0;
	}

	dist[sourceVertex] = 0;     // Make distance from source vertex to itself zero
gems[sourceVertex] = 0;
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
numGems = gems[index];

			if (shortPath == INT_MAX)
				return -1;
			else
				return shortPath;
		}

		for (int j = 0; j < numRealms; j++)
		{
			int distance = 0;
int ng = 0;

			if (vist[j] == false && Graph[index][j].weight > 0)
			{

				distance = dist[index] + Graph[index][j].weight;
ng = gems[index] + Graph[index][j].gems;

				if (distance < dist[j])
				{
					dist[j] = distance;
gems[j] = ng;
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
	graphNode **Graph = new graphNode*[numRealms];

	for (int i = 0; i < numRealms; i++)
	{
		Graph[i] = new graphNode[numRealms];
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
//cout << lisArr[tempLength] << " " << lisArr[tempLength-1] << " " << lisArr[tempLength-2] << endl;
	realms.push_back(new realmNode(charm, lis, sum, lisArr));  //create realm with charm and LIS
	}
	cin >> source >> destination;                     //get source charm and destination charm


	for (int k = 0; k < realms.size(); k++)            //FOR TESTING, outputs realm charm, LIS, and sumLIS
	{
//	  cout << realms[k]->charm << " LIS:" << realms[k]->lis << " sumLIS:" << realms[k]->sumLIS << endl;
          for (int l = 0; l < realms.size(); l++)
          {
            if( k != l )
            {
              int ed = editDistance( realms[k]->charm, realms[l]->charm ); 
              if( canTravel( realms[k]->lis, ed ) )
              {
//cout << realms[k]->sumArr[ed-1] << endl;
                Graph[k][l].weight = ed;
                Graph[k][l].gems = realms[k]->sumArr[ed-1];
//                cout << "Graph[" << k << "][" << l << "] = " << ed << endl;
              }
            }
          }
//          cout << endl;
	}
//	cout << "Source: " << source << "  Destination: " << destination << endl;




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

        int s=0, d=0;
        for(int i = 0; i < realms.size() && (s==0 || d==0) ; i++)
        {
          if(source == realms[i]->charm)
          {
            s = i;
          }
          if(destination == realms[i]->charm)
          {
            d = i;
          }
        }
//        cout << s << " " << d << endl;

	int path2 = shortestPath(Graph, numRealms, s, d);

//	int path = shortestPath(Graph, numRealms, d, s);

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

	//system("pause");

	return 0;
}
