#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WORDLENGTH 30
#define MAX 100

struct team{
    char lag[WORDLENGTH];
    int  win;
    int  draw;
    int  loss;
    int  point;
    int  nrOfGoals;
};
typedef struct team Team;

void skrivUt(Team aTeam){
        printf("%s %d varav %d v, %d o, %d f. Total poäng %d med en målskillnad på %d.\n", aTeam.lag, (aTeam.win+aTeam.draw+aTeam.loss), aTeam.win, aTeam.draw, aTeam.loss, aTeam.point, aTeam.nrOfGoals);
}

Team andraResultatPaLag(Team aTeam, int fram, int bak){
    Team newResult;
    strcpy(newResult.lag, aTeam.lag);
    newResult.win = aTeam.win;
    newResult.draw = aTeam.draw;
    newResult.loss = aTeam.loss;
    newResult.point = aTeam.point;
    newResult.nrOfGoals = aTeam.nrOfGoals;
    if(fram > bak){
            printf("Ändra\n");
            newResult.win += 1;
            newResult.point += 3;
           newResult.nrOfGoals += (fram-bak);
    }else if(fram < bak){
            newResult.loss += 1;
            newResult.nrOfGoals += (fram-bak);
    }else{
            newResult.draw += 1;
           newResult.point += 1;
    }
    return newResult;
}

void laggTillMatch(Team all[], int lagEtt, int lagTva, int fram,int  bak){
        all[lagEtt] = andraResultatPaLag(all[lagEtt], fram, bak);
        all[lagTva] = andraResultatPaLag(all[lagTva], bak, fram);
}

int main(){
    //Uppgift A
    Team malo = {"Malmö", 7, 3, 1, 21, 9};
    skrivUt(malo);
    
    //Uppgift B
    malo = andraResultatPaLag(malo, 3, 0);
    skrivUt(malo);
    
    //Uppgift C
    Team allsvenskan[5];
    Team BKH = {"BK Häcken", 6, 2, 2, 8, 20};
    Team DIF = {"Djurgården IF", 5, 3, 2, 7, 18};
    Team IFK = {"IFK Göteborg", 5, 2, 2,8, 17};
    Team HIF = {"Hammarby IF", 5, 2, 2, 6, 17};
    allsvenskan[0]= malo;
    allsvenskan[1] = BKH;
    allsvenskan[2] = DIF;
    allsvenskan[3] = IFK;
    allsvenskan[4] = HIF;
    
    laggTillMatch(allsvenskan, 4, 3, 0, 3);
    
    for(int i = 0; i < 5; i++){
        skrivUt(allsvenskan[i]);
    }
    
    return 0;
}