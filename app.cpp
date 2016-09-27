#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

xmlDocPtr getdoc (char *docname)
{
    xmlDocPtr doc;


    doc = xmlParseFile(docname);

    if (doc == NULL )
    {
        fprintf(stderr, "Document not parsed successfully.\n");
        return NULL;
    }

    return doc;
}

int main(){
    printf("Start:--------------------\n");
    xmlDocPtr doc = NULL;
    char *docname = "simple.xml";
    doc = getdoc(docname);
    xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    printf("End:--------------------\n");
    return(0);
}
