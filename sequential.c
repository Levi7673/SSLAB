#include<stdio.h>
#include<string.h>

typedef struct {
        char fname[20];
        int sb , nob ;
    }file;
int main()
{
    int i , j , n ; 
    char s[20];
    file f[20];
    printf("Enter number of files : ");
    scanf("%d",&n);
    for (i=0;i<n;i++){
        printf("Enter file name : ");
        scanf("%s",&f[i].fname);
        printf("starting block of file :");
        scanf("%d",&f[i].sb);
        printf("Enter no. of block :");
        scanf("%d",&f[i].nob);
    }
    printf("Enter a file name to be searched : ");
    scanf("%s",s);
    for (i=0;i<n;i++){
        if (strcmp(f[i].fname,s)==0){
            printf("File_name\t\tstarting_block\t\tno_block\n");
            printf("%s\t\t%d\t\t%d\n",f[j].fname,f[j].sb,f[j].nob);
        } return 0;
    }
printf("file not found!");
return 0;
}
