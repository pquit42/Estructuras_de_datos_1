 #include "vertex.h"
#include <string.h>
#include <stdio.h>

#define TAG_LENGHT 64

struct _Vertex {
  long id;
  char tag[TAG_LENGHT];
  Label state;
};

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/

Status vertex_setField (Vertex *v, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return vertex_setId(v, atol(value));
  } else if (strcmp(key, "tag") == 0) {
    return vertex_setTag(v, value);
  } else if (strcmp(key, "state") == 0) {
    return vertex_setState(v, (Label)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Vertex *vertex_initFromString(char *descr){
  char buffer[1024];
  char *token;
  char *key;
  char *value;
  char *p;
  Vertex *v;

  /* Check args: */
  if (!descr) return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v) return NULL;

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
  while (token) {
    p = strchr(token, ':');
    if (!p) continue;

    *p = '\0';
    key = token;
    value = p+1;

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}

/**  rest of the functions in vertex.h **/

/*----------------------------------------------------------------------------------------*/
Vertex * vertex_init (){
  Vertex *new_vertex = NULL;

  if(!(new_vertex = (Vertex *)malloc(sizeof(Vertex)))){
      return NULL;
  }
    
  new_vertex->id = 0;
  *new_vertex->tag = "\0";
  new_vertex->state = WHITE;

  return new_vertex;  
}


/**
 * @brief Constructor. Initialize a vertex from its description.
 * 
 * This function allocates memory for a vertex and sets its fields  
 * according to the description provided. A description string is 
 * a set of key:value pairs separated by any amount of whitespace, 
 * where the key can be any of id, tag or state. 
 * No space is allowed in the definition of a key:value pair.
 * The key:value pairs can be provided in any order.
 * 
 * Examples
 *
 * vertex_initFromString("id:1 tag:Toledo state:1");
 * vertex_initFromString("tag:Toledo state:1 id:1");
 * vertex_initFromString("tag:Toledo state:1");
 * vertex_initFromString("id:1 state:1");
 *
 * @param descr String describing the vertex.
 *
 * @return Return the initialized vertex if it was done correctly, 
 * otherwise return NULL.
*/
Vertex *vertex_initFromString(char *descr);

/**
 * @brief Destructor. Free the dynamic memory reserved for a vertex .
 *
 * @param v Vertex to free
 */
void vertex_free (void * v){
  if(v)
    free(v);   
};


/**
 * @brief  Gets the vertex id.
 *
 * @param v Vertex pointer
 *
 * @return  Returns the id of the given vertex, or -1 in case of error.
 */
long vertex_getId (const Vertex * v){
  if(!v)
    return -1;

  return v->id;
};


/**
 * @brief Gets the vertex tag.
 *
 * @param v Vertex pointer
 *
 * @return Returns a pointer to the tag of the vertex, or NULL in 
 * case of error.
 */
const char* vertex_getTag (const Vertex * v){
  if(!v)
    return NULL;

  return v->tag;
};


/**
 * @brief Gets the state of a given vertex.
 *
 * @param Vertex pointer
 *
 * @return Returns the state of a given vertex, or ERROR_VERTEX in 
 * case of error.
 */
Label vertex_getState (const Vertex * v){
  if(!v)
    return ERROR_VERTEX;

  return v->state;
};



/**
 * @brief Modifies the id of a given vertex.
 *
 * @param v Vertex pointer
 * @param id New vertex id, must be equal or greater than 0
 *
 * @return Returns OK or ERROR in case of error 
 */
Status vertex_setId (Vertex * v, const long id){
  if(!v || !id)
    return ERROR;

  v->id = id;
  return OK;
};


/**
 * @brief Modifies the tag of a given vertex
 *
 * @param v Vertex pointer
 * @param id New vertex tag, must fit in the Vertex
 *
 * @return  Returns OK or ERROR in case of error.
 */
Status vertex_setTag (Vertex * v, const char * tag){
  if(!v || !tag)
    return ERROR;

  strcpy(v->tag, tag);
  return OK;
};


/**
 * @brief Modifies the state of a given vertex
 *
 * @param v Vertex pointer
 * @param state New vertex state
 *
 * @return Returns OK or ERROR in case of error.
 */
Status vertex_setState (Vertex * v, const Label state){
  if(!v || !state)
    return ERROR;

  v->state = state;
  return OK;
};



/**
 * @brief Compares two vertices.
 *
 * First it compares their ids. If they are equal, then compares
 * their tags.
 * 
 * @param v1,v2 Vertices to compare.
 *
 * @return It returns an integer less than or greater than zero if
 * id of v1 is found,  respectively, to be less than or be greater 
 * than id of v2. If their are equal, thenreturns the result of 
 * comparing their tags. In case of error, returns 0. 
 */
int vertex_cmp (const void * v1, const void * v2){
  if(!v1 || !v2)
    return 0;

  if(vertex_getId((const Vertex *)v1) < vertex_getId((const Vertex *)v2))
    return -1;
  if(vertex_getId((const Vertex *)v1) > vertex_getId((const Vertex *)v2))
    return 1;

  if(vertex_getId(v1) == vertex_getId(v2))
    return strcmp(vertex_getTag(v1), vertex_getTag(v2)); ////// NPIDCHEF
 
};


/**
 * @brief Reserves memory for a vertex where it copies the data from
 * the vertex src.
 * 
 * @code
 * // Example of use
 * Vertex *trg, *src;
 * src = vertex_init();
 * trg = vertex_copy(src);
 * // .... aditional code ...
 * // free vertexs
 * vertex_free(src);
 * vertex_free(trg);
 * @endcode
 * 
 * @param src Original vertex pointer
 *
 * @return Returns the pointer of the copied vertex if everything 
 * went well, or NULL otherwise.
 */
void * vertex_copy (const void * src){
  Vertex *trg = NULL;
  if(!src)
    return NULL;

  trg = (Vertex*)malloc(sizeof(Vertex));
  if(!trg)
    return NULL;

  trg->id = ((Vertex*)src)->id;
  strcpy(trg->tag, ((Vertex*)src)->tag;
  trg->state = ((Vertex*)src)->state;
};


/** 
 * @brief Prints in pf the data of a vertex.
 * 
 * The format will be: [id, tag, state], without line break at the 
 * end. The type Label is an enumeration so it can be printed as an
 * int. 
 *
 * @code
 * Vertex * v;
 * v = vertex_init();
  while(fscanf(pf, "%ld, %s, %"))
 * vertex_print (stdout, v);
 * @endcode
 *
 * @param pf File descriptor
 * @param v Vertex to be printed
 *
 * @return Returns the number of characters that have been written 
 * successfully. If there have been errors returns -1.
 */
int vertex_print (FILE * pf, const void * v){
  long n;

  if(!(pf) || !(v))
    return -1;

  n = fprintf(pf, "[%ld, %s, %int]", ((Vertex *)v)->id, ((Vertex *)v)->tag, ((Vertex *)v)->state);

  return n;
}