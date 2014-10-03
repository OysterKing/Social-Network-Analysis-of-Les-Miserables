	/*Comhghall McKeating 12328401*/
	/*Software Engineering Project 4*/
	/*Social Network Analysis*/
	
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	
	const int n_characters = 64; //number of characters in the book
	
	struct node
	{
		int line_number;
		struct node *next;
	};
	
	struct names
	{
		char name[20];
	};

	struct names cast[64];

	struct node* heads[64]; //array with the roots of each list
	struct node* currs[64]; //array holding pointers to current positions in list
	
	
	void read_in(void) /*this function takes the character names into an array of structs. */
	{
		int i = 0, length;
	
		FILE *fopen(), *fp1;
		
		fp1 = fopen("LongNames.txt", "r");
		
		
		if (fp1 == NULL) /*	Check if opened correctly */
		{
			printf("ERROR, unable to open Names.txt for reading.\n PROGRAM TERMINATED");
			exit(0); /*Terminate program*/
		}
		
		else
		{
			while(fgets(cast[i].name, 20, fp1) != NULL) //note: fgets considers the newline character a valid char
			{	
			//fgets includes the \n when it reads in the string.
				length = strlen(cast[i].name); //find length of the current string.
				
				cast[i].name[length - 1] = '\0'; //we must replace the newline character with the terminating null character for strstr to work
				i = i + 1; 
			}	
		}
		fclose(fp1);
	}
	
	void setup(int n) //links the head and current pointers for n lists in an array
	{
		int i;
		
		for(i = 0; i < n; i++)
		{
			heads[i] = NULL;
			currs[i] = heads[i];
		}
	}

	struct node* create_list(int current_line, int character) //this function creates the list that will store the line number on which the current character appears
	{
		struct node *ptr = (struct node*)malloc(sizeof(struct node));
		
		ptr -> line_number = current_line;
		ptr -> next = NULL; //last node points to nothing
		
		heads[character] = currs[character] = ptr; //reset pointer to start of list
		
		return ptr;
	}	
	
	struct node* add_to_list(int current_line, int character)
	{
		if(heads[character] == NULL)
		{
			return (create_list(current_line, character));
		}	
	
		struct node *ptr = (struct node*)malloc(sizeof(struct node));
		
		ptr -> line_number = current_line;
		ptr -> next = NULL;
		currs[character] -> next = ptr;
		currs[character] = ptr;
		
		return ptr;
	}
	

	void comparitor()
	{
		FILE *fp;
		fp = fopen("PairedNames.csv", "w");
		if (fp == NULL)
		{
			printf("ERROR UNABLE TO OPEN PairedNames.csv\nPROGRAM TERMINATED\n");
			exit(0);
		}
	
		struct node *ptr;
		struct node *ptr2;
		int i,j;
	
		for(i=0;i<n_characters;i++)
		{
			ptr = heads[i];
			while(ptr!=NULL)
		{
		
		for(j=(i+1);j<n_characters;j++)
		{
			ptr2 = heads[j];
			if(i==j)continue;
			while(ptr2!=NULL)
		{

		if((ptr->line_number>=(ptr2->line_number-5))&&(ptr->line_number<=(ptr2->line_number+5))) //this loop checks if characters occur within 5 lines of each other
		{
			char temp[20],temp2[20];
			strcpy(temp,cast[i].name);
			strcpy(temp2,cast[j].name);
			int k=0;

		while(1)
		{
			if(temp[k]=='\n'||temp[k]==EOF)
			{
				temp[k]='\0';
				break;
			}
			
			k++;

			if(k>20)break;
		}

		k=0;

		while(1)
		{
			if(temp2[k]=='\n'||temp2[k]==EOF)
			{
				temp2[k]='\0';
				break;
			}
			k++;
			if(k>20)break;
		}

		printf("%s , %s\n",temp,temp2);
		fprintf(fp, "%s,%s\n",temp,temp2);//prints to file ComparedNames.csv
		break;
	}

	ptr2=ptr2->next;
}
}
ptr = ptr->next;
}
}
fclose(fp);
return;
}
	
	
	int main()
	{
		int i = 0, j, k = 0, current_line = 1, length;
		char temp[20], temp2[100];
		char *pch;
		
		
		read_in();
		
		FILE *fopen(), *fp1;
		FILE *fopen(), *fp2;
		FILE *fopen(), *fp3;
		
		fp1 = fopen("LongNames.txt", "r");
		fp2 = fopen("LesMiserables.txt", "r");
		fp3 = fopen("Paired.txt", "w");
		
		setup(n_characters); //this fucntion creates a list for each character
		
		while(fgets(temp2, 100, fp2) != NULL) 
		{
		
			for(i = 0; i < 64; i++)//note that fgets includes the newline character meaning that strstr won't function.
			{
			//	current_line = 1; //reset for each character
	
				if(temp[0] == '\n')
				{
					break;
				}	
		
				length = strlen(cast[i].name); //find length of the current string.
				
				pch = strstr(temp2, cast[i].name);
				
				if(pch != NULL)
				{
					add_to_list(current_line, i); //if the character is found, add the line number to his/her list and move on
				}	
			}
		
			current_line = current_line + 1;
		}	
		
		comparitor();
		
		printf("%d", i);
		
		fclose(fp1);
		fclose(fp2);
		fclose(fp3);
		return EXIT_SUCCESS;
	}	