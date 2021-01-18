#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

void Create(void);
void Delete(void);
void Append(void);
void Display(void);
void Search(void);
void Duplicate(void);

int main() {
	system("color 80");
	char choice;
	PlaySound("./Sound/open.wav", NULL, SND_FILENAME | SND_ASYNC);
	do {
		system("cls");
		printf("   ----Welcome to Spectre | A text editor by Ayaan Danish---\n");
		printf("\n\t    MAIN MENU: \n");
		printf("----------------------------------\n");
		printf("1. \x1b[97mCREATE\x1b[30m a new text file\n"); 				//ANSI escape sequences used to color the option keywords white
		printf("2. \x1b[97mAPPEND\x1b[30m to an existing text file\n");
		printf("3. \x1b[97mDISPLAY\x1b[30m an existing text file\n");
		printf("4. \x1b[97mDELETE\x1b[30m an existing text file\n");
		printf("5. \x1b[97mDUPLICATE\x1b[30m an existing file.\n");
		printf("6. \x1b[97mSEARCH\x1b[30m for text within a file\n");		
		printf("0. \x1b[97mQUIT\x1b[30m the program\n");
		printf("\nNote: All files will be created in and read from the \x1b[97m'Text Files'\x1b[30m folder.");
		printf("\n\nEnter your choice: \x1b[97m");
		choice = getche();
		printf("\x1b[30m");
		PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
		switch(choice) {
			case '1':
				Create();
				break;
			case '2':
				Append();
				break;
			case '3':
				Display();
				break;
			case '4':
				Delete();
				break;
			case '5':
				Duplicate();
				break;
			case '6':
				Search();
				break;
			case '0':
				break;
			default:
				PlaySound("./Sound/error.wav", NULL, SND_FILENAME | SND_ASYNC);
				printf("\nInvalid Entry, press any key to try again...");
				getch();
		}
	} while (choice!= '0');
	printf("\n\x1b[97mThank you for using my text editor!\nMade By Ayaan Danish (all rights reserved)\x1b[30m");
	PlaySound("./Sound/quit.wav", NULL, SND_FILENAME | SND_SYNC);
}

void Create(void) {
	FILE *fptr;
	char name[20], c, dir[20] = "./Text Files/";
	int invalid=0;
	do {
		invalid=0;
		printf("\nWhat would you like to name your file (enter 'esc' to cancel'):\x1b[97m ");
		gets(name);
		printf("\x1b[30m");
		for(int i=0; i<strlen(name); i++) {
			switch (name[i]) {
				case '/':
				case '\\':
				case ':':
				case '*':
				case '?':
				case '"':
				case '<':
				case '>':
				case '|':
					printf("The file name you entered contains a forbidden character. Please try again.\n\n");
					PlaySound("./Sound/error.wav", NULL, SND_FILENAME | SND_ASYNC);
					invalid = 1;
			}
		}
	} while(invalid == 1);
	PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
	if(strcmp(name,"esc") == 0)
		return;
	strcat(name,".txt");
	fptr = fopen(strcat(dir,name), "w");
	printf("Text file '\x1b[97m\x1b[4m%s\x1b[24m\x1b[30m' created. Enter text to write to the file, press Enter, then CTRL+Z and then Enter again to end input: \n",name);
	printf("--------------------------------------------------------------------------------------------------------\n\x1b[97m");		  																																																				
	do {
		c = getchar();
		fputc(c, fptr);
	} while(c != EOF);
	PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
	printf("\x1b[30m--------------------------------------------------------------------------------------------------------\n");
	fclose(fptr);
	printf("\nFile Saved in the \x1b[97m'Text Files'\x1b[30m folder. Press any key to return to main menu...");
	getch();
}

void Append(void) {
	FILE *fptr;
	char name[20], line[100], c, dir[20] = "./Text Files/";
	printf("\nEnter name of file to append to, enter 'esc' to cancel: \x1b[97m");
	gets(name);
	printf("\x1b[30m");
	PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
	if(strcmp(name,"esc") == 0)
		return;
	strcat(name,".txt");
	fptr = fopen(strcat(dir,name), "r");
	while(!fptr) {
		PlaySound("./Sound/error.wav", NULL, SND_FILENAME | SND_ASYNC);
		printf("Error. File not found. Make sure the file is placed in the \x1b[97m'Text Files'\x1b[30m folder.");
		fclose(fptr);
		printf("\n\nEnter name of file to append to, enter 'esc' to cancel: \x1b[97m");
		gets(name);
		printf("\x1b[30m");
		if(strcmp(name,"esc") == 0)
			return;
		PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
		strcat(name,".txt");
		fptr = fopen(strcat(dir,name), "r");
	}
	printf("--------------------------------------------------------------------------------------------------------\n\x1b[97m");
	while(!feof(fptr)) {
		fgets(line,100,fptr);
		printf("%s",line);
	}
	fclose(fptr);
	fptr = fopen(strcat(dir,name), "a");
	printf("\nEnter text to append from here, press Enter, then CTRL+Z and then Enter again to end input:\n");
	do {
		c = getchar();
		fputc(c, fptr);
	} while(c != EOF);
	PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
	fclose(fptr);
	printf("\x1b[30m--------------------------------------------------------------------------------------------------------\n");
	printf("\nFile Saved in the \x1b[97m'Text Files'\x1b[30m folder. Press any key to return to main menu...");
	getch();
}

void Display(void) {
	FILE *fptr;
	char name[20], line[100], dir[20] = "./Text Files/";
	printf("\nEnter name of text file to display, or enter 'esc' to cancel and return to menu: \x1b[97m");
	gets(name);
	printf("\x1b[30m");
	PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
	if(strcmp(name,"esc") == 0)
		return;
	strcat(name,".txt");
	fptr = fopen(strcat(dir,name), "r");
	while(!fptr) {
		PlaySound("./Sound/error.wav", NULL, SND_FILENAME | SND_ASYNC);
		printf("Error. Text file not found. Make sure it exists and is placed in the \x1b[97m'Text Files'\x1b[30m folder.");
		fclose(fptr);
		printf("\n\nEnter name of text file to display, or enter 'esc' to cancel and return to menu: \x1b[97m");
		gets(name);
		printf("\x1b[30m");
		PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
		if(strcmp(name,"esc") == 0)
			return;
		strcat(name,".txt");
		fptr = fopen(strcat(dir,name), "r");	
	}
	printf("--------------------------------------------------------------------------------------------------------\n\x1b[97m");
	while(!feof(fptr)) {
		fgets(line,100,fptr);
		printf("%s",line);
	}
	printf("\n\x1b[30m--------------------------------------------------------------------------------------------------------\n");
	printf("Press any key to return to main menu...");
	getch();
}

void Delete(void) {
	FILE *fptr;
	char name[20], dir[20] = "./Text Files/";
	int flag;
	printf("\nEnter name of text file to delete, or enter 'esc' to cancel and return to menu: \x1b[97m");
	gets(name);
	printf("\x1b[30m");
	PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
	if(strcmp(name,"esc") == 0)
		return;
	strcat(name,".txt");
	flag = remove(strcat(dir,name));
	while(flag != 0) {
		PlaySound("./Sound/error.wav", NULL, SND_FILENAME | SND_ASYNC);
		printf("Error, text file could not be deleted. Make sure it exists is in the \x1b[97m'Text Files'\x1b[30m folder.");
		printf("\n\nEnter name of text file to delete, or enter 'esc' to cancel and return to menu: \x1b[97m");
		gets(name);
		printf("\x1b[30m");
		PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
		if(strcmp(name,"esc") == 0)
			return;
		strcat(name,".txt");
		flag = remove(name);
	}
	printf("\n\x1b[97mFile deleted successfully.\x1b[30m Press any key to return to main menu...");
	getch();
}

void Duplicate(void) {
	FILE *fptr, *cfptr;
	char name[20], cname[20], line[100], dir[20] = "./Text Files/";
	int invalid=0;
	printf("\nEnter name of text file to duplicate, or enter 'esc' to cancel and return to menu: \x1b[97m");
	gets(name);
	printf("\x1b[30m");
	PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
	fflush(stdin);
	if(strcmp(name,"esc") == 0)
		return;
	strcat(name,".txt");
	fptr = fopen(strcat(dir,name), "r");
	while(!fptr) {
		PlaySound("./Sound/error.wav", NULL, SND_FILENAME | SND_ASYNC);
		printf("Error. Text file not found. Make sure it exists and is placed in the \x1b[97m'Text Files'\x1b[30m folder.");
		fclose(fptr);
		printf("\n\nEnter name of text file to duplicate, or enter 'esc' to cancel and return to menu: \x1b[97m");
		gets(name);
		printf("\x1b[30m");
		PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
		if(strcmp(name,"esc") == 0)
			return;
		strcat(name,".txt");
		fptr = fopen(strcat(dir,name), "r");
	}
	
	do {
		invalid=0;
		printf("What would you like to name your duplicate file (enter 'esc' to cancel'): \x1b[97m");
		gets(cname);
		printf("\x1b[30m");
		for(int i=0; i<strlen(cname); i++) {
			switch (cname[i]) {
				case '/':
				case '\\':
				case ':':
				case '*':
				case '?':
				case '"':
				case '<':
				case '>':
				case '|':
					printf("The file name you entered contains a forbidden character. Please try again.\n\n");
					PlaySound("./Sound/error.wav", NULL, SND_FILENAME | SND_ASYNC);
					invalid = 1;
			}
		}
	} while(invalid == 1);
	PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
	if(strcmp(cname,"esc") == 0)
		return;
	strcat(cname,".txt");
	strcpy(dir, "./Text Files/");
	cfptr = fopen(strcat(dir,cname), "w");
	while(!feof(fptr)) {
		fgets(line,100,fptr);
		fputs(line,cfptr);
	}
	fclose(cfptr);
	fclose(fptr);
	printf("\nText file '\x1b[97m\x1b[4m%s\x1b[24m\x1b[30m' has been duplicated as '\x1b[97m\x1b[4m%s\x1b[24m\x1b[30m'. Press any key to return to main menu.",name,cname);
	getch();
}

void Search(void) {
	FILE *fptr;
	char name[20], key[30], line[100], dir[20] = "./Text Files/";
	int linenum=1, found=0;
	printf("\nEnter name of text file to search from, or enter 'esc' to cancel and return to menu: \x1b[97m");
	gets(name);
	printf("\x1b[30m");
	PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);	
	if(strcmp(name,"esc") == 0)
		return;
	strcat(name,".txt");
	fptr = fopen(strcat(dir,name), "r");
	while(!fptr) { 
		PlaySound("./Sound/error.wav", NULL, SND_FILENAME | SND_ASYNC);
		printf("Error. Text file not found. Make sure it exists and is placed in the \x1b[97m'Text Files'\x1b[30m folder.");
		fclose(fptr);
		printf("\n\nEnter name of text file to search from, or enter 'esc' to cancel and return to menu: \x1b[97m");
		gets(name);
		printf("\x1b[30m");
		PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
		if(strcmp(name,"esc") == 0)
			return;
		strcat(name,".txt");
		fptr = fopen(strcat(dir,name), "r");
	}
	printf("Enter your search keyword (remember, it is case sensitive): \x1b[97m"); //searching starts here
	gets(key);
	printf("\x1b[30m");
	PlaySound("./Sound/click.wav", NULL, SND_FILENAME | SND_ASYNC);
	while(!feof(fptr)) {
		fgets(line,100,fptr);
		if(strstr(line,key)) {
			found=1;
			std::string str(line);
			printf("Keyword found in line %d:\n", linenum);
			printf("--------------------------------------------------------------------------------------------------------\n\x1b[97m");
			int pos = str.find(key);
            int keylen = strlen(key);
            int linelen = strlen(line);
            if (pos == 0) {																			//if the line starts with the keyword then this case runs
				printf("\x1b[34m\x1b[4m%s\x1b[100m\x1b[24m", str.substr(pos, keylen).c_str());		//print the keyword (the first word in this case) in a different color
                printf("\x1b[97m%s\r\n", str.substr(pos+keylen, linelen).c_str());					//reset the color to default and print the rest of the line																			
        	}	
            else { 																					//if the line does NOT start with the keyword then this case will run
                printf("%s", str.substr(0, pos).c_str()); 											//print the line until the keyword is reached, in default colors
                printf("\x1b[34m\x1b[4m%s\x1b[100m\x1b[24m", str.substr(pos, keylen).c_str()); 		//print the keyword in a different color so it stands out
                printf("\x1b[97m%s\r\n", str.substr(pos+keylen, linelen).c_str()); 		    		//reset the color to default and print the rest of the line
        	}
			printf("\x1b[30m--------------------------------------------------------------------------------------------------------\n\n");
		}
		linenum++;
	}
	if(!found) {
		PlaySound("./Sound/error.wav", NULL, SND_FILENAME | SND_ASYNC);
		printf("Keyword not found in file.");
	}
	printf("\nPress any key to return to main menu: ");
	getch();
}

