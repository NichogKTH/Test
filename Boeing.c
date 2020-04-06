#include <stdio.h>


void inputOfAttackAngle(float ar[], int size){
    for(int i=0; i < size; i++){
            printf("value  %d: ", i+1);
            scanf("%f", &ar[i]);
    }
}

void printArray(float ar[], int size){
        for(int i = 0; i < size; i++){
                printf("%d : %5.1f\n", i, ar[i]);
        }
}

void mergeAttackAngleData(float first[], int fSize, float second[], int sSize, float result[]){
    float tmp;
    
    // merge 
    for(int i = 0; i < fSize; i++){
            result[i] = first[i];
    }
    
    for(int i = 0; i < sSize; i++){
            result[fSize+i] = second[i];
    }
    
    //sort
    for(int i = 0; i < fSize + sSize  - 1;  i++){
        for(int j = 0; j < fSize + sSize - 1 - i;  j++ ){
                if(result[j] > result[j+1]){
                        tmp = result[j];
                        result[j] = result[j+1];
                        result[j+1] = tmp;
                    }
        }
        
    }
}

float medianOfAttackAngleData(float result[], int size){
     float median;
     if(size % 2  == 0){
        median  = (result[size/2] + result[size/2-1]) / 2;
     }else{
        median = result[(int) size/2];
    }
    return median;
}



int main(int argc, char **argv)
{
	float first[5];
    float second[5];
    float merged[10];
    
    // Uppgift A
    inputOfAttackAngle(first, 5);
    printArray(first, 5);
    inputOfAttackAngle(second, 5);
    printArray(second, 5);
    
    // Uppgift B
    
    mergeAttackAngleData(first, 5, second, 5, merged);
    printArray(merged, 10);
    
    // Uppgift C
    
    printf("Medianvärdet är %5.2f \n", medianOfAttackAngleData(merged, 10) );
    
}
