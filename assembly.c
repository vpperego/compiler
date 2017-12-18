#include "assembly.h"

void writeCode(TAC *code, FILE * assemblyCode){
  if(code->type == TAC_MOVE){
      fprintf(assemblyCode, "global %s\n.data\n.align 4\n.type %s, @object\n.size %s, 4\n%s:\n.long %d",code->res->text,
        code->res->text,code->res->text,code->res->text,atoi(code->op1->text));
    }
}

void generateAssembly(TAC * code){
  FILE * assemblyCode = fopen("a.s","w");
  writeCode(code,assemblyCode);
  fclose(assemblyCode);
}
