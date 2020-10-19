#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout <<"***********************\n" <<"!! Welcome !!\n"   <<"\n***********************\n";
    
    int rows,columns;
    int fuelCapacity;
    char c;
    int numPumps,numHoles,numTolls;
    int payToll, payTravel;
    vector <vector <char> > path;

    cout <<"Would you like to create a new maze [Y] or use the default one [N]?";
    cin >>c;


    if(c=='Y')
    {
        cout <<"Enter the dimensions of the path [ROW x COLUMN]";
        cout <<"Enter number of rows\n";
        cin >>rows;
        cout <<"Enter number of columns\n";
        cin >>columns;

        path.resize(rows);
        for (int i=0; i<rows; i++)
        {
            path[i].resize(columns);
            for(int j=0;j<columns;j++)
            {
                path[i][j]='O';
            }
        }

        cout <<"Enter the fuel capacity of the vehicle\n";
        cin >> fuelCapacity;
        cout <<"Enter the cost of one traversal \, that is the units of fuel that would burn to "
            <<"accomplish that one unit of fuel cost one amount of money\n";
        cin >> payTravel;
        cout << "Enter the units of amount needed to be paid on one toll tax station\n";
        cin >> payToll;
        

        cout <<"Enter the number of petrol pumps in the entire path\n";
        cin >>numPumps;
        cout <<"Enter the coordinates of the petrol pumps [X,Y] one by one\n";
        for(int i=0;i<numPumps;i++)
        {
            int x,y;
            path[x-1][y-1]='P';
        }

        cout <<"Enter the number of toll tax stops in the entire path\n";
        cin >>numPumps;
        cout <<"Enter the coordinates of the toll tax stops [X,Y] one by one\n";
        for(int i=0;i<numPumps;i++)
        {
            int x,y;
            path[x-1][y-1]='T';
        }

        cout <<"Enter the number of holes in the entire path\n";
        cin >>numPumps;
        cout <<"Enter the coordinates of the holes [X,Y] one by one\n";
        for(int i=0;i<numPumps;i++)
        {
            int x,y;
            path[x-1][y-1]='H';
        }
    }
    else
    {

    }

    

    

    
}