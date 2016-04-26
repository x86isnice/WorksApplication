#include <iostream>
#include <vector>
#include <math.h>
#include <list>

using namespace std;

int a[500][500];

typedef struct Node
{
   int x;
   int y;
   int sum;
   vector<int> path;
   Node(int xx, int yy ,int sss,vector<int> vec):path(vec)
   {
      x = xx;
	  y = yy;
	  sum = sss;
   }
   
}Node;
/*
 x  col
y 0 0 0 0 0 0 0 rows
  1 1 1 1 1 1 1
*/
inline void getlocate(int &x,int &y,int total,int m)
{
  y = total/m;
  x = total%m;
}

inline bool check(int x,int y, const vector<int> &path,int m)
{   
	int len = path.size(); 
	for (int i = 0; i < len; i++)
	{
	   if ((y*m+x) == path[i])
			return false;
	}
	return true;
}

int search(int rows, int n, int m)
{
	vector<int> path;
    int result = -1;
//	bool signal[500 * 500] = {0};
	Node start(0, rows, a[rows][0],path);
	start.path.push_back(start.y*m+start.x);

	list<Node> recorder;
//	signal[rows*m ] = 1;
	recorder.push_back(start);

	while ( !recorder.empty())
	{
	  int count = 0;
	  
	  Node middle = recorder.front();
      recorder.pop_front();
	  
	  bool tick[3] = {1,1,1};
	  int rightx = 0, righty = 0;
	  rightx = middle.x + 1;
	  righty = middle.y;
	 // if (a[righty][rightx] == -1 || rightx == m || signal[righty * m + rightx] == 1)
	  if (a[righty][rightx] == -1 || rightx == m || !check(rightx, righty,middle.path, m))
	  { 
		 count++;
	     tick[0] = 0;
	  }

	  int upx = middle.x,upy = middle.y + 1;
	  bool teleport_up = 0;
	  if (upy%n != upy )
	  {
		  teleport_up = 1;
	      upy = upy%n;
	  }
	//  if (a[upy][upx] == -1 || signal[righty * m + rightx] == 1)
	  if (a[upy][upx] == -1 || !check(upx, upy,middle.path, m))
      {
		 count++;
		 tick[1] = 0;
	  }

	  int downx = middle.x, downy = middle.y - 1;
	  bool teleport_down = 0;
	  if (downy < 0)
	  {
	      teleport_down = 1;
		  downy = downy + n;
	  }
	//  if (a[downy][downx] == -1 || signal[downy * m + downx] == 1)
	  if (a[downy][downx] == -1 || !check(downx, downy,middle.path, m))
	  { 
		count++;
	    tick[2] = 0;
	  }

	//  if (count == 3 && middle.x == (m - 1) && middle.sum > result)
	  if (  middle.x == (m - 1) && middle.sum > result)
		 {
			 result =  middle.sum;
		/*	 cout << "sum = " << result << endl; 
			if (middle.path.size() != 0)
			 for (vector<int>::iterator it = middle.path.begin(); it !=  middle.path.end(); it++)
			 {
				 int x;int y;
		     	getlocate(x,y,*it, m);
			 	 cout << *it << " " <<"x="<< x<< " " <<"y="<<y << endl;
			 }
			cout << "------------------------------" <<endl;
              */
	     }
	  if (tick[0] == 1)
	  {
			Node right( rightx, righty, middle.sum+a[righty][rightx], middle.path);
			right.path.push_back(righty * m + rightx);
		//  signal[righty*m + rightx] = 1;
			recorder.push_back(right);
	  }

	  if (tick[1] == 1)
	  {
			Node up(upx, upy, (1-teleport_up) * middle.sum + a[upy][upx], middle.path);
			up.path.push_back(upy * m + upx);
		//	signal[upy*m+ upx] = 1;
			recorder.push_back(up);
	  }

	  if (tick[2] == 1)
	  {
		   Node down(downx, downy, (1-teleport_down) * middle.sum + a[downy][downx], middle.path);
		   down.path.push_back(downy * m + downx);
		//   signal[downy *m + downx] = 1;
		   recorder.push_back(down);
	  }
	}
//	delete []signal;
	return result;
}

int main()
{
  int n ,m;

  cin >> n >> m;
  for (int i = 0; i < n; i++)
  {
     for (int j = 0; j < m; j++)
		 cin >> a[i][j]; 
  }

  int max = -1;
  for (int i = 0; i < n; i++)
  {
	 if ( -1 != a[i][0] )
     {
	   int result = search(i, n , m);
	   
	   if (result > max)
		  max = result;
	 }
  }
  cout << max << endl;
  return 0;
}//g++ Main.cc -o Main -fno-asm -Wall -lm --static -std=c++0x -DONLINE_JUDGE
