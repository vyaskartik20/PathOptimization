#include <bits/stdc++.h>
using namespace std;
typedef pair < int, pair < pair< pair< int,int >, pair <int , pair<int,int> > >, vector <pair <int,int> > > > queueElement;

int heuristicValueCalculator (vector <vector <char> > &path,int fuelLeft,int fuelCapacity, int payToll, int payTravel, int x, int y,int rows, int columns)
{
    int heuristicValue;

    heuristicValue = rows+columns;
    heuristicValue= heuristicValue - (x+y)-2
    ;
    if(path[x][y]=='T')
    {
        heuristicValue=heuristicValue+(payToll/3);
    }


    heuristicValue=heuristicValue - fuelLeft;

    if(fuelLeft<=0)
    {
        heuristicValue=INT_MAX;
    }

    if(path[x][y]=='H')
    {
        heuristicValue=INT_MAX;
    }

    return heuristicValue;
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
        else if(currCol==(columns-1))
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
    else if(currRow==(rows-1))
    {
        if(currCol==0)
        {
            nextPossibileMoves.push_back({(currRow),(currCol+1)});
            nextPossibileMoves.push_back({(currRow-1),(currCol)});
        }
        else if(currCol==(columns-1))
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
    else if(currCol==(columns-1))
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
    cout <<"***********************\n" <<"!! Welcome !!\n"   <<"\n***********************\n\n";
    
    int rows,columns;
    int fuelCapacity;
    char c_char;
    int c_int;
    int numPumps,numHoles,numTolls;
    int payToll, payTravel;
    int heuristicValue;
    int fuelLeft;
    bool repeat1=true;
    bool repeat2=true;
    vector <vector <char> > path;
    vector <vector <int> > visitedUtil;

    while(repeat1)
    {
        cout <<"Would you like to create a new maze [Y] or use the default one [N]?";
        cin >>c_char;
        repeat1=false;

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
            cout <<"Enter the cost of one traversal, that is the units of fuel that would burn to "
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
        else if(c_char=='N')
        {
            while(repeat2)
            {
                cout <<"Choose the default grid : \n" <<"1 to 7 : \n";
                cin >>c_int;

                if (c_int == 1)
                {
                    // H T O P
                    //   0 1 2 3
                    // 0 P T P O
                    // 1 O O H T
                    // 2 O O O O

                    rows=3;
                    columns=4;

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

                    path[0][0]='P';
                    path[0][2]='P';

                    path[1][2]='H';

                    path[0][1]='T';
                    path[1][3]='T';

                    fuelCapacity=5;
                    payToll=10;
                    payTravel=4;

                    numHoles=1;
                    numTolls=2;
                    numPumps=2;
                
                }
        

                else if(c_int==2)
                {
                    // P _ H _ P
                    // _ _ _ _ _
                    // _ T P _ P
                    // P H _ _ _
                    // H _ _ _ _

                    rows=5;
                    columns=5;

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

                else if (c_int == 3)
                {
                    // H T O P

                    // P O O O O O
                    // P O O O O O
                    // P O P T P O
                    // P O O O O O
                    // P O O H O O
                    // P O P T O O

                    rows=6;
                    columns=6;

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

                    path[0][0]='P';
                    path[1][0]='P';
                    path[2][0]='P';
                    path[3][0]='P';
                    path[4][0]='P';
                    path[5][0]='P';
                    path[2][2]='P';
                    path[1][5]='P';
                    path[2][4]='P';

                    path[4][3]='H';

                    path[5][3]='T';
                    path[2][3]='T';

                    fuelCapacity=4;
                    payToll=10;
                    payTravel=1;

                    numHoles=1;
                    numTolls=2;
                    numPumps=9;
                
                }


                else if (c_int == 4)
                {
                    // H T O P
                    //   0 1 2 3 4 5 6
                    // 0 P T O O H O O
                    // 1 T T O O O O O
                    // 2 H O P T T P O
                    // 3 P T O T O H T
                    // 4 O O P H O O O

                    rows=5;
                    columns=7;

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

                    path[0][0]='P';
                    path[2][2]='P';
                    path[2][5]='P';
                    path[3][0]='P';
                    path[4][2]='P';

                    path[0][4]='H';
                    path[2][0]='H';
                    path[3][5]='H';
                    path[4][3]='H';

                    path[0][1]='T';
                    path[1][0]='T';
                    path[1][1]='T';
                    path[2][3]='T';
                    path[2][4]='T';
                    path[3][1]='T';
                    path[3][3]='T';
                    path[3][6]='T';

                    fuelCapacity=5;
                    payToll=10;
                    payTravel=4;

                    numHoles=4;
                    numTolls=8;
                    numPumps=5;
                
                }

                else if (c_int == 5)
                {
                    // H T O P
                    //   0 1 2 3 4 5 6
                    // 0 P T O O H O O
                    // 1 T T O O O O O
                    // 2 H O P T T P O
                    // 3 P T O T O H T
                    // 4 O O P H O O O

                    rows=5;
                    columns=7;

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

                    path[0][0]='P';
                    path[2][2]='P';
                    path[2][5]='P';
                    path[3][0]='P';
                    path[4][2]='P';

                    path[0][4]='H';
                    path[2][0]='H';
                    path[3][5]='H';
                    path[4][3]='H';

                    path[0][1]='T';
                    path[1][0]='T';
                    path[1][1]='T';
                    path[2][3]='T';
                    path[2][4]='T';
                    path[3][1]='T';
                    path[3][3]='T';
                    path[3][6]='T';

                    fuelCapacity=5;
                    payToll=10;
                    payTravel=15;

                    numHoles=4;
                    numTolls=8;
                    numPumps=5;
                
                }

                else if (c_int ==6)
                {
                    // H T O P

                    // P T O O H O O
                    // T T O O O O O
                    // T O P T P O O
                    // P T O O O O O
                    // O O P H O O O
                    // O O O T P O O
                    // O O P O H P O

                    rows=7;
                    columns=7;

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

                    path[0][0]='P';
                    path[2][2]='P';
                    path[2][4]='P';
                    path[3][0]='P';
                    path[4][2]='P';
                    path[5][4]='P';
                    path[6][2]='P';
                    path[6][5]='P';

                    path[0][4]='H';
                    path[4][3]='H';
                    path[6][4]='H';

                    path[0][1]='T';
                    path[1][0]='T';
                    path[1][1]='T';
                    path[2][0]='T';
                    path[2][3]='T';
                    path[3][1]='T';
                    path[5][3]='T';

                    fuelCapacity=3;
                    payToll=10;
                    payTravel=1;

                    numHoles=3;
                    numTolls=7;
                    numPumps=8;
                
                }

                else if (c_int == 7)
                {
                    // H T O P

                    // P T O P H O O
                    // T T O O O O O
                    // T O P T P O O
                    // P T O O O O O
                    // O O P H O O O
                    // O O O T P O O
                    // O O P O H P O

                    rows=7;
                    columns=7;

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

                    path[0][0]='P';
                    path[0][3]='P';
                    path[2][2]='P';
                    path[2][4]='P';
                    path[3][0]='P';
                    path[4][2]='P';
                    path[5][4]='P';
                    path[6][2]='P';
                    path[6][5]='P';

                    path[0][4]='H';
                    path[4][3]='H';
                    path[6][4]='H';

                    path[0][1]='T';
                    path[1][0]='T';
                    path[1][1]='T';
                    path[2][0]='T';
                    path[2][3]='T';
                    path[3][1]='T';
                    path[5][3]='T';

                    fuelCapacity=3;
                    payToll=10;
                    payTravel=1;

                    numHoles=3;
                    numTolls=7;
                    numPumps=9;
                
                }
                else
                {
                    repeat2=true;
                    cout <<"Enter a valid input\n";
                }
            }
        }
        else
        {
            repeat1=true;
            cout <<"Enter a valid input\n";
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
    tempPath.push_back({0,0});

    // cout <<"hari om 1\n";
     
    priority_queue<queueElement, vector<queueElement>, greater<queueElement> > QUEUE;
    // priority_queue< pair < int, pair < pair< pair< int,int >, int>, vector <pair <int,int> > > > > QUEUE;
    // cout <<"hari om 1\n";
    heuristicValue=heuristicValueCalculator(path,fuelCapacity,fuelCapacity,payToll,payTravel, 0,0,rows,columns);
    // cout <<"hari om 1\n";
    visitedUtil[0][0]=fuelCapacity;
    // cout <<"hari om 1\n";
    QUEUE.push(make_pair(0, make_pair( make_pair( make_pair(0,0) ,make_pair(fuelCapacity, make_pair(0,0) ) ) , tempPath )));

    vector <pair <int,int> > ans;

    // cout <<"hari om 2\n";

    while(!QUEUE.empty())
    {
        // cout <<"hari om 3\n";

        pair < int, pair < pair< pair< int,int > ,pair< int, pair <int,int> > >, vector <pair <int,int> > > > curr = QUEUE.top();
        QUEUE.pop();
        tempPath=curr.second.second;

        int costBase=curr.second.first.second.second.second;

        // cout <<curr.second.first.first.first <<"      " <<curr.second.first.first.second <<"        " <<curr.second.first.second.first <<endl;

        // for(int i=0;i<curr.second.second.size();i++)
        // {
        //     cout <<curr.second.second[i].first <<"        " <<curr.second.second[i].second <<endl;
        // }

        if(ans.size()!=0)
        {
            break;
        }

        // if( ( curr.second.first.first.first ==(rows-1) ) && ( curr.second.first.first.second == (columns-1) ) )
        // {
        //     // cout <<"yesyesyseyseyesyesyseyseyesyesyseyseyesyesyseyseyesyesyseyseyesyesyseyse";
        //     ans=curr.second.second;
        //     break;
        // } 

        // if(curr.first==INT_MIN)
        // {
        //     break;
        // }

        vector <pair <int,int> >nextPossibileMoves = nextUtilFunction(path, rows,columns,curr.second.first.first.first, curr.second.first.first.second);

        for(int i=0;i<nextPossibileMoves.size();i++)
        {
            pair <int,int> coordsNext = nextPossibileMoves[i];
            fuelLeft=(curr.second.first.second.first-1);

            if(path[coordsNext.first][coordsNext.second] =='P')
            {
                fuelLeft=fuelCapacity;
            }

            // cout <<"njkd        "    <<coordsNext.first <<"         " <<coordsNext.second <<"        " <<fuelLeft <<"       ";

            //  path[curr.second.first.first.first][curr.second.first.first.first] =='P' || 
            
            if( ( coordsNext.first ==(rows-1) ) && ( coordsNext.second == (columns-1) ) )
            {
                // cout <<"yesyesyseyseyesyesyseyseyesyesyseyseyesyesyseyseyesyesyseyseyesyesyseyse";
                ans=curr.second.second;
                ans.push_back({(rows-1),(columns-1)});
                break;
            } 

            if(fuelLeft> visitedUtil[coordsNext.first][coordsNext.second])
            {
                // cout <<"yes\n";
                visitedUtil[coordsNext.first][coordsNext.second]=fuelLeft;
                heuristicValue=heuristicValueCalculator(path,fuelLeft,fuelCapacity,payToll, payTravel, coordsNext.first, coordsNext.second,rows,columns);
                // heuristicValue=heuristicValue;

                if(heuristicValue==INT_MAX)
                {
                    // cout <<endl <<"yes" <<endl;
                    continue;
                }
                tempPath.push_back(coordsNext);

                int costTillNow=costBase+payTravel;

                if(path[coordsNext.first][coordsNext.second]=='T')
                {
                    costTillNow=costTillNow+payToll;
                }

                int aStarCost=costTillNow+ heuristicValue;
                // cout <<heuristicValue <<"        " <<costBase  <<"        " <<costTillNow  <<"           " <<aStarCost;

                QUEUE.push(make_pair(aStarCost, make_pair( make_pair( make_pair(coordsNext.first,coordsNext.second)
                                 ,make_pair( fuelLeft , make_pair(heuristicValue, costTillNow ) ) )  , tempPath )));
            

                tempPath.pop_back();
            }
            else
            {
                // cout <<endl;
                continue;
            }
            // cout <<endl;


        }
        // cout <<endl;



    }

    // cout <<endl <<endl <<endl;

    if(ans.empty())
    {
        cout  <<"No path exists to reach the end point \n\n";
    }
    else
    {
        cout <<"The most optimzed path is : \n";
        for(int i=0;i<ans.size();i++)
        {
            cout <<ans[i].first <<"     " <<ans[i].second <<endl;
        }
    }

}
    