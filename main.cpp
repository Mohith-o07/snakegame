#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <unistd.h>
#include<random>  //used to generate random fruits..
#include<chrono>   //header for sleep_for
#include<thread>
#include<fstream>  //header for file handling..
using namespace std;
int t=100,nex=50; //variables used to make the game tougher on scoring more by speeding the flow of game..
bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruitx, fruity;
int tailx[100],taily[100]; //arrays to store coordinates of tail..
int ntail; //length of tail..
int score,f=-1; //variable to store existing high score from the file..
enum edir { STOP = 0, LEFT, RIGHT, UP, DOWN };
edir dir;
string r;
string name,player;
int z=1;

void setCursorPosition(int x, int y)  //set the position of the board on screen..
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void setup()
{
    score=0;
    f=-1;
    t=100;
    nex=50;
    for(int i=0;i<100;i++)
    {
        tailx[i]=0;
        taily[i]=0;
    }
    ntail=0;
    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    random_device rd;
    mt19937 gen(rd()); //seed
    uniform_int_distribution<> distribx(1,19);
    uniform_int_distribution<> distriby(0,19);
    fruitx = distribx(gen);
    fruity = distriby(gen);
    score = 0;
}

void draw()
{
    setCursorPosition(0, 8);
    for (int i = 0; i <= width; i++)
        cout << "X";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <=width; j++)
        {
            if (j == 0 || j == width)
                cout << "#";
            else if (i == y && j == x)
                cout << "O";
            else if (i == fruity && j == fruitx)
                cout << "F";
            else
            {
                bool print=false;
                for(int k=0;k<ntail;k++)
                {
                    if(tailx[k]==j and taily[k]==i)
                    {
                        cout<<"o";
                        print=true;
                    }
                }
                if(!print)
                    cout<<" ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i <= width; i++)
        cout << "X";
    cout << endl;

    cout << "\nscore : " << score << endl;
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'm':
            gameover = true;
        }
    }
}

void logic()
{
    int prevx=tailx[0];
    int prevy=taily[0];
    int prev2x,prev2y;
    tailx[0]=x;
    taily[0]=y;
    for(int i=1;i<ntail;i++)
    {
        prev2x=tailx[i];
        prev2y=taily[i];
        tailx[i]=prevx;
        taily[i]=prevy;
        prevx=prev2x;
        prevy=prev2y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (/*x > width - 1 || x < 1 || */y > height - 1 || y < 0)
    {
        gameover = true;
        cout<<"you hit the barriers!\n";
    }
        if(x>=width)
            x=1;
        else if(x<1)
            x=width;
        for(int i=0;i<ntail;i++)
        {
            if(tailx[i]==x and taily[i]==y)
            {
            gameover=true;
            cout<<"snake is eating its OWN tail!"<<endl;
            }
        }
    if (x == fruitx && y == fruity)
    {
        score += 10;
         random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distribx(1,19);
        uniform_int_distribution<> distriby(0,19);
        fruitx = distribx(gen) % width;
        fruity = distriby(gen) % height;
        ntail++;
    }
}

int main()
{
    while(z)
    {
    cout<<"\t\t\t\t\t  --- SNAKE GAME ---\n";
    cout<<"\t\t\t\t\t\tRULES:"<<endl;
    cout<<"\t\t\t\t(1)direction\t--->\tkey\n";
    cout<<"\t\t\t\tup\t--->\tw\tleft\t--->\ta\n";
    cout<<"\t\t\t\tdown\t--->\ts\tright\t--->\td\n";
    cout<<"\t\t\t\t(2)snake should not eat its tail.\n";
    cout<<"\t\t\t\t(3)press m to exit the game.\n";
    cout<<"\t\t\t\t(4)XXXXXX are walls (do not hit them).\n";

    // Hide the console cursor
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    setup();
    while (!gameover)
    {
        draw();
        input();
        logic();
        this_thread::sleep_for(chrono::milliseconds(t));
        if(score==nex and t!=0)
        {
            t-=25;
            nex+=50;
        }
    }
    // Show the console cursor before exiting
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    ifstream fin("scores.txt");
    fin>>f>>player;
    fin.close();
    if(score==f)
    {
        cout<<"You equaled the highest score!\n";
        cout<<"High score : "<<score<<endl;
        cout<<"player: "<<player<<endl;
    }
    else if(score>f)
    {
        cout<<"You set the new high score!\n";
        cout<<"New high score : "<<score<<endl;
        cout<<"enter your name: ";
        cin>>name;
        ofstream fout("scores.txt");
        fout<<score<<"\t"<<name;
        fout.close();
    }
    else
    {
        cout<<"High score : "<<f<<endl;
        cout<<"player: "<<player<<endl;
    }
    cout<<"Game over!\n";
    cout<<"do you want to play again? yes/no: ";
    cin>>r;
    while(1)
        {
            if(r=="no")
            {
                z=0;
                break;
            }
    else if(r=="yes")
    {
        system("cls");
        break;
    }
    else{
        cout<<"error! check the word you entered\n";
        cout<<"do you want to play again? yes/no: ";
        cin>>r;
    }
        }
}
    return 0;
}
