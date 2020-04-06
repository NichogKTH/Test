#include <stdio.h>



int main(int argc, char **argv)
{
	float offset;
    float offsetMin;
    float offsetMax;
    float summa = 0;
    
    printf("Offsettid 1: ");
    scanf("%f", &offset);
    offsetMax = offsetMin = offset;

    for(int i = 1; i < 10; i++){
            printf("Offsettid %d: ", i+1);
            scanf("%f", &offset);
            if(offset  > offsetMax){
                offsetMax = offset;
            }
            else if(offset < offsetMin){
                offsetMin = offset;
            }
            summa  += offset;
    }

    offset = (summa-offsetMax-offsetMin)/8;
    
    printf("Offsettiden är: %5.2f\n", offset);

	return 0;
}
