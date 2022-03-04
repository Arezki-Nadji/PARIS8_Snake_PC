#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "random.h"
#include <pthread.h>

#define N 20
#define M 40
int i,j,Field[N][M],Cheery,a,b,var,HighScore,speed,fruit;

static int GameCount = 0;
static pthread_mutex_t Mutex;
typedef struct snake
{
    int x, y;
    int Head, Tail, Gy;
    int direction;
    int Game;
    int Score;
    int Frame;


} snake;

void gameOver(snake *Snake);


static int frame = 0;
void *snakeIntialization(snake *Snake, int snakeIndex)
{


    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            Field[i][j]=0;
        }
    }
    Snake->x=5 + snakeIndex * 2;
    Snake->y=5 + snakeIndex * 10;
    Snake->Head=1;
    Snake->Tail=1;
    Snake->Gy=Snake->y;
    Snake->Game =0;
    Snake->Score=0;
    speed=20;

    for(i=0;i<Snake->Head;i++)
    {
        Snake->Gy++;
        Field[Snake->x][Snake->Gy-Snake->Head]=i+1;
    }
}
void DrawTheField(snake *SnakeList, int SnakeCount)
{
    printf("Current Score: \n");
        for(int i = 0; i < SnakeCount; i++)
    {
     snake *Snake = SnakeList + i;

        printf("Snake %d : %d ",i+1, Snake->Score);
        if (Snake->Game == 0)
        {
            printf(" (Alive) ");
        }
        else printf(" (Dead) ");
        printf("\n");
    }

    for(i =0;i<=M+1;i++)
    {
        if(i==0){
            printf("%c",201);

        }else if(i==M+1)
        {
            printf("%c",187);
        }else
        {
            printf("%c",205);
        }
    }
    printf("\n");


    for(i=0;i<N;i++)
    {
        printf("%c",186);
        for(j=0;j<M;j++)
        {
            if(Field[i][j]==0) printf(" ");
            if(Field[i][j]>0 && Field[i][j] != SnakeList->Head) printf("%c",178) ;
            if(Field[i][j]==SnakeList->Head) printf("%c",178);
            if(Field[i][j]==-1) printf("%c",15);
            if(Field[i][j]==-2) printf("%c",229);
            if(Field[i][j]==-3) printf("%c",42);
            if(Field[i][j]==-4) printf("%c",248);
            if(j==M-1) printf("%c\n",186);
        }
    }
        for(i =0;i<=M+1;i++)
    {
        if(i==0){
            printf("%c",200);

        }else if(i==M+1)
        {
            printf("%c",188);
        }else
        {
            printf("%c",205);
        }
    }
}
void ResetScreenPosition()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X=0;
    Position.Y=0;
    SetConsoleCursorPosition(hOut,Position);
}
Random()
{
    srand(time(0));
    a= 1+ rand()%N-2;
    b= 1+ rand()%M-2;
    fruit = rand()%4;
    if(Cheery == 0 && Field[a][b]==0 && fruit==0)
    {
        Field[a][b]=-1;
        Cheery= 1;
    }
    if(Cheery == 0 && Field[a][b]==0 && fruit==1)
    {
        Field[a][b]=-2;
        Cheery= 1;
    }
    if(Cheery == 0 && Field[a][b]==0 && fruit==2)
    {
        Field[a][b]=-3;
        Cheery= 1;
    }
    if(Cheery == 0 && Field[a][b]==0 && fruit==3)
    {
        Field[a][b]=-4;
        Cheery= 1;
    }
}
void movement(int var, snake *Snake)
{

    if(var ==0)
    {
        Snake->y++;
        if (Snake->y > M - 1)
        {
            Snake->y = 0;
        }

        if(Field[Snake->x][Snake->y]!=0 && Field[Snake->x][Snake->y]!=-1 && Field[Snake->x][Snake->y]!=-2 && Field[Snake->x][Snake->y]!=-3 &&Field[Snake->x][Snake->y]!=-4) gameOver(Snake);
        pthread_mutex_lock(&Mutex);
        if(Field[Snake->x][Snake->y]==-1)
        {
            Cheery=0;
            Snake->Score +=5;
            Snake->Head+=1;
            Random();
        }
        if(Field[Snake->x][Snake->y]==-2)
        {
            Cheery=0;
            Snake->Score +=3;
            Snake->Head+=1;
            Random();
        }
        if(Field[Snake->x][Snake->y]==-3)
        {
            Cheery=0;
            Snake->Score +=2;
            Snake->Head+=1;
            Random();
        }
        if(Field[Snake->x][Snake->y]==-4)
        {
            Cheery=0;
            Snake->Score +=1;
            Snake->Head+=1;
            Random();
        }
        Snake->Head ++;
        Field[Snake->x][Snake->y]=Snake->Head;
                TailRemove(Snake);
        pthread_mutex_unlock(&Mutex);


    }

     if(var == 1)
    {


        Snake->y--;

        if (Snake->y < 0)
        {
            Snake->y = M - 1;
        }

        if(Field[Snake->x][Snake->y]!=0 && Field[Snake->x][Snake->y]!=-1 && Field[Snake->x][Snake->y]!=-2 && Field[Snake->x][Snake->y]!=-3 &&Field[Snake->x][Snake->y]!=-4) gameOver(Snake);
        pthread_mutex_lock(&Mutex);
        if(Field[Snake->x][Snake->y]==-1)
        {
            Cheery=0;
            Snake->Score+=5;
            Snake->Head +=1;
            Random();
        }
         if(Field[Snake->x][Snake->y]==-2)
        {
            Cheery=0;
            Snake->Score +=3;
            Snake->Head+=1;
            Random();
        }
        if(Field[Snake->x][Snake->y]==-3)
        {
            Cheery=0;
            Snake->Score +=2;
            Snake->Head+=1;
            Random();
        }
        if(Field[Snake->x][Snake->y]==-4)
        {
            Cheery=0;
            Snake->Score +=1;
            Snake->Head+=1;
            Random();
        }

        Snake->Head ++;
        Field[Snake->x][Snake->y]=Snake->Head;
        TailRemove(Snake);
        pthread_mutex_unlock(&Mutex);

    }
     if(var ==2)
    {

        Snake->x--;

        if (Snake->x < 0)
        {
            Snake->x = N - 1;
        }

        if(Field[Snake->x][Snake->y]!=0 && Field[Snake->x][Snake->y]!=-1 && Field[Snake->x][Snake->y]!=-2 && Field[Snake->x][Snake->y]!=-3 &&Field[Snake->x][Snake->y]!=-4) gameOver(Snake);
        pthread_mutex_lock(&Mutex);
        if(Field[Snake->x][Snake->y]==-1)
        {
            Cheery=0;
            Snake->Score+=5;
            Snake->Head +=1;
            Random();
        }
         if(Field[Snake->x][Snake->y]==-2)
        {
            Cheery=0;
            Snake->Score +=3;
            Snake->Head +=1;
            Random();
        }
        if(Field[Snake->x][Snake->y]==-3)
        {
            Cheery=0;
            Snake->Score +=2;
            Snake->Head +=1;
            Random();
        }
        if(Field[Snake->x][Snake->y]==-4)
        {
            Cheery=0;
            Snake->Score +=1;
            Snake->Head +=1;
            Random();
        }

        Snake->Head ++;
        Field[Snake->x][Snake->y]=Snake->Head;
                TailRemove(Snake);
        pthread_mutex_unlock(&Mutex);

    }
    if(var ==3 )
    {

        Snake->x++;

        if (Snake->x > N - 1)
        {
            Snake->x = 0;
        }

        if(Field[Snake->x][Snake->y]!=0 && Field[Snake->x][Snake->y]!=-1 && Field[Snake->x][Snake->y]!=-2 && Field[Snake->x][Snake->y]!=-3 &&Field[Snake->x][Snake->y]!=-4) gameOver(Snake);
        pthread_mutex_lock(&Mutex);
        if(Field[Snake->x][Snake->y]==-1)
        {
            Cheery=0;
            Snake->Score =+5;
            Snake->Head +=1;
            Random();
        }
         if(Field[Snake->x][Snake->y]==-2)
        {
            Cheery=0;
            Snake->Score +=3;
            Snake->Head +=1;
            Random();
        }
        if(Field[Snake->x][Snake->y]==-3)
        {
            Cheery=0;
            Snake->Score +=2;
            Snake->Head +=1;
            Random();
        }
        if(Field[Snake->x][Snake->y]==-4)
        {
            Cheery=0;
            Snake->Score +=1;
            Snake->Head +=1;
            Random();
        }

        Snake->Head ++;
        Field[Snake->x][Snake->y]=Snake->Head;
                TailRemove(Snake);
        pthread_mutex_unlock(&Mutex);
    }


}

void TailRemove(snake *Snake)
{
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            if(Field[i][j]==Snake->Tail)
                {
                    Field[i][j]=0;
                }
        }
    }
    Snake->Tail++;
}
void gameOver(snake *Snake)
{
    Snake->Game =1;
    GameCount--;
        for(i=0;i<Snake->Head;i++)
    {
        Snake->Gy++;
        Field[Snake->x][Snake->Gy-Snake->Head]=0;
    }

}

void UpdateSnake(snake *Snake)
{
    srand(time(0));
    static int F = 0;
    if(1)
    {

        if (Snake->Game == 0)
        {

            if(Snake->Frame%1==0)
            {
                int lastDirection = Snake->direction;
                while(1){

                    Snake->direction = (rand() + F)%4;
                    if(Snake->direction==0 && lastDirection!=1)
                        break;
                    if(Snake->direction==1 && lastDirection!=0)
                        break;
                    if(Snake->direction==2 && lastDirection!=3)
                        break;
                    if(Snake->direction==3 && lastDirection!=2)
                        break;

                    Snake->Frame++;
                }
            }
            Snake->Frame++;
            movement(Snake->direction, Snake);
        }

    }
   F++;
}

void gameStartForSpek(snake *SnakeList, int SnakeCount)
{

    frame = rand() % 5000;
    int direction=0;



    GameCount = SnakeCount;
    Random();
    while(1)
    {
        // pthread_mutex_lock(&Mutex);
        DrawTheField(SnakeList, SnakeCount);
        ResetScreenPosition();
        //Random();

       pthread_t *thread_group = malloc(sizeof(pthread_t)*SnakeCount);
         for(int i = 0; i < SnakeCount; i++)
        {

            snake *Snake = SnakeList + i;

            pthread_create(thread_group + i, NULL, UpdateSnake, Snake);
        }

            for(int i = 0;i<SnakeCount;i++)
            {
                 pthread_join(thread_group[i],NULL);
            }

        if (GameCount == 0)break;
       // pthread_mutex_unlock(&Mutex);
        Sleep(speed);
    }



}
void main(int argc, char **argv)
{

    Mutex = PTHREAD_MUTEX_INITIALIZER;
    int SnakeCount = 4;
    snake *SnakeList = (snake *)calloc(1, sizeof(snake) * SnakeCount);
    for(int i = 0; i < SnakeCount; i++)
    {
        snakeIntialization(SnakeList + i, i);
    }
    gameStartForSpek(SnakeList, SnakeCount);

        printf("\a");


}




