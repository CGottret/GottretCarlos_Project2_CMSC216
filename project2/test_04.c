#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {
    Document doc;
    const char *doc_name = "Okay";
    if (init_document(&doc, doc_name) == FAILURE) {
        printf("Initialization failed\n");
    }
    else {
        printf("Num of Paragraphs: %d\n", doc.number_of_paragraphs);
        printf("Document Name: %s\n", doc.name);
    }
    doc.number_of_paragraphs = 10;
    printf("Num of Paragraphs: %d\n", doc.number_of_paragraphs);
    reset_document(&doc);
    printf("Num of Paragraphs now: %d\n", doc.number_of_paragraphs);
    return 0;
}

