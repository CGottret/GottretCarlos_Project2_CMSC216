#include <stdio.h>
#include <string.h>
#include "document.h"

int main()
{
    Document doc;
    const char *doc_name = "Loading Document ";
    int data_lines = 8;
    char data[20][MAX_STR_SIZE + 1] = {
        "This is a test written by me.",
        "please don't be hard on me.",
        "The word please is a word that is very useful.",
        "",
        "Use please anything you can.",
        "The rate at which im learning please.",
        "",
        "please please please please please please."};

    init_document(&doc, doc_name);
    load_document(&doc, data, data_lines);

    highlight_text(&doc, "please");

    print_document(&doc);

    return 0;
}
