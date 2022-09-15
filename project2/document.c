#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "document.h"

/* initializes Document structure */
int init_document(Document *doc, const char *name)
{
    /*if paramater *doc is null*/
    if (doc == NULL)
    {
        return FAILURE;
    }
    /* if paramater *name is null*/
    if (name == NULL)
    {
        return FAILURE;
    }
    /* if size of name is negative or larger than MAX_STR_SIZE */
    if (strlen(name) < 1 || strlen(name) > MAX_STR_SIZE)
    {
        return FAILURE;
    }
    /* making number of paragraphs 0 */
    doc->number_of_paragraphs = 0;

    /* copying name into doc */
    strcpy(doc->name, name);

    return SUCCESS;
}

/* resets doc struct */
int reset_document(Document *doc)
{
    /* if paramater *doc is null */
    if (doc == NULL)
    {
        return FAILURE;
    }

    /* resets the number of paragraphs to 0 */
    doc->number_of_paragraphs = 0;

    return SUCCESS;
}

/* prints what is inside document */
int print_document(Document *doc)
{
    int i, j;
    /* if paramater *doc is null */
    if (doc == NULL)
    {
        return FAILURE;
    }
    /* prints document name and number of paragraphs */
    printf("Document name: %c%s%c\nNumber of Paragraphs: %d\n", '"', doc->name,
           '"', doc->number_of_paragraphs);
    /* loops through the paragraphs */
    for (i = 0; i < doc->number_of_paragraphs; i++)
    {
        /* loops through the lines of each paragraph */
        for (j = 0; j < doc->paragraphs[i].number_of_lines; j++)
        {
            /* prints the text at every line of every paragraph in the doc */
            printf("%s\n", doc->paragraphs[i].lines[j]);
        }
        /* checks if the document has at least 2 paragraphs and if it is the
           last paragraph it doesnt print*/
        if (doc->number_of_paragraphs > 1 && 
           (doc->number_of_paragraphs - 1 != i))
        {
            printf("\n");
        }
    }
    return SUCCESS;
}

/* This function adds a paragraph at specified place */
int add_paragraph_after(Document *doc, int paragraph_number)
{
    int i;
    /* initializes paragraph struct */
    Paragraph paragraph;

    /* if paramater *doc is null */
    if (doc == NULL)
    {
        return FAILURE;
    }
    /* if there are already the maximum number of paragraphs */
    if (doc->number_of_paragraphs == MAX_PARAGRAPHS)
    {
        return FAILURE;
    }
    /* checks for valid position */
    if (paragraph_number < 0 || paragraph_number >= MAX_PARAGRAPHS)
    {
        return FAILURE;
    }
    /* sets number of lines to 0 */
    paragraph.number_of_lines = 0;
    /*looping backwards to shift paragraphs to correct position */
    for (i = doc->number_of_paragraphs; i >= paragraph_number; i--)
    {
        doc->paragraphs[i] = doc->paragraphs[i - 1];
    }
    /* adds paragraph to specified spot */
    doc->paragraphs[paragraph_number] = paragraph;
    /* increases the number of paragraphs */
    doc->number_of_paragraphs++;

    return SUCCESS;
}

/* this function adds a line to a specified spot */
int add_line_after(Document *doc, int paragraph_number, int line_number, 
                   const char *new_line)
{
    int i;
    /* if paramater *doc is null */
    if (doc == NULL)
    {
        return FAILURE;
    }
    /* if there are already the maximum number of paragraphs */
    if (paragraph_number < 0 || paragraph_number > doc->number_of_paragraphs)
    {
        return FAILURE;
    }
    /* the paragraph already has max number of lines */
    if (doc->paragraphs[paragraph_number - 1].number_of_lines == MAX_PARAGRAPH_LINES)
    {
        return FAILURE;
    }
    /* if specified spot is negative or greater than max*/
    if (line_number < 0 || 
        line_number > doc->paragraphs[paragraph_number - 1].number_of_lines)
    {
        return FAILURE;
    }
    /* if new line is null */
    if (new_line == NULL)
    {
        return FAILURE;
    }
    /* loops through every paragraph */
    for (i = doc->paragraphs[paragraph_number - 1].number_of_lines; 
         i > line_number; i--)
    {
        /* moves lines to correct new spot after adding */
        strcpy(doc->paragraphs[paragraph_number - 1].lines[i], 
               doc->paragraphs[paragraph_number - 1].lines[i - 1]);
    }
    /* adds new line */
    strcpy(doc->paragraphs[paragraph_number - 1].lines[line_number], new_line);
    /* adds one to number of lines */
    doc->paragraphs[paragraph_number - 1].number_of_lines++;
    return SUCCESS;
}

/* keeps of number of lines in paragraph */
int get_number_lines_paragraph(Document *doc, int paragraph_number, int *number_of_lines)
{
    int num_lines;
    /* if doc is null or number of lines is null returns failure */
    if (doc == NULL || number_of_lines == NULL)
    {
        return FAILURE;
    }
    /* finds if specified paragraph is an existing paragraph */
    if (paragraph_number < 0 || paragraph_number > doc->number_of_paragraphs)
    {
        return FAILURE;
    }
    /* assigns number of lines in paragraph to num_lines */
    num_lines = doc->paragraphs[paragraph_number - 1].number_of_lines;
    /* assigns num_lines to the parameter pointer */
    *number_of_lines = num_lines;

    return SUCCESS;
}

/* adds a line to the end of a paragraph */
int append_line(Document *doc, int paragraph_number, const char *new_line)
{   
    /* initializes line number */
    int line_number = doc->paragraphs[paragraph_number - 1].number_of_lines;
    /* if paramater *doc is null */
    if (doc == NULL)
    {
        return FAILURE;
    }
    /* if there are already the maximum number of paragraphs or paragraph is -*/
    if (paragraph_number < 0 || paragraph_number > doc->number_of_paragraphs)
    {
        return FAILURE;
    }
    /* the paragraph already has max number of lines */
    if (doc->paragraphs[paragraph_number - 1].number_of_lines == MAX_PARAGRAPH_LINES)
    {
        return FAILURE;
    }
    /* if new line is null */
    if (new_line == NULL)
    {
        return FAILURE;
    }
    /* adds line */
    add_line_after(doc, paragraph_number, line_number, new_line);
    return SUCCESS;
}

/* removes a specific line */
int remove_line(Document *doc, int paragraph_number, int line_number)
{
    int i;
    /* if paramater *doc is null */
    if (doc == NULL)
    {
        return FAILURE;
    }
    /* checks if it is an existing paragraph */
    if (paragraph_number < 0 || paragraph_number > doc->number_of_paragraphs)
    {
        return FAILURE;
    }
    /* if specified spot is negative or greater than max*/
    if (line_number < 0 || 
        line_number > doc->paragraphs[paragraph_number - 1].number_of_lines)
    {
        return FAILURE;
    }
    /* loops through to find correct line */
    for (i = 0; i <= doc->paragraphs[paragraph_number - 1].number_of_lines - 1;
         i++)
    {
        /* deletes the line */
        if (i >= line_number - 1)
        {
            strcpy(doc->paragraphs[paragraph_number - 1].lines[i], doc->paragraphs[paragraph_number - 1].lines[i + 1]);
        }
    }
    /* number of lines - 1 */
    doc->paragraphs[paragraph_number - 1].number_of_lines--;
    return SUCCESS;
}

/* loads document */
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1], int data_lines)
{
    int i = 0;
    /* if paramater doc, data, or data_lines is null */
    if (doc == NULL || data == NULL || data_lines == 0)
    {
        return FAILURE;
    }

    /* calls add_paragraph_after function */
    add_paragraph_after(doc, 0);

    /* loops through data */
    for (i = data_lines - 1; i >= 0; i--)
    {
        /* finds empty string */
        if (strcmp(data[i], "") == 0)
        {
            /* adds paragraph */
            add_paragraph_after(doc, 0);
        }
        else
        {
            /*
            if (doc->paragraphs[0].number_of_lines != MAX_PARAGRAPH_LINES)
            {
                return FAILURE;
            }
            */
           /* adds line */
            add_line_after(doc, 1, 0, data[i]);
        }
    }

    return SUCCESS;
}

/*auxilaury function for repalace text*/
void aux_function(const char *line, const char *target,
                  const char *replacement, char *final)
{
    int i, text_tracker = 0;
    /* len_target and len_replacement finds size of strings respectfully */
    int len_target = strlen(target);
    int len_replacement = strlen(replacement);

    /* loops through until end of array */
    for (i = 0; line[i] != '\0'; i++)
    {
        /* checks if target exists in line[i] */
        if (strstr(&line[i], target) == &line[i])
        {
            /* tracker goes up by 1 */
            text_tracker++;
            /* index goes to next */
            i += len_target - 1;
        }
    }
    i = 0;  
    while (*line)
    {
        if (strstr(line, target) == line)
        {
            strcpy(&final[i], replacement);
            i += len_replacement;
            line += len_target;
        }
        else
        {
            final[i++] = *line++;
        }
    }
    final[i] = '\0';
}

/* 10 */
int replace_text(Document *doc, const char *target, const char *replacement)
{
    int i, j;
    char new_text[MAX_STR_SIZE + 1];

    if (doc == NULL || target == NULL || replacement == NULL)
    {
        return FAILURE;
    }
    for (i = 0; i < doc->number_of_paragraphs; i++)
    {
        for (j = 0; j < doc->paragraphs[i].number_of_lines; j++)
        {
            aux_function(doc->paragraphs[i].lines[j], target, replacement,
                         new_text);
            strcpy(doc->paragraphs[i].lines[j], new_text);
        }
    }
    return SUCCESS;
}

/* highlights a specific string */
int highlight_text(Document *doc, const char *target)
{   
    /* creates array highlight */
    char highlight[MAX_PARAGRAPH_LINES + 1] = "";
    if (doc == NULL || target == NULL)
    {
        return FAILURE;
    }
    
    strcat(highlight, HIGHLIGHT_START_STR);
    strcat(highlight, target);
    strcat(highlight, HIGHLIGHT_END_STR);
    replace_text(doc, target, highlight);
    return SUCCESS;
}

/* removes text */
int remove_text(Document *doc, const char *target)
{
    /* char array remoce */
    char remove[MAX_PARAGRAPH_LINES + 1] = "";
    /* if doc and target are null */
    if (doc == NULL || target == NULL)
    {
        return FAILURE;
    }
    /* replace text is called */ 
    replace_text(doc, target, remove);
    return SUCCESS;
}
/*
This function is similar to load document, except that data is loaded from a file instead of from an array
in memory. A new paragraph is started at the beginning of the document. An empty line indicates the
beginning of a new paragraph. The function returns FAILURE if doc is NULL, filename is NULL, or
opening the file fails. Otherwise the function returns SUCCESS. No error message is generated if the file
cannot be opened.
*/
int load_file(Document *doc, const char *filename){
    int i = 0;
    FILE *file;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    /* if paramater doc, data, or data_lines is null */
    if (doc == NULL)
    {
        return FAILURE;
    }

    if ((file = fopen(filename,"r")) == NULL){
       return FAILURE;
       }

    /* calls add_paragraph_after function */
   add_paragraph_after(doc, 0);

   while ((read = getline(&line, &len, file)) != -1) {
       /* finds empty string */
        if (strcmp(line, "") == 0)
        {
            /* adds paragraph */
            add_paragraph_after(doc, 0);
        }
        else
        {
           /* adds line */
            add_line_after(doc, 1, 0, line);
        }
    }
    fclose(file);
    if (line){
        free(line);
    }

    return SUCCESS;
}
/*This function prints the document (same format as in project 2) to the specified file (overwriting the
file). The function returns FAILURE if doc is NULL, filename is NULL, or the file cannot be opened.
Otherwise the function returns SUCCESS. No error message is generated if the file cannot be opened.*/
int save_document(Document *doc, const char *filename){
    int i, j;
    FILE *file;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    /* if paramater *doc is null */
    if (doc == NULL)
    {
        return FAILURE;
    }
    if ((file = fopen(filename,"r")) == NULL){
       return FAILURE;
    }

    /* prints document name and number of paragraphs */
    printf("Document name: %c%s%c\nNumber of Paragraphs: %d\n", '"', doc->name,
           '"', doc->number_of_paragraphs);
    /* loops through the paragraphs */
    for (i = 0; i < doc->number_of_paragraphs; i++)
    {
        /* loops through the lines of each paragraph */
        for (j = 0; j < doc->paragraphs[i].number_of_lines; j++)
        {
            /* prints the text at every line of every paragraph in the doc */
            fputs(doc->paragraphs[i].lines[j], file);
        }
        /* checks if the document has at least 2 paragraphs and if it is the
           last paragraph it doesnt print*/
        if (doc->number_of_paragraphs > 1 && 
           (doc->number_of_paragraphs - 1 != i))
        {
            fputs("\n", file);
        }
    }
    fclose(file);
    
    return SUCCESS;
}



