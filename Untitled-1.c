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
        printf("Checkpoint: %d", i);
        for(j = 0; j < m[i].nrOfBoxes; j++)
        {
            if(m[i].saldos[j] < threshold)
            {
                k++;
            }
            if(k > 0)
            { 
                strcpy(printFormatName, m[i].name);
                makeLonger(printFormatName);
                printf("%s  ",printFormatName);
            }
            for(i = 1; i < BOXES_MAX; i++)
            {
                if(m[i].boxes[j] != 0 && m[i].saldos[j] < threshold)
                {
                    snprintf(intToString, sizeof(intToString), "%d", m[i].boxes[j]);
                    if(l > 0)
                        strcat(printFormatBoxes, ",");
                    l++;
                    strcat(printFormatBoxes, intToString);
                }
            }
        }
    }
}