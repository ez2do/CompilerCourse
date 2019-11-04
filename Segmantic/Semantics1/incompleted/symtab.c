/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object *obj);
void freeScope(Scope *scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab *symtab;
Type *intType;
Type *charType;

/******************* Type utilities ******************************/

Type *makeIntType(void)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type *makeCharType(void)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type *makeArrayType(int arraySize, Type *elementType)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type *duplicateType(Type *type)
{
  // TODO
  Type *newCopiedType = (Type *)malloc(sizeof(Type));
  return memcpy(newCopiedType, type, sizeof(Type));
}

int compareType(Type *type1, Type *type2)
{
  // TODO
  if (type1->typeClass == type2->typeClass && type1->elementType == type2->elementType)
  {
    return 1;
  }
  return 0;
}

void freeType(Type *type)
{
  // TODO
  free(type);
}

/******************* Constant utility ******************************/

ConstantValue *makeIntConstant(int i)
{
  // TODO
  ConstantValue *constValue = (ConstantValue *)malloc(sizeof(ConstantValue));
  constValue->type = TP_INT;
  constValue->intValue = i;
  return constValue;
}

ConstantValue *makeCharConstant(char ch)
{
  // TODO
  ConstantValue *constValue = (ConstantValue *)malloc(sizeof(ConstantValue));
  constValue->type = TP_CHAR;
  constValue->charValue = ch;
  return constValue;
}

ConstantValue *duplicateConstantValue(ConstantValue *v)
{
  // TODO
  ConstantValue *newConstValue = (ConstantValue *)malloc(sizeof(ConstantValue));
  return memcpy(newConstValue, v, sizeof(ConstantValue));
}

/******************* Object utilities ******************************/

Scope *createScope(Object *owner, Scope *outer)
{
  Scope *scope = (Scope *)malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object *createProgramObject(char *programName)
{
  Object *program = (Object *)malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes *)malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program, NULL);
  symtab->program = program;
  return program;
}

Object *createConstantObject(char *name)
{
  // TODO
  Object *constant = (Object *)malloc(sizeof(Object));
  strcpy(constant->name, name);
  constant->kind = OBJ_CONSTANT;
  constant->constAttrs = (ConstantAttributes *)malloc(sizeof(ConstantAttributes));
  // constant->constAttrs->value = (ConstantValue *)malloc(sizeof(ConstantValue));
  return constant;
}

Object *createTypeObject(char *name)
{
  // TODO
  Object *type = (Object *)malloc(sizeof(Object));
  strcpy(type->name, name);
  type->kind = OBJ_TYPE;
  type->typeAttrs = (TypeAttributes *)malloc(sizeof(TypeAttributes));
  // type->typeAttrs->actualType = (Type *)malloc(sizeof(Type));
  return type;
}

Object *createVariableObject(char *name)
{
  // TODO
  Object *var = (Object *)malloc(sizeof(Object));
  strcpy(var->name, name);
  var->kind = OBJ_VARIABLE;
  var->varAttrs = (VariableAttributes *)malloc(sizeof(VariableAttributes));
  // var->varAttrs->type = (Type *)malloc(sizeof(Type));
  // var->varAttrs->scope = (Scope *)malloc(sizeof(Scope));
  return var;
}

Object *createFunctionObject(char *name)
{
  // TODO
  Object *func = (Object *)malloc(sizeof(Object));
  strcpy(func->name, name);
  func->kind = OBJ_FUNCTION;
  func->funcAttrs = (FunctionAttributes *)malloc(sizeof(FunctionAttributes));
  func->funcAttrs->scope = createScope(func, symtab->currentScope);
  return func;
}

Object *createProcedureObject(char *name)
{
  // TODO
  Object *proc = (Object *)malloc(sizeof(Object));
  strcpy(proc->name, name);
  proc->kind = OBJ_PROCEDURE;
  proc->procAttrs = (ProcedureAttributes *)malloc(sizeof(ProcedureAttributes));
  proc->procAttrs->scope = createScope(proc, symtab->currentScope);
  return proc;
}

Object *createParameterObject(char *name, enum ParamKind kind, Object *owner)
{
  // TODO
  Object *param = (Object *)malloc(sizeof(Object));
  strcpy(param->name, name);
  param->kind = OBJ_PARAMETER;
  param->paramAttrs = (ParameterAttributes *)malloc(sizeof(ParameterAttributes));
  // param->paramAttrs->type = (Type *)malloc(sizeof(Type));
  // param->paramAttrs->function = (Object *)malloc(sizeof(Object));
  return param;
}

void freeObject(Object *obj)
{
  // TODO
  free(obj);
}

void freeScope(Scope *scope)
{
  // TODO
  free(scope);
}

void freeObjectList(ObjectNode *objList)
{
  // TODO
  free(objList);
}

void freeReferenceList(ObjectNode *objList)
{
  // TODO
  free(objList);
}

void addObject(ObjectNode **objList, Object *obj)
{
  ObjectNode *node = (ObjectNode *)malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL)
    *objList = node;
  else
  {
    ObjectNode *n = *objList;
    while (n->next != NULL)
      n = n->next;
    n->next = node;
  }
}

Object *findObject(ObjectNode *objList, char *name)
{
  // TODO
  ObjectNode *currentNode = (ObjectNode *)malloc(sizeof(ObjectNode));
  currentNode = objList;
  while(currentNode)
  {
    if (currentNode->object->name == name)
    {
      return currentNode->object;
    }
    currentNode = currentNode->next;
  }
  return NULL;
}

/******************* others ******************************/

void initSymTab(void)
{
  Object *obj;
  Object *param;

  symtab = (SymTab *)malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;

  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEI");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  addObject(&(obj->procAttrs->paramList), param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEC");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  addObject(&(obj->procAttrs->paramList), param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
}

void cleanSymTab(void)
{
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope *scope)
{
  symtab->currentScope = scope;
}

void exitBlock(void)
{
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object *obj)
{
  if (obj->kind == OBJ_PARAMETER)
  {
    Object *owner = symtab->currentScope->owner;
    switch (owner->kind)
    {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      addObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }

  addObject(&(symtab->currentScope->objList), obj);
}
