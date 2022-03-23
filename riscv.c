#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
//#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file
#include "string.h"

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 s* Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}

/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */

bool interpret(char* instr){
	char* token = strtok(instr, " ");

	if((token[0] == 'A') && (token[1] == 'D') && (token[2] == 'D') && (token[3] == 'I')){
		
		int x = ((int)(token[6]-48)*10 + (int)(token[7])-48);
		int y = ((int)(token[10]-48)*10 + (int)(token[11])-48);
		int z = ((int)(token[13]-48)*10 + (int)(token[14])-48);

		if ((x > -1) && (x < 32) && (y > -1) && (y < 32) && (z > -1) && (z < 32)){

			reg[x] = y + z;
		}

		printf("Operation is completed");		

	}else if((token[0] == 'A') && (token[1] == 'D') && (token[2] == 'D')){
		
		int x = ((int)(token[5]-48)*10 + (int)(token[6])-48);
		int y = ((int)(token[9]-48)*10 + (int)(token[10])-48);
		int z = ((int)(token[13]-48)*10 + (int)(token[14])-48);

		if ((x > -1) && (x < 32) && (y > -1) && (y < 32) && (z > -1) && (z < 32)){

			reg[x] = y + z;
		}

		printf("Operation is completed");

	}else if((token[0] == 'L') && (token[1] == 'W')){
		int x = ((int)(token[4]-48)*10 + (int)(token[5])-48);
		int y = ((int)(token[7]-48)*10 + (int)(token[8])-48);
		int z = ((int)(token[11]-48)*10 + (int)(token[12])-48);

		if ((x > -1) && (x < 32) && (y > -1) && (y < 32) && (z > -1) && (z < 32)){

			int offSet = y + z;

			int32_t data = read_address(offSet, "mem.txt");
			
			reg[x] = data;
		}
		printf("Operation is completed");
	
	}else if((token[0] == 'S') && (token[1] == 'W')){
		int x = ((int)(token[4]-48)*10 + (int)(token[5])-48);
		int y = ((int)(token[7]-48)*10 + (int)(token[8])-48);
		int z = ((int)(token[11]-48)*10 + (int)(token[12])-48);

		if ((x > -1) && (x < 32) && (y > -1) && (y < 32) && (z > -1) && (z < 32)){

			int offSet = y + z;

			int32_t memory = write_address(reg[x], offSet, "mem.txt");

		}
		printf("Operation is completed");
	}else{
		printf("Worng operation");
	}
}

/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

/**
 * Prints all 32 registers in column-format
 */
void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}

/**
 * Your code goes in the main
 *
 */
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	print_regs();

	// Below is a sample program to a write-read. Overwrite this with your own code.
	//write_read_demo();

	printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");


	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(instruction, 1000, stdin) == NULL;
	while(!is_null){
		interpret(instruction);
		printf("\n");
		print_regs();
		printf("\n");

		is_null = fgets(instruction, 1000, stdin) == NULL;
	}

	printf("Good bye!\n");

	return 0;
}


