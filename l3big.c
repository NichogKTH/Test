#include <stdio.h>
#include <string.h>
#define BOXES_MAX 10
#define WORD_MAX 20
#define MEDS_MAX 10000
struct med{
    int boxes[BOXES_MAX];
    int saldos[BOXES_MAX];
    int nrOfBoxes;
    char name[BOXES_MAX];
};
typedef struct med Med;
void load(int* pNrOfMeds, char chosenFile[], FILE* file, Med meds[]);
void quit(int* pNrOfMeds, char chosenFile[], FILE* file, Med meds[]);
void menu(int* pNrOfMeds, Med meds[]);
void addMed(int* pNrOfMeds, Med meds[]);
void printMed(int index, Med meds[]);
int search(char searchString[], Med meds[]);
void addSize(Med meds[]);
void removeMed(int* pNrOfMeds, Med meds[]);
void warnings(Med meds[]);
int main(){
    char chosenFile[WORD_MAX];
    printf("Ange en fil. Finns den kommer programmet laddas fran den och sedan sparas till den.\nAnnars kommer programmet skapa en fil med det namnet att spara till, till nasta gang.\nFil:");
    scanf("%s", chosenFile);
    strcat(chosenFile, ".txt");
    fflush(stdin);
    FILE *file;
    Med meds[MEDS_MAX];
    int nrOfMeds=0;
    int* pNrOfMeds=&nrOfMeds;
    load(pNrOfMeds, chosenFile, file, meds);
    menu(pNrOfMeds, meds);
    quit(pNrOfMeds, chosenFile, file, meds);
}
void load(int* pNrOfMeds, char chosenFile[], FILE* file, Med meds[]){
    int i,j;
    file=fopen(chosenFile, "r");
    if(file!=NULL){
        fscanf(file, "%d\n", pNrOfMeds);
        for(i=0 ; i<*pNrOfMeds+1 ; i++){
            fscanf(file, "%s\n", meds[i].name);
            fscanf(file, "%d\n", &meds[i].name);
            for(j=0 ; j<meds[i].nrOfBoxes+1 ; j++)
                fscanf(file, "%d\n", &meds[i].boxes[j]);
        }
        fclose(file);
    }
    printf("%s laddad\n", chosenFile);
}
void quit(int* pNrOfMeds, char chosenFile[], FILE* file, Med meds[]){
    int i,j;
    file=fopen(chosenFile,"w");
    if(file!=NULL){
        fprintf(file, "%d\n", *pNrOfMeds);
        for(i=0 ; i<*pNrOfMeds ; i++){
            fprintf(file,"%s\n", meds[i].name);
            fprintf(file,"%d\n", meds[i].nrOfBoxes);
            for(j=0 ; j<meds[i].nrOfBoxes ; j++)
                fprintf(file, "%d\n", meds[i].boxes[j]);
        }
        fclose(file);
    }
    printf("\nSparar till %s & avslutar", chosenFile);
}
void menu(int* pNrOfMeds, Med meds[]){
    char readChar=0;
    char searchString[WORD_MAX];
    int index=0;
    while(readChar != 'Q' && readChar != 'q'){
    do{
        printf("\nVad vill du gora?\n\nRegistrera nytt lakemedel (1)\nSkriva ut alla lakemedel (2)\nSoka efter lakemedel (3)");
        printf("\nLagga till storlek for lakemedel (4)\nAvregistrera lakemedel (5)\nSe varningar om laga lagersaldon (6)\nAvsluta (7)\nVal:");
        fflush(stdin);
        } while((readChar=getchar())!='1'&&readChar!='2'&&readChar!='3'&&readChar!='4'&&readChar!='5'&&readChar!='6'&&readChar!='Q'&&readChar!='q');
    if(readChar=='1')
        addMed(pNrOfMeds, meds);
    else if(readChar=='2'){
        printf("Lakemedel, Storlekar, Saldo");
        for(index=0;index<*pNrOfMeds;index++)
            printMed(index, meds);
    }
    else if(readChar=='3'){
        printf("\nSoka lakemedel\n");
        printf("Ange sokstrang: ");
        scanf("%s",&searchString);
        fflush(stdin);
        search(searchString, meds);
    }
    else if(readChar=='4')
        addSize(meds);
    else if(readChar=='5')
        removeMed(pNrOfMeds, meds);
    else if(readChar=='6')
        warnings(meds);
    }
}
void addMed(int* pNrOfMeds,Med meds[]){
    int medsWalker, duplicateControl, entryCleaner, booleanDoRedo=1,boxesWalker=0;
    for(medsWalker=0;meds[medsWalker].name[0]!='\0'&&medsWalker<MEDS_MAX;medsWalker++){
        ;
        printf("\n(Checkpoint 1.)\n");
    }
    if(medsWalker>=MEDS_MAX){
        printf("Databas full.\n");
    }
    else{
        printf("(Checkpoint 2.)\n");
        while(booleanDoRedo!=0){
            booleanDoRedo=0;
            printf("\nRegistrera lakemedel\nAnge namn: ");
            scanf("%s",meds[medsWalker].name);
            for(duplicateControl=0;duplicateControl<=medsWalker;duplicateControl++){
                if(meds[duplicateControl].name==meds[medsWalker].name){
                    printf("Lakemedel finns redan.\n");
                        for(entryCleaner=0;entryCleaner<WORD_MAX;entryCleaner++){
                            meds[medsWalker].name[entryCleaner]='\0';
                        }
                    booleanDoRedo++;
                }
            }
        }
        printf("Ange storlek (0 for att avsluta): ");
        scanf("%d",&meds[medsWalker].boxes[boxesWalker]);
        while(meds[medsWalker].boxes[boxesWalker]!=0&&boxesWalker<BOXES_MAX){
            boxesWalker++;
            printf("Ange storlek (0 for att avsluta): ");
            scanf("%d",&meds[medsWalker].boxes[boxesWalker]);
            meds[medsWalker].nrOfBoxes++;
        }
        *pNrOfMeds=(*pNrOfMeds+1);
    }
}
void printMed(int index,Med meds[]){
    int i=0;
    printf("\nNamn: %s, %d storlekar: %d", meds[index].name, meds[index].nrOfBoxes, meds[index].boxes[i]);
    i++;
    while(i<meds[index].nrOfBoxes){
        printf(", %d",meds[index].boxes[i]);
        i++;
    }
}
int search(char searchString[],Med meds[]){
    int rI,bI,sI,duplicateControl=0;
    for(rI=0 ; meds[rI].name[0]!='\0' && rI<MEDS_MAX ; rI++){
        for(bI=0 ; meds[rI].name[bI]!='\0' && bI<WORD_MAX ; bI++){
            if(searchString[0]==meds[rI].name[bI]){
                for(sI=0 ; searchString[sI]==meds[rI].name[bI+sI] && searchString[sI]!='\0' ; sI++){
                    if(searchString[sI+1]=='\0'){
                        printMed(rI,meds);
                        duplicateControl++;
                        break;
                    }
                }
            }
        }
    }
    return duplicateControl;
}
void addSize(Med meds[]){
    //sök för att hitta rätt läkemedel
    //vill använda denna i registrera
    //menyn bör därför fixa så att denna som standalone gör mer avancerat
    //scanf("%d",&reg[i].boxar[j]);
    printf("\nLagga till storlek\n");
}
void removeMed(int* pNrOfMeds, Med meds[]){
    printf("\nAvregistrera ett lakemedel\n");
}
void warnings(Med meds[]){
    int boundary, writer;
    int writeThis[BOXES_MAX];
    int rI,sI;
    printf("\nVarningar\nUnder vilket saldo vill du ha varningar: ");
    scanf("%d",boundary);
    printf("Foljande forpackningar har ett saldo under %d",boundary);
    printf("Lakemedel         Storlekar           Saldo\n");
    printf("____________________________________________________________");
    for(rI=0;meds[rI].name[0]!=0&&rI<MEDS_MAX;rI++){
        for(sI=0;meds[rI].name[sI]<meds[rI].nrOfBoxes&&sI<BOXES_MAX;sI++){
            if(meds[rI].name[sI]<boundary){
                writer++;
                writeThis[0]=meds[rI].name[sI];
            }
        }
        if(writer==0)
            ;
        else if(writer==1)
            printf("%.20s%.20d%.20d",meds[rI].name,meds[rI].boxes[writeThis[0]],meds[rI].saldos[writeThis[0]]);
            printf("123456789012345678901234567890123456789012345678901234567890");
            printf("________10________20________30________40________50________60");
            printf("");
    }
    printf("123456789012345678901234567890123456789012345678901234567890");
    printf("________10________20________30________40________50________60");
    printf("");
}
//Work it, makes it, makes us
//Harder, better, faster, stronger
int findTop(Med meds[]){
    int i;
    for(i=0;meds[i].name[0]!='\0';i++)
        ;
    return i;
}
void nameMed(int index, Med meds[], char input[]){
    int i;
    for(i=0 ; i<WORD_MAX ; i++)
        meds[index].name[i]=input[i];
}
void addMed2(Med meds[]){
    char input[WORD_MAX];
    int h,i,j,k;
    int booleanRedo;
    h=findTop(meds);
    if(h>=MEDS_MAX)
        printf("Databas full.");
    else{
        do {
            booleanRedo=0;
            printf("\nRegistrera lakemedel\nAnge namn: ");
            scanf("%s",input);
            for(i=0;meds[i].name==input;i++){
                printMed(i,meds);
                booleanRedo++;
            }
        } while(booleanRedo!=0);
    nameMed(h,meds,input);
    for(j=0 ; meds[h].boxes[j]!=0 ; j++)
        addSize(meds);
    }
}​