#include "genco.h"

int LFBid, LFEid = 0;
int labelNmbr = 2;
int lableLC = 2;
char parReg[6][4]  = {{"edi\0"}, {"esi\0"},{"edx\0"}, {"ecx\0"}, {"r8d\0"}, {"r9d\0"}};
int parNmbr1 = 0, parNmbr2 = 0;
int aux = 0;


TAC* makeFuncDec(TAC* type, TAC* params, TAC* cmdBlock, HASH_NODE *symbol);
TAC* makeIfThen(TAC* code0, TAC* code1);
TAC* makeIfThenElse(TAC* code0, TAC* code1, TAC* code2);
TAC* makeWhile(TAC* code0, TAC* code1);
TAC* makeFuncDef(TAC* type, TAC* params, TAC* cmdBlock, HASH_NODE *symbol);
TAC* tacGenerateNot(int type, TAC* op1);
TAC* tacGenerateOp(int type, TAC* op1, TAC* op2);

TAC* makeFunction(TAC* symbol, TAC* par, TAC* code);

TAC * tacCreate(int type, HASH_NODE * res, HASH_NODE * op1, HASH_NODE * op2){
  TAC * newtac = (TAC *) calloc(1,sizeof(TAC));
  newtac->type = type;
  newtac->res = res;
  newtac->op1 = op1;
  newtac->op2 = op2;
  newtac->prev = 0;
  newtac->next = 0;
  return newtac;
}

TAC * tacJoin(TAC *l1, TAC *l2){
  TAC * tac;
  if (!l1) return l2;
  if (!l2) return l1;
  tac = l2;
  while(tac->prev){
    tac = tac->prev;
  }
  tac->prev = l1;
 // l1->next = l2;

  return l2;
}

TAC* tacReverse(TAC* tac)
{
  if(!tac){
    fprintf(stderr, "tes");
    return NULL;
  }
	TAC* t;
	for(t = tac; t->prev; t = t->prev)
		t->prev->next = t;
	return t;
}

void tacPrintFoward(TAC* first)
{
	fprintf(stderr, "\n ---Imprimindo codigo gerado---\n");

	TAC *tac;

	for(tac = first; tac; tac = tac->next){
		tacPrintSingle(tac);
	}

}

void tacPrintSingle(TAC *tac){
  if (!tac) {
    return;
  }
  TAC* tacPrint = tac;

  fprintf(stderr, "TAC(" );
  switch (tacPrint->type) {
    case TAC_SYMBOL:  fprintf(stderr,"TAC_SYMBOL"); break;
    case TAC_ADD:  fprintf(stderr,"TAC_ADD"); break;
    case TAC_SUB:  fprintf(stderr,"TAC_SUB"); break;
    case TAC_MUL:  fprintf(stderr,"TAC_MUL"); break;
    case TAC_DIV:  fprintf(stderr, "TAC_DIV"); break;
    case TAC_LESS: fprintf(stderr, "TAC_LESS"); break;
    case TAC_MORE: fprintf(stderr, "TAC_MORE"); break;
    case TAC_NOT:  fprintf(stderr, "TAC_NOT"); break;
    case TAC_LE: fprintf(stderr, "TAC_LE"); break;
    case TAC_GE: fprintf(stderr, "TAC_GE"); break;
    case TAC_EQ: fprintf(stderr, "TAC_EQ"); break;
    case TAC_NE: fprintf(stderr, "TAC_NE"); break;
    case TAC_AND: fprintf(stderr, "TAC_AND"); break;
    case TAC_OR: fprintf(stderr, "TAC_OR"); break;
    case TAC_FUNC: fprintf(stderr, "TAC_FUNC"); break;
    case TAC_INIT_ARRAY: fprintf(stderr, "TAC_INIT_ARRAY"); break;
    case TAC_ARRAY_INIT_VALUES: fprintf(stderr, "TAC_ARRAY_INIT_VALUES"); break;
    case TAC_ARRAY: fprintf(stderr, "TAC_ARRAY"); break;
    case TAC_ATRIB: fprintf(stderr, "TAC_ATRIB"); break;
    case TAC_ATRIB_ARRAY: fprintf(stderr, "TAC_ATRIB_ARRAY"); break;
    case TAC_READ: fprintf(stderr, "TAC_READ"); break;
    case TAC_BEGIN_PRINT: fprintf(stderr, "TAC_BEGIN_PRINT"); break;
    case TAC_END_PRINT: fprintf(stderr, "TAC_END_PRINT"); break;
    case TAC_RETURN: fprintf(stderr, "TAC_RETURN"); break;
    case TAC_LIST_PARAM: fprintf(stderr, "TAC_LIST_PARAM"); break;
    case TAC_PARAM: fprintf(stderr, "TAC_PARAM"); break;
    case TAC_ARG_ID: fprintf(stderr, "TAC_ARG_ID"); break;
    case TAC_LIST_ARG: fprintf(stderr, "TAC_LIST_ARG"); break;
    case TAC_ARG: fprintf(stderr, "TAC_ARG"); break;
    case TAC_VARDEC: fprintf(stderr, "TAC_VARDEC"); break;
    case TAC_FUNDEC: fprintf(stderr, "TAC_FUNDEC"); break;
    case TAC_BEGIN_FUN: fprintf(stderr, "TAC_BEGIN_FUN"); break;
    case TAC_END_FUN: fprintf(stderr, "TAC_END_FUN"); break;
    case TAC_JMP: fprintf(stderr, "TAC_JMP"); break;
    case TAC_IFZ: fprintf(stderr, "TAC_IFZ"); break;
    case TAC_MOVE: fprintf(stderr, "TAC_MOVE"); break;
    case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
    case TAC_PRINT: fprintf(stderr, "TAC_PRINT"); break;
    default: fprintf(stderr, "TAC_UNKNOWN"); break;
  }

  if(tacPrint->res && tacPrint->res->text ) fprintf(stderr, ", %s",tacPrint->res->text ); else fprintf(stderr, ", null" );
  if(tacPrint->op1 && tacPrint->op1->text) fprintf(stderr, ", %s",tacPrint->op1->text ); else fprintf(stderr, ", null" );
  if(tacPrint->op2 && tacPrint->op2->text) fprintf(stderr, ", %s",tacPrint->op2->text ); else fprintf(stderr, ", null" );
  fprintf(stderr, ")\n");

}



void tacPrintBack(TAC * last){
  TAC * tac;
  for ( tac = last; tac; tac = tac->prev) {
     tacPrintSingle(tac);
  }
}

TAC* tacGenerator(AST * node){
  int i;

  TAC *code[MAX_SONS];
  if (!node) return 0;

  for (i = 0; i < MAX_SONS; i++) {
    code[i] = tacGenerator(node->son[i]);
  }

  //TAC * tacCreate(int type, HASH_NODE * res, HASH_NODE * op1, HASH_NODE * op2) Just to remind the order of parameters
  switch (node->type) {
    case AST_SYMBOL: return tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;
    case AST_STRING: return tacCreate(TAC_STRING, node->symbol, 0, 0); break;
    case AST_ADD:  return tacGenerateOp(TAC_ADD, code[0], code[1]); break;
    case AST_SUB:  return tacGenerateOp(TAC_SUB, code[0], code[1]); break;
    case AST_MUL:  return tacGenerateOp(TAC_MUL, code[0], code[1]); break;
    case AST_DIV:  return tacGenerateOp(TAC_DIV, code[0], code[1]); break;
    case AST_LESS: return tacGenerateOp(TAC_LESS, code[0], code[1]); break;
    case AST_MORE: return tacGenerateOp(TAC_MORE, code[0], code[1]); break;
    case AST_LE:   return tacGenerateOp(TAC_LE, code[0], code[1]); break;
    case AST_GE:   return tacGenerateOp(TAC_GE, code[0], code[1]); break;
    case AST_EQ:   return tacGenerateOp(TAC_EQ, code[0], code[1]); break;
    case AST_NE:   return tacGenerateOp(TAC_NE, code[0], code[1]); break;
    case AST_AND:  return tacGenerateOp(TAC_AND, code[0], code[1]); break;
    case AST_OR:   return tacGenerateOp(TAC_OR, code[0], code[1]); break;
    case AST_NOT:  return tacGenerateNot(TAC_NOT, code[0]); break;
    case AST_FUNC: return tacJoin(code[0], tacCreate(TAC_FUNC, makeTemp(), node->symbol, 0)); break;
    case AST_INIT_ARRAY:  return tacJoin(tacCreate(TAC_INIT_ARRAY,node->symbol,code[1]?code[1]->res:0,0),code[2]);
//    case AST_ARRAY_INIT_VALUES: break;
    case AST_ARRAY: return tacJoin(code[0],tacCreate(TAC_ARRAY, node->symbol, 0, 0)); break;
    case AST_ATRIB: return tacJoin(code[0], tacCreate(TAC_MOVE, node->symbol, code[0]?code[0]->res:0, 0)); break;
    case AST_ATRIB_ARRAY: return tacJoin(tacJoin(code[0],code[1]),
          tacCreate(TAC_MOV_IND,node->symbol,code[0]?code[0]->res:0,code[1]?code[1]->res:0)); break;
    case AST_READ: return tacCreate(TAC_READ, node->symbol, 0, 0); break;
    case AST_PRINT: 
    return tacJoin(tacCreate(TAC_PRINT, code[0]?code[0]->res:0, 0, 0), code[1]); break;
    //return tacJoin(tacJoin( tacCreate(TAC_BEGIN_PRINT, node->symbol, 0, 0), code[0] ), tacCreate(TAC_END_PRINT, node->symbol, makeTemp(), 0));break;
    case AST_RETURN: return tacJoin(code[0], tacCreate(TAC_RETURN, node->symbol, 0, 0)); break;
    case AST_IF: return makeIfThen(code[0], code[1]); break;
    case AST_IF_ELSE: return makeIfThenElse(code[0], code[1], code[2]); break;
    case AST_WHILE: return makeWhile(code[0], code[1]); break;
  //  case AST_LIST_PARAM: return tacJoin(tacJoin(code[0], tacCreate(TAC_PARAM, code[0]? code[0]->res : 0, 0, 0)), code[1]); break;
//    case AST_PARAM: return tacCreate(TAC_PARAM, code[0]->res, 0, 0); break;
    case AST_ARG_ID: return tacCreate(TAC_ARG_ID, node->symbol, 0, 0); break;
 //   case AST_LIST_ARG: break;
    //case AST_ARG: break;
    case AST_VARDEC: return tacJoin(code[0], tacCreate(TAC_MOVE, node->symbol, code[1]->res, 0)); break;
    case AST_FUNDEC:
      return  makeFunction(tacCreate(TAC_SYMBOL, node->symbol, 0, 0), code[1], code[2]);
      //return makeFuncDec(code[0],code[1],code[2],node->symbol);
      break;
		case AST_INTEGER: return tacCreate(TAC_INTEGER, node->symbol, 0, 0);break;
		case AST_REAL: return tacCreate(TAC_REAL, node->symbol, 0, 0);break;
		case AST_CHAR: return tacCreate(TAC_CHAR, node->symbol, 0, 0);break;
    default:
       return tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);
      break;
    }
}




TAC* tacGenerateNot(int type, TAC* op1){
    return tacJoin(op1, tacCreate(type, makeTemp(), op1?op1->res:0, 0));
}


TAC* tacGenerateOp(int type, TAC* op1, TAC* op2){
    return tacJoin(tacJoin(op1,op2),
									 tacCreate(type, makeTemp(), op1?op1->res:0, op2?op2->res:0));
//op1,
  //              tacJoin(op2, tacCreate(type, makeTemp(), op1?op1->res:0, op2?op2->res:0)));
}


TAC* makeIfThen(TAC* code0, TAC* code1) {
  TAC *iftac, *labeltac;
  HASH_NODE* newlabel = makeLabel();
  iftac = tacCreate(TAC_IFZ, newlabel,code0?code0->res:0,0);
  labeltac = tacCreate(TAC_LABEL, newlabel, 0,0);
  return tacJoin(tacJoin(tacJoin(code0,iftac),code1),labeltac);
}

TAC* makeIfThenElse(TAC* code0, TAC* code1, TAC* code2) {
  TAC *iftac, *jumptac, *labeltac, *labeltac2;
  HASH_NODE *newlabel, *newlabel2;
  newlabel = makeLabel();
  newlabel2 = makeLabel();
  iftac = tacCreate(TAC_IFZ, newlabel,code0?code0->res:0,0);
  labeltac = tacCreate(TAC_LABEL, newlabel, 0,0);
  jumptac = tacCreate(TAC_JMP, newlabel2, 0, 0);
  labeltac2 = tacCreate(TAC_LABEL, newlabel2, 0,0);
  return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(code0,iftac),code1),jumptac),labeltac),code2),labeltac2);
}

TAC* makeWhile(TAC* code0, TAC* code1) {
  TAC *iftac, *jumptac, *labeltac, *labeltac2, *movetac;
  HASH_NODE *newlabel, *newlabel2;
  newlabel = makeLabel();
  newlabel2 = makeLabel();
  iftac = tacCreate(TAC_IFZ, newlabel,code0?code0->res:0,0);
  labeltac = tacCreate(TAC_LABEL, newlabel, 0,0);
  jumptac = tacCreate(TAC_JMP, newlabel2, 0, 0);
  labeltac2 = tacCreate(TAC_LABEL, newlabel2, 0,0);
  return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(labeltac2,code0),iftac),code1),jumptac),labeltac);
}

TAC* makeFuncDec(TAC* type, TAC* params, TAC* cmdBlock, HASH_NODE *symbol) {
  TAC* beginf = tacCreate(TAC_BEGIN_FUN, symbol, 0, 0);
  TAC* endf = tacCreate(TAC_END_FUN, symbol, 0, 0);
  return tacJoin(tacJoin(tacJoin(tacJoin(type,params),beginf), cmdBlock), endf);
}

TAC* makeFunction(TAC* symbol, TAC* par, TAC* code)
{
	return tacJoin(tacJoin(tacJoin( tacCreate(TAC_BEGIN_FUN, symbol->res, 0, 0), par) , code ), tacCreate(TAC_END_FUN, symbol->res, 0, 0));
}


// .globl	FUN_NAME
// 			.type	FUN_NAME, @function
// 		FUN_NAME:
// 		.LFB1:
// 			.cfi_startproc
// 			pushq	%rbp\n.cfi_def_cfa_offset 16\n.cfi_offset 6, -16\nmovq	%rsp, %rbp\n.cfi_def_cfa_register 6\n
//
//       movl	$RET, %eax
// 			popq	%rbp\n.cfi_def_cfa 7, 8\nret\n.cfi_endproc\n.LFE1:\n.size	FUN_NAME, .-FUN_NAME
/*
  TODO - .LFB1 e .LFE1 precisam ser incrementados para suportar diversas funcoes
*/
void writeCode(TAC *code, FILE * assemblyCode){
  if(!code) return;


   if(code->type == TAC_BEGIN_FUN){
     fprintf(assemblyCode, "##TAC_BEGIN_FUN# \n"
                           "\n\t.globl %s\n"
                           "\t.type %s, @function\n%s:\n.LFB%d:\n"
                           "\t.cfi_startproc\n\tpushq	%%rbp\n"
                           "\t.cfi_def_cfa_offset 16\n"
                           "\t.cfi_offset 6, -16\n"
                           "\tmovq	%%rsp, %%rbp\n"
                           "\t.cfi_def_cfa_register 6\n",
     code->res->text,code->res->text,code->res->text, LFBid);
     LFBid++;
    }
    else if(code->type == TAC_END_FUN){
      fprintf(assemblyCode, "##TAC_END_FUN# \n"
                            "\tpopq	%%rbp\n"
                            "\t.cfi_def_cfa 7, 8\n"
                            "\tret\n"
                            "\t.cfi_endproc\n"
                            ".LFE%d:\n"
                            "\t.size	%s, .-%s\n",
      LFEid, code->res->text,code->res->text );
      LFEid++;
    }
    else if(code->type == TAC_RETURN){
      fprintf(assemblyCode, "## TAC_RETURN\n"
        "\tmovl	_%s(%%rip), %%eax\n" , code->op1->text);
    }
    else if (code->type == TAC_END_PRINT){
      fprintf(assemblyCode, "\tmovl	$.%s, %%edi\n"
              "\tmovl	$0, %%eax\n"
              "\tcall	printf\n",code->op1->text);
    }
    else if(code->type == TAC_MOVE){
      fprintf(assemblyCode, "\tmovl	_%s(%%rip), %%eax\n"
      "\tmovl	%%eax, _%s(%%rip)\n" , code->op1->text, code->res->text);
    }
    else if(code->type == TAC_ADD){
      fprintf(assemblyCode,
        "## TAC_ADD\n"
        "\tmovl	_%s(%%rip), %%edx\n"
        "\tmovl	_%s(%%rip), %%eax\n"
        "\taddl	%%eax, %%edx\n"
        "\tmovl	%%edx, _%s(%%rip)\n", code->op1->text,code->op2->text,code->res->text);
    }
    else if(code->type == TAC_SUB){
      
      fprintf(assemblyCode, "## TAC_SUB\n"
      "\tmovl	_%s(%%rip), %%edx\n"
      "\tmovl	_%s(%%rip), %%eax\n"
      "\tsubl	%%eax, %%edx\n"
      "\tmovl	%%edx, _%s(%%rip)\n", code->op1->text,code->op2->text,code->res->text);
    }
    else if(code->type == TAC_DIV){
      
      fprintf(assemblyCode, "## TAC_DIV\n"
      "\tmovl	_%s(%%rip), %%eax\n"
      "\tmovl	_%s(%%rip), %%ecx\n"
      "\tcltd\n"
      "\tidivl	%%ecx\n"
      "\tmovl	%%eax, _%s(%%rip)\n", code->op1->text,code->op2->text,code->res->text); 
    }
    else if(code->type == TAC_MUL){
 
      fprintf(assemblyCode,  "## TAC_MUL\n"
      "\tmovl	_%s(%%rip), %%edx\n"
      "\tmovl	_%s(%%rip), %%eax\n"       
      "\timull %%eax, %%edx\n"
      "\tmovl	%%edx, _%s(%%rip)\n", 
      code->op1->text,code->op2->text,code->res->text);
     
    }
    else if(code->type == TAC_EQ){
      fprintf(assemblyCode,"## TAC_EQ\n"
      "\tmovl	_%s(%%rip), %%edx\n"
      "\tmovl	_%s(%%rip), %%eax\n"
      "\tcmpl	%%eax, %%edx\n"
      "\tsete	%%al\n"
      "\tmovzbl	%%al, %%eax\n"
      "\tmovl	%%eax, _%s(%%rip)\n", code->op1->text,code->op2->text,code->res->text);
    }
    else if(code->type == TAC_NE){
      fprintf(assemblyCode, "## TAC_NE\n"
      "\tmovl	_%s(%%rip), %%edx\n"
      "\tmovl	_%s(%%rip), %%eax\n"
      "\tcmpl	%%eax, %%edx\n"
      "\tsetne	%%al\n"
      "\tmovzbl	%%al, %%eax\n"
      "\tmovl	%%eax, _%s(%%rip)\n", code->op1->text,code->op2->text,code->res->text);
    } 
    else if(code->type == TAC_NOT){

    }
    else if(code->type == TAC_OR){
      fprintf(assemblyCode, "##TAC_OR\n"
      "\tmovl	_%s(%%rip), %%eax\n"
      "\ttestl	%%eax, %%eax\n"
      "\tjne	.L%d\n"
      "\tmovl	_%s(%%rip), %%eax\n"
      "\ttestl	%%eax, %%eax\n"
      "\tje	.L%d\n"
      ".L%d:\n"
      "\tmovl	$1, %%eax\n" 
      "\tjmp	.L%d\n"
      ".L%d:\n"
      "\tmovl	$0, %%eax\n" 
      ".L%d:\n"
      "\tmovl	%%eax, _%s(%%rip)\n", code->op1->text, labelNmbr, code->op2->text, labelNmbr+1, labelNmbr, labelNmbr+2, labelNmbr+1, labelNmbr+2, code->res->text); 
      labelNmbr += 3;
    }
    else if(code->type == TAC_AND){
      fprintf(assemblyCode, "##TAC_AND\n"
      "\tmovl	_%s(%%rip), %%eax\n"
      "\ttestl	%%eax, %%eax\n"
      "\tje	.L%d\n"
      "\tmovl	_%s(%%rip), %%eax\n"
      "\ttestl	%%eax, %%eax\n"
      "\tje	.L%d\n"
      "\tmovl	$1, %%eax\n"  
      "\tjmp	.L%d\n"
      ".L%d:\n"
      "\tmovl	$0, %%eax\n" 
      ".L%d:\n"
      "\tmovl	%%eax, _%s(%%rip)\n", code->op1->text, labelNmbr, code->op2->text, labelNmbr, labelNmbr+1, labelNmbr, labelNmbr+1, code->res->text);
      labelNmbr += 2; 
    }
    else if(code->type == TAC_MORE){
      fprintf(assemblyCode, "##TAC_MORE \n"
      "\tmovl	_%s(%%rip), %%edx\n"
      "\tmovl	_%s(%%rip), %%eax\n"
      "\tcmpl	%%eax, %%edx\n"
      "\tsetg	%%al\n"
      "\tmovzbl	%%al, %%eax\n"
      "\tmovl	%%eax, _%s(%%rip)\n", code->op1->text, code->op2->text, code->res->text); 
    }
    else if(code->type == TAC_LESS){
      fprintf(assemblyCode, "##TAC_LESS"
      "\tmovl	_%s(%%rip), %%edx\n"
      "\tmovl	_%s(%%rip), %%eax\n"
      "\tcmpl	%%eax, %%edx\n"
      "\tsetl	%%al\n"
      "\tmovzbl	%%al, %%eax\n"
      "\tmovl	%%eax, _%s(%%rip)\n", code->op1->text, code->op2->text, code->res->text);
    }
    else if(code->type == TAC_GE){
      fprintf(assemblyCode, "##TAC_GE \n"
      "\tmovl	_%s(%%rip), %%edx\n"
      "\tmovl	_%s(%%rip), %%eax\n"
      "\tcmpl	%%eax, %%edx\n"
      "\tsetge	%%al\n"
      "\tmovzbl	%%al, %%eax\n"
      "\tmovl	%%eax, _%s(%%rip)\n", code->op1->text, code->op2->text, code->res->text);
    }
    else if(code->type == TAC_LE){
      fprintf(assemblyCode, "\tmovl	_%s(%%rip), %%edx\n"
      "\tmovl	_%s(%%rip), %%eax\n"
      "\tcmpl	%%eax, %%edx\n"
      "\tsetle	%%al\n"
      "\tmovzbl	%%al, %%eax\n"
      "\tmovl	%%eax, _%s(%%rip)\n", code->op1->text, code->op2->text, code->res->text);
    }
    else if(code->type == TAC_FUNC){
      fprintf(assemblyCode, "##TAC_FUNCALL \n"
      "\tcall	%s\n"
      "\tmovl	%%eax, _%s(%%rip)\n" , code->op1->text, code->res->text); parNmbr1 = 0;
    }
    else if(code->type == TAC_LABEL){
      fprintf(assemblyCode, "##TAC_LABEL \n"
        "\t.%s:\n" , code->res->text);
    }
    else if(code->type == TAC_JMP){
      fprintf(assemblyCode, "##TAC_LABEL \n"
        "\tjmp	.%s\n" , code->res->text);
    }
    else if(code->type == TAC_IFZ){
      fprintf(assemblyCode, "##TAC_IFZ \n"
      "\tmovl	_%s(%%rip), %%eax\n"
      "\ttestl	%%eax, %%eax\n"
      "\tjne	.L%d\n"
      "\tjmp	.%s\n"
      ".L%d:", code->op1->text, labelNmbr, code->res->text, labelNmbr); labelNmbr++;
    }
    else if(code->type == TAC_READ){
      fprintf(assemblyCode, "##TAC_READ \n"
      "\tmovl	$_%s, %%esi\n"
      "\tmovl	$.LC0, %%edi\n"
      "\tcall	__isoc99_scanf\n", code->res->text); 
    }

    else if(code->type == TAC_MOV_IND){
      fprintf(assemblyCode, "##TAC_MOV_IND\n"
      "\tmovl	_%s, %%eax\n"
      "\tmovl	_%s(%%rip), %%edx\n"
      "\tcltq\n"
      "\tmovl	%%edx, _%s(,%%rax,4)\n", code->op1->text, code->op2->text, code->res->text);
    }

    else if(code->type == TAC_PRINT){
      if(code->res->text[0] == '\"'){ 
        printf("STRING\n");
        fprintf(assemblyCode, "\tmovl	$.LC%d, %%edi\n"
        "\tmovl	$0, %eax\n"
        "\tcall	printf\n", lableLC); 
        lableLC++; 
      } else{			
        printf("VARIAVEL\n");				
        fprintf(assemblyCode, "\tmovl	_%s(%%rip), %%eax\n" 
        "\tmovl	%%eax, %%esi\n"
        "\tmovl	$.LC0, %%edi\n"
        "\tcall	printf\n", code->res->text); 
      }
    }

    writeCode(code->next, assemblyCode);

}
TAC * writePrint(TAC*code, FILE *assemblyCode){
  char *printString = calloc(1000,sizeof(char)); //a string do print

  while(code->type != TAC_END_PRINT){
    if(code->type == TAC_STRING){
      //precisa remover as aspas da string
      code->res->text[strlen(code->res->text)-1] = '\0'; //isso aqui ta certo, remove a ultima aspa
      code->res->text[0] = ' '; //isso aqui ta errado pq tira a aspa e bota um espaco no lugar
      strcat(printString,code->res->text);
    }else{
      strcat(printString,"%d");
    }
    // fprintf(assemblyCode, "\nmovl	%s(%%rip), %%ecx",code->res->text);
    code = code->next;
  }
  fprintf(assemblyCode, "\n.%s:\n.string \"%s\"",code->op1->text,printString);
  return code;
}

void generateTextArea(TAC *code,FILE *assemblyCode){
  if(!code) return;
  if(code->type == TAC_BEGIN_PRINT){
    code = writePrint(code->next,assemblyCode);
  }
  generateTextArea(code->next,assemblyCode);
}

void generateAssembly(TAC * code){
  FILE * assemblyCode = fopen("asm.s","a");
   //generateTextArea(code,assemblyCode);
   //fprintf(assemblyCode, "\n.text" );
  writeCode(code,assemblyCode);
  fclose(assemblyCode);
}

//
