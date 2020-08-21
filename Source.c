/* Andrew Lucas CSC632 Programming Assignment #1 Dr. Richard Fox
This program is written in C and is design to decode messages from a simple formula
The program will step through the file going character by character to determine
if it should be outputted, converted then outputted, or discarded.  The program then
will output those characters to a new file and generate a results page in the console log.
The code is UpperCase then lowercase repeating until we see a period, then we look for another
uppercase. Only the first letter of a sentence will ever be uppercase in the output.
A summary is then printed to the console once it is complete with some statistics.
*/

//Required Libraries for the Assignment
#include <stdio.h>
#include <ctype.h>
//Allows program to run
#pragma warning(disable : 4996);

void main()
{
	//All this does is allow me to hardcode file names and
	//switch between which ones run.
	char file[] = "file1.txt";
	//char file[] = "file2.txt";
	//char file[] = "file3.txt";
	char fileOut[] = "file1out.txt";
	//char fileOut[] = "file2out.txt";
	//char fileOut[] = "file3out.txt";

	FILE* fp1 = fopen(file, "r");		//input file pointer
	FILE* fp2 = fopen(fileOut, "w");	//output file pointer
	char c;								//current input char to test
	int totalChar = 0;					//vars to keep track of total char
	int totalOut = 0;
	int upCase = 1;		//used to test if we need to find a Upper/Lower char
	int start = 1;		//for the start of a sentence							
	int var;		//this is used in my last line to keep the terminal open
	double reduction;	//used for math in the summary

	//Starts the loop to step through the input file char by char
	while ((c = getc(fp1)) != EOF) {
		//keeps track of the total number of char in the input file.
		totalChar++;
		//tests to see if its not a letter, in which case it is always outputted
		if (!isalpha(c)) {
			putc(c, fp2);
			totalOut++;
			//tests for a . in case we need to start a new sentence.
			if (c == '.') {
				if (!upCase) {
					//We need to make sure we look for an uppercase after a period.
					upCase = 1;
				}
				start = 1;
			}
		}
		else {
			//this tests to see if the ascii value of char is under 95 for a uppercase
			if (upCase && c < 95) {
				//if its the start then we output it as uppercase, otherwise its lowercase
				if (!start) {
					//putc writes the char to file
					putc(tolower(c), fp2);
					//increases totalOut to keep track of output size in char.
					totalOut++;
					//changes the upper/lower toggle for the next loop interation
					upCase = 0;
				}
				else {
					putc(toupper(c), fp2);
					totalOut++;
					upCase = 0;
					//start being zero makes sure that every output is done as a lowercase
					//until we reach a period, which is the only way it becomes 1 again.
					start = 0;
				}
			}
			//tests to see if the char ascii value in greater than 95 for a lowercase
			if (!upCase && c > 95) {
				putc(tolower(c), fp2);
				totalOut++;
				upCase = 1;
			}
		}
	}
	//closes our file pointers
	fclose(fp1);
	fclose(fp2);

	//the math casted as doubles since they are int types.
	reduction = (double)(((double)totalOut / (double)totalChar) * 100);
	
	//output for the summary for each run.
	printf("\nInput file:\t\t\t file1.txt");
	printf("\nOutput file:\t\t\t file1out.txt");
	printf("\nNumber of input characters:\t %d", totalChar);
	printf("\nNumber of output characters:\t %d", totalOut);
	//this is formatted as a percent with 2 decimal places
	printf("\nPercent reduction in output:\t %.2f%%\n", reduction);

	//this only keeps the window open so I can review the summary.
	var = scanf("%d", &var);
}

/*

File 1:

Input file:                      file1.txt
Output file:                     file1out.txt
Number of input characters:      92
Number of output characters:     36
Percent reduction in output:     39.13%

File 2:

Input file:                      file2.txt
Output file:                     file2out.txt
Number of input characters:      348
Number of output characters:     155
Percent reduction in output:     44.54%

File 3:

Input file:                      file3.txt
Output file:                     file3out.txt
Number of input characters:      726
Number of output characters:     672
Percent reduction in output:     92.56%

*/