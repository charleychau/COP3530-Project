#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct realmNode
{
  string charm;                                     //contains the string of realm (charm)
  int lis;                                          //contains LIS value
  vector<realmNode*> accessibleRealms;              //vector containing all accessible realms
  
  realmNode(string c, int l) : charm(c), lis(l) {}  //constructor for realmNode

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
int LIS(int magiPowerOrder[], int MPOsize)
{
  int longest=0, mpiLength=0, tempLength=0;
  mpiLength = MPOsize;
  int temp[mpiLength];                             //create array to keep track of LSI

  for(int k = 0; k < mpiLength; k++)               //traverse magi
  {
    if(k == 0)
    {
      temp[k] = magiPowerOrder[k];                //Put first element in LSI list
    }
    else
    {
      if( temp[tempLength] < magiPowerOrder[k] )  //if new value larger than largest in set
      {
        temp[++tempLength] = magiPowerOrder[k];   //append new value to set
      }
      else if( temp[0] > magiPowerOrder[k] )      //if new value less than smallest in set
      {
        temp[0] = magiPowerOrder[k];              //replace smallest value with new value
      }
      else                                        //binary search (nlogn)
      {
        int l=0, m=0, r=0;
	r = tempLength;
        while( l <= r )
        {
          m = (l+r)/2;
	  if( temp[m] == magiPowerOrder[k] )
	  {
	    break; //break out of loop
	  }
	  else if( temp[m] < magiPowerOrder[k] )
	  {
	    l = m+1;
	  }
	  else //temp[m] > magiPowerOrder[k]
       	  {
	    r = m-1;
	  }
        }
        
	if( l <= r )
	{
	  //magiPowerOrder[k] already in list
	}
	else
	{
	  temp[m] = magiPowerOrder[k];  //replace first larger-than-new-value with new value
	}
      }
    }
  }
  return (tempLength+1);  //return LIS
}





int main()
{
  int numRealms=0, numMagi=0;
  string charm="", source="", destination="";
  
  cin >> numRealms;                                 //get number of realms
  vector<realmNode*> realms;                        //vector containing all realms
  for(int i = 0; i < numRealms; i++)                //for each realm
  {
    cin >> charm;                                   //get charm associated with realm
    cin >> numMagi;                                 //get the number of Magi that will be encountered
    int MagiPowerOrder[numMagi];                    //create array
    for(int j = 0; j < numMagi; j++)                //for each magi
    {
      cin >> MagiPowerOrder[j];                     //get rank of magi
    }
    int lis = LIS(MagiPowerOrder, numMagi);         //compute Longest Increasing Substring (LIS)
    realms.push_back( new realmNode(charm, lis) );  //create realm with charm and LIS
  }
  cin >> source >> destination;                     //get source charm and destination charm


  for(int k = 0; k < realms.size(); k++)            //FOR TESTING, outputs realm charm and LIS
  {
    cout << realms[k]->charm << " " << realms[k]->lis << endl;
  }
  cout << "Source: " << source << "  Destination: " << destination << endl;

  //need to connect realms to other accessible realms (Algorithm 2)

  //need to find shortest path from source realm to destination realm (Algorithm 3)

return 0;
}
