/*
Samuel Drumond
Program 4
CGS3269 - Spring 2024
*/

/*
READ ME
1. Make sure tinyHarvard.c and file.txt are in the same directory 
2. To compile: gcc tinyHarvard.c
3. To run: ./a.out fileName.txt
*/

#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

#define IM_SIZE 250
#define DM_SIZE 10

// Define opcodes
enum Opcode {
    LOAD = 1,
    ADD,
    STORE,
    SUB,
    IN,
    OUT,
    END,
    JMP,
    SKIPZ
};

int MAR = 0; // Memory Address Register
int MDR = 0; // Memory Data Register
int PC = 0;  // Program Counter
int A = 0;   // Accumulator

int IM[IM_SIZE] = {0}; // Instruction Memory
int DM[DM_SIZE] = {0}; // Data Memory

// Define instruction structure
typedef struct {
    int opcode;
    int address;
} Instruction;
Instruction IR;

// Function prototypes
void loadProgram(const char *filename, Instruction *im);
void executeProgram(Instruction *im, int *dm);


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    Instruction im[IM_SIZE];
    int dm[DM_SIZE] = {0};

    loadProgram(argv[1], im);
    executeProgram(im, dm);
    return 0;
    
}

void loadProgram(const char *filename, Instruction *im) {

    printf("Reading Program...\n");
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        exit(0);
        return;
    }

    int op, addr;
    int i = 0;

    while (fscanf(file, "%d %d", &op, &addr) != EOF && i < IM_SIZE) {
        im[i].opcode = op;
        im[i].address = addr;
        i++;
    }
    printf("Program Loaded\n");
    fclose(file);
}


void executeProgram(Instruction *IM, int *DM)
{
    printf("Run.\n");
    while (IM[PC].opcode != END)
    {
        printf("PC = %d | A = %d | DM = [", PC, A);
        for (int i = 0; i < DM_SIZE; i++)
        {
            printf("%d", DM[i]);
            if (i < DM_SIZE - 1)
            {
                printf(", ");
            }
        }
        printf("]\n");

        //Fetch
        Instruction IR = IM[PC];
        PC += 2;

        if(IR.opcode == LOAD)
        {
            printf("/*Loading value to accumulator*/\n");
            MAR = IR.address;
            MDR = DM[MAR];
            A = MDR; 
        }
        else if(IR.opcode == ADD)
        {
            printf("/*Adding Value to accumalator*/\n");
            MAR = IR.address;
            MDR = DM[MAR];
            A += MDR;
        }
        else if(IR.opcode == STORE)
        {
            printf("/*Storing Value into Variable*/\n");
            MAR = IR.address;
            MDR = A;
            DM[MAR] = MDR;
        }
        else if(IR.opcode == SUB)
        {
            printf("/*Subtracting Value from accumalator*/\n");
            MAR = IR.address;
            MDR = DM[MAR];
            A -= MDR;
        }     
        else if(IR.opcode == IN)
        {
            printf("/*Input Value*/\n");
            scanf("%d", &MDR);
            A = MDR;
        }
        else if(IR.opcode == OUT)
        {
            printf("/*Outputting Value in the acccumulator*/\n%d\n", A);
        } 
        else if(IR.opcode == JMP)
        {
            printf("/*Jumping to intruction*/\n");
            PC = IR.address;
        } 
        else if(IR.opcode == SKIPZ)
        {
            printf("/*Skip to next instruction*/\n");
            if(A==0)
            {
                PC += 1;
            }
        }
        else
        {
            printf("/*Invalid Opcode detected*/\n %d\n", IR.opcode);
        }

    }

    printf("PC = %d | A = %d | DM = [", PC, A);
    for (int i = 0; i < DM_SIZE; i++)
    {
        printf("%d", DM[i]);
        if (i < DM_SIZE - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    printf("/*Program Complete*/\n");

}