///P5_1190270_Nour Naji_SectionNo.2
#include <stdio.h>
#include <stdlib.h>
#define MAX 354
#define INFINITY 99999


//the node structure containing multiple data with different types .
struct Edge
{
    int Dictance;
    char name[40];
};
typedef struct Edge node ;
//Array
node Graph[MAX][MAX];
int numOfCities;

//Dijkstra’s algorithm..
void DijkstraFunction(node Graph[MAX][MAX], int n, int start,int Goal)
{
    FILE *out;
    out = fopen("route.txt","a");
    int weigh[MAX][MAX],distance[MAX], predecessor[MAX],visited[MAX],count, mindistance, nextnode, i, j;

    // Creating first weigh  between two Matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (Graph[i][j].Dictance == 0) // three is no edge between i and j
                weigh[i][j] = INFINITY;    // so the cost(weigh) between i and j will be infinity
            else
                weigh[i][j] = Graph[i][j].Dictance; // else : the cost(weigh) between i and j will be the destance
        }
    }

    for (i = 0; i < n; i++)
    {
        distance[i] = weigh[start][i];
        predecessor[i] = start;
        //Array visit[] initialize to zero
        visited[i] = 0;
    }

    distance[start] = 0;
    // if the vertex  start is the sorce vertex then visit[start] is marked as 1
    visited[start] = 1;
    count = 1;

    while (count < n - 1)
    {
        //Initial distance value
        mindistance = INFINITY;

        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }

        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (mindistance + weigh[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + weigh[nextnode][i];
                    predecessor[i] = nextnode;
                }
        count++;
    }
    if (Goal != start)
    {
        printf("The distance from this point << %d >> to this point << %d >> is equal to : %d \n\n",
               start,Goal,distance[Goal]);
        fprintf(out,"\nThe distance from this point << %d >> to this point << %d >> is equal to : %d \n\n",
                start,Goal,distance[Goal]);
        printf("PATH : \n");
        fprintf(out,"PATH : \n");

        j= Goal;
        do
        {
            j = predecessor[j];
            printf("<-%d", j);
            fprintf(out,"<-%d", j);
        }
        while(j!= start);
    }
    else
    {
        printf("The distance from this point << %d >> to this point << %d >> is equal to Zero\n\n",
               start,Goal);
        fprintf(out,"\nThe distance from this point << %d >> to this point << %d >> is equal to Zero\n",
                start,Goal);
    }
    printf("\n");
    fclose(out);

}
int read(FILE * segments)
{
    /*
    2 5 Zububa 50
    3 21 Al Jalama 88
    22 19 Silat al Harithiya al 94
    */
    int dis1,dis2,Distance;
    /*
    Field 1: Vertex ID of the 1st end of the segment (dis1)
    Field 2: Vertex ID of the 2nd of the segment     (dis2)
    Field 3: Name of the town                        (NameOfTheTown)
    Field 4: Distance in Kilometer                   (Distance)
    */
    char string[MAX];
    if (segments == NULL)
        puts("File does not exist..!!");
    else
    {
        //if the file is successfully opened..
        while(fgets(string, MAX,segments) !=NULL)
        {
            numOfCities++;
            char NameOfTheTown[100]= " ";
            int *H = " " ;
            //to split the new-line character from the read string by using " " -space-
            char* token= strtok(string,H);
            int counter=0;
            while(token!=NULL)
            {
                if(counter==0)
                    //atoi is used for converting from string to integer
                    dis1=atoi(token);
                else  if (counter==1)
                    //atoi is used for converting from string to integer
                    dis2=atoi(token);
                else
                {
                    // if token is number store it in Distance
                    //else - Name- : store it in NameOfTheTown
                    if((strncmp(&(token[0]),"0",1))>=0 && (strncmp(&(token[0]),"9",1)<=0))
                        Distance=atoi(token);
                    else
                    {
                        //strcat ::appends the string pointed to by strcat to the end of the string pointed to by dest
                        strcat(NameOfTheTown,token);
                        strcat(NameOfTheTown,H);
                    }
                }
                counter++;
                token = strtok(NULL,H);
            }

            //store the data in Graph[x1][x2]
            //Make all roads two-ways.
            Graph[dis1][dis2].Dictance= Distance;
            Graph[dis2][dis1].Dictance= Distance;
            strcpy(Graph[dis1][dis2].name,NameOfTheTown);
            strcpy(Graph[dis2][dis1].name,NameOfTheTown);


            //Printing the contents of the Array
            //printf("Graph[%d][%d] = %d \t NameOfTheTown => %s\t\n",dis1,dis2,Distance,NameOfTheTown );

        }
    }
    fclose(segments);
}
void showMenu()
{
    printf("\n   <<< Menu >>>");
    printf("\n>> Enter Your choice please.. \n");
    printf("---------------------------------\n");
    printf("1.Read File and print the Data in the Array. \n");
    printf("2.find the shortest paths between two input points in a graph. \n");
    printf("3.Exit \n");
}
// main function
int main()
{
    puts("Welcome to our system...");
    puts("This system helps you to find the shortest paths between two input points in a graph, representing cities and towns,using Dijkstra’s algorithm.");
    puts("***The below menu show you what you can do using this system, please select what the choice you want :).***");
    // creat input file graph
    FILE *graph ;   // creat out file out
    graph = fopen("segments.txt", "r");
    int d1,d2,d3;
    int choice,x,c;

    //Set the initial value of the distance zero
    for(int i=0; i< MAX; i++)
        for(int j=0; j< MAX; j++)
            Graph[i][j].Dictance = 0;
//-----------------------
    while(x!=4)
    {
        //printing the main menu with the options
        showMenu();
        scanf("%d",&x);
        switch (x)
        {
        case 1:
            //Read File
            read(graph);
            printf("\n >>Reading from the file and storing in the graph successfully completed .. :) \n");
            break;
        case 2:
            while(choice != 2)
            {
                puts("Enter the first ID: ");
                scanf("%d",&d1);

                // If the value is negative or does not exist in the file, this value is not accepted and the user must enter another value
                if( d1> numOfCities)
                {
                    puts("The value must be in the file ,Try Again");
                    //Repeat
                    continue;
                }
                if(d1 < 0 )
                {
                    puts("The value must be positive ,Try Again ");
                    //Repeat
                    continue;
                }
                puts("Enter the Second ID:");
                scanf("%d",&d2);
                // If the value is negative or does not exist in the file, this value is not accepted and the user must enter another value
                if( d2 > numOfCities)
                {
                    puts("The value must be in the file ,Try Again");
                    //Repeat
                    continue;
                }
                if(d2 < 0 )
                {
                    puts("The value must be positive,Try Again");
                    //Repeat
                    continue;
                }
                //Call function Dijkstra
                DijkstraFunction(Graph,MAX,d1,d2);
                printf("\nDo you want to calculate the distance ?\n");
                puts("if Yes , Please Enter 1.");
                puts("if No, Enter 2.");
                scanf("%d",&choice);
                if(choice == 2)
                {
                    puts("Thank You .. :)");
                    exit(0);
                }
            }
            break;
        case 3:
            puts("GOOD BYE ..");
            //Exit the program
            exit(0);
            break;
        default:
            puts("Error .. !");
            puts("Please enter a number in the menu");

        }
    }
    return 0;
}

