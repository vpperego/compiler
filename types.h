#include "astree.h"

enum DATATYPE{
  DATATYPE_BYTE,
  DATATYPE_CHAR,
  DATATYPE_SHORT,
  DATATYPE_FLOAT,
  DATATYPE_DOUBLE,
  DATATYPE_LONG,
  DATATYPE_REAL,
  DATATYPE_STRING,
  DATATYPE_BOOL,
  DATATYPE_UNDEF
};

int checkBooleanType(int type);
int checkArithmeticType(int type);
int setDataType(int nodeType);
int setSymbolType(int type);
int isIntegerType(int type);
int isRealType(int type);
int compareDataType(int type1,int type2);
int getArithmeticType(int type1, int type2);
