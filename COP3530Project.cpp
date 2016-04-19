#include <iostream>
#include <string>
using namespace std;

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
      if( temp[tempLength] < magiPowerOrder[k] )
      {
        temp[++tempLength] = magiPowerOrder[k];
      }
      else if( temp[0] > magiPowerOrder[k] )
      {
        //go to next iteration
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
	  temp[m] = magiPowerOrder[k];
	}
      }
    }
  }
  return (tempLength+1);
}





int main()
{
  int numRealms=0, numMagi=0;
  string charm="", source="", destination="";
  
  cin >> numRealms;                            //get number of realms
  for(int i = 0; i < numRealms; i++)           //for each realm
  {
    cin >> charm;                              //get charm associated with realm
    cin >> numMagi;                            //get the number of Magi that will be encountered
    int MagiPowerOrder[numMagi];               //create array
    for(int j = 0; j < numMagi; j++)           //for each magi
    {
      cin >> MagiPowerOrder[j];                //get rank of magi
    }
    int lis = LIS(MagiPowerOrder, numMagi);    //compute Longest Increasing Substring (LIS)
    cout << lis << endl;                       //just for testing, remove when not needed anymore
  }
  cin >> source >> destination;                //get source charm and destination charm

return 0;
}
