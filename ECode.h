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
#define EASY_UINT2STR
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
unsigned char* uintToStr(unsigned char* c, unsigned int n);
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


#define K_F1	0x69
#define K_F2	0x59
#define K_F3	0x49
#define K_F4	0x39
#define K_F5	0x29
#define K_F6	0x19

#define K_SHIFT	0x68
#define K_OPTN	0x58
#define K_VARS	0x48
#define K_MENU	0x38
#define K_LEFT	0x28
#define K_UP	0x18

#define K_ALPHA	0x67
#define K_SQR	0x57
#define K_EXPO	0x47
#define K_EXIT	0x37
#define K_DOWN	0x27
#define K_RIGHT	0x17

#define K_THETA	0x66
#define K_LOG	0x56
#define K_LN	0x46
#define K_SIN	0x36
#define K_COS	0x26
#define K_TAN	0x16

#define K_FRAC	0x65
#define K_FD	0x55
#define K_LPAR	0x45
#define K_RPAR	0x35
#define K_COMMA	0x25
#define K_STORE	0x15

#define K_7 	0x64
#define K_8		0x54
#define K_9		0x44
#define K_DEL	0x34

#define K_4		0x63
#define K_5		0x53
#define K_6		0x43
#define K_MULT	0x33
#define K_DIV	0x23

#define K_1		0x62
#define K_2		0x52
#define K_3		0x42
#define K_PLUS	0x32
#define K_MINUS	0x22

#define K_0		0x61
#define K_DOT	0x51
#define K_EXP	0x41
#define K_NEG	0x31
#define K_EXE	0x21

#define K_AC	0x00

#endif //EASYCODE
