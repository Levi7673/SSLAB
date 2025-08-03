#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

typedef struct {
    char label[10];
    int addr;
} SYMTAB;

typedef struct {
    char opcode[10];
    char hexcode[10];
} OPTAB;

SYMTAB symtab[MAX];
OPTAB optab[MAX];

char label[10], opcode[10], operand[10];
int symCount = 0, optCount = 0;
int locctr = 0, startAddr = 0, programLen = 0;

FILE *fin, *fopt, *fsym, *fint, *flen;

void readOptab() {
    while (fscanf(fopt, "%s %s", optab[optCount].opcode, optab[optCount].hexcode) != EOF) {
        optCount++;
    }
}

void parseLine(FILE *fp) {
    char temp[3][10] = {"", "", ""};
    int count = fscanf(fp, "%s", temp[0]);
    if (count != 1) return;

    if (fscanf(fp, "%s", temp[1]) == 1) {
        if (fscanf(fp, "%s", temp[2]) == 1) {
            strcpy(label, temp[0]);
            strcpy(opcode, temp[1]);
            strcpy(operand, temp[2]);
        } else {
            strcpy(label, "");
            strcpy(opcode, temp[0]);
            strcpy(operand, temp[1]);
        }
    } else {
        strcpy(label, "");
        strcpy(opcode, temp[0]);
        strcpy(operand, "");
    }
}

int isOpcode(char *code) {
    for (int i = 0; i < optCount; i++) {
        if (strcmp(optab[i].opcode, code) == 0)
            return 1;
    }
    return 0;
}

int symbolExists(char *lbl) {
    for (int i = 0; i < symCount; i++) {
        if (strcmp(symtab[i].label, lbl) == 0)
            return 1;
    }
    return 0;
}

void addSymbol(char *lbl, int addr) {
    if (symbolExists(lbl)) {
        printf("Error: Duplicate symbol %s\n", lbl);
        exit(1);
    }
    strcpy(symtab[symCount].label, lbl);
    symtab[symCount++].addr = addr;
}

int main() {
    fin = fopen("input.txt", "r");
    fopt = fopen("optab.txt", "r");
    fsym = fopen("symtab.txt", "w");
    fint = fopen("intermed.txt", "w");
    flen = fopen("length.txt", "w");

    readOptab();

    fscanf(fin, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        startAddr = atoi(operand);
        locctr = startAddr;
        fprintf(fint, "\t%s\t%s\t%s\n", label, opcode, operand);
    } else {
        locctr = 0;
        strcpy(label, "");
    }

    parseLine(fin);
    while (strcmp(opcode, "END") != 0) {
        fprintf(fint, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "") != 0) {
            addSymbol(label, locctr);
        }

        if (isOpcode(opcode)) {
            locctr += 3;
            programLen += 3;
        } else if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
            programLen += 3;
        } else if (strcmp(opcode, "RESW") == 0) {
            int w = atoi(operand);
            locctr += 3 * w;
        } else if (strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operand);
        } else if (strcmp(opcode, "BYTE") == 0) {
            int len = (operand[0] == 'X') ? (strlen(operand) - 3) / 2 : strlen(operand) - 3;
            locctr += len;
            programLen += len;
        }

        parseLine(fin);
    }

    fprintf(fint, "\t%s\t%s\t%s\n", label, opcode, operand);

    for (int i = 0; i < symCount; i++) {
        fprintf(fsym, "%s\t%d\n", symtab[i].label, symtab[i].addr);
    }

    fprintf(flen, "%d\n%d\n", startAddr, programLen);

    fclose(fin);
    fclose(fopt);
    fclose(fsym);
    fclose(fint);
    fclose(flen);

    printf("Pass 1 complete. Intermediate files generated.\n");
    return 0;
}
