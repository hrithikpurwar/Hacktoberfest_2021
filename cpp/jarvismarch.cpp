#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#define MAX 20
using namespace std;

vector<int> resPos;

struct Point {
    float x;
    float y;
};

Point points[MAX];

bool compare(int a, int b)
{
    return points[a].x < points[b].x;
}

float crossProductAns(Point a, Point b, Point c)
{
    return ((c.x-a.x)*(b.y-a.y)-(c.y-a.y)*(b.x-a.x));
}

float dist(Point p1, Point p2)
{
    return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

int main()
{
    int n;
    cin>>n;
    for (int i=0; i<n; i++)
    {
        string str;
        cin>>str;
        for (int j = 0; j < str.length(); j++) {
            if (str[j]==',') {
                points[i].x = stof(str.substr(1,j-1));
                points[i].y = stof(str.substr(j+1,str.length()-2));
            }
        }
    }

    // jarvis march

    int minXind = 0;
    for (int i = 1; i<n; i++)
    {
        if (points[i].x<points[minXind].x)
        {
            minXind = i;
        }
        else if (points[i].x==points[minXind].x && points[i].y<points[minXind].y)
        {
            minXind = i;
        }
    }

    resPos.push_back(minXind);
    int add = 0;
    bool flag = true;

    while (add!=minXind || resPos.size()<=1)
    {
        for (int i = n-1; i>= 0; i--)
        {
            if (flag && i!=*(--resPos.end()))
            {
                add = i;
                flag = false;
            }
            else if (crossProductAns(points[*(resPos.end()-1)],points[add],points[i])<0)
            {
                add = i;
            }
        }
        resPos.push_back(add);
        flag = true;
    }

    cout<<endl;

    for (int i = 0; i< resPos.size()-1; i++)
    {
        for (int j = i+1; j<resPos.size()-1; j++)
        {
            if (points[resPos[i]].x>points[resPos[j]].x)
            {
                int temp = resPos[i];
                resPos[i] = resPos[j];
                resPos[j] = temp;
            }
            else if (points[resPos[i]].x==points[resPos[j]].x && points[resPos[i]].x>points[resPos[j]].x)
            {
                int temp = resPos[i];
                resPos[i] = resPos[j];
                resPos[j] = temp;
            }
        }
    }

    for (auto itr = resPos.begin(); itr!=resPos.end()-1; ++itr)
    {
        cout<<"("<<points[*itr].x<<","<<points[*itr].y<<")"<<endl;
    }

    return 0;
}