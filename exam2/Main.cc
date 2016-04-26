#include <iostream>
#include <math.h>
#include <vector>
#include <list>

using namespace std;

typedef struct Node
{
	int id_location;
	int sum;

	Node(int id,int sss)
	{
	   id_location = id;
	   sum = sss;
	}
}Node;

int search(int x,const vector<vector<int>> &tasklist, int n );

bool festive_city[100005] = {0};

int main()
{ 
	int n = 0, m = 0;

	festive_city[1] = 1;
	cin >> n >> m;
	vector<vector<int>> matrix(n+1);
	int time = n - 1;

	while (time-- > 0)
	{
		int x,y;
		cin >> x >> y;
		matrix[x].push_back(y);
		matrix[y].push_back(x);
	}
	
//	cout << sizeof(matrix) <<endl;

    while ( m-- > 0 )
	{
	    int qi = 0,ci = 0;
		cin >> qi >> ci;
		if (1 == qi)
			festive_city[ci] = 1;
		else
		{
			if (festive_city[ci] == 1 )
				cout << 0 <<endl;
			else
                        {
                             int result = search(ci,matrix , n); 
                             cout << result << endl;
                        }
			  
		}
	}
	
	return 0;
}

int search( int x, const vector<vector<int>> &tasklist, int n)
{
    int result = -1;
	/*bool *signal = new bool[n + 1];
	for (int i = 0; i <= n; i++)
	{
	   signal[i] = 0;
	}*/
        bool signal[100001] = {0};
	signal[x] = 1;
	
	Node start(x,0);
	list<Node> SearchList;
	SearchList.push_back(start);

	while ( !SearchList.empty() )
	{
	   Node p = SearchList.front();
	   SearchList.pop_front();
	   int id = p.id_location;
	   int len = tasklist[id].size();
	   
	   for ( int i = 0; i < len; i++)
	   {
		   int x = tasklist[id][i];

		   if ( 1 == festive_city[x] )
                   {
                  //         delete [] signal;                   
			   return (p.sum + 1);
		   }
                   else
		   {
	          if ( 1 == signal[x])
				  continue;
			  else
			  {
				  signal[x] = 1;
				  Node middle(x , p.sum+1);
                  SearchList.push_back(middle);	
			  }//inner-else
		   }//out-else

	   }
	}

//	delete [] signal;
	return result;
}//g++ Main.cc -o Main -fno-asm -Wall -lm --static -std=c++0x -DONLINE_JUDGE
