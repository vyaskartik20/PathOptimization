#include <bits/stdc++.h>
using namespace std;
typedef pair < int, pair < pair< pair< int,int >, pair <int , int > >, vector <pair <int,int> > > > queueElement;

int heuristicValueCalculator (vector <vector <char> > &path,int fuelLeft,int fuelCapacity, int payToll, int payTravel, int paySlowTravel, int x, int y,int rows, int columns)
{
    int heuristicValue;

    heuristicValue = rows+columns;
    heuristicValue= heuristicValue - (x+y)-2;

    if(path[x][y]=='T')
    {
        heuristicValue=heuristicValue+(payToll/3);
    }

    if(path[x][y]=='S')
    {
        heuristicValue=heuristicValue+(paySlowTravel-payTravel);
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
    cout <<"\n***********************\n" <<"!! Welcome !!\n"   <<"\n***********************\n\n";
    
    int rows,columns;
    int fuelCapacity;
    char c_char;
    int c_int;
    int numPumps,numHoles,numTolls,numSlowPaths;
    int payToll, payTravel,paySlowTravel;
    int heuristicValue;
    int costOfTheSolution;
    int fuelLeft;
    bool repeat1=true;
    bool repeat2=true;
    vector <vector <char> > path;
    vector <vector <int> > visitedUtil;
    vector <char> gridElement;
    gridElement.push_back('O');
    gridElement.push_back('H');
    gridElement.push_back('P');
    gridElement.push_back('S');
    gridElement.push_back('T');

    while(repeat1)
    {
        cout <<"Would you like to create a new maze [Enter N] or use the default one [Enter D] or create a randomly generated matrix [Enter R]? \n";
        cin >>c_char;
        repeat1=false;

        if(c_char=='N')
        {
            cout <<"Enter the dimensions of the path [ROW x COLUMN]\n";
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
            cout <<"Enter the cost of one traversal, that is the units of fuel that would burn. "
                <<"One unit of fuel cost one amount of money\n";
            cin >> payTravel;
            cout << "Enter the units of amount needed to be paid on one toll tax station\n";
            cin >> payToll;
            cout <<"Enter the cost of one traversal on a slow path (traffic), that is the units of fuel that would burn. 0"
                <<"One unit of fuel cost one amount of money\n";
            cin >> paySlowTravel;
            

            cout <<"Enter the number of petrol pumps in the entire path\n";
            cin >>numPumps;
            cout <<"Enter the coordinates of the petrol pumps [X,Y] one by one\n";
            for(int i=0;i<numPumps;i++)
            {
                int x,y;
                cin >>x >>y;
                path[x][y]='P';
            }

            cout <<"Enter the number of toll tax stops in the entire path\n";
            cin >>numTolls;
            cout <<"Enter the coordinates of the toll tax stops [X,Y] one by one\n";
            for(int i=0;i<numTolls;i++)
            {
                int x,y;
                cin >>x >>y;
                path[x][y]='T';
            }

            cout <<"Enter the number of holes in the entire path\n";
            cin >>numHoles;
            cout <<"Enter the coordinates of the holes [X,Y] one by one\n";
            for(int i=0;i<numHoles;i++)
            {
                int x,y;
                cin >>x >>y;
                path[x][y]='H';
            }

            cout <<"Enter the number of slow paths caused due to traffic in the entire path\n";
            cin >>numSlowPaths;
            cout <<"Enter the coordinates of the slow paths [X,Y] one by one\n";
            for(int i=0;i<numSlowPaths;i++)
            {
                int x,y;
                cin >>x >>y;
                path[x][y]='S';
            }

        }
        else if(c_char=='D')
        {
            while(repeat2)
            {
                cout <<"Choose the default grid : \n" <<"1 to 7 : \n";
                cin >>c_int;
                repeat2=false;

                if (c_int == 1)
                {
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

                    path[1][0]='S';
                    path[2][0]='S';

                    fuelCapacity=5;
                    payToll=10;
                    payTravel=4;
                    paySlowTravel=15;

                    numHoles=1;
                    numTolls=2;
                    numPumps=2;
                    numSlowPaths=2;

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

                    path[1][0]='S';
                    path[2][0]='S';
                    path[2][3]='S';

                    fuelCapacity=3;
                    payToll=10;
                    payTravel=1;
                    paySlowTravel=3;

                    numHoles=3;
                    numTolls=1;
                    numPumps=5;
                    numSlowPaths=3;
                }

                else if (c_int == 3)
                {
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

                    path[1][1]='S';
                    path[3][2]='S';
                    path[1][3]='S';
                    path[3][3]='S';
                    path[4][5]='S';

                    fuelCapacity=4;
                    payToll=10;
                    payTravel=1;
                    paySlowTravel=3;

                    numHoles=1;
                    numTolls=2;
                    numPumps=9;
                    numSlowPaths=5;

                }


                else if (c_int == 4)
                {
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

                    path[0][2]='S';
                    path[1][3]='S';

                    fuelCapacity=5;
                    payToll=10;
                    payTravel=4;
                    paySlowTravel=6;

                    numHoles=4;
                    numTolls=8;
                    numPumps=5;
                    numSlowPaths=2;
                
                }

                else if (c_int == 5)
                {
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

                    path[2][3]='S';
                    path[4][6]='S';

                    fuelCapacity=5;
                    payToll=10;
                    payTravel=15;
                    paySlowTravel=15;

                    numHoles=4;
                    numTolls=8;
                    numPumps=5;
                    numSlowPaths=2;
                
                }

                else if (c_int ==6)
                {
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

                    path[2][0]='S';
                    path[4][1]='S';
                    path[5][2]='S';
                    path[6][6]='S';

                    fuelCapacity=3;
                    payToll=10;
                    payTravel=1;
                    paySlowTravel=3;

                    numHoles=3;
                    numTolls=7;
                    numPumps=8;
                    numSlowPaths=4;
                
                }

                else if (c_int == 7)
                {
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

                    path[0][1]='S';
                    path[2][0]='S';
                    path[4][1]='S';
                    path[5][2]='S';
                    path[6][6]='S';

                    fuelCapacity=3;
                    payToll=10;
                    payTravel=1;
                    paySlowTravel=4;

                    numHoles=3;
                    numTolls=7;
                    numPumps=9;
                    numSlowPaths=5;
                
                }
                else
                {
                    repeat2=true;
                    cout <<"Enter a valid input\n";

                }
            }
        }
        else if(c_char=='R')
        {
            rows=(11-(rand()%10));
            columns=(11-(rand()%10));

            // cout <<rows <<"     "  <<columns <<endl;

            numHoles=0;
            numTolls=0;
            numPumps=0;
            numSlowPaths=0;            

            path.resize(rows);
            visitedUtil.resize(rows);
            for (int i=0; i<rows; i++)
            {
                path[i].resize(columns);
                visitedUtil[i].resize(columns);
                for(int j=0;j<columns;j++)
                {
                    int temp=rand()%5;
                    path[i][j]=gridElement[temp];
                    visitedUtil[i][j]=0;

                    if(gridElement[temp]=='P')
                    {
                        numPumps++;
                    }

                    else if(gridElement[temp]=='H')
                    {
                        numHoles++;
                    }

                    else if(gridElement[temp]=='T')
                    {
                        numTolls++;
                    }

                    else if(gridElement[temp]=='S')
                    {
                        numSlowPaths++;
                    }

                    else 
                    {
                        continue;
                    }
                }
            }
            if(path[0][0]!='P')
            {
                path[0][0]='P';
                numPumps++;
            }

            fuelCapacity=(rows+columns)/3;
            if(fuelCapacity<2)
            {
                fuelCapacity=2;
            }
            payToll=10;
            payTravel=1;
            paySlowTravel=3;

        }
        else
        {
            repeat1=true;
            cout <<"Enter a valid input 1\n";
        }
        
    }


    cout <<"\nThe path is : \n\n";
    
    cout <<"  ";
    for(int j=0;j<columns;j++)
    {
        cout <<j <<" ";
    }
    cout <<endl;

    for(int i=0;i<rows;i++)
    {
        cout <<i <<" ";
        for(int j=0;j<columns;j++)
        {
            cout <<path[i][j] <<" ";
        }
        cout <<endl;
    }

    cout <<"\nThe fuel capacity of the vehicle is : " <<fuelCapacity <<"\n";
    cout <<"The cost of one traversal is : " <<payTravel <<"\n";
    cout << "The cost of one traversal for slow path due to traffic is : " <<paySlowTravel <<"\n";
    cout << "The units of amount needed to be paid on one toll tax station is : " <<payToll <<"\n\n";

    vector <pair<int,int>> tempPath;
    tempPath.push_back({0,0});

     
    priority_queue<queueElement, vector<queueElement>, greater<queueElement> > QUEUE;

    heuristicValue=heuristicValueCalculator(path,fuelCapacity,fuelCapacity,payToll,payTravel,paySlowTravel, 0,0,rows,columns);
    visitedUtil[0][0]=fuelCapacity;
    QUEUE.push(make_pair(0, make_pair( make_pair( make_pair(0,0) ,make_pair(fuelCapacity, 0 ) ) , tempPath )));

    vector <pair <int,int> > ans;

    while(!QUEUE.empty())
    {
        pair < int, pair < pair< pair< int,int > ,pair< int, int > >, vector <pair <int,int> > > > curr = QUEUE.top();
        QUEUE.pop();
        tempPath=curr.second.second;

        int costBase=curr.second.first.second.second;

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

                costOfTheSolution= costBase;
                costOfTheSolution=costOfTheSolution+payTravel;
                if(path[coordsNext.first][coordsNext.second]=='T')
                {
                    costOfTheSolution=costOfTheSolution+payToll;
                }
                else if(path[coordsNext.first][coordsNext.second]=='S')
                {
                    costOfTheSolution=costOfTheSolution+(paySlowTravel-payTravel);
                }

                break;
            } 

            if(fuelLeft> visitedUtil[coordsNext.first][coordsNext.second])
            {
                // cout <<"yes\n";
                visitedUtil[coordsNext.first][coordsNext.second]=fuelLeft;
                heuristicValue=heuristicValueCalculator(path,fuelLeft,fuelCapacity,payToll, payTravel, paySlowTravel, coordsNext.first, coordsNext.second,rows,columns);
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

                else if(path[coordsNext.first][coordsNext.second]=='S')
                {
                    costTillNow=costTillNow+(paySlowTravel-payTravel);
                }

                int aStarCost=costTillNow+ heuristicValue;
                // cout <<heuristicValue <<"        " <<costBase  <<"        " <<costTillNow  <<"           " <<aStarCost;

                QUEUE.push(make_pair(aStarCost, make_pair( make_pair( make_pair(coordsNext.first,coordsNext.second)
                                 ,make_pair( fuelLeft ,  costTillNow  ) )  , tempPath )));
            

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

    if(ans.empty())
    {
        cout  <<"No path exists to reach the end point \n\n";
    }
    else
    {
        cout <<"The most optimzed path is : \n";
        for(int i=0;i<ans.size();i++)
        {
            cout <<ans[i].first <<"    " <<ans[i].second <<endl;
        }

        cout <<"The total cost [toll tax stations + petrol cost for traversing of both types of road] "
        "of the most optimzed path is :  " <<costOfTheSolution <<" \n\n";

    }

}
    