/***********************************/
/**          Easy Coding          **/
/**Category : Snippets Collection **/
/**@author Eiyeron                **/
/**@contact eiyeron@gmail.com     **/
/**@file ECode.h                  **/
/**Version : 1.11                 **/
/**Date of creation : 06/28/2011  **/
/***********************************/

#ifndef EASYCODE
#define EASYCODE

/****************************************************/
/** uncomment #define EASY_of functions you want to use **/
/****************************************************/

// #define EASY_ALL	//define all functions
// #define EASY_MODEL
// #define EASY_STRING
// #define EASY_2STR
// #define EASY_2NUM
// #deinfe EASY_ALL_2HEX
// #define EASY_OPS_BITS
#define EASY_KEYS_DETECTION
// #define EASY_OTHERS

/**MODEL DETECTION**/
// #define EASY_ISEMULATOR
// #define EASY_ISG35P
// #define EASY_ISG75
// #define EASY_ISG85P
// #define EASY_ISG95
// #define EASY_MODELDETECTOR

/**STRING MANIUPLATION**/
// #define EASY_TOLOWER
// #define EASY_TOUPPER
// #define EASY_STRMIRROR
// #define EASY_STRROTATE
// #define EASY_PRINTF
// #define EASY_PRINTN

/**TO STRING**/
// #define EASY_CHAR2STR
// #define EASY_UCHAR2STR
#define EASY_INT2STR
// #define EASY_UINT2STR
// #define EASY_FLOAT2STR

/**TO NUMBER**/
// #define EASY_STR2CHAR
// #define EASY_STR2UCHAR
 #define EASY_STR2INT
// #define EASY_STR2UINT

/**TO HEX**/
// #define EASY_CHAR2HEX
// #define EASY_INT2HEX

/**BITS OPERATIONS**/
// #define EASY_READ_BIT_CHAR
// #define EASY_UP_BIT_CHAR
// #define EASY_DOWN_BIT_CHAR
// #define EASY_INVERSE_BIT_CHAR
// #define EASY_READ_BIT_INT
// #define EASY_UP_BIT_INT
// #define EASY_DOWN_BIT_INT
// #define EASY_INVERSE_BIT_INT

/**FAST KEYS DETECTION**/
#define EASY_KEY_DOWN
#define EASY_KEY_UP
// #define EASY_ANY_KEY

/**OTHERS**/
 #define EASY_INPUT
// #define EASY_NUMARRAY_CHAR
// #define EASY_NUMARRAY_INT

/**USEFUL VARIABLES**/
// #define NULL 0
// #define EXIT_SUCCESS 1


/**************************/
/** Functions prototypes **/
/**************************/


typedef enum {EMUlATOR, G35, G75, G85, G85SD, G95, UNDEFINED} Model;


/**MODEL DETECTION**/
char isEmulator();
char isG35p75();
char isG75();  // BESOIN DE LA VALEUR!!!
char isG85();
char isG85SD();
char isG95();
char hasSD();
Model modelDetector();

/**STRING MANIUPLATION**/
char* toLower(unsigned char* str, unsigned int len);
char* toUpper(unsigned char* str, unsigned int len);
char* strMirror(unsigned char* str, unsigned int len);
char* strRotate(unsigned char* str, unsigned int len, unsigned char mov);
void printf(unsigned char x, unsigned char y, unsigned char str, int mode);
void printn(unsigned char x, unsigned char y, int n, unsigned char mode);

/**TO STRING OPERATIONS**/
unsigned char* intToStr(unsigned char* c, int n);
unsigned char* uintToStr(char* c, unsigned int n);
unsigned char* charToStr(char* c, char n);
unsigned char* ucharToStr(char* c, unsigned char n);
unsigned char* floatToStr(char* c, float f, int pecision);

/**TO NUMBER**/
char strToChar(char* c);
unsigned char strToUchar(char* c);
int strToInt(unsigned char* c);
unsigned int strToUint(char* c);

/**TO HEX**/
char* charToHex(char* result, unsigned char hex);
char* intToHex(char* result, unsigned int hex);

/**BITS OPERATIONS**/
char readBit_char(char num, char index);
char inverseBit_char(char num, char index);
char upBit_char(char num, char index);
char downBit_char(char num, char index);
char readBit_int(int num, char index);
int inverseBit_int(int num, char index);
int upBit_int(int num, char index);
int downBit_int(int num, char index);

/**KEY DETECTION**/
unsigned char KeyDown( unsigned char code);
unsigned char KeyUp( unsigned char code);
unsigned char AnyKey();


/**OTHERS**/
char* input(char* c, int x, int y, int longueur, char nb);
int numArray_char(char* arr);
int numArray_int(char* arr);


/********************/
/** Key Codes List **/
/********************/


#define K_0 71
#define K_1 72
#define K_2 62
#define K_3 52
#define K_4 73
#define K_5 63
#define K_6 53
#define K_7 74
#define K_8 64
#define K_9 54
#define K_DP 61
#define K_EXP 51
#define K_PMINUS 41
#define K_PLUS 42
#define K_MINUS 32
#define K_MULT 43
#define K_DIV 33
#define K_FRAC 75
#define K_LPAR 55
#define K_RPAR 45
#define K_COMMA 35
#define K_STORE 25
#define K_LOG 66
#define K_LN 56
#define K_SIN 46
#define K_COS 36
#define K_TAN 26
#define K_SQUARE 67
#define K_POW 57
#define K_EXE 31
#define K_DEL 44
#define K_AC 32
#define K_FD 65
#define K_EXIT 47
#define K_SHIFT 78
#define K_ALPHA 77
#define K_OPTN 68
#define K_VARS 58
#define K_UP 28
#define K_DOWN 37
#define K_LEFT 38
#define K_RIGHT 27
#define K_F1 79
#define K_F2 69
#define K_F3 59
#define K_F4 49
#define K_F5 39
#define K_F6 29
#define K_MENU 48

#endif //EASYCODE
