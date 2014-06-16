//author: Ed Baafi
//(c)2013 Modkit LLC

//TODO - append __FILE__ macro to make truly unique names

// helper macro to append results of other macros
#define MICRO_APPEND_ITEMS(item1,item2)\
    item1##item2
    
// macros to buils a unique class name
// using the gcc __LINE__ macro 
    
#define MICRO_CLASS_SUFFIX(lineno)\
    MICRO_APPEND_ITEMS(MICRO_THREAD_CLASS_,lineno)

#define MICRO_THREAD_CLASS_FROM_LINE_NUM()\
    MICRO_CLASS_SUFFIX(__LINE__) 

// macros to buils a unique namespace
// using the gcc __LINE__ macro 
// fails whe using function-like macro MICRO_NAMESPACE_FROM_LINE_NUM() when namespace comes before it
#define MICRO_NAMESPACE_SUFFIX(lineno)\
    MICRO_APPEND_ITEMS(MICRO_NAMESPACE_,lineno)

#define MICRO_NAMESPACE_FROM_LINE_NUM\
    MICRO_NAMESPACE_SUFFIX(__LINE__) 
 
    
// macros to buils a unique instance name
// using the gcc __LINE__ macro 

#define MICRO_INSTANCE_SUFFIX(lineno)\
    MICRO_APPEND_ITEMS(MICRO_THREAD_INSTANCE_,lineno)

#define MICRO_THREAD_INSTANCE_FROM_LINE_NUM()\
    MICRO_INSTANCE_SUFFIX(__LINE__) 
    
// macros to build a unique goto label 

#define MICRO_GOTO_SUFFIX(lineno)\
    MICRO_APPEND_ITEMS(MICRO_GOTO_,lineno)

#define MICRO_GOTO_LABEL()\
    MICRO_GOTO_SUFFIX(__LINE__)
    
    
// macros to build a second unique goto label for a single macro's use

#define MICRO_GOTO_SUFFIX(lineno)\
    MICRO_APPEND_ITEMS(MICRO_GOTO_2_,lineno)

#define MICRO_GOTO_LABEL2()\
    MICRO_GOTO_SUFFIX(__LINE__)
   
   
// macros to build a unique function name 

#define MICRO_FUNCTION_SUFFIX(lineno)\
    MICRO_APPEND_ITEMS(MICRO_FUNCTION_,lineno)

#define MICRO_FUNCTION_NAME()\
    MICRO_FUNCTION_SUFFIX(__LINE__)
    
    

// macros to build a pin type

#define MICRO_TYPE_SUFFIX(pin)\
MICRO_APPEND_ITEMS(pin,_TYPE)

#define MICRO_PIN_TYPE_FROM_PIN(pin)\
MICRO_TYPE_SUFFIX(pin)

// macros to build pin setup args 

#define MICRO_SETUP_SUFFIX(pin)\
MICRO_APPEND_ITEMS(pin,_SETUP)

#define MICRO_PIN_SETUP_FROM_PIN(pin)\
MICRO_SETUP_SUFFIX(pin)





