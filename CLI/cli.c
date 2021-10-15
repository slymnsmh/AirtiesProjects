#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define MAX_PARAMS 10

char *tokens[MAX_PARAMS] = {0};
int size;

void concatStrings(char *str1, char* str2) {
    
}

void getTokens(char input[]) {
    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        tokens[i++] = token;
        token = strtok(NULL, " ");
    }
    size = i;
}

/*xmlDocPtr getdoc (char *docname) 
{
	xmlDocPtr doc;
	
	doc = xmlParseFile(docname);
	
	if (doc == NULL ) 
	{
		fprintf(stderr, "Document not parsed successfully.\n");
		return NULL;
	}

	return doc;
}*/

int main ()
{
    /*xmlDocPtr doc = NULL;
    char *docname = "data.xml";


    doc = getdoc(docname);
    xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);

    xmlFreeDoc(doc);
    xmlCleanupParser();

    if (size == 5) {
        system("gcc -o prog prog.c");
        system("./prog");
    }

    return(0);*/

    char input[] = "";
    char cmd[] = "nano ";
    while (strcmp(input, "quit")!= 0)
    {
        printf("ssd-cli$ ");
        scanf("%[^\n]%*c", input);

        getTokens(input);
        if(strcmp(tokens[0], "clear") == 0)
        {
            if (size == 1)
            {
                system("clear");
            }
            else {
                printf(RED "Error: " RESET "Inappropriate number of parameters for command '%s'.\n", tokens[0]);
            }
        }
        else if(strcmp(tokens[0], "print") == 0)
        {
            if (size == 1 &&
                    abc = 5)
            {
                printf(YELLOW "Warning: " RESET "There is no input to print!\n");
            }
            else {
                for (int i = 1; tokens[i] != NULL; i++) {
                    printf("%s ", tokens[i]);
                }
                printf("\n");
            }
        } else if(strcmp(tokens[0], "run") == 0) {
            if (size == 2) {
                printf("--- %s - %ld\n", tokens[1], strlen(tokens[1]));
                for(int i = 0; i < strlen(tokens[1]); i++) {
                    char a = tokens[1][i];
                    printf("-?- %c\n", a);
                    strncat(cmd, &a, 1);
                }
                printf("*** %s\n", cmd);
                //system("nano tokens[1]");
            }
            else {
                printf(RED "Error: " RESET "Inappropriate use of command '%s'.\n", tokens[0]);
            }
        }
        else if(strcmp(tokens[0], "read") == 0)
        {
            if (size == 2)
            {
                //system("nano tokens[1]");
            }
            else {
                printf(RED "Error: " RESET "Inappropriate use of command '%s'.\n", tokens[0]);
            }
        }
        else {
            printf(RED "Error: " RESET "Undefined command '%s'.\n", tokens[0]);
        }
    }
}