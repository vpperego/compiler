#include "types.h"


int checkBooleanType(int type){
  return type == AST_LESS ||
     type == AST_MORE ||
     type == AST_GE ||
     type == AST_LE ||
     type == AST_NE ||
     type == AST_EQ ||
     type == AST_OR ||
     type == AST_AND||
     type == AST_NOT;
}

int checkArithmeticType(int type){
  return type == AST_ADD || type == AST_SUB || type == AST_MUL || type == AST_DIV ;
}


int setDataType(int nodeType){
  switch(nodeType){
    case AST_BYTE:
      return DATATYPE_BYTE;
      break;

    case AST_CHAR:
      return DATATYPE_CHAR;
      break;

    case AST_SHORT:
      return DATATYPE_SHORT;
      break;

    case AST_LONG:
      return DATATYPE_LONG;
      break;

    case AST_FLOAT:
      return DATATYPE_FLOAT;
      break;

    case AST_DOUBLE:
      return DATATYPE_DOUBLE;
      break;

    case AST_INTEGER:
      return DATATYPE_LONG;
      break;

    case AST_REAL:
      return DATATYPE_REAL;
      break;
      default:
      break;
    }
}

int setSymbolType(int type){
    switch ( type) {
        // // case AST_VAR:
        // //     node->symbol->type = SYMBOL_SCALAR;
        // //     break;
        case AST_SYMBOL:
            return SYMBOL_SCALAR;
            break;
        case AST_ARRAY:
            return SYMBOL_ARRAY;
            break;

        case AST_FUNCTION:
            return SYMBOL_FUN;
            break;

        case AST_PARAM:
            return SYMBOL_SCALAR;
            break;
        case AST_ATRIB_ARRAY:
            return SYMBOL_SCALAR;
            break;
        case AST_ATRIB:
            return SYMBOL_SCALAR;
            break;
        default:
            return SYMBOL_UNDEF;
            break;
    }
}

int isIntegerType(int type){
  return (type == DATATYPE_BYTE  ||
      type == DATATYPE_SHORT ||
      type == DATATYPE_LONG) ;
}

int isRealType(int type){
  return (type == DATATYPE_FLOAT  ||
          type == DATATYPE_DOUBLE );
}

int compareDataType(int type1,int type2){
  if ( isIntegerType(type1) &&
       isIntegerType(type2))  {
      return 1;
  }else if(isRealType(type1) &&
          isRealType(type2))
  {
    return 1;
  }else{
    return 0;
  }
}

int getArithmeticType(int type1, int type2)
{
    if (type1 == DATATYPE_BOOL || type2 == DATATYPE_BOOL)
        return DATATYPE_UNDEF;

    // this makes sense since the datatypes are declared
    // in a ascending order of "wideness" (i.e. datatypes declared
    // after in hash.h are bigger)
    if (type1 > type2) {
        return type1;
    } else {
        return type2;
    }
}
