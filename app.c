#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "pylbmaclmanager.h"
//http://www.lemoda.net/c/unix-regex/


int main(){
    Pylbm_AclNode* head = pylbmParseXmlFile("test.xml");

    printf("-----------all acl nodes------------\n\n\n");
    printAclNodes(head);
    pylbmCleanPylbm_AlcNodes(head);
    printf("End:--------------------\n");
    return(0);
}
