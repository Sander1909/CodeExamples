#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;

struct point2D
{
    int x,y;

    point2D(int inX, int inY)
    {
        x = inX;
        y = inY;
    }

    void print()
    {
        cout << "X: " << x << " Y: " << y << endl;
    }

    point2D operator + (point2D other)
    {
        return point2D(x + other.x, y + other.y);
    }

    point2D operator - (point2D other)
    {
        return point2D(x - other.x, y - other.y);
    }
};

double vectorLength(point2D point)
{
    return sqrt(pow(point.x, 2) + pow(point.y, 2));
}

int main()
{

    srand(time(nullptr));

   vector<point2D> points;



   for(int i = 0; i < 20; i++)
   {
       point2D newPoint((rand()%20) - 10, (rand()%20) - 10);
       points.push_back(newPoint);
       points[i].print();
   }

   int index1 = 0;
   int index2 = 0;
   double closestDistance = 100000000;

   for(int i = 0; i < points.size(); i++)
   {
       for(int k = 0; k < points.size(); k++)
       {
           if(i != k)
           {
               if(vectorLength(points[i] - points[k]) < closestDistance)
               {
                   closestDistance = vectorLength(points[i] - points[k]);
                   index1 = i;
                   index2 = k;
               }
           }
       }
   }

   cout << "Closest distance is [" << closestDistance << "] between point [" << index1 << "] and point [" << index2 << "]"<< endl;
   cout << "Point " << index1 << " ";
   points[index1].print();
   cout << "Point " << index2 << " ";
   points[index2].print();

   return 0;
}
