#include<stdio.h>
void main()
{
    int i,j,k,y,n,r,p,index=0,flag=0;
    printf("Enter the number of process\n");
    scanf("%d",&p);
    printf("Enter the number of resources\n");
    scanf("%d",&r);

    int alloc[p][r],max[p][r],avail[r],work[r],need[p][r],finish[p]={0},safeseq[p];


    // ip allocation matrix
    printf("Enter alloc matrix:\n"); 
    for (i=0;i<p;i++){
        for (j=0;j<r;j++){
            printf("P%d: ",i+1);
            scanf("%d",&alloc[i][j]);
        }
    }

    // ip max matrix 
    printf("Enter max matrix:\n");
    for (i=0;i<p;i++){
        for (j=0;j<r;j++){
            printf("P%d: ",i+1);
            scanf("%d",&max[i][j]);
        }
    }

    // ip available resources , and create a temp variable work and copy the available resources
    printf("Enter available resources:\n");
    for (i=0;i<r;i++){
        scanf("%d",&avail[i]);
        work[i]=avail[i];
    }

    // calculate need matrix and printing 
    printf("Need matrix :\n");
    for (i=0;i<p;i++){
        for (j=0;j<r;j++){
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }

    // safety algorithm 

    for (k=0;k<p;k++){
        for (i=0;i<p;i++){
            if (finish[i]==0){
                flag=0;
                for (j=0;j<r;j++){
                    if (need[i][j] > work[j]){
                        flag=1;
                        break;
                    }
                }
                if(flag==0){
                    safeseq[index++]=i;
                    for (y=0;y<r;y++){
                        work[y]+=alloc[i][y];
                        finish[i] = 1;
                    }
                }
            }
        }
    }  
      // Check if system is in a safe state
        int safe = 1;
        for(i = 0; i < p; i++) {
            if(finish[i] == 0) {
                safe = 0;
                break;
            }
        }
    
        if(safe) {
            printf("System is in a safe state.\nSafe Sequence: ");
            for(i = 0; i < p; i++)
                printf("P%d ", safeseq[i]);
            printf("\n");
        } else {
            printf("System is in an unsafe state.\n");
        }
    
}
