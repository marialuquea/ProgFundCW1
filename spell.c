//	Author: Maria Luque Anguita
//	Napier matric number: 40280156
//	Date of last modification: 26 Feb 2017
//	Purpose of program: spell checker


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Compares input word with dictionary words
void compare(char *word, int line, int output_flag, FILE *output_file)
{
	//create new file to store dictionary.txt in read mode
	FILE *file;
	file = fopen("dictionary.txt", "r");

	//initialising values
	char c;
	char word2[50];
	int i = 0;

	//While it is not the end of the file dictionary.txt
	while(!feof(file))
	{
		//get the next character of the file (an unsigned char) and store in variable "c"
		c = fgetc(file);
		
		//if "c" is a letter
		if(isalpha(c))
		{
			//add character in lower case to word2 in that index and increment the index of word2
			word2[i++] = tolower(c);
		}
		else
		{
			//when it is the end of the word, add a null terminator
			word2[i++] = '\0';

			
			//compare to words in dictionary
			if (strcmp(word, word2)==0)
			{
				//if word appears in dictionary, its correct
				break;
			}
			//reset index in word2 to start a new word 
			i = 0;
		}
		//when the file has finished
		if(feof(file))
		{
			//print results to a file if argument -o was passed
			if (output_flag)
			{ 
				fprintf(output_file, "The word '%s' is NOT correct in line %d.\n", word, line);
			}
			//print result to console if there was no -o
			else
			{
				printf("The word '%s' is NOT correct in line %d.\n", word, line);
			}
			break;
		}	
	}
	//close the file
	fclose(file);
}

void append(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

int main(int argc, char **argv)
{
	//initialise variables
	char input_flag = 0;
	char output_flag = 0;
	char case_flag = 0;
	char c;
	char word[50];
	char word_lower[50];
	word_lower[0] = '\0';
	int i = 0;
    int line_count = 1;

	FILE *input_file;
	FILE *output_file;


	//read arguments 
    for(int i = 0; i < argc; ++i)
    {
    	//check if there is an input file
    	if (strcmp(argv[i], "-i") == 0)
    	{
    		input_flag = 1;
    		//Open file after "-i" in the arguements for reading
    		input_file = fopen(argv[i+1], "r");

    	}
    	//check if the user wants the result printed in a file or not
    	if (strcmp(argv[i], "-o") == 0)
    	{
			output_flag = 1;
			//open or create a file for writing
			output_file = fopen(argv[i+1], "w");

    	}
    	//check if the user wants to ignore case
		if (strcmp(argv[i], "-c") == 0)
		{
			case_flag = 1;
		}
	}

	//if -i written in the arguments
	if (input_flag)
	{
		//while it is not the end of the file
		while(!feof(input_file))
		{
			//get each character
			c = fgetc(input_file);
			//if character is a letter
			if(isalpha(c))
			{
				//add character to "word" in that index and increment index
				word[i++] = tolower(c);
			}
			else
			{
				//add null terminator when the word has been read
				word[i++] = '\0';

				//increment line number each time there is a new line
                if(c == '\n')
                {
                  line_count++;
                }
				//compare to words in dictionary
				compare(word, line_count, output_flag, output_file);
				i = 0;
			}
			
		}
		//close the file
		fclose(input_file);
	}
	else
	{
		//if there is no "-i"
		printf("Type a word to check if its correct and press enter:\n");

		//reads a line from the console (thus stdin) and stores it in "word"
		fgets(word, 50, stdin);

		//add a null terminator at the end of the word
		if (word[strlen(word)-1] == '\n')
			word[strlen(word)-1] = '\0';

		//ignore case if "-c" by lowering each case
		if (case_flag == 1)
		{
			//for each char in uppercase word
			for (int i = 0; word[i]; i++)
			{
				//make every char lower case
				word[i] = tolower(word[i]);
				//add each new lowercase char to the new word
				append(word_lower, word[i]);
			}

			//find length of word to add null terminator at the end
			int i = strlen(word_lower);
			//add null terminator to end of word
			word_lower[i++] = '\0';

			//compare lower case word to dictionary
			compare(word_lower, line_count, output_flag, output_file);
		}
		else
		{
			//if it is case sensitive, just compare word to dictionary as it is
			compare(word, line_count, output_flag, output_file);
		}
	//main function must always return 0
	 return 0;
	}
}