#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

char opcode[10], operand[10], label[10], t1[10], t2[10], t3[10];
int locctr, start, len, s = -1, o = -1, i, j = 0, flag, size = 0, opd;
FILE *fp1, *fp2, *fp3, *fp4, *fp5;

struct SYMTAB {
    char label[10];
    int addr;
} ST[30];

struct OPTAB {
    char opcode[10];
    char hexcode[10];
} OT[30];

void read_OPTAB() {
    while (1) {
        o++;
        fscanf(fp2, "%s%s", OT[o].opcode, OT[o].hexcode);
        if (getc(fp2) == EOF) {
            break;
        }
    }
}

void read_line() {
    strcpy(t1, "");
    strcpy(t2, "");
    strcpy(t3, "");
    fscanf(fp1, "%s", t1);
    if (getc(fp1) != '\n') {
        fscanf(fp1, "%s", t2);
        if (getc(fp1) != '\n') {
            fscanf(fp1, "%s", t3);
        }
    }

    if (strcmp(t1, "") != 0 && strcmp(t2, "") != 0 && strcmp(t3, "") != 0) {
        strcpy(label, t1);
        strcpy(opcode, t2);
        strcpy(operand, t3);
    } else if (strcmp(t1, "") != 0 && strcmp(t2, "") != 0 && strcmp(t3, "") == 0) {
        strcpy(label, "");
        strcpy(opcode, t1);
        strcpy(operand, t2);
    } else if (strcmp(t1, "") != 0 && strcmp(t2, "") == 0 && strcmp(t3, "") == 0) {
        strcpy(label, "");
        strcpy(opcode, t1);
        strcpy(operand, "");
    }
}

int main() {
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "w");
    fp4 = fopen("intermed.txt", "w");
    fp5 = fopen("length.txt", "w");

    read_OPTAB();

    fscanf(fp1, "%s%s%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
        read_line();
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "") != 0) {
            for (i = 0; i <= s; i++) {
                if (strcmp(ST[i].label, label) == 0) {
                    printf("Error: Duplicate Symbol\n");
                    exit(0);
                }
            }
            s++;
            strcpy(ST[s].label, label);
            ST[s].addr = locctr;
        }

        flag = 0;
        for (i = 0; i <= o; i++) {
            if (strcmp(opcode, OT[i].opcode) == 0) {
                locctr += 3;
                size += 3;
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
                size += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                opd = atoi(operand);
                locctr += 3 * opd;
            } else if (strcmp(opcode, "RESB") == 0) {
                opd = atoi(operand);
                locctr += opd;
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'X')
                    len = (strlen(operand) - 3) / 2;
                else
                    len = strlen(operand) - 3;
                locctr += len;
                size += len;
            }
        }

        read_line();
    }

    fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);

    for (i = 0; i <= s; i++) {
        fprintf(fp3, "%s\t%d\n", ST[i].label, ST[i].addr);
    }

    fprintf(fp5, "%d\n", start);
    fprintf(fp5, "%d\n", size);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);

    return 0;
}
