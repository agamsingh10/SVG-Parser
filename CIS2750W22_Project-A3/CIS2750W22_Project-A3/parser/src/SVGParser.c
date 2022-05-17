/***********************************Name: Agam Singh Kapoor**************** Student Id: 1121452********A3*/



#include "SVGParser.h"
#include "LinkedListAPI.h"
#include<math.h>

char *allAttr (List *shapes, elementType type) ;
char * getTitle(char * file);
char * getDesc(char * file);
void scaleShapes (char *filename, float rscale, float cScale);
int validate(xmlDoc *doc, const char *XSDFileName );
int validCheck(const SVG * img);
xmlDoc * convert(xmlDoc * xmlDoc,const SVG * img);

void  groupConvert(xmlNode * node,List * g);

void  attributeConvert(xmlNode * node,List * otherAtr);

Group* groupRec(xmlNode * temp);
void delete_null(void * data);
void getGroupHelp( Group * sed, List*groupList );


 char* attributeToString(void* data){
    char* tmpStr;
    Attribute* attr;
    int len;
    
    if (data == NULL){
        return NULL;
    }
    
    attr = (Attribute*)data;

    len = strlen(attr->name)+strlen(attr->value)+5;
    tmpStr = (char*)malloc(sizeof(char)*len);
    
    sprintf(tmpStr, "%s : %s\n",attr->name,attr->value);
    
    return tmpStr;
 }



char* rectangleToString(void* data){
        
    char* tmpStr;
    Rectangle* rect;
    int len;
    
    if (data == NULL){
        return NULL;
    }
    
    rect = (Rectangle*)data;
    
    char * str =toString(rect->otherAttributes);          //returns a string of rectangle list attributes
    len = strlen(str)+ 121+ strlen(rect->units);
    tmpStr = (char*)malloc(sizeof(char)*len);
    
    sprintf(tmpStr, "x: %.2f\ny: %.2f\nwidth: %.2f\nheight: %.2f\nUnits: %s\nAttributes: %s\n",rect->x,rect->y, rect->width, rect->height,rect->units,str);
    free(str);
    
    return tmpStr;

}

char* circleToString(void* data){
 

 char* tmpStr;
    Circle* circ;
    int len;
    
    if (data == NULL){
        return NULL;
    }
    
    circ = (Circle*)data;
    
    char * str =toString(circ->otherAttributes);   //returns a string of attributes of circle
    len = strlen(str)+ 94+ strlen(circ->units);
    tmpStr = (char*)malloc(sizeof(char)*len);
    
    sprintf(tmpStr, "cx: %.2f\ncy: %.2f\nradius: %.2f\nUnits: %s\nAttributes: %s\n",circ->cx,circ->cy, circ->r,circ->units, str);
    free(str);
    
    return tmpStr;


}

char* groupToString(void* data){
 

 char* tmpStr;
    Group* grp;
    int len;
    
    if (data == NULL){
        return NULL;
    }
    
    grp = (Group*)data;
    

    //Returm string of all lists like otherAttributes, rectangles.....
    char * str =toString(grp->otherAttributes);
    char* str2=toString(grp->rectangles);
    char* str3 =toString(grp->circles);
    char *str4 = toString(grp->paths);
    char*str5 = toString(grp->groups);
    len = strlen(str)+ strlen(str2)+strlen(str3)+strlen(str4)+ strlen(str5)+strlen("Attributes: \nRectangle: \nCircle: \nPath: \nGroup: \n") +1;
    tmpStr = (char*)malloc(sizeof(char)*len);
    
    sprintf(tmpStr,"Attributes: \n%sRectangle: \n%sCircle: \n%sPath: \n%sGroup: \n%s",str, str2,str3, str4,str5);
    free(str);
    free(str2);
    free(str3);
    free(str4);
    free(str5);
    
    return tmpStr;


}

char* pathToString(void* data){


char* tmpStr;
    Path* path;
    int len;
    
    if (data == NULL){
        return NULL;
    }
    
    path = (Path*)data;
    
    char * str =toString(path->otherAttributes);      //all attributes of path
    len = strlen(str)+ strlen(path->data)+strlen("d: \nAttributes: \n")+1;
    tmpStr = (char*)malloc(sizeof(char)*len);
    
    sprintf(tmpStr, "d: %s\nAttributes: %s\n",path->data, str);
    free(str);
    
    return tmpStr;

}

//-------------------------------------------------------------------------------------
 

 char* SVGToString(const SVG* img){
    
    //Returns string to get a string containing all attributes, rectangles list and other lists
    char* str2=toString(img->rectangles); 
    char* str3 =toString(img->circles);
    char *str4 = toString(img->paths);
    char *str5 = toString(img->groups);
    char* str1=toString(img->otherAttributes); 
    int len= strlen(str1)+strlen(str2)+strlen(str3)+strlen(str4)+strlen(str5)+strlen(img->description)+strlen(img->title)+strlen(img->namespace)+strlen("Namespace: \nTitle: \nDescription: \nAttributes: \nRectangle: \nCircle: \nPath: \nGroup: \n") +1;
    char *stringg= (char*)malloc(sizeof(char)*len);
    
    
    sprintf(stringg,"Namespace: %s\nTitle: %s\nDescription: %s\nAttributes: \n%sRectangle: \n%sCircle: \n%sPath: \n%sGroup: \n%s",img->namespace,img->title,img->description,str1,str2,str3, str4, str5);

    free(str1);
    free(str2);
    free(str3);
    free(str4);
    free(str5);
    return stringg;
 }

void deleteRectangle(void* data){
      

      Rectangle* tmpName;
    
    if (data == NULL){                       //checks if data is NULL
        return;
    }
    
    tmpName = (Rectangle*)data;
    
    //freeing path and its attributes
    freeList(tmpName->otherAttributes);
    free(tmpName);
}

void deleteAttribute(void *data){
    
    Attribute* tmpName;
    
    if (data == NULL){                     //checks if data is NULL
        return;
    }
    
    tmpName = (Attribute*)data;
    
    //freeing all attributes
    free(tmpName->name);
    free(tmpName);
    
}

void deletePath(void* data){

   Path* tmpName;
    
    if (data == NULL){                           //checks if data is NULL
        return;
    }
    
    tmpName = (Path*)data;
    
    //freeing path and its attributes
    freeList(tmpName->otherAttributes);
    free(tmpName);

}

void deleteCircle(void* data){

    Circle* tmpName;
    
    if (data == NULL){                               //checks if data is NULL
        return;
    }
    
    tmpName = (Circle*)data;
    
     //freeing circle and its attributes
    freeList(tmpName->otherAttributes);
    free(tmpName);
}

void deleteGroup(void* data){

    Group* tmpName;
    
    if (data == NULL){                     //checks if data is NULL
        return;
    }
    
    tmpName = (Group*)data;          //struct group
    
    //freeing all the lists of group
    freeList(tmpName->otherAttributes);
    freeList(tmpName->circles);
    freeList(tmpName->rectangles);
    freeList(tmpName->paths);
    freeList(tmpName->groups);
    free(tmpName);
}

//Empty delete function
void delete_null(void * data){

}

//All the compare functions

int compareFunc(const void *first, const void *second){
    

    
    return 0;
}
int compareAttributes(const void *first, const void *second){

    
    return 0;
}


int compareRectangles(const void *first, const void *second){

    
    return 0;

}

int compareCircles(const void *first, const void *second){

    
    return 0;
}

int comparePaths(const void *first, const void *second){
   
    return 0;

}

int compareGroups(const void *first, const void *second){
  
    return 0;

}

void addComponent(SVG* img, elementType type, void* newElement){

   if(type==RECT){
       Rectangle * rect = (Rectangle*) newElement;
       insertBack(img->rectangles, rect);   

   }

   else if(type==CIRC){
       Circle * circ = (Circle*) newElement;
       insertBack(img->circles, circ);      

   }

   else if(type==PATH){
       Path *path = (Path*) newElement;
       insertBack(img->paths, path);   
   }



}





Group* groupRec(xmlNode * temp){
        Group* grp=  (Group*)malloc(sizeof(Group) );      //malloc a struct of type Group

        //initialize all the lists inside the group
        grp-> rectangles = initializeList(rectangleToString, deleteRectangle, compareRectangles);

        grp-> circles = initializeList(circleToString, deleteCircle, compareCircles);

        grp-> paths = initializeList(pathToString, deletePath, comparePaths);
        grp-> groups = initializeList(groupToString, deleteGroup, compareGroups);
        grp->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);
                
        xmlAttr *attr2  ;
            
        //loop that moves inside the element to read the attributes/properties
        for (attr2 = temp->properties; attr2 != NULL; attr2 = attr2->next)
        {  
            
            xmlNode *value2 = attr2->children;                      //move inside the element
            char *attrName2 = (char *)attr2->name; 
            char *cont2 = (char*) value2->content;                 
            Attribute * att2= (Attribute*) malloc(sizeof(Attribute)+strlen(cont2)+1);
           
            att2->name = malloc(sizeof(char)*strlen(attrName2)+1);
            strcpy(att2->name, attrName2);                          //store the name of attribute   
            strcpy(att2->value , cont2);                             //store the value of attribute

            insertBack(grp->otherAttributes,att2);                //insert the attributes inside the list from back
    
        }
         


               
               
        xmlNode * temp2 = temp->children ;                     //move further inside towards children

        for ( ; temp2!=NULL; temp2= temp2->next){

                if (strcmp((const char*)temp2->name, "rect")==0) {              //check if child is rectangle
            
                    xmlAttr *attr2  ;
            
                    Rectangle * rect = (Rectangle*)malloc(sizeof(Rectangle));         //malloc struct rectangle
                    rect->otherAttributes= initializeList(attributeToString, deleteAttribute, compareAttributes);     //intialize the list
        
                    for (attr2 = temp2->properties; attr2 != NULL; attr2 = attr2->next)
                    {  
            
                          xmlNode *value2 = attr2->children;
                          char *attrName2 = (char *)attr2->name;
                          char *cont2 = (char *)(value2->content);
             
                          if(strcmp(attrName2, "x")==0){                       //if attribute name is x
           
                               rect->x = strtof(cont2, &cont2);                //to put numeric part in x and units in the units
                               strcpy(rect->units, cont2);
             
                           }
                           else if((strcmp(attrName2, "y")==0)){               //if attribute name is y
                
                                rect->y = atof(cont2);                           //convert string to float
                
            
                            }

                            else if((strcmp(attrName2, "width")==0)){             //if attribute name is width
                                 rect->width =atof(cont2);                         //convert string to float
              
                            }
                            
                            else if((strcmp(attrName2, "height")==0)){            //if attribute name is height
                                 rect->height = atof(cont2);                      //convert string to float
               
                            }
                            else{
                   
                                  xmlNode *value3 = attr2->children;
                                  char *attrName3 = (char *)attr2->name;
                                  char *cont3 = (char *)(value3->content);
                                  Attribute *atribute= (Attribute*)malloc (sizeof(Attribute)+strlen(cont3)+1);
                                  atribute->name = malloc (sizeof(char)*strlen(attrName3)+1);
                                  strcpy(atribute->name, attrName3);
                                  strcpy(atribute->value, cont3);
           
                                  insertBack(rect->otherAttributes,atribute);
         
           
                                } 
                        }
                        insertBack(grp->rectangles,rect);                       //insert rect structure in the rectangles list
                }

                else if (strcmp((const char*)temp2->name, "circle")==0) {       //if child is circle
             
                      xmlAttr *attr2  ;
            
                      Circle *circ = (Circle*)malloc(sizeof(Circle));
                      circ->otherAttributes= initializeList(attributeToString, deleteAttribute, compareAttributes);  //initialize list
        
                      for (attr2 = temp2->properties; attr2 != NULL; attr2 = attr2->next)
                       {  
            
                           xmlNode *value2 = attr2->children;
                           char *attrName2 = (char *)attr2->name;
                           char *cont2 = (char *)(value2->content);
 
           
                            if(strcmp(attrName2, "cx")==0){                   //if attribute name is cx
            
                               circ->cx = strtof(cont2, &cont2);
                               strcpy(circ->units,cont2);
             
                             }
                             else if((strcmp(attrName2, "cy")==0)){           //if attribute name is cy
                
                                circ->cy = atof(cont2);
              
                             }

                             else if((strcmp(attrName2, "r")==0)){             //if attribute name is r
              
                                circ->r = atof(cont2);
              
                             }
           
                             else{
              
                   
                                 xmlNode *value3 = attr2->children;
                                 char *attrName3 = (char *)attr2->name;
                                 char *cont3 = (char *)(value3->content);
                                 Attribute *atribute= (Attribute*)malloc (sizeof(Attribute)+strlen(cont3)+1);
                                 atribute->name = malloc (sizeof(char)*strlen(attrName3)+1);
                                 strcpy(atribute->name, attrName3);
                                 strcpy(atribute->value, cont3);
            
                                 insertBack(circ->otherAttributes,atribute);
           
                            }
           
                       }
                       insertBack(grp->circles, circ);             //insert circ structure  in circles list
         
                   }
 

                    else if(strcmp((const char*)temp2->name, "path")==0){        //if child is path
            
                           xmlAttr *attr2  ;
            
                           Path * path = NULL;
                            //allocating memory for pth strutcure
                              //initialize list
        
                           for (attr2 = temp2->properties; attr2 != NULL; attr2 = attr2->next)
                           {  
                                xmlNode *value2 = attr2->children;
                                char *attrName2 = (char *)attr2->name;
                                char *cont2 = (char *)(value2->content);
        
                                

                                 if(strcmp(attrName2, "d")==0){ 
                                     path =(Path*)malloc(sizeof(Path)+strlen(cont2)+ 1);  
                                     path->otherAttributes=initializeList(attributeToString, deleteAttribute, compareAttributes);    //if attribute is d
                                     strcpy(path->data,"");
                                     strcpy(path->data, cont2); 
                                 }

                           }
                           for (attr2 = temp2->properties; attr2 != NULL; attr2 = attr2->next)
                           {  
                                xmlNode *value2 = attr2->children;
                                char *attrName2 = (char *)attr2->name;
                                char *cont2 = (char *)(value2->content);               
                                if(strcmp(attrName2,"d")!=0){
                                 Attribute *atribute= (Attribute*)malloc (sizeof(Attribute)+strlen(cont2)+1);
                                 atribute->name = malloc (sizeof(char)*strlen(attrName2)+1);
                                 strcpy(atribute->name, attrName2);
                                 strcpy(atribute->value, cont2);
       
                                 insertBack(path->otherAttributes,atribute);

                                }
                            }
                            

                             insertBack(grp->paths, path);         //insert path structure in paths list
                       }

                       else if(strcmp((const char*)temp2->name, "g")==0){        //if child is group
          
                       Group *grop= groupRec(temp2);               //call the recursive function
                       insertBack(grp->groups, grop);             //insert group in groups list
          
                       }
               }
               
               return grp;
        }  

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////AAAAAAAAAAAAA22222222222222222///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

bool setAttribute(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute){
     if(img==NULL ||  newAttribute ==NULL ){
        return false;
    }
    if(elemType!=SVG_IMG && elemIndex<0){
        
        return false;
    }

    
    if(elemType == SVG_IMG){
            
            //if(img->otherAttributes != NULL && getLength(img->otherAttributes) > 0){
				ListIterator iter = createIterator(img->otherAttributes);
				void* elem1;
   
                  while ((elem1 = nextElement(&iter)) != NULL){
					Attribute* other = (Attribute*) elem1;
					if(strcmp(other->name, newAttribute->name)==0){
                        strcpy(other->value, newAttribute->value);
                        free(newAttribute->name);
                        free(newAttribute);
                        return true;
                    }
					
				}
                 insertBack(img->otherAttributes,newAttribute);
            return true;
			}
            
      
           
        
          // }
   

    else if(elemType == RECT){

int index=0;
         //  if(img->rectangles && getLength(img->rectangles) >0 ){
		ListIterator itr = createIterator(img->rectangles);

		 void* elem;
         
   
        while ((elem = nextElement(&itr)) != NULL ){
            if(index==elemIndex){
               Rectangle* rect = (Rectangle*) elem;
               
           

           if(strcmp(newAttribute->name, "x")==0){            //if attribute name is x
           
               rect->x = atof(newAttribute->value);
               free(newAttribute->name);
                        free(newAttribute);  
               return true;   
               
             
           }

           
           else if(strcmp(newAttribute->name, "y")==0){            //if attribute name is x
           
               rect->y = atof(newAttribute->value); 
               free(newAttribute->name);
                        free(newAttribute);
               return true;    
               
             
           }
           

           else if((strcmp(newAttribute->name, "width")==0)){   //if attribute name is width
                rect->width =atof(newAttribute->value);
                free(newAttribute->name);
                        free(newAttribute);
                return true;
               
           }
           else if((strcmp(newAttribute->name, "height")==0)){   //if attribute name is height
                rect->height =atof(newAttribute->value);
                free(newAttribute->name);
                        free(newAttribute);
                return true;
                
           }
           else{
                   
           
            
				ListIterator iter = createIterator(rect->otherAttributes);
				void* elem1;
   
                  while ((elem1 = nextElement(&iter)) != NULL){
					Attribute* other = (Attribute*) elem1;
					if(strcmp(other->name, newAttribute->name)==0){
                        strcpy(other->value, newAttribute->value);
                        free(newAttribute->name);
                        free(newAttribute);
                        return true;
                    }
					
				}
                 insertBack(rect->otherAttributes,newAttribute);
            return true;
			
      
           }
        
          }

           index++;
  
        }

    }

//}
else if(elemType == CIRC){

int index=0;
          // if(img->circles && getLength(img->circles) >0 ){
		ListIterator itr = createIterator(img->circles);

		 void* elem;
         
   
        while ((elem = nextElement(&itr)) != NULL ){
            if(index==elemIndex){
               Circle* circ = (Circle*) elem;
               
           

           if(strcmp(newAttribute->name, "cx")==0){            //if attribute name is x
           
               circ->cx = atof(newAttribute->value);
               free(newAttribute->name);
                        free(newAttribute);  
               return true;   
               
             
           }

           
           else if(strcmp(newAttribute->name, "cy")==0){            //if attribute name is x
           
               circ->cy = atof(newAttribute->value); 
               free(newAttribute->name);
                        free(newAttribute);
               return true;    
               
             
           }
           

           else if((strcmp(newAttribute->name, "r")==0)){   //if attribute name is width
                circ->r =atof(newAttribute->value);
                free(newAttribute->name);
                        free(newAttribute);
                return true;
               
           }
           
           else{
                   
           
				ListIterator iter = createIterator(circ->otherAttributes);
				void* elem1;
   
                  while ((elem1 = nextElement(&iter)) != NULL){
					Attribute* other = (Attribute*) elem1;
					if(strcmp(other->name, newAttribute->name)==0){
                        strcpy(other->value, newAttribute->value);
                        free(newAttribute->name);
                        free(newAttribute);
                        return true;
                    }
					
				}
			
      
            insertBack(circ->otherAttributes,newAttribute);
            return true;
        
           }
   
        

            
            }

           index++;
           


        }


    }

//}

else if(elemType == PATH){
int index=0;

          // if(img->paths && getLength(img->paths) >0 ){
		ListIterator itr = createIterator(img->paths);

		 void* elem;
         
   
        while ((elem = nextElement(&itr)) != NULL ){
            if(index==elemIndex){
               Path *path = (Path*) elem;
               
           

           if(strcmp(newAttribute->name, "d")==0){            //if attribute name is x
           
               strcpy(path->data,newAttribute->value);  
               free(newAttribute->name);
                        free(newAttribute);
               return true;   
               
             
           }
           
           else{
                   
           
            // Attribute *atribute= (Attribute*)malloc (sizeof(Attribute)+strlen(cont3)+1);
            
            // strcpy(atribute->name, newAttribute->name);
            // strcpy(atribute->value, newAttribute->value);
            if(path->otherAttributes != NULL && getLength(path->otherAttributes) > 0){
				ListIterator iter = createIterator(path->otherAttributes);
				void* elem1;
   
                  while ((elem1 = nextElement(&iter)) != NULL){
					Attribute* other = (Attribute*) elem1;
					if(strcmp(other->name, newAttribute->name)==0){
                        strcpy(other->value, newAttribute->value);
                        free(newAttribute->name);
                        free(newAttribute);
                        return true;
                    }
					
				}
                 insertBack(path->otherAttributes,newAttribute);
                  return true;
			}
           
        
           }
   
        

            
            }

           index++;
           


        }

    }

//}
else if(elemType == GROUP){

int index=0;
          // if(img->groups && getLength(img->groups) >0 ){
		ListIterator itr = createIterator(img->groups);

		 void* elem;
         
   
        while ((elem = nextElement(&itr)) != NULL ){
            if(index==elemIndex){
               Group *grp = (Group*) elem;
               
           
            // Attribute *atribute= (Attribute*)malloc (sizeof(Attribute)+strlen(cont3)+1);
            
            // strcpy(atribute->name, newAttribute->name);
            // strcpy(atribute->value, newAttribute->value);
            if(grp->otherAttributes != NULL && getLength(grp->otherAttributes) > 0){
				ListIterator iter = createIterator(grp->otherAttributes);
				void* elem1;
   
                  while ((elem1 = nextElement(&iter)) != NULL){
					Attribute* other = (Attribute*) elem1;
					if(strcmp(other->name, newAttribute->name)==0){
                        strcpy(other->value, newAttribute->value);
                        free(newAttribute->name);
                        free(newAttribute);
                        return true;
                    }
					
				}
                insertBack(grp->otherAttributes,newAttribute);
                  return true;
            }

           }
   
        
           index++;
            
            }

        }


free(newAttribute->name);
free(newAttribute);
return false;
}




bool writeSVG(const SVG* img, const char* fileName){
    if(img==NULL )if( fileName==NULL){
        return false;
    }
    if( fileName==NULL){
        return false;
    }
    
    xmlDoc* xmldoc =NULL;
    xmldoc = convert(xmldoc,img);
    if(xmldoc == NULL){
        return false;
    }
    
      int check= xmlSaveFormatFileEnc(fileName, xmldoc, "UTF-8", 1);
      
       /*free the document */
    xmlFreeDoc(xmldoc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
    if(check==-1){
          return false;
      }
   
       return true;
    
}



SVG *createValidSVG(const char* fileName, const char* schemaFile)
{
    
    if(fileName==NULL)
    {return NULL;} 
    if(schemaFile==NULL){return NULL;}
    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    xmlDoc *xmlDoc = NULL;
    xmlNode *a_node = NULL;
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    xmlDoc = xmlReadFile(fileName, NULL, 0);

    if (xmlDoc == NULL) {
       // xmlFreeDoc(doc);

    xmlCleanupParser();
        return NULL;
    }

    SVG * nameSVG= NULL;

    int checkVal = validate(xmlDoc, schemaFile);
    if(checkVal==0)
    {

        xmlFreeDoc(xmlDoc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
    return NULL;
    }
    /*Get the root element node */
    a_node = xmlDocGetRootElement(xmlDoc);
    if(a_node == NULL)
    {
        return NULL;
    }
    
       nameSVG= (SVG*)malloc(sizeof(SVG));
        //Initialize all lists of SVG
        nameSVG->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);
        xmlNode *cur_node = NULL;
        nameSVG-> rectangles = initializeList(rectangleToString, deleteRectangle, compareRectangles);

        nameSVG-> circles = initializeList(circleToString, deleteCircle, compareCircles);

        nameSVG-> paths = initializeList(pathToString, deletePath, comparePaths);
        nameSVG-> groups = initializeList(groupToString, deleteGroup, compareGroups);
       
        
    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
       // if (cur_node->type == XML_ELEMENT_NODE) {
                
                
        if(strcmp((const char*)cur_node->name,"svg")==0){                //checking the parent is it is SVG
        xmlAttr *attr  ;
        strcpy(nameSVG->title,"");                                      //initializing empty title
        strcpy(nameSVG->description,"");                                //initializing empty description
        
        for (attr = cur_node->properties; attr != NULL; attr = attr->next)    //moving towards attributes
        {  
            
            xmlNode *value = attr->children;
            char *attrName = (char *)attr->name;
            char *cont = (char *)(value->content);
            Attribute * att= (Attribute*) malloc(sizeof(Attribute)+strlen(cont)+1);
           
           att->name = malloc(sizeof(char)*strlen(attrName)+1);
           strcpy(att->name, attrName);
           strcpy(att->value , cont);

           insertBack(nameSVG->otherAttributes,att);
        
         
        }
        
        strcpy(nameSVG->namespace,(char*)cur_node->ns->href);           //for storing namespace in the SVG->namespace

          xmlNode * temp = cur_node->children;
            
           for (; temp!=NULL; temp= temp->next) {
               
        if (strcmp((const char*)temp->name, "title")==0) {           //if child is title
            xmlNode *child = temp->children;
            //char *content = (char*)(child->content);
            if(child->content!=NULL){
                strcpy(nameSVG->title,(const char *)child->content);      //storing title in struct    
            }
             
                //char title[256];
                 
               // strcpy(title, content);
                //strcpy(titleSVG->title, title);
               
        }

        else if (strcmp((const char*)temp->name, "desc")==0) {
            xmlNode *child = temp->children;
           
             if(child->content!=NULL){
                strcpy(nameSVG->description,(const char *)child->content);         //storing description in struct 
            }
        }
           

//-------------------------RECTANGLEEEEEEEEEEEEEEEEEEEEEEEE---------------------------------------------------------        

           
        else if (strcmp((const char*)temp->name, "rect")==0) {        //if child is rectangle
             
           // Rectangle * rect =(Rectangle*)malloc(sizeof(Rectangle));
            Rectangle * rect = (Rectangle*)malloc(sizeof(Rectangle) );
            rect->otherAttributes= initializeList(attributeToString, deleteAttribute, compareAttributes);   //initialize the list
            xmlAttr *attr2  ;
            
        
        for (attr2 = temp->properties; attr2 != NULL; attr2 = attr2->next)
        {  
            
            xmlNode *value2 = attr2->children;
            char *attrName2 = (char *)attr2->name;
            char *cont2 = (char *)(value2->content);

           if(strcmp(attrName2, "x")==0){            //if attribute name is x
           
               rect->x = strtof(cont2, &cont2);     
               strcpy(rect->units,cont2);
             
           }
           else if((strcmp(attrName2, "y")==0)){     //if attribute name is y
                rect->y= atof(cont2);                 //convert string to float
               
           }

           else if((strcmp(attrName2, "width")==0)){   //if attribute name is width
                rect->width =atof(cont2);
               
           }
           else if((strcmp(attrName2, "height")==0)){   //if attribute name is height
                rect->height =atof(cont2);
                
           }
           else{
                   
            xmlNode *value3 = attr2->children;
            char *attrName3 = (char *)attr2->name;
            char *cont3 = (char *)(value3->content);
            Attribute *atribute= (Attribute*)malloc (sizeof(Attribute)+strlen(cont3)+1);
            atribute->name = malloc (sizeof(char)*strlen(attrName3)+1);
            strcpy(atribute->name, attrName3);
            strcpy(atribute->value, cont3);
      
            insertBack(rect->otherAttributes,atribute);
        
           }
   
        }
         insertBack(nameSVG->rectangles, rect);

         
        }

/////////////////////////CIRCLEEEEEEEEEEEEEEEEEEEEEEEE/////////////////////////////////////
        else if (strcmp((const char*)temp->name, "circle")==0) {
             
           
            Circle * circ = (Circle*)malloc(sizeof(Circle) );      //malloc memory for Circle struct      

          circ->otherAttributes=initializeList(attributeToString, deleteAttribute, compareAttributes);     //  initialize list
            
            xmlAttr *attr2  ;

        for (attr2 = temp->properties; attr2 != NULL; attr2 = attr2->next)
        {  
            
            xmlNode *value2 = attr2->children;
            char *attrName2 = (char *)attr2->name;
            char *cont2 = (char *)(value2->content);
     
           if(strcmp(attrName2, "cx")==0){                  //if attribute name is cx
          
                circ->cx = strtof(cont2, &cont2);
                strcpy(circ->units, cont2);
            
           }
           else if((strcmp(attrName2, "cy")==0)){                 //if attribute name is cy
                circ->cy =atof(cont2);
               
           }

           else if((strcmp(attrName2, "r")==0)){              //if attribute name is r
                 circ->r =atof(cont2);
                
           }
           
           else{
              
                   
             xmlNode *value3 = attr2->children;
            char *attrName3 = (char *)attr2->name;
            char *cont3 = (char *)(value3->content);
            Attribute *atribute= (Attribute*)malloc (sizeof(Attribute)+strlen(cont3)+1);
            atribute->name = malloc (sizeof(char)*strlen(attrName3)+1);
            strcpy(atribute->name, attrName3);
            strcpy(atribute->value, cont3);
            insertBack(circ->otherAttributes,atribute);   
           }
        }
         insertBack(nameSVG->circles, circ);            //insert circle struct to circles list

        }

///////////////////////////////////////////////PATHHHHHHHHHHHHHHHHH/////////////////////////////////////////////////////////////////////
        
        else if(strcmp((const char*)temp->name, "path")==0){        //if child is path
            
                           xmlAttr *attr2  ;
            
                           Path * path = NULL;
                            //allocating memory for pth strutcure
                              //initialize list
        
                           for (attr2 = temp->properties; attr2 != NULL; attr2 = attr2->next)
                           {  
                                xmlNode *value2 = attr2->children;
                                char *attrName2 = (char *)attr2->name;
                                char *cont2 = (char *)(value2->content);
        
                                

                                 if(strcmp(attrName2, "d")==0){ 
                                     path =(Path*)malloc(sizeof(Path)+strlen(cont2)+ 1);  
                                     path->otherAttributes=initializeList(attributeToString, deleteAttribute, compareAttributes);    //if attribute is d
                                     strcpy(path->data,"");
                                     strcpy(path->data, cont2); 
                                 }

                           }
                           for (attr2 = temp->properties; attr2 != NULL; attr2 = attr2->next)
                           {  
                                xmlNode *value2 = attr2->children;
                                char *attrName2 = (char *)attr2->name;
                                char *cont2 = (char *)(value2->content);               
                                if(strcmp(attrName2,"d")!=0){
                                 Attribute *atribute= (Attribute*)malloc (sizeof(Attribute)+strlen(cont2)+1);
                                 atribute->name = malloc (sizeof(char)*strlen(attrName2)+1);
                                 strcpy(atribute->name, attrName2);
                                 strcpy(atribute->value, cont2);
       
                                 insertBack(path->otherAttributes,atribute);

                                }
                            }
                        
          insertBack(nameSVG->paths, path);            //insert path struct to paths list
        
        }
//--------------------------GROUUUUUUUUUUUPPP--------------------------------------------------------------------------------------
        else if(strcmp((const char *)temp->name, "g")==0){

            Group *grp= groupRec(temp); 
            insertBack(nameSVG->groups, grp);
          }
//--------------------------------------------------------------------------------        
        }        
        
    }
    
    
}
    

    
    
     /*free the document */
    xmlFreeDoc(xmlDoc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
    
   

    return nameSVG;
}



SVG *createSVG(const char* fileName)
{
    xmlDoc *doc = NULL;
    xmlNode *a_node = NULL;
    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    doc = xmlReadFile(fileName, NULL, 0);

    if (doc == NULL) {
        
        return NULL;
    }

    /*Get the root element node */
    a_node = xmlDocGetRootElement(doc);
    SVG * nameSVG= (SVG*)malloc(sizeof(SVG));
      
        //Initialize all lists of SVG
        nameSVG->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);
        xmlNode *cur_node = NULL;
        nameSVG-> rectangles = initializeList(rectangleToString, deleteRectangle, compareRectangles);

        nameSVG-> circles = initializeList(circleToString, deleteCircle, compareCircles);

        nameSVG-> paths = initializeList(pathToString, deletePath, comparePaths);
        nameSVG-> groups = initializeList(groupToString, deleteGroup, compareGroups);
       
        
    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
       // if (cur_node->type == XML_ELEMENT_NODE) {
                
                
        if(strcmp((const char*)cur_node->name,"svg")==0){                //checking the parent is it is SVG
        xmlAttr *attr  ;
        strcpy(nameSVG->title,"");                                      //initializing empty title
        strcpy(nameSVG->description,"");                                //initializing empty description
        
        for (attr = cur_node->properties; attr != NULL; attr = attr->next)    //moving towards attributes
        {  
            
            xmlNode *value = attr->children;
            char *attrName = (char *)attr->name;
            char *cont = (char *)(value->content);
            Attribute * att= (Attribute*) malloc(sizeof(Attribute)+strlen(cont)+1);
           
           att->name = malloc(sizeof(char)*strlen(attrName)+1);
           strcpy(att->name, attrName);
           strcpy(att->value , cont);

           insertBack(nameSVG->otherAttributes,att);
        
         
        }
        
        strcpy(nameSVG->namespace,(char*)cur_node->ns->href);           //for storing namespace in the SVG->namespace

          xmlNode * temp = cur_node->children;
            
           for (; temp!=NULL; temp= temp->next) {
               
        if (strcmp((const char*)temp->name, "title")==0) {           //if child is title
            xmlNode *child = temp->children;
            //char *content = (char*)(child->content);
            if(child->content!=NULL){
                strcpy(nameSVG->title,(const char *)child->content);      //storing title in struct    
            }
             
                //char title[256];
                 
               // strcpy(title, content);
                //strcpy(titleSVG->title, title);
               
        }

        else if (strcmp((const char*)temp->name, "desc")==0) {
            xmlNode *child = temp->children;
           
             if(child->content!=NULL){
                strcpy(nameSVG->description,(const char *)child->content);         //storing description in struct 
            }
        }
           

//-------------------------RECTANGLEEEEEEEEEEEEEEEEEEEEEEEE---------------------------------------------------------        

           
        else if (strcmp((const char*)temp->name, "rect")==0) {        //if child is rectangle
             
           // Rectangle * rect =(Rectangle*)malloc(sizeof(Rectangle));
            Rectangle * rect = (Rectangle*)malloc(sizeof(Rectangle) );
            rect->otherAttributes= initializeList(attributeToString, deleteAttribute, compareAttributes);   //initialize the list
            xmlAttr *attr2  ;
            
        
        for (attr2 = temp->properties; attr2 != NULL; attr2 = attr2->next)
        {  
            
            xmlNode *value2 = attr2->children;
            char *attrName2 = (char *)attr2->name;
            char *cont2 = (char *)(value2->content);

           if(strcmp(attrName2, "x")==0){            //if attribute name is x
           
               rect->x = strtof(cont2, &cont2);     
               strcpy(rect->units,cont2);
             
           }
           else if((strcmp(attrName2, "y")==0)){     //if attribute name is y
                rect->y= atof(cont2);                 //convert string to float
               
           }

           else if((strcmp(attrName2, "width")==0)){   //if attribute name is width
                rect->width =atof(cont2);
               
           }
           else if((strcmp(attrName2, "height")==0)){   //if attribute name is height
                rect->height =atof(cont2);
                
           }
           else{
                   
            xmlNode *value3 = attr2->children;
            char *attrName3 = (char *)attr2->name;
            char *cont3 = (char *)(value3->content);
            Attribute *atribute= (Attribute*)malloc (sizeof(Attribute)+strlen(cont3)+1);
            atribute->name = malloc (sizeof(char)*strlen(attrName3)+1);
            strcpy(atribute->name, attrName3);
            strcpy(atribute->value, cont3);
      
            insertBack(rect->otherAttributes,atribute);
        
           }
   
        }
         insertBack(nameSVG->rectangles, rect);

         
        }

/////////////////////////CIRCLEEEEEEEEEEEEEEEEEEEEEEEE/////////////////////////////////////
        else if (strcmp((const char*)temp->name, "circle")==0) {
             
           
            Circle * circ = (Circle*)malloc(sizeof(Circle) );      //malloc memory for Circle struct      

          circ->otherAttributes=initializeList(attributeToString, deleteAttribute, compareAttributes);     //  initialize list
            
            xmlAttr *attr2  ;

        for (attr2 = temp->properties; attr2 != NULL; attr2 = attr2->next)
        {  
            
            xmlNode *value2 = attr2->children;
            char *attrName2 = (char *)attr2->name;
            char *cont2 = (char *)(value2->content);
     
           if(strcmp(attrName2, "cx")==0){                  //if attribute name is cx
          
                circ->cx = strtof(cont2, &cont2);
                strcpy(circ->units, cont2);
            
           }
           else if((strcmp(attrName2, "cy")==0)){                 //if attribute name is cy
                circ->cy =atof(cont2);
               
           }

           else if((strcmp(attrName2, "r")==0)){              //if attribute name is r
                 circ->r =atof(cont2);
                
           }
           
           else{
              
                   
             xmlNode *value3 = attr2->children;
            char *attrName3 = (char *)attr2->name;
            char *cont3 = (char *)(value3->content);
            Attribute *atribute= (Attribute*)malloc (sizeof(Attribute)+strlen(cont3)+1);
            atribute->name = malloc (sizeof(char)*strlen(attrName3)+1);
            strcpy(atribute->name, attrName3);
            strcpy(atribute->value, cont3);
            insertBack(circ->otherAttributes,atribute);   
           }
        }
         insertBack(nameSVG->circles, circ);            //insert circle struct to circles list

        }

///////////////////////////////////////////////PATHHHHHHHHHHHHHHHHH/////////////////////////////////////////////////////////////////////
        
        
        else if(strcmp((const char*)temp->name, "path")==0){        //if child is path
            
                           xmlAttr *attr2  ;
            
                           Path * path = NULL;
                            //allocating memory for pth strutcure
                              //initialize list
        
                           for (attr2 = temp->properties; attr2 != NULL; attr2 = attr2->next)
                           {  
                                xmlNode *value2 = attr2->children;
                                char *attrName2 = (char *)attr2->name;
                                char *cont2 = (char *)(value2->content);
        
                                

                                 if(strcmp(attrName2, "d")==0){ 
                                     path =(Path*)malloc(sizeof(Path)+strlen(cont2)+ 1);  
                                     path->otherAttributes=initializeList(attributeToString, deleteAttribute, compareAttributes);    //if attribute is d
                                     strcpy(path->data,"");
                                     strcpy(path->data, cont2); 
                                 }

                           }
                           for (attr2 = temp->properties; attr2 != NULL; attr2 = attr2->next)
                           {  
                                xmlNode *value2 = attr2->children;
                                char *attrName2 = (char *)attr2->name;
                                char *cont2 = (char *)(value2->content);               
                                if(strcmp(attrName2,"d")!=0){
                                 Attribute *atribute= (Attribute*)malloc (sizeof(Attribute)+strlen(cont2)+1);
                                 atribute->name = malloc (sizeof(char)*strlen(attrName2)+1);
                                 strcpy(atribute->name, attrName2);
                                 strcpy(atribute->value, cont2);
       
                                 insertBack(path->otherAttributes,atribute);

                                }
                            }
                        
          insertBack(nameSVG->paths, path);            //insert path struct to paths list
        
        }
//--------------------------GROUUUUUUUUUUUPPP--------------------------------------------------------------------------------------
        else if(strcmp((const char *)temp->name, "g")==0){

            Group *grp= groupRec(temp); 
            insertBack(nameSVG->groups, grp);
          }
//--------------------------------------------------------------------------------        
        }        
        
    }
    
    
}

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    return nameSVG;
}







//This function deallocates the object, including all of its subcomponents
void deleteSVG(SVG* img){
      
      if (img == NULL){
        return;
    }

    clearList(img->rectangles);
    clearList(img->circles);
    clearList(img->paths);
   
    clearList(img->otherAttributes);
    clearList(img->groups);
    
    free(img->rectangles);
    free(img->circles);
    free(img->paths);
    free(img->otherAttributes);
    free(img->groups);
  
    free(img);
    
}

//recursion function for the getgroups function
void getGroupHelp( Group * sed, List*groupList ){
    insertBack(groupList, (void*)sed);
    
   ListIterator iter = createIterator(sed->groups);
   
   while ((sed = nextElement(&iter)) != NULL){
		

    getGroupHelp((Group *)sed, groupList);           //calling recursive function	
    
	} 

}

//returns a list of all groups in the SVG struct. if there are none, it returns an empty list 
List* getGroups(const SVG* img){
    if(img==NULL){
        return NULL;
    }

   List* groupList = initializeList(groupToString, delete_null, compareGroups);
   ListIterator iter = createIterator(img->groups);
   void* elem;
   
    while ((elem = nextElement(&iter)) != NULL){
		

     getGroupHelp((Group *)elem, groupList);	
   // 
    
	} 
    
    return groupList;

}

//returns a list of all rectangles in the SVG struct, if there are none, it returns an empty list

List* getRects(const SVG* img){
    if(img==NULL){
        return NULL;
    }

   List* rectList = initializeList(rectangleToString, delete_null, compareRectangles);
   ListIterator iter = createIterator(img->rectangles);                   //calling function to iterate the the list paths
   void* elem;
   
    while ((elem = nextElement(&iter)) != NULL){
		
		
		insertBack(rectList, elem);                                   //inserting if any rectangle found
	}
    List* get_group = getGroups(img); 
                                                                                   //calling getgroups function
    ListIterator iter2 = createIterator(get_group);                          //itering through the group list
     
    while ((elem = nextElement(&iter2))!= NULL){
		
    Group * grp = (Group*) elem;
    ListIterator iter3 = createIterator(grp->rectangles);
    while((elem = nextElement(&iter3))!= NULL){
		
		insertBack(rectList, (elem));
	}
    }
    freeList(get_group);
    return rectList;

}
//returns a list of all circles in the SVG struct,if there are none, it returns an empty list

List* getCircles(const SVG* img){
    if(img==NULL){
        return NULL;
    }

   List* circList = initializeList(circleToString, delete_null, compareCircles);    //initialize the list
   ListIterator iter = createIterator(img->circles);                   //calling function to iterate the the list paths
   void* elem;
   
    while ((elem = nextElement(&iter)) != NULL){
		
		                                                              //inserting if any circle found
		insertBack(circList, elem);
	}
    List* get_group = getGroups(img);                                //calling getgroups function

    ListIterator iter2 = createIterator(get_group);                      //itering through the group list
    
    while ((elem = nextElement(&iter2))!= NULL){
		
        Group * grp = (Group*) elem;
    ListIterator iter3 = createIterator(grp->circles);                         //iterating through circle list in group
    while((elem = nextElement(&iter3))!= NULL){
		
		insertBack(circList, (elem));
	}
    }
    freeList(get_group);
    return circList;

}

 //returns a list of all groups in the SVG struct if there are none, it returns an empty list
List* getPaths(const SVG* img){
    if(img==NULL){
        return NULL;
    }

   List* pathList = initializeList(pathToString, delete_null, comparePaths);    //initialize the list
   ListIterator iter = createIterator(img->paths);              //calling function to iterate the the list paths
   void* elem;
   
    while ((elem = nextElement(&iter)) != NULL){
		
		                                                   //inserting if any path found
		insertBack(pathList, elem);
	}
    List* get_group = getGroups(img);                       //calling getgroups function

    ListIterator iter2 = createIterator(get_group);           //itering through the group list
    
    while ((elem = nextElement(&iter2))!= NULL){             
		
        Group * grp = (Group*) elem; 
    ListIterator iter3 = createIterator(grp->paths);           //iterating through path list in group
    while((elem = nextElement(&iter3))!= NULL){
		
		insertBack(pathList, (elem));
	}
    }

    freeList(get_group);
    return pathList;

}




int numRectsWithArea(const SVG* img, float area){         
    if(img == NULL || area<0){                        //error check
        return 0;
    }



   List* rectList = getRects(img);              //to get the list of rectangles
   ListIterator iter = createIterator(rectList);
   void* elem;
   int count=0;
   
    while ((elem = nextElement(&iter)) != NULL){
		
		Rectangle * rect = (Rectangle*) elem;
        if(ceil(area) == ceil(rect->width*rect->height)){           //if area equal
            count++;
        }
		
	}
    freeList(rectList);
    return count;

}



int numCirclesWithArea(const SVG* img, float area){
    if(img == NULL || area<0){                    //error check
        return 0;
    }

   List* circList = getCircles(img);                //to get the list of circles
   ListIterator iter = createIterator(circList);
   void* elem;
   int count=0;
   
    while ((elem = nextElement(&iter)) != NULL){
		
		Circle*circ = (Circle*) elem;
        if(ceil(area) == ceil(3.1415926 * circ->r * circ->r)){                       //if area equal
            count++;
        }
		
	}
    freeList(circList);

    return count;

}


int numPathsWithdata(const SVG* img, const char* data){
    if(img == NULL || data==NULL){                      //error check
        return 0;
    }

   List* pathList = getPaths(img);                   //to get the list of paths
   ListIterator iter = createIterator(pathList);
   void* elem;
   int count=0;
   
    while ((elem = nextElement(&iter)) != NULL){
		
		Path *path = (Path*) elem;                                    //if data equal
        if(strcmp(path->data,data)==0){
            count++;
        }
		
	}
    freeList(pathList);

    return count;

}



int numGroupsWithLen(const SVG* img, int len){
    if(img == NULL || len<0){
        return 0;
    }

 List* groupList = getGroups(img);                         //call getgroups function
 //ListIterator iteration = createIterator(groupList);
 void *elem;

 int count=0, count2=0;
  if (img == NULL || len < 0){
		return -1;
	}
 
	//List *group_list = getGroups(img);
    
    if (groupList == NULL ){
		return 0;
	}

    ListIterator iter = createIterator(groupList);
    while((elem = nextElement(&iter)) != NULL)
    {
        count =0;
        Group * tmp = (Group*) elem;
        void* elem2;

        ListIterator iter1 = createIterator(tmp->rectangles);                 //traverses through rectangles list
        while((elem2 = nextElement(&iter1)) != NULL){
            count++;
        }

        ListIterator iter2 = createIterator(tmp->circles);                      //traverses through circles list
        while((elem2 = nextElement(&iter2)) != NULL){
          count++;  
        }
        
        ListIterator iter3 = createIterator(tmp->paths);                        //traverses through paths list
        while((elem2 = nextElement(&iter3)) != NULL){
           count++;  
        }
        ListIterator iter4 = createIterator(tmp->groups);                   //traverses through groups list
        while((elem2 = nextElement(&iter4)) != NULL){
           count++; 
        }

        if(count == len)
        {
          count2++;
        }
    }

 

freeList(groupList);

return count2;
}



int numAttr(const SVG* img){
    if(img == NULL){
        return 0;
    }

   
   void* elem;
   void *elem2;
   int count=0;

     ListIterator iterr = createIterator(img->otherAttributes);       //traversing through the attribute list of SVG
    while((elem2 = nextElement(&iterr))!= NULL){
		
		count++;
	}

//traversing through the attribute list of circle
   List* circList = getCircles(img);
   ListIterator iter1 = createIterator(circList);
   while ((elem = nextElement(&iter1)) != NULL){
		
	Circle * circ = (Circle*) elem;
    ListIterator iter = createIterator(circ->otherAttributes);
    while((elem = nextElement(&iter))!= NULL){
		
		count++;
	}
	}

//traversing through the attribute list of Rect
    List* rectList = getRects(img);
     ListIterator iter2 = createIterator(rectList);
    while ((elem = nextElement(&iter2)) != NULL){
		
		 Rectangle * rect = (Rectangle*) elem;
    ListIterator iter = createIterator(rect->otherAttributes);
    while((elem = nextElement(&iter))!= NULL){
		
		count++;
	}
	}

//traversing through the attribute list of Path
     List* pathList = getPaths(img);
     ListIterator iter3 = createIterator(pathList);
    while ((elem = nextElement(&iter3)) != NULL){
		
		 Path * path = (Path*) elem;
    ListIterator iter = createIterator(path->otherAttributes);
    while((elem = nextElement(&iter))!= NULL){
		
		count++;
	}
	}

//traversing through the attribute list of group
     List* groupList = getGroups(img);
     ListIterator iter4 = createIterator(groupList);
    while ((elem = nextElement(&iter4)) != NULL){
		
		 Group * grp = (Group*) elem;
    ListIterator iter = createIterator(grp->otherAttributes);
    while((elem = nextElement(&iter))!= NULL){
		
		count++;
	}
	}
    freeList(circList);
    freeList(rectList);
    freeList(groupList);
    freeList(pathList);


return count;
   
    
}



int validCheck(const SVG * img){

    void *elem;
    
    
    int flag=1;
    
    


    List *list = getRects(img);
    ListIterator iter = createIterator(list);
    while((elem = nextElement(&iter)) != NULL) {
        Rectangle *rect = (Rectangle *)elem;

        if (rect -> otherAttributes == NULL || rect -> width < 0 || rect -> height < 0) {
            freeList(list);
            
            flag=0;
            return 0;
        }
        
        void *elemm;
    ListIterator iterr = createIterator(rect->otherAttributes);
    while((elemm = nextElement(&iterr)) != NULL) {
        Attribute * other = (Attribute *)elemm;
        if (other -> name == NULL) {
            flag=0;
            break;
        }
        
    }
    
        if(flag==0){
            
            freeList(list);
            return 0;
        }
    }
    freeList(list);


   void *elem2;
    List * list2 = getCircles(img);
    ListIterator iter2 = createIterator(list2);

    while((elem2 = nextElement(&iter2)) != NULL) {
        Circle *circ = (Circle*)elem2;

        if (circ -> otherAttributes == NULL || circ -> r < 0 ) {
            freeList(list2);
                    flag=0;
            return 0;
        }
        void *elemm1;
    ListIterator iterr1 = createIterator(circ->otherAttributes);
    while((elemm1 = nextElement(&iterr1)) != NULL) {
        Attribute * other = (Attribute *)elemm1;
        if (other -> name == NULL) {
            flag=0;
            break;
        }

    }
        if(flag==0){
            
            freeList(list);
            return 0;
        }
    }
    freeList(list2);


    List *list3 = getPaths(img);
    ListIterator iter3 = createIterator(list3);
    void * elem3;
    while((elem3 = nextElement(&iter3)) != NULL) {
        Path *pth = (Path*)elem3;

        if (pth -> otherAttributes == NULL || pth -> data==NULL) {
            freeList(list3);
            
            flag=0;
            return 0;
        }
        void *elemm2;
    ListIterator iterr2 = createIterator(pth->otherAttributes);
    while((elemm2 = nextElement(&iterr2)) != NULL) {
        Attribute * other = (Attribute *)elemm2;
        if (other -> name == NULL) {
            flag=0;
            break;
        }
    }
        if(flag==0){
            
            freeList(list);
            return 0;
        }
    }
    freeList(list3);
  

    List *list4 = getGroups(img);
    ListIterator iter4 = createIterator(list4);
    void * elem4;
    while((elem4 = nextElement(&iter4)) != NULL) {
        
        Group *grp = (Group*)elem4;
        if(grp -> otherAttributes == NULL || grp->rectangles == NULL || grp->circles == NULL || grp->paths == NULL || grp->groups ==NULL || grp->otherAttributes == NULL){
            freeList(list4);
            
            flag=0;
            return 0;
        }
       void *elemm3;
    ListIterator iterr3 = createIterator(grp->otherAttributes);
    while((elemm3 = nextElement(&iterr3)) != NULL) {
        Attribute * other = (Attribute *)elemm3;
        if (other -> name == NULL) {
            flag=0;
            break;
        }
    }
        if(flag==0){
           
            freeList(list);
            return 0;
        }
    }
    freeList(list4);

  if(flag==1){
    return 1;
  }
    else{
    return 0;
}
}

xmlDoc * convert(xmlDoc * xmlDoc, const SVG * img){

    

    xmlDoc = xmlNewDoc(BAD_CAST "1.0");
    xmlNode * root_node = xmlNewNode(NULL, BAD_CAST "svg");
    xmlDocSetRootElement(xmlDoc, root_node);
  
   
    xmlNsPtr ns = xmlNewNs(root_node,(xmlChar *)img->namespace,NULL);
    xmlSetNs(root_node,ns);


    if(strcmp(img->title,"") != 0){
    xmlNewTextChild(root_node,NULL,BAD_CAST "title",BAD_CAST img->title);
    }
    if(strcmp(img->description,"") != 0){

    xmlNewTextChild(root_node,NULL,BAD_CAST "desc",BAD_CAST img->description);
    }

  attributeConvert(root_node,img->otherAttributes);
   
     if(root_node == NULL || img->rectangles == NULL){
        return xmlDoc;
    }
    void *elem;
    ListIterator iter= createIterator(img->rectangles);
    while((elem = nextElement(&iter))!=NULL){
        Rectangle *rect = (Rectangle *) elem;
        xmlNode * rectang= xmlNewChild(root_node,NULL,(xmlChar *)"rect",NULL);
        

       char x[200];
			sprintf(x, "%f%s", rect->x, rect->units);
			char y[200];
			sprintf(y, "%f%s", rect->y, rect->units);
            char width[200];
			sprintf(width,"%f%s",rect->width, rect->units);
			char height[200];
			sprintf(height, "%f%s", rect->height, rect->units);
			xmlNewProp (rectang, BAD_CAST "x", BAD_CAST x);
			xmlNewProp( rectang, BAD_CAST "y", BAD_CAST y);
            xmlNewProp( rectang, BAD_CAST "width", BAD_CAST width);
			xmlNewProp( rectang, BAD_CAST "height", BAD_CAST height);

       

        attributeConvert( rectang,rect->otherAttributes);
    }
        
        if(root_node == NULL || img->circles == NULL){
        return xmlDoc;
    }
    void *elem2;
    ListIterator iter2= createIterator(img->circles);
    while((elem2 = nextElement(&iter2))!=NULL){
        Circle *circle = (Circle *) elem2;
        xmlNode * circ= xmlNewChild(root_node,NULL,(xmlChar *)"circle",NULL);
       

        char cx[200];
			sprintf(cx, "%f%s", circle->cx, circle->units);
			char cy[200];
			sprintf(cy, "%f%s", circle->cy, circle->units);
            char r[200];
			sprintf(r, "%f%s", circle->r, circle->units);
			
			xmlNewProp(circ, BAD_CAST "cx", BAD_CAST cx);
			xmlNewProp(circ, BAD_CAST "cy", BAD_CAST cy);
            xmlNewProp(circ, BAD_CAST "r", BAD_CAST r);

       // xmlNewProp(cir,(const xmlChar *) "units",(const xmlChar *)circle->units);

       attributeConvert(circ,circle->otherAttributes);
    }
       
        if(root_node == NULL || img->paths == NULL){
        return xmlDoc;
    }
    void *elem1;
    ListIterator iter1= createIterator(img->paths);
    while((elem1 = nextElement(&iter1))!=NULL){
        Path *path = (Path *) elem1;
        xmlNode * paaath= xmlNewChild(root_node,NULL,(xmlChar *)"path",NULL);

        xmlNewProp(paaath,(const xmlChar *) "d",(const xmlChar *)path->data);
        attributeConvert(paaath,path->otherAttributes);
    }
        groupConvert(root_node,img->groups);
         
  
    return xmlDoc;


}





void  attributeConvert(xmlNode * node,List * otherAtr){
    if(node == NULL || otherAtr == NULL){
        return ;
    }
    void * elem;
    ListIterator iter= createIterator(otherAtr);
    while((elem = nextElement(&iter))!=NULL){
        Attribute *atr = (Attribute *) elem;
        xmlNewProp(node,(const xmlChar *) atr->name,(const xmlChar *)atr->value);

    }
}



void  groupConvert(xmlNode * node,List * grpList){
    if(node == NULL || grpList == NULL){
        return;
    }
    void *elem;
    ListIterator iter= createIterator(grpList);
    while((elem = nextElement(&iter))!=NULL){
        Group *group = (Group *) elem;
        xmlNode * grp = xmlNewChild(node,NULL,(xmlChar *)"g",NULL);
        attributeConvert(grp,group->otherAttributes);
        //rectangleConvert(grp,group->rectangles);
        if(node == NULL || group->rectangles == NULL){
        return ;
    }
    void *elem1;
    ListIterator iter1= createIterator(group->rectangles);
    while((elem1 = nextElement(&iter1))!=NULL){
        Rectangle *rect = (Rectangle *) elem1;
        xmlNode * rectang= xmlNewChild(grp,NULL,(xmlChar *)"rect",NULL);
        //char floatConvert[100000];
char x[200];
			sprintf(x, "%f%s", rect->x, rect->units);
			char y[200];
			sprintf(y, "%f%s", rect->y, rect->units);
            char width[200];
			sprintf(width,"%f%s",rect->width, rect->units);
			char height[200];
			sprintf(height, "%f%s", rect->height, rect->units);
			xmlNewProp(rectang, BAD_CAST "x", BAD_CAST x);
			xmlNewProp(rectang, BAD_CAST "y", BAD_CAST y);
            xmlNewProp(rectang, BAD_CAST "width", BAD_CAST width);
			xmlNewProp(rectang, BAD_CAST "height", BAD_CAST height);

        // xmlNewProp(rectt,(const xmlChar *) "units",(const xmlChar *)rectangle->units);

        attributeConvert(rectang,rect->otherAttributes);
    }
        //circleConvert(grp,group->circles);
        if(node == NULL || group->circles == NULL){
        return;
    }
    void *elem2;
    ListIterator iter2= createIterator(group->circles);
    while((elem2 = nextElement(&iter2))!=NULL){
        Circle *circle = (Circle *) elem2;
        xmlNode * circ= xmlNewChild(node,NULL,(xmlChar *)"circle",NULL);
        //char floatConvert[10000];

        char cx[200];
			sprintf(cx, "%f%s", circle->cx, circle->units);
			char cy[200];
			sprintf(cy, "%f%s", circle->cy, circle->units);
            char r[200];
			sprintf(r, "%f%s", circle->r, circle->units);
			
			xmlNewProp(circ, BAD_CAST "cx", BAD_CAST cx);
			xmlNewProp(circ, BAD_CAST "cy", BAD_CAST cy);
            xmlNewProp(circ, BAD_CAST "r", BAD_CAST r);

       // xmlNewProp(cir,(const xmlChar *) "units",(const xmlChar *)circle->units);

       attributeConvert(circ,circle->otherAttributes);
    }
        //pathConvert(grp,group->paths);
        if(node == NULL || group->paths == NULL){
        return;
    }
    void *elem3;
    ListIterator iter3= createIterator(group->paths);
    while((elem3 = nextElement(&iter3))!=NULL){
        Path *path = (Path *) elem3;
        xmlNode * paaath= xmlNewChild(node,NULL,(xmlChar *)"path",NULL);

        xmlNewProp(paaath,(const xmlChar *) "d",(const xmlChar *)path->data);
        attributeConvert(paaath,path->otherAttributes);
    }
        
        groupConvert(grp,group->groups);
        

    }
}

bool validateSVG(const SVG* img, const char* schemaFile){
    if (img == NULL || schemaFile == NULL) {
        
        return false;
    }
    
    xmlDoc *doc =NULL;
    doc=convert(doc,img);

    if (validate(doc, schemaFile)==0) {
        
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return false;
    }
    if(img->rectangles == NULL || img->circles == NULL || img->paths == NULL || img->groups ==NULL || img->otherAttributes == NULL){
        
        return false;
    }

    int result = validCheck(img);
    if(result==0){
        
        return false;
    }
     
    return true;
}

int validate(xmlDoc *doc, const char *XSDFileName ){
   
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt1;
   

    xmlLineNumbersDefault(1);

    ctxt1 = xmlSchemaNewParserCtxt(XSDFileName);

    if(ctxt1==NULL){
        xmlSchemaFreeParserCtxt(ctxt1);
        xmlSchemaCleanupTypes();
               xmlCleanupParser();
                xmlMemoryDump();
                
                return 0;
    }

  //  xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
    schema = xmlSchemaParse(ctxt1);
    if(schema==NULL){
        xmlSchemaFree(schema);
        xmlSchemaCleanupTypes();
               xmlCleanupParser();
                xmlMemoryDump();
                xmlSchemaFreeParserCtxt(ctxt1);
                
                return 0;
    }
    xmlSchemaFreeParserCtxt(ctxt1);
//xmlSchemaDump(stdout, schema); //To print schema dump

    //doc = xmlReadFile(XSDFileName, NULL, 0);

    if (doc == NULL)
    {
         fprintf(stderr, "Could not parse \n");
          xmlSchemaFree(schema);
          //xmlFreeDoc(doc);
               xmlSchemaCleanupTypes();
               xmlCleanupParser();
                xmlMemoryDump();
               return 0;
    }
    else
    {
         xmlSchemaValidCtxtPtr ctxt;
         int ret;

         ctxt = xmlSchemaNewValidCtxt(schema);
         //xmlSchemaSetValidErrors(ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
         ret = xmlSchemaValidateDoc(ctxt, doc);
         if (ret == 0)
         {
              //printf("validates\n");
              xmlSchemaFreeValidCtxt(ctxt);
        
               xmlSchemaFree(schema);

               xmlSchemaCleanupTypes();
               xmlCleanupParser();
               // xmlMemoryDump();
             
               return 1;
         }
         
         else
         {
              //printf("validation generated an internal error\n");
              xmlSchemaFreeValidCtxt(ctxt);
                xmlSchemaFree(schema);

               xmlSchemaCleanupTypes();
               xmlCleanupParser();
                xmlMemoryDump();
               return 0;
         }
    }
    
// free the resource

}



char *attrToJSON(const Attribute *a)
{   

    
    if (a == NULL)
    {
        return "{}";
    }

    char *attr = (char*)malloc(sizeof(char) * (strlen(a->name) + strlen(a->value) + 28));
    sprintf(attr, "{\"name\":\"%s\",\"value\":\"%s\"}", a->name, a->value);

    return attr;
}



char* rectToJSON(const Rectangle *r)
{

  if (r==NULL){
      return "{}";
  }
  int count= 0;
  count= getLength(r->otherAttributes);
  
    char *rect = (char *) malloc(sizeof(char) * (strlen(r->units) + 145));
    sprintf(rect, "{\"x\":%0.2f,\"y\":%0.2f,\"w\":%0.2f,\"h\":%0.2f,\"numAttr\":%d,\"units\":\"%s\"}", r->x , r->y, r->width, r->height, count,r->units);

    return rect;
}
char* pathToJSON(const Path *p){
    char *tmpStr;
    if (p == NULL) {
        tmpStr  = (char *)malloc(sizeof(char) * strlen("{}")+1);
        strcpy(tmpStr,"{}");
        return tmpStr;
    }
    int len;

    int number = getLength(p->otherAttributes);
    char *cpath = malloc(sizeof(char) * 65 );
    strncpy(cpath,p->data, sizeof(char) * 64);
    cpath[64] = '\0';
 
    len =  strlen(p->data) + strlen("{\"d\":\"\",\"numAttr\":}") + 21;
    tmpStr =(char *) malloc(sizeof(char) * len);

    sprintf(tmpStr,"{\"d\":\"%s\",\"numAttr\":%d}",cpath,number);

    free(cpath);
    return tmpStr;
}


char* circleToJSON(const Circle *c){

  if (c==NULL){
      return "{}";
  }
  int count =0;
  count= getLength(c->otherAttributes);
  
  int length = 0;
    length = strlen(c->units) + 140;

    char *circ = (char *)malloc(sizeof(char) + length * sizeof(char));
    sprintf(circ, "{\"cx\":%.2f,\"cy\":%.2f,\"r\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}", c->cx,c->cy,c->r, count,c->units);

    

    return circ;


}

//{"children":cVal,"numAttr":attVal}
char* groupToJSON(const Group *g){
     if (g==NULL){
      return "{}";
  }
  int sum = 0;
  int count = 0;

  sum= getLength(g->rectangles)+ getLength(g->circles) + getLength(g->paths) + getLength(g->groups);
  

count = getLength(g->otherAttributes);


  int num = 0;
    num = strlen("{\"children\":,\"numAttr\":}") + 9;

    char *grop = (char *)malloc(sizeof(char) + num * sizeof(char));
    sprintf(grop, "{\"children\":%d,\"numAttr\":%d}", sum, count);

    return grop;
}


//{"numRect":numR,"numCirc":numC,"numPaths":numP,"numGroups":numG}
char* SVGtoJSON(const SVG* img){
    char *temp;
    if (img == NULL) {//if img is NULL
        //memory allocation
        temp  = (char *)malloc(sizeof(char) * 4);
        strcpy(temp,"{}");
        return temp;
    }
    temp = (char *)malloc(sizeof(char) * (130));
    //declared lists
    List * rect  = getRects(img);
    int numRect = getLength(rect);
    List * circ  = getCircles(img);
    int numCirc = getLength(circ);
    List * path  = getPaths(img);
    int numPath = getLength(path);
    List * grp  = getGroups(img);
    int numGrp = getLength(grp);  
    
    
    
    
    //stored in specified format
    sprintf(temp,"{\"numRect\":%d,\"numCirc\":%d,\"numPaths\":%d,\"numGroups\":%d}",numRect, numCirc, numPath, numGrp);
    //free the lists
    freeList(rect);
    freeList(circ);
    freeList(path);
    freeList(grp);

    return temp;
}







char* attrListToJSON(const List *list){
    char * temp;
     if(list == NULL){
        temp = malloc(sizeof(char) * 2+1);
        strcpy(temp,"[]");
        return temp;
    }
    char * temp2 =  malloc(sizeof(char) * 3);
   
    strcpy(temp2,"[");
    void * elem;
    int sum=0, sum2=0;
    ListIterator iter= createIterator((List *)list);
    while((elem = nextElement(&iter))!=NULL){
        
        Attribute *other= (Attribute *)elem;
        temp = attrToJSON(other);
        sum=strlen(temp);
        temp2 = realloc(temp2, sizeof(char) * (strlen(temp2) + sum + 3));

        strcat(strcat(temp2,(char *)temp),",");
        
        free(temp);
    }
    sum2=strlen(temp2);
    if(sum2 == 1){
        strcpy(temp2,"[]");
        return temp2;
    }
    temp2[sum2-1]=']';
    return temp2;

}


char* circListToJSON(const List *list){
   char * temp;
     if(list == NULL){
        temp = malloc(sizeof(char) * 2+1);
        strcpy(temp,"[]");
        return temp;
    }
    char * temp2 =  malloc(sizeof(char) * 3);
   
    strcpy(temp2,"[");
    void * elem;
    int sum=0, sum2=0;
    ListIterator iter= createIterator((List *)list);
    while((elem = nextElement(&iter))!=NULL){
        
        Circle* other = (Circle*) elem;
        temp = circleToJSON(other);
        sum=strlen(temp);
        temp2 = realloc(temp2, sizeof(char) * (strlen(temp2) + sum + 3));

        strcat(strcat(temp2,(char *)temp),",");
        
        free(temp);
    }
    sum2=strlen(temp2);
    if(sum2 == 1){
        strcpy(temp2,"[]");
        return temp2;
    }
    temp2[sum2-1]=']';
    return temp2;


}


char* rectListToJSON(const List *list){
     char * temp;
     if(list == NULL){
        temp = malloc(sizeof(char) * 2+1);
        strcpy(temp,"[]");
        return temp;
    }
    char * temp2 =  malloc(sizeof(char) * 3);
   
    strcpy(temp2,"[");
    void * elem;
    int sum=0, sum2=0;
    ListIterator iter= createIterator((List *)list);
    while((elem = nextElement(&iter))!=NULL){
        
        Rectangle* other = (Rectangle*) elem;
        temp = rectToJSON(other);
        sum=strlen(temp);
        temp2 = realloc(temp2, sizeof(char) * (strlen(temp2) + sum + 3));

        strcat(strcat(temp2,(char *)temp),",");
        
        free(temp);
    }
    sum2=strlen(temp2);
    if(sum2 == 1){
        strcpy(temp2,"[]");
        return temp2;
    }
    temp2[sum2-1]=']';
    return temp2;
}


char* pathListToJSON(const List *list){
    char * temp;
    if(list == NULL){
        temp = malloc(sizeof(char) * 2+1);
        strcpy(temp,"[]");
        return temp;
    }
    char * temp2 =  malloc(sizeof(char) * 3);
    strcpy(temp2,"[");
    void * elem;
    int sum=0, sum2=0;
    ListIterator iter= createIterator((List *)list);
    while((elem = nextElement(&iter))!=NULL){

        Path* other = (Path*) elem;
        temp = pathToJSON(other);
        sum = strlen(temp);
        temp2 = realloc(temp2, sizeof(char) * (strlen(temp2) + sum + 3));

        
         strcat(strcat(temp2,(char *)temp),",");
        free(temp);
    }
    sum2=strlen(temp2);
    if(sum2 == 1){
        strcpy(temp2,"[]");
        return temp2;
    }
    temp2[sum2-1]=']';
    return temp2;

}

char* groupListToJSON(const List *list){
    char * temp;
    if(list == NULL){
        temp = malloc(sizeof(char) * 2+1);
        strcpy(temp,"[]");
        return temp;
    }
    char * temp2 =  malloc(sizeof(char) * 3);

    strcpy(temp2,"[");
    void * elem;
    int sum=0, sum2=0;
    ListIterator iter= createIterator((List *)list);
    while((elem = nextElement(&iter))!=NULL){

        Group * other = (Group*) elem;
        temp = groupToJSON(other);
        sum = strlen(temp) ;
        temp2 = realloc(temp2, sizeof(char) * (strlen(temp2) + sum+ 3));

     
        
        strcat(strcat(temp2,(char *)temp),",");
        free(temp);
    }
    sum2=strlen(temp2);
    if(sum2 == 1){
        strcpy(temp2,"[]");
        return temp2;
    }
    temp2[sum2-1]=']';
    return temp2;

}



char *helpJSON(char *fileName) {
    if (fileName == NULL) {
        return NULL;
    }
    
    SVG *svg = createSVG(fileName);
    if(!validateSVG(svg, "svg.xsd")) {
        deleteSVG(svg);
        return NULL;
    }
    char *svgString = SVGtoJSON(svg);

    List *rect = getRects(svg);
    char *rectangle = rectListToJSON(rect);
    char *attrRect = allAttr(rect, RECT);
  

    List *circ = getCircles(svg);
    char *circle = circListToJSON(circ);
    char *attrCirc = allAttr(circ, CIRC);
  

    List *path = getPaths(svg);
    char *pa = pathListToJSON(path);
    char *attrPath = allAttr(path, PATH);


    List *group = getGroups(svg);
    char *grp = groupListToJSON(group);
    char *attrGrp = allAttr(group, GROUP);
 

    // add more fields to the JSON string, title, desc and components
    char *finalString = malloc(sizeof(char)*(strlen(svgString) + strlen("\"rects\":,\"circs\":,\"paths\":,\"groups\":"",\"attrRect\":,\"attrCirc\":,\"atrPath\":,\"attrGrp\":}") + strlen(attrRect) + strlen(attrCirc) + strlen(attrPath) + strlen(attrGrp) + strlen(rectangle) + strlen(circle) + strlen(pa) + strlen(grp) + 3));

    svgString[strlen(svgString) - 1] = ',';        
    sprintf(finalString, "%s\"rects\":%s,\"circs\":%s,\"paths\":%s,\"groups\":%s,\"attrRect\":%s,\"attrCirc\":%s,\"attrPath\":%s,\"attrGrp\":%s}",svgString, rectangle, circle, pa, grp, attrRect,attrCirc, attrPath, attrGrp);
    
    freeList(rect);
    freeList(circ);
    freeList(path);
    freeList(group);

    deleteSVG(svg);
    free(svgString);
    free(rectangle);
    free(circle);
    free(pa);
    free(grp);
    free(attrRect);
    free(attrCirc);
    free(attrPath);
    free(attrGrp);

    return finalString;
}


char *allAttr (List *shapes, elementType type) {
    if (shapes == NULL) {
        return NULL;
    }
    ListIterator iter = createIterator(shapes);
    void *elem;
    int i = 0;
    char **dblptr = NULL;
    

    while((elem = nextElement(&iter)) != NULL) {
        dblptr = realloc(dblptr, sizeof(char *) * (i + 1));

        if (type == RECT) {
            dblptr[i] = attrListToJSON(((Rectangle *)elem) -> otherAttributes);
        }

        if (type == CIRC) {
            dblptr[i] = attrListToJSON(((Circle *)elem) -> otherAttributes);
        }

        if (type == PATH) {
            dblptr[i] = attrListToJSON(((Path *)elem) -> otherAttributes);
        }

        if (type == GROUP) {
            dblptr[i] = attrListToJSON(((Group *)elem) -> otherAttributes);
        }

        i++;
    }
    
    char *ch = malloc(sizeof(char) * 2);
    strcpy (ch, "[");

   
    for (i = 0; i < shapes -> length; i++) {
        ch = realloc(ch, sizeof(char) * (strlen(ch) + strlen(dblptr[i]) + 2));

        if (i > 0) {
            strcat(ch, ",");
        }

        strcat(ch, dblptr[i]);

        free(dblptr[i]);
        dblptr[i] = NULL;
    }
    
  
    ch = realloc(ch, sizeof(char) * (strlen(ch) + 2));
    strcat(ch, "]");
    free(dblptr);
    
    return ch;
}




char * getDesc(char * fileName){
    if (fileName == NULL) {
        return NULL;
    }
    SVG * svg = createSVG(fileName);
    if(!validateSVG(svg,"svg.xsd")){
        deleteSVG(svg);
        return NULL;
    }
    int len = strlen(svg->description)+1;
    char * ch = malloc(sizeof(char) * len);
    strcpy(ch,svg->description);
    deleteSVG(svg);
    return ch;
}
char * getTitle(char * fileName){
    if (fileName == NULL) {
        return NULL;
    }
    SVG * svg = createSVG(fileName);
    if(!validateSVG(svg,"svg.xsd")){
        deleteSVG(svg);
        return NULL;
    }
    int len= strlen(svg->title)+1;
    char * ch = malloc(sizeof(char) * len );
    strcpy(ch,svg->title);
    deleteSVG(svg);
    return ch;
}

SVG* JSONtoSVG(const char* svgString){
    return NULL;
}

Rectangle* JSONtoRect(const char* svgString){
    return NULL;
}
 Circle* JSONtoCircle(const char* svgString){
     return NULL;
 }