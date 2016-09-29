#ifndef PYLBMACLMANAGER_H
#define PYLBMACLMANAGER_H

#include <libxml/parser.h>
#include <libxml/tree.h>
typedef enum{
    UNKONWN_ACTION = 0,
    ALLOW = 1,
    DENY = 2
} Pylbm_Action;

typedef enum{
    UNKONWN_TYPE = 0,
    SOURCE = 1,
    RECEIVER = 2
} Pylbm_Type;

struct _Pylbm_AclNode{
    char* prodId;
    char* pattern;
    Pylbm_Type type;
    Pylbm_Action action;
    struct _Pylbm_AclNode* next;
};

typedef struct _Pylbm_AclNode Pylbm_AclNode;

Pylbm_AclNode* pylbmParseXmlFile(char* xmlFile);
Pylbm_AclNode* pylbmParseXmlNode(xmlNode* node, const char* name, Pylbm_AclNode* head, Pylbm_AclNode* tail);
Pylbm_AclNode* generateAclNodeFromXmlNode(xmlNode* node);
void pylbmCleanPylbm_AlcNodes(Pylbm_AclNode* node);
void pylbmCleanPylbm_AlcNode(Pylbm_AclNode* node);
int pylbmVerifyAclNode(const Pylbm_AclNode* node);

void printAclNodes(Pylbm_AclNode* node);
void printAclNode(const Pylbm_AclNode* node);
void printXmlNode(const xmlNode* node);
void pause();


#endif // PYLBMACLMANAGER_H
