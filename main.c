//Huzaifa Faisal
//Csc 362
//This program will simulate a race between the tortoise and hare but with some differences like
//the hare not being able to go over rocks and streams while the tortoise is able to, etc

#include <stdio.h>
#include <stdlib.h>
#define MAX 60

char *moveTortoise(char *, char *, int ); //function prototype
void print(char *, char *, char *, int , int , int ); //function prototype
char *moveHare(char *, char *, int , int ); //function prototype

int main() {
    int turn = 0; //no turns to start
    int collision = 0; //no collision detected in beginning
    int nap = 0; //hare has not napped by default
    char path[]=" R  R  R  SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R "; //original path of race
    char *hare = path; //set hare to path
    char *tortoise = path; //set tortoise to path

    while (hare < path + MAX && tortoise < path + MAX){ //while tortoise and hare are in path
        nap = 0; //reset nap
        collision = 0; //reset collision
        tortoise = moveTortoise(tortoise, hare, collision); //move tortoise
        hare = moveHare(tortoise, hare, collision, nap); //move hare
        //printf("TESTM:%d",nap);
        turn++; //increment turn
        print(path, tortoise, hare, turn, collision, nap); //print out pos of hare and tortoise
    }
    if(hare > tortoise){ //win conditions
        printf("\nhare wins\n");
    }
    else{
        printf("\ntortoise wins\n");
    }
    return 0;
}

char *moveTortoise(char *tortoise, char *hare, int collisionCheck){
    int move = (rand()%3) + 2; //random amount to move 2-4
    tortoise = tortoise + move; //tortoise is now moving
    if(tortoise == hare){ //if tortoise landed on hare
        collisionCheck = 1; //collision true
        tortoise--; //decrement pos upon collision
    }
    return tortoise;
}

char *moveHare(char *tortoise, char *hare, int collisionCheck, int nap){
    int isNapping = (rand()%4 + 1); //1 in 5 chance hare is napping
    if(isNapping == 1) { //is hare is napping
        nap = 1; //turn on nap
        //printf("TEST");
        return hare;
    }else if (*hare == 'C'){ //if hare steps on carrot
            *hare = ' '; //it eats the carrot
            return hare;
        }
    else {
        int move = (rand()%8 + 1); //hare moves 1 in 9 spaces
        hare = hare + move; //move the hare
        if(hare == tortoise){ //if hare steps on tortoise
            hare--; //make hare step back and turn on collision
            collisionCheck = 1;
        }
        if (*hare == 'S' || *hare == 'R') { //if hare steps on rock or stream move it back
            hare--;
        }
            while(*hare == 'S' || *hare == 'R'){ //if the hare is still on a rock or stream after the backstep
                hare--; //move it back even more
                if(hare == tortoise){ //if now it is on top of the tortoise
                    collisionCheck = 1; //turn on collision check
                    hare--;
                }
            }
            return hare;
        }
    }



void print(char *path, char *tortoise, char *hare, int turn, int collision, int nap) {
    printf("\nturn:\t%d\t", turn); //the path the race will be on
    char *i = path; //set a pointer to array beginning

    while (*i != '\0') { //while the pointer has not fully iterated through the arary
        if (i == tortoise) { //if it is the tortoise
            printf("T");
        } else if(i == hare){ //if it is the hare
            printf("H");
        } else  {
            printf("%c", *i); //print the remaining path
        }
        if(collision == 1){ //if collision occurs
            printf("\t-collision-");
        }
        if(nap == 1){ //if the hare naps
            printf("\t-hare napping-");
        }
        i++;
    }
}

/*OUTPUT:
C:\Users\HueF3\Documents\clionProjects\untitled3\cmake-build-debug\untitled3.exe

turn:   1        R  T HR  SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
turn:   2        R  R  T HSSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
turn:   3        R  R  RTHSSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
turn:   4        R  R  R HSSTSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
turn:   5        R  R  R HSSSSST  R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
turn:   6        R  R  R  SSSSS H RT R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
turn:   7        R  R  R  SSSSS H R  T CCCC  R   R   CCCCCCCCCC  R  SSSS  R
turn:   8        R  R  R  SSSSS H R  R TCCC  R   R   CCCCCCCCCC  R  SSSS  R
turn:   9        R  R  R  SSSSS   R HR CCCCT R   R   CCCCCCCCCC  R  SSSS  R
turn:   10       R  R  R  SSSSS   R  R CCHC  RT  R   CCCCCCCCCC  R  SSSS  R
turn:   11       R  R  R  SSSSS   R  R CCHC  R   RT  CCCCCCCCCC  R  SSSS  R
turn:   12       R  R  R  SSSSS   R  R CC C HR   R   CTCCCCCCCC  R  SSSS  R
turn:   13       R  R  R  SSSSS   R  R CC C HR   R   CCCTCCCCCC  R  SSSS  R
turn:   14       R  R  R  SSSSS   R  R CC C  R  HR   CCCCCCCTCC  R  SSSS  R
turn:   15       R  R  R  SSSSS   R  R CC C  R   R  HCCCCCCCCCT  R  SSSS  R
turn:   16       R  R  R  SSSSS   R  R CC C  R   R   CHCCCCCCCC  RT SSSS  R
turn:   17       R  R  R  SSSSS   R  R CC C  R   R   CHCCCCCCCC  R  SSTS  R
turn:   18       R  R  R  SSSSS   R  R CC C  R   R   C CCCCHCCC  R  SSSS TR
turn:   19       R  R  R  SSSSS   R  R CC C  R   R   C CCCCHCCC  R  SSSS  R
tortoise wins

Process finished with exit code 0
*/


