#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main() {
    char address[10], label[10], opcode[10], operand[10];
    char code[10], mnemonic[10], lab[10], loc[10];
    char start_address[10], prog_length[10];
    int length;

    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("out.txt", "r");
    fp2 = fopen("length.txt", "r");
    fp3 = fopen("optab.txt", "r");
    fp4 = fopen("symtbl.txt", "r");
    
    // Read the first line from the intermediate file (out.txt)
    fscanf(fp1, "%s\t%s\t%s\t%s", address, label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        strcpy(start_address, operand);
        fscanf(fp2, "%s", prog_length);
        printf("H^%s^%s^%s\n", label, start_address, prog_length); // Header record
        printf("T^%s", start_address); // Start of Text record
    }

    // Read the next line
    fscanf(fp1, "%s\t%s\t%s\t%s", address, label, opcode, operand);

    while (strcmp(opcode, "END") != 0) {
        // Handle instructions
        if (strcmp(label, "XX") != 0 && strcmp(label, "**") != 0) { // Check for a label
            // Reset optab.txt file pointer to the beginning
            rewind(fp3);
            while (fscanf(fp3, "%s\t%s", code, mnemonic) != EOF) {
                if (strcmp(opcode, code) == 0) {
                    // Reset symtbl.txt file pointer to the beginning
                    rewind(fp4);
                    while (fscanf(fp4, "%s\t%s", lab, loc) != EOF) {
                        if (strcmp(operand, lab) == 0) {
                            printf("^%s%s", mnemonic, loc);
                            break;
                        }
                    }
                    break;
                }
            }
        }
        
        // Handle BYTE, WORD, RESW, RESB
        if (strcmp(opcode, "BYTE") == 0) {
            printf("^");
            if (operand[0] == 'X') {
                for (int i = 2; i < strlen(operand) - 1; i++) {
                    printf("%c", operand[i]);
                }
            } else if (operand[0] == 'C') {
                for (int i = 2; i < strlen(operand) - 1; i++) {
                    printf("%X", operand[i]); // ASCII to hex
                }
            }
        } else if (strcmp(opcode, "WORD") == 0) {
            printf("^00000%s", operand);
        }

        fscanf(fp1, "%s\t%s\t%s\t%s", address, label, opcode, operand);
    }
    
    printf("\nE^00%s", start_address); // End record
    
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
}
