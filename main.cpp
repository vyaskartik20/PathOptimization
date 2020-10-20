#include <bits/stdc++.h>
using namespace std;

int heuristicValueCalculator (vector <vector <char> > &path, int payToll, int fuelLeft, int x, int y)
{
    int heuristicValue;

    heuristicValue

}

vector <pair <int,int> > nextUtilFunction (vector <vector <char> > &path, int rows, int columns, int currRow, int currCol)
{
    vector < pair <int,int> > nextPossibileMoves;
    if(currRow==0)
    {
        if(currCol==0)
        {
            nextPossibileMoves.push_back({(currRow),(currCol+1)});
            nextPossibileMoves.push_back({(currRow+1),(currCol)});
        }
        else if(currCol==columns)
        {
            nextPossibileMoves.push_back({(currRow),(currCol-1)});
            nextPossibileMoves.push_back({(currRow+1),(currCol)});
        }
        else
        {
            nextPossibileMoves.push_back({(currRow),(currCol-1)});
            nextPossibileMoves.push_back({(currRow),(currCol+1)});
            nextPossibileMoves.push_back({(currRow+1),(currCol)});
        }
    }
    else if(currRow==rows)
    {
        if(currCol==0)
        {
            nextPossibileMoves.push_back({(currRow),(currCol+1)});
            nextPossibileMoves.push_back({(currRow-1),(currCol)});
        }
        else if(currCol==columns)
        {
            nextPossibileMoves.push_back({(currRow),(currCol-1)});
            nextPossibileMoves.push_back({(currRow-1),(currCol)});
        }
        else
        {
            nextPossibileMoves.push_back({(currRow),(currCol-1)});
            nextPossibileMoves.push_back({(currRow),(currCol+1)});
            nextPossibileMoves.push_back({(currRow-1),(currCol)});
        }
    }
    else if(currCol==0)
    {
        nextPossibileMoves.push_back({(currRow+1),(currCol)});
        nextPossibileMoves.push_back({(currRow-1),(currCol)});
        nextPossibileMoves.push_back({(currRow),(currCol+1)});
    }
    else if(currCol==columns)
    {
        nextPossibileMoves.push_back({(currRow+1),(currCol)});
        nextPossibileMoves.push_back({(currRow-1),(currCol)});
        nextPossibileMoves.push_back({(currRow),(currCol-1)});
    }
    else
    {
        nextPossibileMoves.push_back({(currRow+1),(currCol)});
        nextPossibileMoves.push_back({(currRow-1),(currCol)});
        nextPossibileMoves.push_back({(currRow),(currCol-1)});
        nextPossibileMoves.push_back({(currRow),(currCol+1)});
    }
    return nextPossibileMoves;
}


int main()
{
    cout <<"***********************\n" <<"!! Welcome !!\n"   <<"\n***********************\n";
    
    int rows,columns;
    int fuelCapacity;
    char c_char;
    int c_int;
    int numPumps,numHoles,numTolls;
    int payToll, payTravel;
    int heuristicValue;
    int fuelLeft;
    vector <vector <char> > path;
    vector <vector <int> > visitedUtil;

    cout <<"Would you like to create a new maze [Y] or use the default one [N]?";
    cin >>c_char;

    if(c_char=='Y')
    {
        cout <<"Enter the dimensions of the path [ROW x COLUMN]";
        cout <<"Enter number of rows\n";
        cin >>rows;
        cout <<"Enter number of columns\n";
        cin >>columns;

        path.resize(rows);
        visitedUtil.resize(rows);
        for (int i=0; i<rows; i++)
        {
            path[i].resize(columns);
            visitedUtil[i].resize(columns);
            for(int j=0;j<columns;j++)
            {
                path[i][j]='O';
                visitedUtil[i][j]=0;
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
        cin >>numTolls;
        cout <<"Enter the coordinates of the toll tax stops [X,Y] one by one\n";
        for(int i=0;i<numTolls;i++)
        {
            int x,y;
            path[x-1][y-1]='T';
        }

        cout <<"Enter the number of holes in the entire path\n";
        cin >>numHoles;
        cout <<"Enter the coordinates of the holes [X,Y] one by one\n";
        for(int i=0;i<numHoles;i++)
        {
            int x,y;
            path[x-1][y-1]='H';
        }
    }
    else
    {
        cout <<"Choose the default grid : \n" <<"[1] : [5x5]";
        cin >>c_int;

        if(c_int==1)
        {
            // P _ H _ P
            // _ _ _ _ _
            // _ T P _ P
            // P H _ _ _
            // H _ _ _ _

            rows=5;
            columns=5;

            path.resize(rows);
            for (int i=0; i<rows; i++)
            {
                path[i].resize(columns);
                for(int j=0;j<columns;j++)
                {
                    path[i][j]='O';
                }
            }

            path[0][0]='P';
            path[0][4]='P';
            path[2][4]='P';
            path[2][2]='P';
            path[3][0]='P';
        
            path[0][2]='H';
            path[4][0]='H';
            path[3][1]='H';

            path[2][1]='T';

            fuelCapacity=3;
            payToll=10;
            payTravel=1;

            numHoles=3;
            numTolls=1;
            numPumps=5;
        }
    } 

    cout <<"The path is : \n";
    
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            cout <<path[i][j] <<" ";
        }
        cout <<endl;
    }

    cout <<"The fuel capacity of the vehicle is : " <<fuelCapacity <<"\n";
    cout <<"The cost of one traversal is : " <<payTravel <<"\n";
    cout << "The units of amount needed to be paid on one toll tax station is : " <<payToll <<"\n\n";

    vector <pair<int,int>> tempPath;
    tempPath.push_back({1,1});

    priority_queue< pair < int, pair < pair< pair< int,int >, int>, vector <pair <int,int> > > > > QUEUE;
    heuristicValue=heuristicValueCalculator(path,fuelCapacity,payToll, 0,0);
    visitedUtil[0][0]=fuelCapacity;
    QUEUE.push(make_pair(0, make_pair( make_pair( make_pair(0,0) ,heuristicValue) , tempPath )));

    vector <pair <int,int> > ans;

    while(!QUEUE.empty())
    {
        pair < int, pair < pair< pair< int,int > ,int >, vector <pair <int,int> > > > curr = QUEUE.top();
        QUEUE.pop();
        tempPath=curr.second.second;

        if( (curr.second.first.first.first ==rows) && (curr.second.first.first.second == columns) )
        {
            ans=curr.second.second;
            break;
        } 

        vector <pair <int,int> >nextPossibileMoves = nextUtilFunction(path, rows,columns,curr.second.first.first.first, curr.second.first.first.second);

        for(int i=0;i<nextPossibileMoves.size();i++)
        {
            pair <int,int> coordsNext = nextPossibileMoves[i];
            fuelLeft=(curr.second.first.second-1);

            if( path[curr.second.first.first.first][curr.second.first.first.first] =='P' || 
                     fuelLeft> visitedUtil[curr.second.first.first.first][curr.second.first.first.second])
            {
                if(path[curr.second.first.first.first][curr.second.first.first.first] =='P')
                {
                    fuelLeft=fuelCapacity;
                }
                visitedUtil[curr.second.first.first.first][curr.second.first.first.second]=fuelLeft;
                heuristicValue=heuristicValueCalculator(path,fuelLeft,payToll, coordsNext.first, coordsNext.second);
                
                tempPath.push_back(coordsNext);

                QUEUE.push(make_pair(heuristicValue, make_pair( make_pair( make_pair(coordsNext.first,coordsNext.second)
                                 ,fuelLeft) , tempPath )));
            
                tempPath.pop_back();
            }
            else
            {
                continue;
            }

        }

    }
}
    