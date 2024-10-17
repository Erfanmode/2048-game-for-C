#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
// project of group 

void pr (void);

char s[1000][20];

int b=0;

int e=0;

int v[1000];

int max_array;

int pre_max_array;

int score=0;// score should be a global parameter

int previous_score=0;

int stuck_moves=0;

int signal=0;// 2 is for checking if you won.1 for impossible move.0 for normal move.3 for continuing a saved game

void startgame(int n, int m, int board[n][m]);

int organize(char direcrion, int n, int m, int board[n][m]);

int fill_rand(int n, int m, int board[n][m]);

void printboard(int n, int m, int board[n][m]);

void initia0(int n, int m, int board[n][m]);

void assign_array(int n, int m, int board[n][m], int un[n][m]);

int is_array_same(int n, int m, int board[n][m], int clone[n][m]);

int notfilled(int n, int m, int board[n][m]);

void save_scores(int n, int m);

int top_scores(int a, int b);

void bubble(int n, int number[100], int scores[100]);

int maximum_array(int n, int m, int board[n][m]);

int main()

{
    srand(time(NULL));

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole,

    FOREGROUND_GREEN);

    pr();

    int n,m; //n and m are the the dimension of your board

    scanf ("%d%d",&n,&m);// you can put any number for n and m

    int board[n][m];

    initia0(n,m,board);

    startgame(n,m,board);

    printf ("\n");

    return 0;

}

void startgame(int n,int m,int board[n][m])

{


    char direction;

    pre_max_array=maximum_array(n,m,board);

    max_array=pre_max_array;

    int isnotfin=1;

    int un[n][m];


    assign_array(n,m,un,board);

    previous_score=score;

    if(signal!=3)fill_rand(n,m,board);// we use it if we are stating a new game

     signal=0;

    printboard(n,m,board); //which cleans the console and prints whole board and the random 2 and asks for direction
                           //it also print the score.This printboard is temporary and we need a better and more detailed one
      while(isnotfin)

      {

         scanf(" %c",&direction);

         if(direction=='b')

           {

               assign_array(n,m,board,un);

               isnotfin=1;

               score=previous_score;

               max_array=pre_max_array;

           }



          else
               {

                    assign_array(n,m,un,board);//2 is for invalid move

                    previous_score=score;

                     pre_max_array=max_array;

                    isnotfin=organize(direction,n,m,board);// organize and update score and return if game still continues

               }

         if(direction!='z') printboard(n,m,board);

      }

   if(direction!='z') { save_scores(n,m);


                      if(max_array>=2048)

                       {

                       printf("\nYou won with score of ");

                         printf("\n");
                         printf ("%d",score);

                       }

                   else

                      {

                           printf("\nYour final score is ");

                           printf("\n");

                           printf("%d",score);

                       }
                     }
      return;

}


int organize(char direction, int n, int m, int board[n][m])

{

    int clone[n][m];

    int filled[n][m];

    assign_array(n,m,clone,board);





    int i,j,empty,hold;




    if (direction=='z')  // if you press z you will be able to continue a saved game but be careful that
                         //the dimension of saved game should be same with the current game
    {

        char *filename = "test.txt";

        FILE *fp = fopen(filename, "r");

        if (fp == NULL)

        {

        printf("Error: could not open file %s", filename);

        return 1;

        }



        int i=0;

        fscanf(fp,"%d %d",&n,&m);

        int a[n][m];

        while (i<n)

              {

                 int j=0;

                 while (j<m)

                       {

                         fscanf(fp,"%d",&a[i][j]);

                         j++;

                       }

                i++;

             }

        int q;

        fscanf(fp,"%d",&q);

        fclose(fp);

        signal=3;

        score =q;

        startgame(n,m,a);

        return 0;



    }
    //**************************************************
    if (direction=='u')   //if you press u you can save your game

       {

          char *filename = "test.txt";

          FILE *fp = fopen(filename, "w");

          if (fp == NULL)

             {

                printf("Error opening the file %s", filename);

                return 1;

             }
             fprintf(fp,"%d %d\n",n,m);

          int i = 0;

          for ( i = 0;i < n; i++)

              {

                 int j=0;

                 while (j<m)

                       {

                          fprintf(fp, "%d ", board[i][j]);

                          j++;

                       }

                 fprintf(fp,"\n");

              }
          fprintf(fp, "%d ",score);

          fclose(fp);

      }
    //****************************************************

    if (direction=='d')

       {

          for(i=0;i<n;i++)

             {

                 empty=0;

                 for(j=m-1;j>=0;j--)

                    {

                       if(board[i][j]==0)

                            empty++;

                       else

                         {

                            hold=board[i][j];

                            board[i][j]=0;

                            board[i][j+empty]=hold;

                         }

                    }

            }

         for(i=0;i<n;i++)

            {

               for(j=m-1;j>0;j--)

                  {

                     if(board[i][j]==board[i][j-1])

                       {

                          hold=2*board[i][j];

                          score+=hold;

                          if(max_array<hold)max_array=hold;

                          board[i][j]=0;

                          board[i][j-1]=0;

                          board[i][j]=hold;

                       }

                  }

           }

        for(i=0;i<n;i++)

           {

               empty=0;

               for(j=m-1;j>=0;j--)

                  {

                     if(board[i][j]==0)

                          empty++;

                     else

                         {

                            hold=board[i][j];

                            board[i][j]=0;

                            board[i][j+empty]=hold;

                         }

                 }

           }

    }
//*******************************
    if (direction=='a')

       {

          for(i=0;i<n;i++)

             {

                empty=0;

                for(j=0;j<m;j++)

                   {

                      if(board[i][j]==0)

                           empty++;

                      else

                        {

                            hold=board[i][j];

                            board[i][j]=0;

                            board[i][j-empty]=hold;

                        }

                   }

             }

          for(i=0;i<n;i++)

             {

                for(j=0;j<m-1;j++)

                   {

                        if (board[i][j]==board[i][j+1])

                          {

                             hold=2*board[i][j];

                             score+=hold;

                             if(max_array<hold)max_array=hold;

                             board[i][j]=0;

                             board[i][j+1]=0;

                             board[i][j]=hold;

                          }

                   }

            }


         for(i=0;i<n;i++)

            {

                empty=0;

                for(j=0;j<m;j++)

                   {

                      if(board[i][j]==0)

                           empty++;

                      else

                         {

                            hold=board[i][j];

                            board[i][j]=0;

                            board[i][j-empty]=hold;

                         }

                   }

            }

    }

//*******************************


  if (direction=='w')

     {

        for(j=0;j<m;j++)

           {

               empty=0;

               for(i=0;i<n;i++)

                  {

                     if(board[i][j]==0)

                          empty++;

                     else

                       {

                          hold=board[i][j];

                          board[i][j]=0;

                          board[i-empty][j]=hold;

                       }

                  }

           }


        for(j=0;j<m;j++)

           {

              for(i=0;i<n-1;i++)

                 {

                    if(board[i][j]==board[i+1][j])

                      {

                          hold=2*board[i][j];

                          score+=hold;

                          if(max_array<hold)max_array=hold;

                          board[i][j]=0;

                          board[i+1][j]=0;

                          board[i][j]=hold;

                      }

                }

            }

         for(j=0;j<m;j++)

            {

                empty=0;

                for(i=0;i<n;i++)

                   {

                      if(board[i][j]==0)

                           empty++;

                      else

                        {

                           hold=board[i][j];

                           board[i][j]=0;

                           board[i-empty][j]=hold;

                        }

                   }

            }

    }
//*******************************

    if (direction=='s')

       {

          for(j=0;j<m;j++)

             {

                empty=0;

                for(i=n-1;i>=0;i--)

                   {

                      if(board[i][j]==0)

                           empty++;

                      else

                        {

                           hold=board[i][j];

                           board[i][j]=0;

                           board[i+empty][j]=hold;

                        }

                   }

             }


          for(j=0;j<m;j++)

             {

                 empty=0;

                 for(i=n-1;i>0;i--)

                    {

                       if(board[i][j]==board[i-1][j])

                         {

                            hold=2*board[i][j];

                            score+=hold;

                            if(max_array<hold)max_array=hold;

                            board[i][j]=0;

                            board[i-1][j]=0;

                            board[i][j]=hold;

                         }

                    }

              }


           for(j=0;j<m;j++)

              {

                  empty=0;

                  for(i=n-1;i>=0;i--)

                     {

                        if(board[i][j]==0)

                            empty++;

                        else

                          {

                             hold=board[i][j];

                             board[i][j]=0;

                             board[i+empty][j]=hold;

                          }

                     }

              }

    }


//**********************************



if (direction=='m')

{

    return 0;

}

if(direction=='h')

{

    int a,b,is_found;

    char useless;

    printf("\nType the dimension of score table you want to see :");

    scanf("%d %d",&a,&b);

    is_found=top_scores(a,b);

    if(is_found==0)

    {

        printf("\nSuch a score table does not exist\nPress 'c' to continue :");

    }

    scanf(" %c",&useless);

    return 1;

}



//****************************************************************
 if(signal==2)

    score=previous_score;

 if(notfilled(n,m,board))

       {

          if(is_array_same(n,m,board,clone))

            {

               if(direction!='m' && direction!='u' && direction!='z'&&direction!='h') signal=1;

                return 1;

            }

          else

            {
                stuck_moves=0;

                 if(direction!='m' && direction!='u' && direction!='z'&&direction!='h')

                return fill_rand(n,m,board);

                else return 1;
            }
        }

   else

    {

        if(is_array_same(n,m,board,clone))

          { assign_array(n,m,filled,board);

             if(direction!='m' && direction!='u' && direction!='z'&&direction!='h') signal=1;


             stuck_moves++;

              signal=2;

             if(stuck_moves==1)return organize('w',n,m,filled);

             if(stuck_moves==2)return organize('s',n,m,filled);

             if(stuck_moves==3)return organize('a',n,m,filled);

             if(stuck_moves==4)return organize('d',n,m,filled);


             if(stuck_moves==5)

               {

                   return 0;

               }


             else

                {

                    return 1;

                }

          }

          else

            {

                return 1;

            }


       }



//*******************************

}

int fill_rand(int n, int m, int board[n][m])

{

    int random;

    if(max_array>2048)

        random=8;

    else if(max_array>256)

        random=4;

    else random=2;

    int i,j,empties=0,address2;

    int emp[n*m];

    for(i=0;i<n;i++)

       {

          for(j=0;j<m;j++)

             {

                if(board[i][j]==0)

                  {

                     empties++;

                     emp[empties-1]=i*m+j;

                  }

             }

       }

    if(empties==0)

        return 0;

    address2=emp[rand()%empties];

    *(*board+address2)=random;

    return empties;

}

void printboard(int n, int m, int board[n][m])

{

    int i,j;

    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole,

    FOREGROUND_BLUE);

    printf("press %c for %s\npress %c for %s\npress %c for %s\npress %c for %s\npress %c for %s\n\n",'w',"UP",'s',"DOWN",'d',"RIGHT",'a',"LEFT",'b',"UNDO");

     SetConsoleTextAttribute(hConsole,

    FOREGROUND_GREEN);

    printf("you can enter m to quit game and save your score \n");

    printf("you can enter u to save your current board\n");

    printf("you can enter z to continue a saved game\n");

    printf("you can enter h to see score board\n");

    int k=0;

    while (k<m)

          {

               SetConsoleTextAttribute(hConsole,

               FOREGROUND_RED);

              printf("    _    ");

              k++;

          }

    for(i=0;i<n;i++)

          {

             for(j=0;j<m;j++)

                  {

                     if(j==0)

                           printf("\n\n");

                     if(j==0)

                           printf("|");

                     if(board[i][j])

                     {

                         SetConsoleTextAttribute(hConsole,

                         FOREGROUND_BLUE);

                         printf("%5d   ",board[i][j]);

                         SetConsoleTextAttribute(hConsole,

               FOREGROUND_RED);

                         printf ("|");

                         SetConsoleTextAttribute(hConsole,

                    FOREGROUND_RED);


                     }


                     else printf("        |");



                  }

          }

    printf("\n");

    k=0;

    while (k<m)

          {

             printf("    _    ");

             k++;

          }

    printf("\n");

    SetConsoleTextAttribute(hConsole,

                         FOREGROUND_GREEN);

    printf("score : %d ",score);

    //printf("\n");score;

    printf("\n");

    if(signal)

        {

            printf("\nYour move is not possible try something else\n");

        }

    signal=0;

    return;

}

void initia0(int n, int m, int board[n][m])

{

    int i,j;

    for(i=0;i<n;i++)

       {

          for(j=0;j<m;j++)

             {

                board[i][j]=0;

             }

       }

    return;

}

void assign_array(int n, int m, int board[n][m], int un[n][m])

{

    int i,j;

    for(i=0;i<n;i++)

    {

        for(j=0;j<m;j++)

        {

          board[i][j]=un[i][j];

        }

    }

    return;

}

int is_array_same(int n, int m, int board[n][m], int clone[n][m])

{

    int is_same=1,i,j;

    for(i=0;i<n;i++)

    {

        for(j=0;j<m;j++)

        {

            if(board[i][j] != clone[i][j])

              {

                    is_same=0;

                    break;
              }

        }

    }

    return is_same;
}

int notfilled(int n, int m, int board[n][m])

{

   int not_full=0,i,j;

   for(i=0;i<n;i++)

      {

         for(j=0;j<m;j++)

            {

               if(board[i][j]==0){not_full=1;break;}

            }

     }

    return not_full;

}

void pr (void)

{

    printf("Welcome\n");

    printf("Enter the dimensions of your board\n");

    printf("the first number that you enter is the number of columns and the second one is the number of lines\n");

    return;
}

void save_scores(int n, int m)

{

   FILE *f;

   char file_name[30];

   char user[30];

   printf("\nEnter your name (Don't use space in your name): ");

   scanf("%s",user);

   sprintf(file_name,"%d %d scores.txt",n,m);

   f=fopen(file_name,"a");

   fprintf(f,"%s\n%d\n",user,score);

   fclose(f);

}

int top_scores(int a, int b)

{

    system("cls");

    FILE *f;

    char *user[100];

    int k=0;

    for(k=0;k<100;k++)

    {

        user[k]=(char *)calloc(30,sizeof(char));

    }

    int scores[100];

    int number[100];

    int i,rank;

    char useless;

   char file_name[30];

   sprintf(file_name,"%d %d scores.txt",a,b);

   f=fopen(file_name,"r");

   if(f==NULL)return 0;

   for(i=0;!feof(f);i++)

   {

       number[i]=i;

     fscanf(f,"%s",user[i]);

     fscanf(f,"%d",&scores[i]);

   }

   //i-1 is space and is invalid


   fclose(f);

   bubble(i-2,number,scores);

   int j=0;

   for(j=0;j<i-1;j++)

   {

       rank=number[j];

       printf("%d - %s with score of %d\n",j+1,user[rank],scores[j]);

   }

   printf("Press 'c' to go back to the game ");

   scanf("%c",&useless);

   return 1;

}

void bubble(int n, int number[100], int scores[100])

{

    int holdnum,holdsco,i,j;

   for(i=0;i<n;i++)

   {

       for(j=n;j>i;j--)

       {

           if(scores[j]>scores[j-1])

           {

               holdsco=scores[j];

               scores[j]=scores[j-1];

               scores[j-1]=holdsco;

               holdnum=number[j];

               number[j]=number[j-1];

               number[j-1]=holdnum;

           }

       }

   }

  return;

}

int maximum_array(int n, int m, int board[n][m])

{

    int largest=2,i,j;

   for(i=0;i<n;i++)

   {

       for(j=0;j<m;j++)

       {

           if(board[i][j]>largest)

           largest=board[i][j];

       }

   }

   return largest;

}
