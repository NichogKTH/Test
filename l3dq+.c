#include <stdio.h>
#include <string.h>
#define BOXES_MAX 8
#define WORD_MAX 20
#define DRUGS_MAX 5
struct drug{
    int boxes[BOXES_MAX];
    int saldos[BOXES_MAX];
    int nrOfBoxes;
    char name[BOXES_MAX];
};
typedef struct drug Drug;
void load(int* pNrOfDrugs, char chosenFile[], FILE* file, Drug drugs[]);
void quit(int* pNrOfDrugs, char chosenFile[], FILE* file, Drug drugs[]);
void menu(int* pNrOfDrugs, Drug drugs[]);
void addDrug(int* pNrOfDrugs, Drug drugs[]);
void print(int index, Drug drugs[]);
int search(char searchString[], Drug drugs[]);
void addSize(Drug drugs[]);
void removeDrug(int* pNrOfDrugs, Drug drugs[]);
void warnings(Drug drugs[]);
int main(){
    char chosenFile[WORD_MAX];
    printf("Ange en fil. Finns den kommer programmet laddas fran den och sedan sparas till den.\nAnnars kommer programmet skapa en fil med det namnet att spara till, till nasta gang.\nFil:");
    scanf("%s", chosenFile);
    strcat(chosenFile, ".txt");
    fflush(stdin);
    FILE *file;
    Drug drugs[DRUGS_MAX];
    int nrOfDrugs=0;
    int* pNrOfDrugs=&nrOfDrugs;
    load(pNrOfDrugs, chosenFile, file, drugs);
    menu(pNrOfDrugs, drugs);
    quit(pNrOfDrugs, chosenFile, file, drugs);
}
void load(int* pNrOfDrugs, char chosenFile[], FILE* file, Drug drugs[]){
    int i,j;
    file=fopen(chosenFile, "r");
    if(fil!=NULL){
        fscanf(file, "%d\n", pNrOfDrugs);
        for(i=0 ; i<*pNrOfDrugs+1 ; i++){
            fscanf(file, "%s\n", drugs[i].name);
            fscanf(file, "%d\n", &drugs[i].name);
            for(j=0 ; j<drugs[i].nrOfBoxes+1 ; j++)
                fscanf(file, "%d\n", &drugs[i].boxes[j]);
        }
        fclose(file);
    }
    printf("%s laddad\n", chosenFile);
}
void avsluta(int* pNrOfDrugs, char chosenFile[], FILE* file, Drug drugs[]){
    int i,j;
    file=fopen(chosenFile,"w");
    if(file!=NULL){
        fprintf(file, "%d\n", *pNrOfDrugs);
        for(i=0 ; i<*pNrOfDrugs ; i++){
            fprintf(file,"%s\n", drugs[i].name);
            fprintf(file,"%d\n", drugs[i].nrOfBoxes);
            for(j=0 ; j<drugs[i].nrOfBoxes ; j++)
                fprintf(file, "%d\n", drugs[i].boxes[j]);
        }
        fclose(file);
    }
    printf("\nSpara till %s & avsluta", chosenFile);
}
void meny(int* pNrOfDrugs, Drug drugs[]){
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
        addDrug(pNrOfDrugs, drugs);
    else if(readChar=='2'){
        printf("Lakemedel, Storlekar, Saldo");
        for(index=0;index<*pNrOfDrugs;index++)
            printf(index, drugs);
    }
    else if(readChar=='3'){
        printf("\nSoka lakemedel\n");
        printf("Ange sokstrang: ");
        scanf("%s",&searchString);
        fflush(stdin);
        search(searchString,drugs);
    }
    else if(readChar=='4')
        addSize(drugs);
    else if(readChar=='5')
        removeDrug(pNrOfDrugs,drugs);
    else if(readChar=='6')
        warnings(drugs);
    }
}
void addDrug(int* pNrOfDrugs,Drug drugs[]){
    int drugsIndex, duplicateControl, entryCleaner, booleanRedo=0,boxIndex=0;
    for(drugsIndex=0;drugs[regIndex].name[0]!='\0'&&drugsIndex<DRUGS_MAX;drugsIndex++){
        ;
    }
    if(drugsIndex>=DRUGS_MAX){
        printf("Databas full.\n");
    }
    else{
        while(booleanRedo!=0){
            booleanRedo=0;
            printf("\nRegistrera lakemedel\nAnge namn: ");
            scanf("%s",drugs[drugsIndex].name);
            for(duplicateControl=0;duplicateControl<=drugsIndex;duplicateControl++){
                if(reg[duplicateControl].name==drugs[drugsIndex].name){
                    printf("Lakemedel finns redan.\n");
                        for(entryCleaner=0;entryCleaner<WORD_MAX;entryCleaner++){
                            drugs[drugsIndex].name[entryCleaner]='\0';
                        }
                    booleanRedo++;
                }
            }
        }
        printf("Ange storlek (0 for att avsluta): ");
        scanf("%d",&drugs[drugsIndex].boxar[boxIndex]);
        while(drugs[drugsIndex].boxar[boxIndex]!=0&&boxIndex<BOXES_MAX){
            boxIndex++;
            printf("Ange storlek (0 for att avsluta): ");
            scanf("%d",&drugs[drugsIndex].boxar[boxIndex]);
            drugs[drugsIndex].antalBoxar++;
        }
        *pNrOfDrugs=(*pNrOfDrugs+1);
    }
}
void skrivUt(int index,Drug drugs[]){
    int i=0;
    printf("\nNamn: %s, %d storlekar: %d",drugs[index].name,drugs[index].nrOfBoxes,drugs[index].boxes[i]);
    i++;
    while(i<drugs[index].nrOfBoxes){
        printf(", %d",drugs[index].boxes[i]);
        i++;
    }
}
int sok(char searchString[],Drug drugs[]){
    int rI,bI,sI,duplicateControl=0;
    for(rI=0 ; reg[rI].name[0]!='\0' && rI<DRUGS_MAX ; rI++){
        for(bI=0 ; reg[rI].name[bI]!='\0' && bI<WORD_MAX ; bI++){
            if(searchString[0]==drugs[rI].name[bI]){
                for(sI=0 ; searchString[sI]==drugs[rI].name[bI+sI] && searchString[sI]!='\0' ; sI++){
                    if(searchString[sI+1]=='\0'){
                        skrivUt(rI,reg);
                        duplicateControl++;
                        break;
                    }
                }
            }
        }
    }
    return duplicateControl;
}
void addSize(Drug drugs[]){
    //sök för att hitta rätt läkemedel
    //vill använda denna i registrera
    //menyn bör därför fixa så att denna som standalone gör mer avancerat
    //scanf("%d",&reg[i].boxar[j]);
    printf("\nLagga till storlek\n");
}
void removeMed(int* pNrOfDrugs, Drug drugs[]){
    printf("\nAvregistrera ett lakemedel\n");
}
void warnings(Drug drugs[]){
    int boundary, writer;
    int writeThis[BOXES_MAX];
    int rI,sI;
    printf("\nVarningar\nUnder vilket saldo vill du ha varningar: ");
    scanf("%d",boundary);
    printf("Foljande forpackningar har ett saldo under %d",boundary);
    printf("Lakemedel         Storlekar           Saldo\n");
    printf("____________________________________________________________");
    for(rI=0;reg[rI].namn[0]!=0&&rI<REGISTER_MAXIMUM;rI++){
        for(sI=0;reg[rI].namn[sI]<reg[i].antalBoxar&&sI<BOXAR_MAXIMUM;sI++){
            if(reg[rI].namn[sI]<boundary){
                writer++;
                writeThis[0]=reg[rI].namn[sI];
            }
        }
        if(writer==0)
            ;
        else if(writer==1)
            printf("%.20s%.20d%.20d",reg[i].namn,reg[i].boxar[writeThis[0]],reg[i].saldon[writeThis[0]])
            printf("123456789012345678901234567890123456789012345678901234567890");
            printf("________10________20________30________40________50________60");
            printf("")
    }
        printf("123456789012345678901234567890123456789012345678901234567890");
    printf("________10________20________30________40________50________60");
    printf("")
}
"%.20s", "Lakemedel"