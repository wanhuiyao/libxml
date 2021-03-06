#include <stdio.h>
#include <string.h>
#include "pylbmaclmanager.h"

Pylbm_AclNode* pylbmParseXmlFile(char* xmlFile){
#ifdef LIBXML_TREE_ENABLED
    xmlDoc* doc = xmlReadFile(xmlFile, NULL, 0);
    Pylbm_AclNode* head = NULL;
    if(doc){
        xmlNode* root = xmlDocGetRootElement(doc);
        if(root){
            xmlNode* firstUmpAclNode = pylbmFindXmlNode(root, "UMPACL");
            if(firstUmpAclNode){
                head = pylbmParseXmlNode(firstUmpAclNode);
            }
        }
        xmlFreeDoc(doc);
        xmlCleanupParser();
    }
    return head;
#else
    printf("Collection support not compiled in.\n");
    return NULL;
#endif
}

xmlNode* pylbmFindXmlNode(xmlNode* node, const char* name){
    if(node){
        xmlNode* currentXmlNode = NULL;
        for(currentXmlNode = node; currentXmlNode; currentXmlNode = currentXmlNode->next){
            if(currentXmlNode->type == XML_ELEMENT_NODE
                    && strcmp((const char*)currentXmlNode->name, name) == 0){
                return currentXmlNode;
            }

            xmlNode *t = pylbmFindXmlNode(currentXmlNode->children, name);
            if(t){
                return t;
            }
        }
    }
    return NULL;
}

Pylbm_AclNode* pylbmParseXmlNode(xmlNode* node){
    Pylbm_AclNode* cursor = NULL;
    Pylbm_AclNode* head = NULL;
    xmlNode* currentXmlNode = node;
    for(; currentXmlNode; currentXmlNode= currentXmlNode->next){
        if(currentXmlNode->type == XML_ELEMENT_NODE
                && strcmp((const char*)(currentXmlNode->name), "UMPACL") == 0){
            printXmlNode(currentXmlNode);
            Pylbm_AclNode* t = generateAclNodeFromXmlNode(currentXmlNode);
            if(t){
                if(head == NULL){
                    head = t;
                    cursor = t;
                }

                cursor->next = t;
                cursor = cursor->next;
            }
        }
    }
    return head;
}

Pylbm_AclNode* generateAclNodeFromXmlNode(xmlNode* node){
    if(node){
        Pylbm_AclNode* newAclNode = (Pylbm_AclNode*)malloc(sizeof(Pylbm_AclNode));
        newAclNode->prodId = NULL;
        newAclNode->pattern = NULL;
        xmlAttr* cur_attr = node->properties;
        for(; cur_attr; cur_attr = cur_attr->next){
            if(cur_attr->children){
                if(strcmp((const char*)cur_attr->name, "prodid") == 0){
                    int len = strlen((const char*)cur_attr->children->content);
                    if(len > 0){
                        newAclNode->prodId = (char*)malloc(len);
                        strcpy(newAclNode->prodId, (const char*)cur_attr->children->content);
                    }
                }else if(strcmp((const char*)cur_attr->name, "pattern") == 0){
                    int len = strlen((const char*)cur_attr->children->content);
                    if(len > 0){
                        newAclNode->pattern = (char*)malloc(len);
                        strcpy(newAclNode->pattern, (const char*)cur_attr->children->content);
                    }
                }else if(strcmp((const char*)cur_attr->name, "type") == 0){
                    if(strcmp((const char*)cur_attr->children->content, "src") == 0){
                        newAclNode->type = SOURCE;
                    }else if(strcmp((const char*)cur_attr->children->content, "rcv") == 0){
                        newAclNode->type = RECEIVER;
                    }
                }else if(strcmp((const char*)cur_attr->name, "action") == 0){
                    if(strcmp((const char*)cur_attr->children->content, "allow") == 0){
                        newAclNode->action = ALLOW;
                    }else if(strcmp((const char*)cur_attr->children->content, "deny") == 0){
                        newAclNode->action = DENY;
                    }
                }
            }
        }
        if(!pylbmVerifyAclNode(newAclNode)){
            pylbmCleanPylbm_AlcNode(newAclNode);
            newAclNode = NULL;
        }
        return newAclNode;
    }else{
        return NULL;
    }
}

void pylbmCleanPylbm_AlcNodes(Pylbm_AclNode* node){
    while(node){
        pylbmCleanPylbm_AlcNode(node);
        node = node->next;
    }
}

void pylbmCleanPylbm_AlcNode(Pylbm_AclNode* node){
    if(node){
        if(node->prodId){
            free(node->prodId);
        }
        if(node->pattern){
            free(node->pattern);
        }
        free(node);
    }
}

int pylbmVerifyAclNode(const Pylbm_AclNode* node){
    if(node == NULL){
        printf("This node is NULL\n");
        return 0;
    }

    if(node->prodId){
        if(strlen(node->prodId) < 1){
            printf("This prodId length less than 1\n");
            return 0;
        }
    }else{
        printf("This prodId is NULL\n");
        return 0;
    }

    if(node->pattern){
        if(strlen(node->pattern) < 1){
            printf("This pattern length less than 1\n");
            return 0;
        }
    }else{
        printf("This pattern is NULL\n");
        return 0;
    }

    if(node->type == UNKONWN_TYPE){
        printf("The type is UNKNOWN\n");
        return 0;
    }

    if(node->action == UNKONWN_ACTION){
        printf("The action is UNKNOWN\n");
        return 0;
    }
    return 1;
}

void printAclNodes(Pylbm_AclNode* node){
    while(node){
        printAclNode(node);
        node = node->next;
    }
}

void printAclNode(const Pylbm_AclNode* node){
    printf("%s, %s, %s, %s\n", node->prodId, node->pattern,
           (node->type == SOURCE) ? "src" : (node->type == RECEIVER) ? "rcv" : "unknown",
           (node->action == ALLOW) ? "allow" : (node->action == DENY) ? "deny" : "unknown");
}

void printXmlNode(const xmlNode* node){
    printf("xml node: %s ", node->name);
    xmlAttr* cur_attr = NULL;
    for(cur_attr = node->properties; cur_attr; cur_attr = cur_attr->next){
        printf(" %s=\"%s\"", cur_attr->name, cur_attr->children->content);
    }
    printf("\n");
}

void pause(){
    int a;
    scanf("%d", &a);
}
