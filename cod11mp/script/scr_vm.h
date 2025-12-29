#pragma once
#include "scr_variable.h"
//#include <xanim/xanim.h>
#include "../qcommon/q_shared.h"
#include "scr_debugger.h"
#include "../bgame/bg_local.h"
enum Opcode_t
{
    OP_End,
    OP_Return,
    OP_GetUndefined,
    OP_GetZero,
    OP_GetByte,
    OP_GetNegByte,
    OP_GetUnsignedShort,
    OP_GetNegUnsignedShort,
    OP_GetInteger,
    OP_GetFloat,
    OP_GetString,
    OP_GetIString,
    OP_GetVector,
    OP_GetLevelObject,
    OP_GetAnimObject,
    OP_GetSelf,
    OP_GetLevel,
    OP_GetGame,
    OP_GetAnim,
    OP_GetAnimation,
    OP_GetGameRef,
    OP_GetFunction,
    OP_CreateLocalVariable,
    OP_RemoveLocalVariables,
    OP_EvalLocalVariableCached0,
    OP_EvalLocalVariableCached1,
    OP_EvalLocalVariableCached2,
    OP_EvalLocalVariableCached3,
    OP_EvalLocalVariableCached4,
    OP_EvalLocalVariableCached5,
    OP_EvalLocalVariableCached,
    OP_EvalLocalArrayCached,
    OP_EvalArray,
    OP_EvalLocalArrayRefCached0,
    OP_EvalLocalArrayRefCached,
    OP_EvalArrayRef,
    OP_ClearArray,
    OP_EmptyArray,
    OP_GetSelfObject,
    OP_EvalLevelFieldVariable,
    OP_EvalAnimFieldVariable,
    OP_EvalSelfFieldVariable,
    OP_EvalFieldVariable,
    OP_EvalLevelFieldVariableRef,
    OP_EvalAnimFieldVariableRef,
    OP_EvalSelfFieldVariableRef,
    OP_EvalFieldVariableRef,
    OP_ClearFieldVariable,
    OP_SafeCreateVariableFieldCached,
    OP_SafeSetVariableFieldCached0,
    OP_SafeSetVariableFieldCached,
    OP_SafeSetWaittillVariableFieldCached,
    OP_clearparams,
    OP_checkclearparams,
    OP_EvalLocalVariableRefCached0,
    OP_EvalLocalVariableRefCached,
    OP_SetLevelFieldVariableField,
    OP_SetVariableField,
    OP_SetAnimFieldVariableField,
    OP_SetSelfFieldVariableField,
    OP_SetLocalVariableFieldCached0,
    OP_SetLocalVariableFieldCached,
    OP_CallBuiltin0,
    OP_CallBuiltin1,
    OP_CallBuiltin2,
    OP_CallBuiltin3,
    OP_CallBuiltin4,
    OP_CallBuiltin5,
    OP_CallBuiltin,
    OP_CallBuiltinMethod0,
    OP_CallBuiltinMethod1,
    OP_CallBuiltinMethod2,
    OP_CallBuiltinMethod3,
    OP_CallBuiltinMethod4,
    OP_CallBuiltinMethod5,
    OP_CallBuiltinMethod,
    OP_wait,
    OP_waittillFrameEnd,
    OP_PreScriptCall,
    OP_ScriptFunctionCall2,
    OP_ScriptFunctionCall,
    OP_ScriptFunctionCallPointer,
    OP_ScriptMethodCall,
    OP_ScriptMethodCallPointer,
    OP_ScriptThreadCall,
    OP_ScriptThreadCallPointer,
    OP_ScriptMethodThreadCall,
    OP_ScriptMethodThreadCallPointer,
    OP_DecTop,
    OP_CastFieldObject,
    OP_EvalLocalVariableObjectCached,
    OP_CastBool,
    OP_BoolNot,
    OP_BoolComplement,
    OP_JumpOnFalse,
    OP_JumpOnTrue,
    OP_JumpOnFalseExpr,
    OP_JumpOnTrueExpr,
    OP_jump,
    OP_jumpback,
    OP_inc,
    OP_dec,
    OP_bit_or,
    OP_bit_ex_or,
    OP_bit_and,
    OP_equality,
    OP_inequality,
    OP_less,
    OP_greater,
    OP_less_equal,
    OP_greater_equal,
    OP_shift_left,
    OP_shift_right,
    OP_plus,
    OP_minus,
    OP_multiply,
    OP_divide,
    OP_mod,
    OP_size,
    OP_waittillmatch,
    OP_waittill,
    OP_notify,
    OP_endon,
    OP_voidCodepos,
    OP_switch,
    OP_endswitch,
    OP_vector,
    OP_NOP,
    OP_abort,
    OP_object,
    OP_thread_object,
    OP_EvalLocalVariable,
    OP_EvalLocalVariableRef,
    OP_prof_begin,
    OP_prof_end,
    OP_breakpoint,
    OP_assignmentBreakpoint,
    OP_manualAndAssignmentBreakpoint,
    OP_count,
};
inline Opcode_t &operator++(Opcode_t &e) {
    e = static_cast<Opcode_t>(static_cast<int>(e) + 1);
    return e;
}
inline Opcode_t &operator++(Opcode_t &e, int i)
{
    ++e;
    return e;
}
struct Scr_StringNode_s 
{
    const char *text;
    Scr_StringNode_s *next;
};
struct function_stack_t 
{                                       
    const char *pos;                    
    unsigned int localId;               
    unsigned int localVarCount;         
    VariableValue *top;                 
    VariableValue *startTop;            
};
struct function_frame_t 
{                                       
    function_stack_t fs;                
    Vartype_t topType;
};
struct scrVmPub_t 
{                                       
    unsigned int* localVars;            
    VariableValue* maxstack;            
    int function_count;                 
    function_frame_t* function_frame;   
    VariableValue* top;                 
    bool debugCode;                     
    bool abort_on_error;                
    bool terminal_error;                
    unsigned int inparamcount;          
    unsigned int outparamcount;         
    unsigned int breakpointOutparamcount; 
    bool showError;                     
    function_frame_t function_frame_start[32]; 
    VariableValue stack[2048];          
};
struct FuncDebugData 
{                                       
    int breakpointCount;                
    const char *name;                   
    int prof;                           
    int usage;                          
};
struct scrVmDebugPub_t 
{                                       
    FuncDebugData func_table[1024];     
    int checkBreakon;                   
    int profileEnable[32768];           
    int builtInTime;                    
    const char *jumpbackHistory[128];   
    int jumpbackHistoryIndex;           
    int dummy;
};
struct scrVmGlob_t 
{                                       
    VariableValue eval_stack[2];        
    const char *dialog_error_message;   
    int loading;                        
    int starttime;                      
    unsigned int localVarsStack[2048];  
    bool recordPlace;                   
    char *lastFileName;                 
    int lastLine;                       
};