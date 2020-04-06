#include <stdio.h>
#include <string.h>
#define BOXES_MAX 10
#define WORD_MAX 20
#define MEDICINES_MAX 10000
#define PRINT_STANDARD 18
struct medicine{
    int boxes[BOXES_MAX];
    int saldos[BOXES_MAX];
    char name[BOXES_MAX];
    int nrOfBoxes;
};
typedef struct medicine Medicine;


int searchTypes(int searchMode, Medicine m[], int* pSizeOfM, char searchString[], int matches[]);


void registerMedicine(Medicine m[], int* pSizeOfM, char searchString[]);
void unregisterMedicine(Medicine m[], int* pSizeOfM, int currentMedicine);


void addSize(Medicine m[], int currentMedicine);
void changeSaldo(Medicine m[], int currentMedicine);


void warnings(Medicine m[], int* pSizeOfM);


void printHeader();
void printMedicine(Medicine m[], int index);
void makeLonger(char word[]);

int main()
{
    char chosenFile[WORD_MAX];
    FILE *file;
    Medicine m[MEDICINES_MAX];
    int sizeOfM = 0;
    int* pSizeOfM = &sizeOfM;
    int menuChoice;
    int searchMode = 0;
    char searchString[WORD_MAX];
    int matches[MEDICINES_MAX];
    int index = 0;
    int currentMedicine;
    int i, j;
    printf("\nLakemedelsdatabas 1.0\nAnge en fil. Finns den kommer programmet laddas fran den och sedan sparas till den.\nAnnars kommer programmet skapa en fil med det namnet att spara till, till nasta gang.\nFil:");
    scanf("%s", chosenFile);
    fflush(stdin);
    strcat(chosenFile, ".txt");
    file=fopen(chosenFile, "r");
    if(file!=NULL)
    {
        fscanf(file, "%d\n", pSizeOfM);
        for(i=0 ; i<*pSizeOfM+1 ; i++)
        {
            fscanf(file, "%s\n", m[i].name);
            fscanf(file, "%d\n", &m[i].nrOfBoxes);
            for(j=0 ; j<m[i].nrOfBoxes+1 ; j++)
            {
                fscanf(file, "%d\n", &m[i].boxes[j]);
                fscanf(file, "%d\n", &m[i].saldos[j]);
            }
        }
        fclose(file);
    }
    printf("%s laddad\n", chosenFile);
    while(menuChoice != 8)
    {
        printf("\nVad vill du gora?\n\n(1) Registrera nytt lakemedel\n(2) Skriva ut alla lakemedel\n(3) Soka efter lakemedel");
        printf("\n(4) Lagga till storlek for lakemedel\n(5) Andra lagersaldot for ett lakemedel\n(6) Avregistrera lakemedel\n(7) Se varningar om laga lagersaldon\n(8) Avsluta\nVal:");
        scanf("%d",&menuChoice);
        fflush(stdin);
        if(menuChoice == 1)
        {
            printf("Registrera lakemedel\n");
            printf("Ange namn: ");
            scanf("%s",&searchString);
            fflush(stdin);
            searchTypes(0, m, pSizeOfM, searchString, matches);
            registerMedicine(m, pSizeOfM, searchString);
        }
        else if(menuChoice == 2)
        {
            printHeader();
            for(i=0; i < sizeOfM; i++)
            {
                printMedicine(m, i);
            }
        }
        else if(menuChoice == 3)
        {
            printf("Soka lakemedel\nAnge sokstrang: ");
            scanf("%s", searchString);
            fflush(stdin);
            searchTypes(1, m, pSizeOfM, searchString, matches);
        }
        else if(menuChoice == 4)
        {
            printf("Lagga till storlek\nAnge sokstrang: ");
            scanf("%s", searchString);
            fflush(stdin);
            currentMedicine = searchTypes(2, m, pSizeOfM, searchString, matches);
            addSize(m, currentMedicine);
        }
        else if(menuChoice == 5)
        {
            printf("Andra lagersaldo\nAnge sokstrang: ");
            scanf("%s", searchString);
            fflush(stdin);
            currentMedicine = searchTypes(2, m, pSizeOfM, searchString, matches);
            changeSaldo(m, currentMedicine);
        }
        else if(menuChoice == 6)
        {
            printf("Avregistrera\nAnge sokstrang: ");
            scanf("%s", searchString);
            fflush(stdin);
            currentMedicine = searchTypes(2, m, pSizeOfM, searchString, matches);
            unregisterMedicine(m, pSizeOfM, currentMedicine);
        }
        else if(menuChoice == 7)
            warnings(m, pSizeOfM);
        else
            ;   
    }
    printf("\nSparar till %s & avslutar", chosenFile);
    file=fopen(chosenFile,"w");
    if(file!=NULL)
    {
        fprintf(file, "%d\n", *pSizeOfM);
        for(i=0 ; i<*pSizeOfM ; i++)
        {
            fprintf(file,"%s\n", m[i].name);
            fprintf(file,"%d\n", m[i].nrOfBoxes);
            for(j=0 ; j<m[i].nrOfBoxes ; j++)
            {
                fprintf(file, "%d\n", m[i].boxes[j]);
                fprintf(file, "%d\n", m[i].saldos[j]);
            }
        }
        fclose(file);
    }
}

int searchTypes(int searchMode, Medicine m[], int* pSizeOfM, char searchString[], int matches[])
{
    int i, j=0, k=0;
    while(1)
    {
        k=0;
        j=0;
        for(i=0; i < MEDICINES_MAX; i++)
            matches[i]=0;
        for(i=0; i < *pSizeOfM; i++)
        {
            if(strstr(m[i].name, searchString) != NULL)
            {
                j++;
                matches[i]++;
                if(strstr(searchString, m[i].name) != NULL)
                    k++;
            }
        }
        if(searchMode == 0 && k == 0)
            return 0;
        else if(searchMode == 0)
        {
            printf("Lakemedel finns redan. Vanligen skriv in ett annat namn: ");
            scanf("%s", searchString);
            fflush(stdin);
        }
        else if(searchMode == 1 && j == 0)
        {
            printf("Din sokning gav inga traffar.");
            return 0;
        }
        else if(searchMode == 1 && j > 0)
        {
            printHeader();
            for(i = 0; i < *pSizeOfM; i++)
            {
                if(matches[i] > 0)
                {
                    printMedicine(m, i);
                }
            }
            return 0;
        }
        else if(searchMode == 2 && j == 1)
        {
            for(i = 0; matches[i] == 0; i++)
                ;
            printHeader();
            printMedicine(m, i);
            return i;
        }
        else if(searchMode == 2 && j == 0)
        {
            printf("Lakemedel finns inte. Vanligen skriv in ett annat lakemedel.\nAnge sokstrang: ");
            scanf("%s", searchString);fflush(stdin);
            fflush(stdin);
        }
        else if(searchMode == 2 && j > 1)
        {
            printHeader();
            for(i = 0; i < *pSizeOfM; i++)
            {
                if(matches[i] > 0)
                {
                    printMedicine(m, i);
                }
            }
            printf("Du fick inte endast ett alternativ. Vanligen gor en ny sokning.\nAnge sokstrang: ");
            scanf("%s", searchString);
            fflush(stdin);
        }
    }
}

void registerMedicine(Medicine m[], int* pSizeOfM, char searchString[])
{
    int i=0;
    int buffer = 1;
    strcpy(m[*pSizeOfM].name, searchString);
    while(buffer != 0 && i < BOXES_MAX)
    {
        printf("Ange storlek (0 for att avsluta): ");
        scanf("%d", &buffer);
        fflush(stdin);
        if(buffer != 0){
            m[*pSizeOfM].boxes[i] = buffer;
            m[*pSizeOfM].nrOfBoxes++;
            m[*pSizeOfM].saldos[i] = 0;
        }
        i++;
    }
    *pSizeOfM = *pSizeOfM + 1;
}

void unregisterMedicine(Medicine m[], int* pSizeOfM, int currentMedicine)
{
    int i;
    char confirmation = '0';
    printf("Vill du avregistrera %s (j/n)?", m[currentMedicine].name);
    while(confirmation != 'j' && confirmation != 'n')
    {
        scanf("%c", &confirmation);
        fflush(stdin);
    }
    if(confirmation == 'j')
    {
        printf("%s avregistreras.", m[currentMedicine].name);
        for(; currentMedicine < *pSizeOfM; currentMedicine++)
            m[currentMedicine] = m[currentMedicine + 1];
        strcpy(m[*pSizeOfM].name, "");
        m[*pSizeOfM].nrOfBoxes=0;
        for(i = 0; i < BOXES_MAX; i++)
            m[*pSizeOfM].boxes[i]=0;
            m[*pSizeOfM].saldos[i]=0;
        *pSizeOfM = *pSizeOfM - 1;
    }
    if(confirmation == 'n')
        return;
}

void addSize(Medicine m[], int currentMedicine)
{
    int i = 0, j = 0;
    int buffer;

    if(m[currentMedicine].nrOfBoxes>=BOXES_MAX)
    {
        printf("Saknas plats for ytterligare storlek. Atergar till huvudmeny.");
        return;
    }
    printf("Lagga till storlek\nAnge ny storlek: ");
    scanf("%d", &buffer);
    fflush(stdin);
    for(i = 0, j = 0; m[currentMedicine].boxes[i] != 0 && i < BOXES_MAX; i++)
    {
        if(m[currentMedicine].boxes[i] == buffer)
        {
            printf("Storlek finns redan.");
            return;
        }
        if(m[currentMedicine].boxes[i] < buffer)
            j++;
    }
    printf("\nCheckpoint before add insert: i=%d, j=%d", i, j);
    for(; i - j >= 0; i--)
    {
        printf("\nCheckpoint in add insert: i=%d, j=%d", i, j);
        m[currentMedicine].boxes[i] = m[currentMedicine].boxes[i-1];
        m[currentMedicine].saldos[i] = m[currentMedicine].saldos[i-1];
    }
    m[currentMedicine].boxes[j] = buffer;
    m[currentMedicine].saldos[j] = 0;
    m[currentMedicine].nrOfBoxes++;
}

void changeSaldo(Medicine m[], int currentMedicine)
{
    int i;
    int buffer;
    for(i = 0; i < m[currentMedicine].nrOfBoxes; i++)
    {
        printf("Ange andring (+/-) for storlek %d:", m[currentMedicine].boxes[i]);
        scanf("%d", &buffer);
        fflush(stdin);
        buffer = m[currentMedicine].saldos[i] + buffer;
        if(buffer < 0)
        {
            printf("VARNING finns endast %d satter saldo till 0.", m[currentMedicine].saldos[i]);
            m[currentMedicine].saldos[i] = 0;
        }
        else
            m[currentMedicine].saldos[i] = buffer;
    }
}

void warnings(Medicine m[], int* pSizeOfM)
{
    int threshold;
    int i, j, k = 0, l = 0;
    char intToString[10];
    char printFormatName[20];
    char printFormatBoxes[60] = "";
    char printFormatSaldos[60] = "";
    printf("Varningar\nUnder vilket saldo vill du ha varningar: ");
    scanf("%d", &threshold);
    fflush(stdin);
    printHeader();
    for(i = 0; i < *pSizeOfM; i++)
    {
        for(j = 0; j < m[i].nrOfBoxes; j++)
        {
            if(m[i].saldos[j] < threshold)
            {
                k++;
            }
        }
        if(k > 0)
        { 
            strcpy(printFormatName, m[i].name);
            makeLonger(printFormatName);
            printf("%s  ",printFormatName);
            
            strcpy(printFormatBoxes, "");
            for(j = 0, l = 0; j < m[i].nrOfBoxes; j++)
            {
                if(m[i].boxes[j] != 0 && m[i].saldos[j] < threshold)
                {
                    if(l > 0)
                        strcat(printFormatBoxes, ",");
                    snprintf(intToString, sizeof(intToString), "%d", m[i].boxes[j]);
                    strcat(printFormatBoxes, intToString);
                    l++;
                }
            }
            makeLonger(printFormatBoxes);
            printf("%s  ", printFormatBoxes);
            
            strcpy(printFormatSaldos, "");
            for(j = 0, l = 0; j < m[i].nrOfBoxes; j++)
            {
                if(m[i].boxes[j] != 0 && m[i].saldos[j] < threshold)
                {
                    if(l > 0)
                        strcat(printFormatSaldos, ",");
                    snprintf(intToString, sizeof(intToString), "%d", m[i].saldos[j]);
                    strcat(printFormatSaldos, intToString);
                    l++;
                }
            }
            makeLonger(printFormatSaldos);
            printf("%s  \n", printFormatSaldos);
            
        }
    }
}

void printHeader()
{
    printf("\nLakemedel           Storlekar           Saldo               ");
    printf("\n____________________________________________________________\n");
}

void printMedicine(Medicine m[], int index)
{
    int i = 0, j = 0;
    char intToString[10];
    char printFormatName[20];
    char printFormatBoxes[60] = "";
    char printFormatSaldos[60] = "";
    strcpy(printFormatName, m[index].name);
    makeLonger(printFormatName);
    printf("%s  ",printFormatName);

    snprintf(intToString, sizeof(intToString), "%d", m[index].boxes[0]);
    strcat(printFormatBoxes, intToString);
    for(i = 1; i < BOXES_MAX; i++)
    {
        if(m[index].boxes[i] != 0)
        {
            snprintf(intToString, sizeof(intToString), "%d", m[index].boxes[i]);
            strcat(printFormatBoxes, ",");
            strcat(printFormatBoxes, intToString);
        }
    }
    makeLonger(printFormatBoxes);
    printf("%s  ", printFormatBoxes);

    snprintf(intToString, sizeof(intToString), "%d", m[index].saldos[0]);
    strcat(printFormatSaldos, intToString);
    for(i = 1; i < BOXES_MAX; i++)
    {
        if(m[index].boxes[i] != 0)
        {
            snprintf(intToString, sizeof(intToString), "%d", m[index].saldos[i]);
            strcat(printFormatSaldos, ",");
            strcat(printFormatSaldos, intToString);
        }
    }
    makeLonger(printFormatSaldos);
    printf("%s  \n", printFormatSaldos);
}

void makeLonger(char word[])
{
    int i = strlen(word);
    if(i<PRINT_STANDARD)
    {
        word[PRINT_STANDARD] = '\0';
        for(i = strlen(word); i < PRINT_STANDARD; i++)
            word[i] = ' ';
    }
}