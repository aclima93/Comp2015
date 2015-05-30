#include "node_t.h"
#include "sym_t.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Counts current local variables. Don't forget to reset it once we start a new method! */
unsigned int llvm_tmp_var_count = 0;

unsigned int llvm_return_label_count = 0;
unsigned int llvm_label_count = 0;

/* llvm_type_t shall be "i32", "i16", etc, as the LLVM IR requires */
typedef const char* llvm_type_t;

/* Gives us a valid local variable name that we can use, such as %1, %2 or %3 */
char* get_local_var_name() {
    char* buf = (char*)malloc(16);
    sprintf(buf, "%%%u", ++llvm_tmp_var_count);
    return buf;
}

void reset_local_vars() {
    llvm_tmp_var_count = 0;
}

void increase_return_label_count() {
    ++llvm_return_label_count;
}

char* get_current_return_label_name() {
    char* buf = (char*)malloc(64);
    sprintf(buf, ".return%u", llvm_return_label_count);
    return buf;
}

char* get_label_name() {
    char* buf = (char*)malloc(64);
    sprintf(buf, ".label%u", ++llvm_label_count);
    return buf;
}

/* This structure is passed around when we're outputting code. It represents a given type and "id"/representation of a node.
 llvm_var_t->repr stores the "representation", its name.
 llvm_var_t->type is the type of this node.
 
 Representation is useful because of situations where we need temporary and intermediate variables.
 For instance, assuming we have currently used 32 local variables (that is llvm_tmp_var_count = 32), the operation
 a + b + c
 will be turned into (this pseudo-LLVM IR) [note that we have left-associativity]
 %33 = a + b
 %34 = %33 +c
 
 NOTE: These pointers must be free()-able. strdup() all you want to make sure they're sittin' on the heap!
 */

typedef struct _llvm_var_t {
    char* repr; /* Representation: %1,@1, etc... */
    ijavatype_t type; /* TYPE_INTARRAY, TYPE_INT... */
    int value; /* To specify if it's a raw value instead of a pointer */
} llvm_var_t;

llvm_var_t* llvm_var_create() {
    llvm_var_t* ret = (llvm_var_t*)malloc( sizeof (llvm_var_t));
    ret->value = 0;
    ret->type = TYPE_UNKNOWN;
    ret->repr = NULL;
    
    return ret;
}

/* Frees an llvm_var_t */
void llvm_var_free(llvm_var_t* self) {
    if ( self->repr != NULL ) free(self->repr);
    free(self);
}

/* Prints an LLVM binary op to stdout. Note that we always store the result even if we never use it.
 Inefficient? I call it inefficient to have Mooshak's tests coming out less than one week away from the submission date!! */
void llvm_bin_op(const char* op, llvm_type_t type, char* lhs, char* arg1, char* arg2) {
    printf("%s = %s %s %s, %s\n", lhs, op, type, arg1, arg2);
}

void llvm_file_header() {
    printf("%%.IntArray = type { i32, i32* }\n");
    printf("%%.BoolArray = type { i32, i1* }\n");
    printf("declare i32 @printf(i8*, ...)\n");
    printf("declare i32 @atoi(i8*) nounwind readonly\n");
    printf("declare noalias i8* @malloc(i32) nounwind\n");
    printf("declare noalias i8* @calloc(i32, i32) nounwind");
    printf("@str.printf_callstr = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\"\n");
    printf("@str.false_str = private unnamed_addr constant [7 x i8] c\"false\\0A\\00\"\n");
    printf("@str.true_str = private unnamed_addr constant [7 x i8] c\"true\\0A\\00\\00\"\n");
    printf("@str.bools_array = global [2 x i8*] [i8* getelementptr inbounds ([7 x i8]* @str.false_str, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8]* @str.true_str, i32 0, i32 0)]\n");
}



/* Prints an LLVM unary op to stdout (might not correspond to an ijava unary op */
void llvm_unary_op(const char* op, llvm_type_t type, char* val) {
    printf("%s %s %s\n", op, type, val);
}

/* Used to convert TYPE_INT, TYPE_BOOL, TYPE_INTLIT, etc to their llvm_type_t types */
const char* llvm_types_from_ijavatypes[]  = {
    "i32" /* TYPE_INT */,
    "i1" /* TYPE_BOOL */,
    "%.IntArray" /* TYPE_INTARRAY */,
    "%.BoolArray" /* TYPE_BOOLARRAY */,
    "i8**" /* TYPE_STRINGARRAY */,
    "void" /*TYPE_VOID*/,
    "NOT_EXPECTED_ID" /* TYPE_STRINGARRAY */,
    "i32" /* TYPE_INTLIT */,
    "i1" /* TYPE_BOOLLIT */,
    "i8*" /* TYPE_STRING */,
    "NOT_EXPECTED_METHOD" /* TYPE_METHOD */,
    "NOT_EXPECTED_UNKNOWN" /* TYPE_UNKNOWN */
};

const char* llvm_type_from_ijavatype(ijavatype_t type) {
    return llvm_types_from_ijavatypes[type];
}

void llvm_declare_global_onetype(const char* type, const char* name) {
    printf("@%s = global %s 0, align 4\n", name, type);
}

void llvm_declare_global_array(const char* type, const char* name) {
    printf("@%s = global %s zeroinitializer, align 8\n", name, type);
}

void llvm_declare_global(ijavatype_t type, const char* name) {
    if ( type == TYPE_INTARRAY || type == TYPE_BOOLARRAY )
        return llvm_declare_global_array(llvm_type_from_ijavatype(type), name);
    else
        return llvm_declare_global_onetype(llvm_type_from_ijavatype(type), name);
}

void llvm_declare_local_onetype(ijavatype_t ijava_type, const char* name) {
    const char* type = llvm_type_from_ijavatype(ijava_type);
    if ( *name == '%' ) name++; /* Skip over '%' which might be extra */
    printf("%%%s = alloca %s, align 4\n", name, type);
    printf("store %s 0, %s* %%%s\n", type, type, name);
}

void llvm_declare_local_array(ijavatype_t ijava_type, const char* name) {
    if ( *name == '%' ) name++; /* Skip over '%' which might be extra */
    const char* type = llvm_type_from_ijavatype(ijava_type);
    
    /*FIXME: Join the common parts of the if-else operations??*/
    if ( ijava_type == TYPE_INTARRAY ) {
        
        printf("%%%s = alloca %s, align 8\n", name, type);
        printf("%%.array.%s = getelementptr inbounds %s* %%%s, i32 0, i32 0\n", name, type, name);
        printf("store i32 0, i32* %%.array.%s, align 4\n", name);
        printf("%%..array.%s = getelementptr inbounds %s* %%%s, i32 0, i32 1\n", name, type, name);
        printf("store i32* null, i32** %%..array.%s, align 8\n", name);
        /*
         %array = alloca %.IntArray, align 8
         %.1 = getelementptr inbounds %.IntArray* %array, i32 0, i32 0
         store i32 40, i32* %.1, align 4
         %..1 = getelementptr inbounds %.IntArray* %array, i32 0, i32 1
         store i32* null, i32** %..1, align 8
         */
    } else if ( ijava_type == TYPE_BOOLARRAY ) {
        
        printf("%%%s = alloca %s, align 8\n", name, type);
        printf("%%.array.%s = getelementptr inbounds %s* %%%s, i32 0, i32 0\n", name, type, name);
        printf("store i32 0, i32* %%.array.%s, align 4\n", name);
        printf("%%..array.%s = getelementptr inbounds %s* %%%s, i32 0, i32 1\n", name, type, name);
        printf("store i1* null, i1** %%..array.%s, align 8\n", name);
        
        /*
         %array = alloca %.BoolArray, align 8
         %.1 = getelementptr inbounds %.BoolArray* %array, i32 0, i32 0
         store i32 40, i32* %.1, align 4
         %..1 = getelementptr inbounds %.BoolArray* %array, i32 0, i32 1
         store i1* null, i1** %..1, align 8
         */
        
    }
}

void llvm_storearray(llvm_var_t* array_loaded, llvm_var_t* index_loaded, llvm_var_t* value_loaded) {
    char* array_data_name = get_local_var_name();
    char* index_ptr_name = get_local_var_name();
    const char* type = llvm_type_from_ijavatype(array_loaded->type);
    const char* value_type = llvm_type_from_ijavatype(value_loaded->type);
    printf("%s = extractvalue %s %s, 1\n", array_data_name, type, array_loaded->repr);
    printf("%s = getelementptr %s* %s, i32 %s\n", index_ptr_name, value_type, array_data_name, index_loaded->repr);
    printf("store %s %s, %s* %s\n", value_type, value_loaded->repr, value_type, index_ptr_name);
    
    free(array_data_name);
    free(index_ptr_name);
}


/* DON'T CONFUSE THIS WITH THE LOADARRAY OPERATION! */
char* llvm_loadarray(llvm_var_t* src, llvm_var_t* index) {
    assert(src); assert(index);
    ijavatype_t elementtype = src->type == TYPE_INTARRAY ? TYPE_INT : TYPE_BOOL;
    const char* arraytype = llvm_type_from_ijavatype(src->type);
    const char* value_type = llvm_type_from_ijavatype(index->type);
    const char* element_type = llvm_type_from_ijavatype(elementtype);
    
    char* array_data_name = get_local_var_name();
    char* index_ptr_name = get_local_var_name();
    char* loaded = get_local_var_name();
    
    printf("%s = extractvalue %s %s, 1\n", array_data_name, arraytype, src->repr);
    printf("%s = getelementptr %s* %s, %s %s\n", index_ptr_name, element_type, array_data_name, value_type, index->repr);
    printf("%s = load %s* %s\n", loaded, element_type, index_ptr_name);
    
    free(array_data_name);
    free(index_ptr_name);
    
    return loaded;
}

llvm_var_t* llvm_array_get_index(llvm_var_t* array_loaded, llvm_var_t* index_loaded) {
    ijavatype_t elementtype = array_loaded->type == TYPE_INTARRAY ? TYPE_INT : TYPE_BOOL;
    
    char* arraydata = llvm_loadarray(array_loaded, index_loaded);
    llvm_var_t* ret = llvm_var_create(); ret->type = elementtype; ret->value = 1;
    
    ret->repr = arraydata;
    
    return ret;
}

char* llvm_length_from_array(llvm_var_t* array) {
    const char* arraytype = llvm_type_from_ijavatype(array->type);
    
    char* array_data_name = get_local_var_name();
    
    printf("%s = extractvalue %s %s, 0\n", array_data_name, arraytype, array->repr);
    
    return array_data_name;
}

void llvm_declare_local(ijavatype_t type, char* id) {
    if ( type == TYPE_INTARRAY || type == TYPE_BOOLARRAY )
        llvm_declare_local_array(type, id);
    else
        llvm_declare_local_onetype(type, id);
}

void llvm_label(char* label) {
    printf("%s:\n", label);
}

void llvm_store_names_types(char* dest, char* src, ijavatype_t ijavatype) {
    assert(src); assert(dest);
    const char* type = llvm_type_from_ijavatype(ijavatype);
    printf("store %s %s, %s* %s\n", type, src, type, dest);
}

void llvm_store(llvm_var_t* dest, llvm_var_t* src) {
    assert(src); assert(dest); assert(src->type == dest->type);
    llvm_store_names_types(dest->repr, src->repr, src->type);
}


void llvm_define_function(sym_t* function_table) {
    assert(function_table);
    ijavatype_t return_type = function_table->next->type;
    if ( return_type == TYPE_VOID ) return_type = TYPE_INT;
    printf("define %s @%s(", llvm_type_from_ijavatype(return_type), function_table->id);
    
    sym_t* current;
    /* Start at next->next to skip return value */
    for ( current = function_table->next->next; current != NULL; current = current->next ) {
        
        if ( current->is_parameter ) {
            if(current->type == TYPE_STRINGARRAY)
                printf("i32 %%args.length, %s %%args", llvm_type_from_ijavatype(current->type));
            else
                printf("%s %%.%s", llvm_type_from_ijavatype(current->type), current->id);
        }
        
        /* Print comma if there is one more parameter */
        if ( current->next && current->next->is_parameter ) printf(", ");
    }
    
    printf(") {\n");
}

void llvm_declare_locals(sym_t* function_table) {
    sym_t* current;
    /* Start at next->next to skip return value */
    for ( current = function_table->next->next; current != NULL; current = current->next )
        if ( !current->is_parameter )
            llvm_declare_local(current->type, current->id);
        else {
            if ( current->type == TYPE_STRINGARRAY) continue;
            char* buf_in = (char*)malloc(strlen(current->id)+2);
            char* buf_out = (char*)malloc(strlen(current->id)+2);
            sprintf(buf_in,"%%.%s", current->id);
            sprintf(buf_out,"%%%s", current->id);
            llvm_declare_local(current->type, current->id);
            llvm_store_names_types(buf_out, buf_in, current->type);
            free(buf_in);
            free(buf_out);
        }
}

void llvm_goto_nonewlabel(char* label) {
    printf("br label %%%s\n", label);
}

void llvm_goto(char* label) {
    llvm_goto_nonewlabel(label);
    
    char* newlabel = get_label_name();
    llvm_label(newlabel);
    free(newlabel);
}


void llvm_load(char* loaded, llvm_var_t* src) {
    assert(loaded); assert(src);
    const char* type = llvm_type_from_ijavatype(src->type);
    printf("%s = load %s* %s\n", loaded, type, src->repr);
}

void llvm_function_prologue(ijavatype_t ret) {
    if ( ret == TYPE_VOID ) ret = TYPE_INT;
    
    llvm_declare_local(ret, "return");
    increase_return_label_count();
}

/* We need to do some hacky stuff. First we need to have at least one reference to the return label, so
 we add a goto. Then, we need to return the value stored at return. Since return is on the stack,
 we must load it onto another variable (we chose .return) and this is what we return
 */
void llvm_function_epilogue(ijavatype_t ret) {
    char* label = get_current_return_label_name();
    if ( ret == TYPE_VOID ) ret = TYPE_INT;
    llvm_var_t* return_val = llvm_var_create(); return_val->repr=strdup("%return"); return_val->type = ret;
    llvm_goto_nonewlabel(label);
    llvm_label(label);
    llvm_load("%.return_final", return_val);
    printf("ret %s %%.return_final\n", llvm_type_from_ijavatype(ret));
    free(label);
    printf("}\n");
    llvm_var_free(return_val);
}


llvm_var_t* llvm_get_value_from_ptr_or_value(llvm_var_t* var) {
    assert(var);
    llvm_var_t* var_loaded = llvm_var_create();
    
    if ( var->value ) {
        var_loaded->type = var->type; var_loaded->value = 1;
        var_loaded->repr = strdup(var->repr);
    }
    else {
        var_loaded->type = var->type; var_loaded->value = 1;
        var_loaded->repr = get_local_var_name();
        llvm_load(var_loaded->repr, var);
    }
    
    return var_loaded;
}


void llvm_return(ijavatype_t ret, llvm_var_t* var) {
    char* label = get_current_return_label_name();
    
    if ( ret == TYPE_VOID ) {
        /* Do nothing */
    } else {
        assert(ret == var->type);
        llvm_store_names_types("%return", var->repr, ret);
    }
    
    llvm_goto(label);
    free(label);
}

void llvm_icmp(const char* comparison, char* dest, char* op1, char* op2, const char* type) {
    printf("%s = icmp %s %s %s, %s\n", dest, comparison, type, op1, op2);
}

void llvm_br(char* condvar, char* labelthen, char* labelelse) {
    printf("br i1 %s, label %%%s, label %%%s\n", condvar, labelthen, labelelse);
}

#define RETURN_LOADABLE(x) do { llvm_var_t* x ## _loaded = llvm_get_value_from_ptr_or_value(x); llvm_var_free(x); return x ## _loaded; } while(0)

void llvm_recurse_down(node_t* iter, sym_t* class_table, sym_t* table_method);

llvm_var_t* llvm_node_to_instr_binop(node_t* node, sym_t* class_table, sym_t* curr_method_table);
llvm_var_t* llvm_node_to_instr_node_type(node_t* node, sym_t* class_table, sym_t* curr_method_table);
llvm_var_t* llvm_node_to_instr_unop(node_t* node, sym_t* class_table, sym_t* curr_method_table);
llvm_var_t* llvm_node_to_instr_return(node_t* node, sym_t* class_table, sym_t* curr_method_table);
llvm_var_t* llvm_node_to_instr_store(node_t* node, sym_t* class_table, sym_t* curr_method_table);
llvm_var_t* llvm_node_to_instr_ifelse(node_t* node, sym_t* class_table, sym_t* curr_method_table);
llvm_var_t* llvm_node_to_instr_while(node_t* node, sym_t* class_table, sym_t* curr_method_table);
llvm_var_t* llvm_node_to_instr_call(node_t* node, sym_t* class_table, sym_t* curr_method_table);
llvm_var_t* llvm_node_to_instr_storearray(node_t* node, sym_t* class_table, sym_t* curr_method_table);
llvm_var_t* llvm_node_to_instr_loadarray(node_t* node, sym_t* class_table, sym_t* curr_method_table);
llvm_var_t* llvm_node_to_instr_print(node_t* node, sym_t* class_table, sym_t* curr_method_table);
llvm_var_t* llvm_node_to_instr_length(node_t* node, sym_t* class_table, sym_t* curr_method_table);
llvm_var_t* llvm_node_to_instr_parseargs(node_t* node, sym_t* class_table, sym_t* curr_method_table);
llvm_var_t* llvm_node_to_instr_new(node_t* node, sym_t* class_table, sym_t* curr_method_table);

/* This is generic and it just binds the several cases we have: binops, types (which end recursion), and others */
/* This function works just like get_tree_type() in semantic analysis. It (indirecty) recurses down a statement,
 except instead of just parsing the code, it outputs LLVM IR */
llvm_var_t* llvm_node_to_instr(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node);
    if ( is_binary_oper(node->nodetype) )
        return llvm_node_to_instr_binop(node, class_table, curr_method_table);
    else if ( is_unary_oper(node->nodetype) )
        return llvm_node_to_instr_unop(node, class_table, curr_method_table);
    else if ( node->nodetype == NODE_TYPE )
        return llvm_node_to_instr_node_type(node, class_table, curr_method_table);
    else if ( node->nodetype == NODE_STATEMENT_RETURN )
        return llvm_node_to_instr_return(node, class_table, curr_method_table);
    else if ( node->nodetype == NODE_STATEMENT_STORE )
        return llvm_node_to_instr_store(node, class_table, curr_method_table);
    else if ( node->nodetype == NODE_STATEMENT_IFELSE )
        return llvm_node_to_instr_ifelse(node, class_table, curr_method_table);
    else if ( node->nodetype == NODE_STATEMENT_WHILE )
        return llvm_node_to_instr_while(node, class_table, curr_method_table);
    else if ( node->nodetype == NODE_OPER_CALL )
        return llvm_node_to_instr_call(node, class_table, curr_method_table);
    else if ( node->nodetype == NODE_STATEMENT_STOREARRAY )
        return llvm_node_to_instr_storearray(node, class_table, curr_method_table);
    else if ( node->nodetype == NODE_STATEMENT_PRINT )
        return llvm_node_to_instr_print(node, class_table, curr_method_table);
    else if ( node->nodetype == NODE_STATEMENT_COMPOUNDSTATEMENT )
        llvm_recurse_down(node->n1, class_table, curr_method_table);
    
    return NULL;
}


/* Used to convert the operations represented by nodes into LLVM IR operations. for instance,
 we map NODE_ADD to "add" */
const char* llvm_node_to_nodetype [] = {
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen", /* NODE_STATEMENT_IFELSE, */
    "null_should_not_happen", /* NODE_STATEMENT_PRINT, */
    "null_should_not_happen", /*NODE_STATEMENT_RETURN, */
    "null_should_not_happen", /*NODE_STATEMENT_STORE, */
    "null_should_not_happen", /*NODE_STATEMENT_STOREARRAY, */
    "null_should_not_happen", /*NODE_STATEMENT_WHILE, */
    "or",
    "and",
    "eq",
    "ne",
    "slt",
    "sgt",
    "sle",
    "sge",
    "add",
    "sub",
    "mul",
    "sdiv",
    "srem",
    "xor",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen",
    "null_should_not_happen"
};

const char* llvm_get_op_from_node(node_t* node) {
    assert(node);
    
    return llvm_node_to_nodetype [node->nodetype];
}


llvm_var_t* llvm_node_to_instr_binop_relational(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    /* Declare result, which will hold the answer */
    llvm_var_t* result = llvm_var_create(); result->type = TYPE_BOOL; result->repr=get_local_var_name(); result->value=0;
    llvm_var_t* a, *b;
    llvm_declare_local(TYPE_BOOL, result->repr);
    
    if ( node->nodetype == NODE_OPER_AND ) {
        /* Implement short circuiting */
        /* a && b becomes
         result = a;
         if ( result ) result = b;
         */
        char* labelthen = get_label_name();
        char* labelendifelse = get_label_name();
        
        a = llvm_node_to_instr(node->n1, class_table, curr_method_table);   /* get "%a" */
        llvm_store(result, a);                                       /* result = a */
        
        llvm_var_t* result_loaded = llvm_get_value_from_ptr_or_value(result);
        llvm_br(result_loaded->repr, labelthen, labelendifelse);                   /* if ( result ) goto labelthen; else goto labelendifelse; */
        llvm_label(labelthen);                                              /* labelthen: */
        b = llvm_node_to_instr(node->n2, class_table, curr_method_table); /* get "%b" */
        
        llvm_var_free(result_loaded);
        llvm_store(result, b);                                       /* result = a */                                          /* result = b */
        llvm_goto_nonewlabel(labelendifelse);                                        /* goto labelendifelse; */
        llvm_label(labelendifelse);                                         /* labelendifelse: */
        free(labelthen); free(labelendifelse);
        /*llvm_var_free(loaded_b);*/
    } else if  ( node->nodetype == NODE_OPER_OR ) {
        /* Implement short circuiting */
        /* a || b becomes
         result = a;
         if ( !result ) result = b;
         */
        char* labelthen = get_label_name();
        char* labelendifelse = get_label_name();
        
        a = llvm_node_to_instr(node->n1, class_table, curr_method_table); /* get "%a" */
        llvm_store(result, a); /* tmp = a */
        
        llvm_var_t* result_loaded = llvm_get_value_from_ptr_or_value(result);
        llvm_var_t* notresult = llvm_var_create(); notresult->type = TYPE_BOOL; notresult->repr=get_local_var_name(); notresult->value = 1;
        
        llvm_bin_op("xor", "i1", notresult->repr, result_loaded->repr, "true");    /* notresult = result xor true //// same as notresult = !result */
        llvm_var_free(result_loaded);
        llvm_br(notresult->repr, labelthen, labelendifelse);                /* if ( notresult ) goto labelthen; else goto labelendifelse; */
        llvm_label(labelthen);                                              /* labelthen: */
        b = llvm_node_to_instr(node->n2, class_table, curr_method_table); /* get "%b" */
        llvm_store(result, b);                                            /* tmp = b */
        llvm_goto_nonewlabel(labelendifelse);                                        /* goto labelendifelse; */
        llvm_label(labelendifelse);                                         /* labelendifelse: */
        
        free(labelthen); free(labelendifelse);
    } else {
        a = llvm_node_to_instr(node->n1, class_table, curr_method_table);        /* Evaluate first operand */
        b = llvm_node_to_instr(node->n2, class_table, curr_method_table);        /* Evaluate second operand */
        
        char* tmp = get_local_var_name();
        
        llvm_icmp(llvm_get_op_from_node(node), tmp, a->repr, b->repr, llvm_type_from_ijavatype(a->type));  /* Store comparison in result */
        llvm_store_names_types(result->repr, tmp, TYPE_BOOL);
    }
    
    llvm_var_free(a);
    llvm_var_free(b);
    
    RETURN_LOADABLE(result);
}

/* Currently only does arithmetic */
llvm_var_t* llvm_node_to_instr_binop(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node);
    assert(node->n1);
    assert(node->n2);
    
    if ( is_binary_op_boolean(node->nodetype) )
        return llvm_node_to_instr_binop_relational(node, class_table, curr_method_table);
    else if ( node->nodetype == NODE_OPER_LOADARRAY) {
        return llvm_node_to_instr_loadarray(node, class_table, curr_method_table);
    }
    else if (node->nodetype == NODE_OPER_PARSEARGS) {
        return llvm_node_to_instr_parseargs(node, class_table, curr_method_table);
    } else {
        llvm_var_t* ret = llvm_var_create();
        
        /* Recurse down and find the variables that will be our operands */
        llvm_var_t* op1 = llvm_node_to_instr(node->n1, class_table, curr_method_table);
        llvm_var_t* op2 = llvm_node_to_instr(node->n2, class_table, curr_method_table);
        
        /* Get a nice juicy name for ourselves */
        ret->repr = get_local_var_name();
        
        /* Get the type from the previously calculated "tree_type". Avoids having a fixed table where we map operations to their output sizes */
        ret->type = node->tree_type;
        
        ret->value = 1;
        
        /* Output the binary op code */
        llvm_bin_op(llvm_get_op_from_node(node), llvm_type_from_ijavatype(ret->type), ret->repr, op1->repr, op2->repr);
        llvm_var_free(op1);
        llvm_var_free(op2);
        
        RETURN_LOADABLE(ret);
    }
    
    
}

/* Currently only does arithmetic */
llvm_var_t* llvm_node_to_instr_unop(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node);
    assert(node->n1);
    
    if ( node->nodetype == NODE_OPER_LENGTH )
        return llvm_node_to_instr_length(node, class_table, curr_method_table);
    else if ( node->nodetype == NODE_OPER_NEWINT || node->nodetype == NODE_OPER_NEWBOOL )
        return llvm_node_to_instr_new(node, class_table, curr_method_table);
    
    llvm_var_t* ret = llvm_var_create();
    const char* op;
    llvm_var_t* op1 = llvm_var_create();
    
    if      ( node->nodetype == NODE_OPER_PLUS )  { op = "add"; op1->repr = strdup("0");    op1->type = TYPE_INT;  op1->value = 1;}
    else if ( node->nodetype == NODE_OPER_MINUS ) { op = "sub"; op1->repr = strdup("0");    op1->type = TYPE_INT;   op1->value = 1;}
    else if ( node->nodetype == NODE_OPER_NOT )   { op = "xor"; op1->repr = strdup("true"); op1->type = TYPE_BOOL;  op1->value = 1; }
    
    /* Recurse down and find the variables that will be our operands */
    llvm_var_t* op2 = llvm_node_to_instr(node->n1, class_table, curr_method_table);
    
    
    /* Get a nice juicy name for ourselves */
    ret->repr = get_local_var_name();
    
    ret->type = node->tree_type;
    
    ret->value = 1;
    
    /* Output the binary op code */
    llvm_bin_op(op, llvm_type_from_ijavatype(ret->type), ret->repr, op1->repr, op2->repr);
    llvm_var_free(op1);
    llvm_var_free(op2);
    
    RETURN_LOADABLE(ret);
}

void llvm_lookup_symbol_from_table(llvm_var_t* ret, char* id, sym_t* class_table, sym_t* curr_method_table) {
    
    assert(ret);
    assert(id);
    assert(class_table);
    
    int local;
    
    sym_t* result = lookup_symbol(class_table, curr_method_table, id, &local);
    
    ret->type = result->type;
    
    ret->repr = (char *)malloc((2 + strlen(id))*sizeof(char));
    
    ret->value = 0;
    
    assert((local == 0 || local == 1));/*SHOULD NOT BE NEEDED BUT LET'S KEEP IT SAFE*/
    
    sprintf(ret->repr, "%s%s", local==1 ? "%" : "@", id);
}

llvm_var_t* llvm_node_to_instr_node_type(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node->nodetype == NODE_TYPE);
    assert(node->type == TYPE_INTLIT || node->type == TYPE_BOOLLIT || node->type == TYPE_ID);
    int value;
    llvm_var_t* ret = llvm_var_create();
    
    if ( node->type == TYPE_ID ) {
        
        llvm_lookup_symbol_from_table(ret, node->id, class_table, curr_method_table);
    } else if ( node->type == TYPE_BOOLLIT) {
        ret->type = TYPE_BOOL;
        ret->repr = get_local_var_name();
        printf("%s = add i1 0, %d\n", ret->repr, node->id[0] == 't' ? 1 : 0);
        ret->value = 1;
        
    } else {
        char* val;
        ret->type = TYPE_INT;
        ret->repr = get_local_var_name();
        
        value = check_intlit(node->id);
        
        printf("%s = add i32 0, %d\n", ret->repr, value);
        ret->value = 1;
    }
    
    if ( ret->type == TYPE_STRINGARRAY )
        return ret;
    else
        RETURN_LOADABLE(ret);
}


llvm_var_t* llvm_node_to_instr_return(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node);
    ijavatype_t ret = get_return_type(curr_method_table);
    
    
    if ( ret == TYPE_VOID ) {
        llvm_return(ret, NULL);
    }  else {
        llvm_var_t* val = llvm_node_to_instr(node->n1, class_table, curr_method_table);
        llvm_return(ret, val);
        llvm_var_free(val);
    }
    return NULL;
}

llvm_var_t* llvm_node_to_instr_store(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node);
    assert(node->n1);
    assert(node->n2);
    llvm_var_t* src = llvm_node_to_instr(node->n2, class_table, curr_method_table);
    llvm_var_t* dest = llvm_var_create(); llvm_lookup_symbol_from_table(dest, node->n1->id, class_table, curr_method_table);
    
    llvm_var_t* src_loaded = llvm_get_value_from_ptr_or_value(src);
    llvm_store(dest, src_loaded);
    llvm_var_free(src);
    llvm_var_free(src_loaded);
    llvm_var_free(dest);
    return NULL;
}

llvm_var_t* llvm_node_to_instr_ifelse(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node); assert(node->n1); assert(node->n2); assert(node->n3);
    char* labelthen = get_label_name();
    char* labelelse = get_label_name();
    char* labelendifelse = get_label_name();
    
    llvm_var_t* cond = llvm_node_to_instr(node->n1, class_table, curr_method_table);
    llvm_br(cond->repr, labelthen, labelelse);
    llvm_label(labelthen);
    if (node->n2->nodetype != NODE_NULL ) llvm_recurse_down(node->n2, class_table, curr_method_table);
    llvm_goto_nonewlabel(labelendifelse);
    llvm_label(labelelse);
    if (node->n3->nodetype != NODE_NULL ) llvm_recurse_down(node->n3, class_table, curr_method_table);
    llvm_goto_nonewlabel(labelendifelse);
    llvm_label(labelendifelse);
    
    llvm_var_free(cond);
    free(labelthen); free(labelelse); free(labelendifelse);
    return NULL;
}

llvm_var_t* llvm_node_to_instr_while(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node); assert(node->n1); assert(node->n2);
    char* labelwhile = get_label_name();
    char* labelwhilebody = get_label_name();
    char* labelendifelse = get_label_name();
    
    
    llvm_goto_nonewlabel(labelwhile);
    llvm_label(labelwhile);
    llvm_var_t* cond = llvm_node_to_instr(node->n1, class_table, curr_method_table);
    llvm_br(cond->repr, labelwhilebody, labelendifelse);
    llvm_label(labelwhilebody);
    if (node->n2->nodetype != NODE_NULL ) llvm_recurse_down(node->n2, class_table, curr_method_table);
    llvm_goto_nonewlabel(labelwhile);
    llvm_label(labelendifelse);
    
    llvm_var_free(cond);
    free(labelwhile); free(labelwhilebody );free(labelendifelse);
    return NULL;
}

llvm_var_t* llvm_node_to_instr_call(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node);
    assert(node->n1);
    assert(node->n1->nodetype == NODE_TYPE && node->n1->type == TYPE_ID);
    
    ijavatype_t return_type = lookup_return_type(class_table, node->n1->id);
    assert(return_type != TYPE_VOID);
    llvm_var_t* function = llvm_var_create();
    llvm_lookup_symbol_from_table(function, node->n1->id, class_table, NULL); /* NULL indicates we want a function */
    
    llvm_var_t* ret = llvm_var_create(); ret->value = 1; ret->type = return_type;
    
    sym_t* function_table = lookup_method(class_table, node->n1->id)->next->next;
    sym_t* current;
    int num_vars = 0;
    for ( current = function_table; current != NULL; current = current->next )
        if ( current->is_parameter )
            num_vars++;
    
    llvm_var_t** variables = (llvm_var_t**)malloc(num_vars * sizeof(llvm_var_t*));
    
    int i = 0;
    node_t* arguments = node->n2;
    for ( current = function_table; current != NULL; current = current->next ) {
        if ( current->is_parameter ) {
            variables[i++] = llvm_node_to_instr(arguments, class_table, curr_method_table);
            arguments = arguments->next;
        }
    }
    
    
    ret->repr = get_local_var_name();
    printf("%s = call %s (", ret->repr, llvm_type_from_ijavatype(return_type));
    
    for ( i = 0; i < num_vars; i++) {
        printf("%s", llvm_type_from_ijavatype(variables[i]->type));
        
        if ( i != num_vars-1 ) printf(", ");
    }
    
    printf(")* %s(", function->repr);
    
    for ( i = 0; i < num_vars; i++) {
        printf("%s %s", llvm_type_from_ijavatype(variables[i]->type), variables[i]->repr);
        if ( i != num_vars-1 ) printf(", ");
        llvm_var_free(variables[i]);
        
    }
    
    printf(")\n");
    free(variables);
    
    
    
    RETURN_LOADABLE(ret);
}

llvm_var_t* llvm_node_to_instr_storearray(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node);
    assert(node->n1);
    assert(node->n2);
    assert(node->n3);
    
    llvm_var_t* id = llvm_node_to_instr(node->n1, class_table, curr_method_table);
    llvm_var_t* index = llvm_node_to_instr(node->n2, class_table, curr_method_table);
    llvm_var_t* value = llvm_node_to_instr(node->n3, class_table, curr_method_table);
    
    llvm_storearray(id, index, value);
    
    llvm_var_free(id);
    llvm_var_free(index);
    llvm_var_free(value);
    
    return NULL;
}

llvm_var_t* llvm_node_to_instr_loadarray(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node);
    assert(node->n1);
    assert(node->n2);
    
    llvm_var_t* id = llvm_node_to_instr(node->n1, class_table, curr_method_table);
    llvm_var_t* index = llvm_node_to_instr(node->n2, class_table, curr_method_table);
    
    llvm_var_t* ret = llvm_array_get_index(id, index);
    
    llvm_var_free(id);
    llvm_var_free(index);
    
    return ret;
}

llvm_var_t* llvm_node_to_instr_print(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node);
    assert(node->n1);
    
    llvm_var_t* toprint = llvm_node_to_instr(node->n1, class_table, curr_method_table);
    
    if ( toprint->type == TYPE_INT) {
        char* callval = get_local_var_name();
        printf("%s = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @str.printf_callstr, i32 0, i32 0), i32 %s)\n", callval, toprint->repr);
        free(callval);
    } else {
        char* cast = get_local_var_name();
        char* index = get_local_var_name();
        char* value = get_local_var_name();
        char* callval = get_local_var_name();
        printf("%s = zext i1 %s to i32\n", cast, toprint->repr);
        printf("%s = getelementptr inbounds [2 x i8*]* @str.bools_array, i32 0, i32 %s\n", index, cast);
        printf("%s = load i8** %s\n", value, index);
        printf("%s = call i32 (i8*, ...)* @printf(i8* %s)\n", callval, value);
        free(cast);
        free(index);
        free(value);
        free(callval);
    }
    
    llvm_var_free(toprint);
    
    return NULL;
}

llvm_var_t* llvm_node_to_instr_length(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node);
    assert(node->n1);
    
    llvm_var_t* id = llvm_node_to_instr(node->n1, class_table, curr_method_table);
    llvm_var_t* ret = llvm_var_create(); ret->type = TYPE_INT; ret->value = 1;
    if ( id->type == TYPE_STRINGARRAY ) {
        char* name = id->repr;
        name++; /* Skip over % */
        ret->repr = get_local_var_name();
        llvm_bin_op("sub", "i32", ret->repr, "%args.length", "1");
    } else {
        ret->repr = llvm_length_from_array(id);
    }
    
    llvm_var_free(id);
    
    RETURN_LOADABLE(ret);
}

llvm_var_t* llvm_node_to_instr_parseargs(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node);
    assert(node->n1);
    assert(node->n2);
    
    llvm_var_t* val = llvm_node_to_instr(node->n2, class_table, curr_method_table);
    
    char* plus_one = get_local_var_name();
    llvm_bin_op("add", "i32", plus_one, val->repr, "1");
    llvm_var_free(val);
    
    
    char* index = get_local_var_name();
    char* loaded = get_local_var_name();
    llvm_var_t* ret = llvm_var_create(); ret->repr = get_local_var_name(); ret->type = TYPE_INT; ret->value = 1;
    printf("%s= getelementptr inbounds i8** %%args, i32 %s\n", index, plus_one);
    printf("%s = load i8** %s\n", loaded, index);
    printf("%s = call i32 @atoi(i8* %s) nounwind readonly\n", ret->repr, loaded);
    
    free(index); free(loaded); free(plus_one);
    RETURN_LOADABLE(ret);
}

llvm_var_t* llvm_node_to_instr_new(node_t* node, sym_t* class_table, sym_t* curr_method_table) {
    assert(node);
    assert(node->n1);
    
    ijavatype_t type = node->nodetype == NODE_OPER_NEWINT ? TYPE_INTARRAY : TYPE_BOOLARRAY;
    ijavatype_t type_element = node->nodetype == NODE_OPER_NEWINT ? TYPE_INT : TYPE_BOOL;
    const char* type_str = llvm_type_from_ijavatype(type);
    const char* ptr_type = llvm_type_from_ijavatype(type);
    const char* ptr_type_element = llvm_type_from_ijavatype(type_element);
    
    /*%1 = getelementptr inbounds %struct.IntArray* %array, i32 0, i32 0 ;Ponteiro para array.size
     store i32 40, i32* %1, align 4                                     ;array.size = 40
     %2 = getelementptr inbounds %struct.IntArray* %array, i32 0, i32 0 ;Ponteiro para array.size
     %3 = load i32* %2, align 4                                         ;%3 = array.size
     %4 = sext i32 %3 to i64                                            ;Extend to type i64 - Going to need this?
     %4 = call noalias i8* @calloc(i64 %3, i64 4) nounwind
     %7 = bitcast i8* %6 to i32*                                        ;malloc devolve i8*, temos que passar para i32*
     %8 = getelementptr inbounds %struct.IntArray* %array, i32 0, i32 1
     store i32* %7, i32** %8, align 8                                   ;Guardar o array
     */
    llvm_var_t* size = llvm_node_to_instr(node->n1, class_table, curr_method_table);
    
    llvm_var_t* ret = llvm_var_create(); ret->type = type; ret->value = 0;
    ret->repr = get_local_var_name();
    llvm_declare_local_array(type, ret->repr);
    char* arraysize_ptr = get_local_var_name();
    /*char* casted_size = get_local_var_name();*/
    printf("%s = getelementptr inbounds %s* %s, i32 0, i32 0\n", arraysize_ptr, type_str, ret->repr);
    printf("store i32 %s, i32* %s, align 4\n", size->repr, arraysize_ptr);
    /*printf("%s = sext i32 %s to i64\n", casted_size, ret->repr);*/
    
    /*char* tmpsize = get_local_var_name();
     printf("%s = mul i32 %s, %s\n", tmpsize, type == TYPE_INTARRAY ? "4" : "1", size->repr);*/ /* FIXME: i64? note arraysize_ptr */
    char* calloc_var = get_local_var_name();
    printf("%s = call noalias i8* @calloc(i32 %s, i32 %s) nounwind\n", calloc_var, size->repr, type == TYPE_INTARRAY ? "4" : "1");
    
    char* bitcast_var = get_local_var_name();
    printf("%s = bitcast i8* %s to %s*\n", bitcast_var, calloc_var, ptr_type_element);
    
    char* array_indx_ptr = get_local_var_name();
    printf("%s = getelementptr inbounds %s* %s, i32 0, i32 1\n", array_indx_ptr, type_str, ret->repr);
    
    printf("store %s* %s, %s** %s, align 8\n", ptr_type_element, bitcast_var, ptr_type_element, array_indx_ptr);
    
    free(arraysize_ptr); /*free(casted_size)*/ /*free(tmpsize);*/ free(calloc_var); free(bitcast_var); free(array_indx_ptr);
    
    RETURN_LOADABLE(ret);
    
}

void llvm_recurse_down(node_t* iter, sym_t* class_table, sym_t* table_method) {
    assert(iter);
    
    for ( ;iter != NULL ; iter = iter->next) {
        assert( node_is_statement(iter) );
        if ( iter->nodetype == NODE_STATEMENT_COMPOUNDSTATEMENT) {
            llvm_recurse_down(iter->n1, class_table, table_method);
        } else {
            llvm_node_to_instr(iter, class_table, table_method);
        }
    }
    
}

void llvm_output_code(node_t* root, sym_t* class_table) {
    if ( !root || !class_table ) return; /* FIXME: WIll this ever happen? */
    
    /* Find all the method entry points and recurse down on them */
    sym_t* iter;
    
    llvm_file_header();
    
    printf("\n\n");
    
    for (iter = class_table; iter != NULL; iter = iter->next) {
        if (iter->node_type == VARIABLE) {
            llvm_declare_global(iter->type, iter->id);
        }      
    }
    
    printf("\n\n");
    
    for (iter = class_table; iter != NULL; iter = iter->next) {
        if (iter->node_type == METHOD) {
            ijavatype_t return_val = get_return_type(iter->table_method);
            reset_local_vars();
            llvm_define_function(iter->table_method);        
            llvm_function_prologue(return_val);
            llvm_declare_locals(iter->table_method);
            printf("\n");
            if ( iter->method_start->n2 )
                llvm_recurse_down(iter->method_start->n2, class_table, iter->table_method);
            printf("\n");
            llvm_function_epilogue(return_val);
            printf("\n\n");
        }      
    }
    
}
