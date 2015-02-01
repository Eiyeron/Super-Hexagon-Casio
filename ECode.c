 /***********************************/
/**          Easy Coding          **/
/**Category : Snippets Collection **/
/**@author Eiyeron                **/
/**@contact eiyeron@gmail.com     **/
/**@file ECode.c                  **/
/**Version : 1.11                 **/
/**Date of creation : 06/28/2011  **/
/***********************************/


#include "ECode.h"

/******************************/
/** Dependencies management  **/
/******************************/

#ifdef EASY_ALL
	#define EASY_MODEL
	#define EASY_STRING
	#define EASY_2STR
	#define EASY_2NUM
	#define EASY_2HEX
	#define EASY_BITS
	#define EASY_KEYS
	#define EASY_OTHERS

#endif

#ifdef EASY_MODEL
	#define EASY_ISEMULATOR
	#define EASY_ISG35P
	#define EASY_ISG75
	#define EASY_ISG85
	#define EASY_ISG85SD
	#define EASY_ISG95
	#define EASY_MODELDETECTOR
	#define EASY_HASSD
#endif

#ifdef EASY_STRING
	#define EASY_TOLOWER
	#define EASY_TOUPPER
	#define EASY_STRMIRROR
	#define EASY_STRROTATE
	#define EASY_PRINTF
	#define EASY_PRINTN
#endif

#ifdef EASY_2STR
	#define EASY_CHAR2STR
	#define EASY_UCHAR2STR
	#define EASY_INT2STR
	#define EASY_UINT2STR
	#define EASY_FLOAT2STR
#endif

#ifdef EASY_2NUM
	#define EASY_STR2CHAR
	#define EASY_STR2UCHAR
	#define EASY_STR2INT
	#define EASY_STR2UINT
#endif

#ifdef EASY_2HEX
	#define EASY_CHAR2HEX
	#define EASY_INT2HEX
#endif

#ifdef EASY_BITS
	#define EASY_READ_BIT_CHAR
	#define EASY_UP_BIT_CHAR
	#define EASY_DOWN_BIT_CHAR
	#define EASY_INVERSE_BIT_CHAR
	#define EASY_READ_BIT_INT
	#define EASY_UP_BIT_INT
	#define EASY_DOWN_BIT_INT
	#define EASY_INVERSE_BIT_INT
#endif

#ifdef EASY_KEYS
	#define EASY_KEY_DOWN
	#define EASY_KEY_UP
	#define EASY_ANY_KEY
#endif

#ifdef EASY_OTHERS
	#define EASY_INPUT
	#define EASY_NUMARRAY_CHAR
	#define EASY_NUMARRAY_INT
#endif

#ifdef EASY_KEY_UP
#define EASY_KEY_DOWN
#endif

#ifdef EASY_FLOAT2STR
#define EASY_INT2STR
#endif

#ifdef EASY_INPUT
#include "fxlib.h"
#endif

#ifdef EASY_PRINTF
#include "fxlib.h"
#endif

#ifdef EASY_PRINTN
#include "fxlib.h"
#endif
#include "fxlib.h"
/***************/
/** Functions **/
/***************/

static int SysCallCode[] = {0xD201422B,0x60F20000,0x80010070};
static int (*SysCall)( int R4, int R5, int R6, int R7, int FNo ) = (void*)&SysCallCode; // Elles sont en static, car je ne vais pas encore publier la liste des syscalls "utiles"

#ifdef EASY_ISEMULATOR
char isEmulator()
{
	return !( *(int*)0x80000300 );
}
#endif

#ifdef EASY_ISG35P
char isG35p75()
{
	return ( *(int*)0x80000300 == 0x33363246 ) && ( *(char*)0x8024FEE0  == 0xB4393341);
}
#endif

#ifdef EASY_ISG75
char isG75()
{
	return ( *(int*)0x80000300 ==  0xFAE0FB2C && *(char*)0x8024FEE0 == 0x4BC8053F);
}
#endif

#ifdef EASY_ISG85
char isG85()
{
	return ( *(int*)0x80000300 == 0x80005D7C );
}
#endif

#ifdef EASY_ISG85SD
char isG85SD()
{

	return *(int*)((*SysCall)(0, 0, 0, 0, 1128));
}
#endif

#ifdef EASY_ISG95
char isG95()
{
	return ( *(int*)0x80000300 == 0x34393342 );
}
#endif

#ifdef EASY_MODELDETECTOR
Model modelDetector()
{
	int model = *(int*)0x80000300;

	switch(model)
	{
		case 0 :
		return EMULATOR;
		break;

		case 0x33363246:
		if ( *(int*)0x8024FEE0  == 0xB4393341)
			return G35;
		else return UNDEFINED;
		break;

		case 0x34393542:
		if((int*)((*SysCall)(0, 0, 0, 0, 1128))) return G75;
		else return G75;
		break;

		case 0x80005D7C :
		if((int*)((*SysCall)(0, 0, 0, 0, 1128))) return G85SD;
		else return G85;
		break;

		case 0x34393342 :
		return G95;
		break;

		default :
		return UNDEFINED;
		break;
	}

}
#endif

#ifdef EASY_HASSD
char hasSD()
{
	return ( *(char*)((*SysCall)(0, 0, 0, 0, 1128)) );
}
#endif



#ifdef EASY_TOLOWER/**						OK					*/
unsigned char* toLower(unsigned char* str)
{
	int i;
	for(i=0; str[i] != '\0'; i++)
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
	}
	return str;
}
#endif

#ifdef EASY_TOUPPER/**						OK					*/
unsigned char* toUpper(unsigned char* str)
{
	int i;
	for(i=0; str[i] != '\0' ; i++)
	{
		if(str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
	return str;
}
#endif

#ifdef EASY_STRMIRROR/**						OK					*/
unsigned char* strMirror(unsigned char* str)
{
	int i, len;
	unsigned char tmp;

	for(len=0; str[len]!= '\0' ; len++);

		for(i=0; i< (int) len/2; i++)
		{
			tmp = str[len-i-1];
			str[len-i-1] = str[i];
			str[i] = tmp;
		}
		return str;
	}
#endif

#ifdef EASY_STRROTATE /**						OK					*/
	unsigned char* strRotate(unsigned char* str, char mov)
	{
		int i, len;
		unsigned char tmp;

		for(len=0; str[len]!= '\0' ; len++);

			mov= mov%len;
		if(mov < 0)
			mov += len;
		if(mov == 0)
			return str;
		while(mov)
		{
			tmp = str[len-1];
			for(i=len-1;i>0;i--)
				str[i] = str[i-1];
			str[0] = tmp;
			mov--;
		}
		return str;
	}
#endif

#ifdef EASY_PRINTF/**						OK					*/
/*void printf(unsigned char x, unsigned char y, unsigned char* str, int mode)
{
	locate(x,y);
	switch(mode)
	{
	case 0:
	Print(str);
	return;

	case 1:
	PrintRev(str);
	return;
	}
}*/
	void printf(unsigned char x, unsigned char y, unsigned char* str, char mode)
	{
		locate(x,y);
		if(mode)
			PrintRev(str);
		else
			Print(str);
	}
#endif

#ifdef EASY_PRINTN/**						OK					*/
	void printn(unsigned char x, unsigned char y, int n, char mode)
	{
		unsigned char c[12];

		intToStr(c, n);
		locate(x,y);
		if(mode)
			PrintRev(c);
		else
			Print(c);
	}
#endif



#ifdef EASY_INT2STR/**						OK					*/
	unsigned char* intToStr(unsigned char* c, int n)
	{
		if(n==0)
		{
			c[0] = '0';
			c[1] = 0;
		}
		else
		{
			int i, l=0;
			if(n<0)
			{
				c[0] = '-';
				n = abs(n);
				l++;
			}
			for(i=n ; i ; i/=10)
				l++;
			c[l] = 0;
			for(i=n ; i ; i/=10)
				c[--l] = i%10+'0';
		}
		return c;
	}
#endif

#ifdef EASY_UINT2STR/**						OK					*/
	unsigned char* uintToStr(unsigned char* c, unsigned int n)
	{
		if(n==0)
		{
			c[0] = '0';
			c[1] = 0;
		}
		else
		{
			unsigned int i, l=0;
			for(i=n ; i ; i/=10)
				l++;
			c[l] = 0;
			for(i=n ; i ; i/=10)
				c[--l] = i%10+'0';
		}
		return c;
	}
#endif

#ifdef EASY_CHAR2STR/**						OK					*/
	unsigned char* charToStr(unsigned char* c, char n)
	{
		if(n==0)
		{
			c[0] = '0';
			c[1] = 0;
		}
		else
		{
			int i, l=0;
			if(n<0)
			{
				c[0] = '-';
				n = abs(n);
				l++;
			}
			for(i=n ; i ; i/=10)
				l++;
			c[l] = 0;
			for(i=n ; i ; i/=10)
				c[--l] = i%10+'0';
		}
		return c;
	}
#endif

#ifdef EASY_UCHAR2STR/**						OK					*/
	unsigned char* ucharToStr(unsigned char* c, unsigned char n)
	{
		if(n==0)
		{
			c[0] = '0';
			c[1] = 0;
		}
		else
		{
			int i, l=0;
        /*if(n<0)
        {
            c[0] = '-';
            n = abs(n);
            l++;
        }*/
            for(i=n ; i ; i/=10)
            	l++;
            c[l] = 0;
            for(i=n ; i ; i/=10)
            	c[--l] = i%10+'0';
        }
        return c;
    }
#endif

#ifdef EASY_FLOAT2STR
    unsigned char* floatToStr(unsigned char* c, float f, int precision)
    {
    	int i, n=0, index = 0;
    	if(f<0)
    	{
    		f *=-1;
    		c[0] = '-';
    		index++;
    	}

    	i = f;
    	intToStr((unsigned char*)((int)c+index), i);
    	while(c[index])
    		index++;
    	if(f-i) {
    		c[index] = '.';
    		index++;
    		i = f = (f-i)*10;
    		while(f && n<precision) {
    			c[index] = i;
    			index++;
    			n++;
    			i = f = (f-i)*10;
    		}
    		c[index+1] = 0;

    	}
    	return c;
    }
#endif



#ifdef EASY_STR2CHAR
    char strToChar(unsigned char* c)
    {
    	int i, start = 0;
    	char n = 0;
    	if(c[0] == '-')
    		start++;
    	for(i=start; c[i]; i++)
    	{
    		if(c[i]<='9' && c[i] >= '0')
    			n = n*10+c[i] - '0';
    	}
    	if(start)
    		n *= -1;
    	return n;
    }
#endif

#ifdef EASY_STR2UCHAR
    unsigned char strToUchar(unsigned char* c)
    {
    	int i = 0;
    	char n = 0;
    	for(i=0; c[i]; i++)
    	{
    		if(c[i]<='9' && c[i] >= '0')
    			n = n*10+c[i] - '0';
    	}
    	return n;
    }
#endif

#ifdef EASY_STR2INT
    int strToInt(unsigned char* c)
    {
    	int i,n = 0, start = 0;
    	if(c[0] == '-')
    		start++;
    	for(i=start; c[i]; i++)
    	{
    		if(c[i]<='9' && c[i] >= '0')
    			n = n*10+c[i] - '0';
    	}
    	if(start)
    		n *= -1;
    	return n;
    }
#endif

#ifdef EASY_STR2UINT
    unsigned int strToUint(unsigned char* c)
    {
    	int i,n = 0;
    	for(i=0; c[i]; i++)
    	{
    		if(c[i]<='9' && c[i] >= '0')
    			n = n*10+c[i] - '0';
    	}
    	return n;
    }
#endif



#ifdef EASY_CHAR2HEX
char* charToHex(char* result, unsigned char hex) // Needs an 3-char array ("xx\0")
{
	char HEX1=hex/16;
	char HEX2=hex%16;

	if (HEX1<=9)
		HEX1+='0';
	else
		HEX1=HEX1-10+'a';

	if (HEX2<=9)
		HEX2+='0';
	else
		HEX2=HEX2-10+'a';

	result[0] = HEX1;
	result[1] = HEX2;
	result[2] = '\0';

	return result;
}
#endif

#ifdef EASY_INT2HEX
char* intToHex(char* result, unsigned int hex) // Needs an 9-char array ("xxxxxxxx\0")
{
	int i;
	for(i=0 ; i<8 ; i++)
	{
		result[7-i] = (hex&15) + ((hex&15)>9 ? 'A'-10 : '0');
		hex >>= 4;
	}
	result[8] = '\0';
	return result;
}
#endif



#ifdef EASY_READ_BIT_CHAR
char readBit_char(char num, char index)
{
	return !(num & 1<< (7 - index)) ==0;
}
#endif

#ifdef EASY_INVERSE_BIT_CHAR
char inverseBit_char(char num, char index)
{
	return num ^ 1<<7-index;
}
#endif

#ifdef EASY_UP_BIT_CHAR
char upBit_char(char num, char index)
{
	return num | 1<<7-index;
}
#endif

#ifdef EASY_DOWN_BIT_CHAR
char downBit_char(char num, char index)
{
	return num & (~(1<<(7-index)));
}
#endif

#ifdef EASY_READ_BIT_INT
char readBit_int(int num, char index)
{
	return (num & 1 << 31 - index)& 1;
}
#endif

#ifdef EASY_INVERSE_BIT_INT
int inverseBit_int(int num, char index)
{
	return num ^ 1<<31-index;
}
#endif

#ifdef EASY_UP_BIT_INT
int upBit_int(int num, char index)
{
	return num | 1<<31-index;
}
#endif

#ifdef EASY_DOWN_BIT_INT
int downBit_int(int num, char index)
{
	return num & (~1<<31-index);
}
#endif

// TODO : Foudn the new function to detect architecture instead of using versions.

static void delay( void ) // Cette fonction n'est utilisée que pour KeyDown/Up, et elle n'est absolument pas utile ailleurs. D'où le static.
{
	unsigned char i;
	for (i=0;i<5;i++);
}

#ifdef EASY_KEY_DOWN
int GetMPU()
{
    int mpu;
    unsigned char s[30];
    unsigned int key;
    unsigned char savevalue;
    mpu = 0;
    savevalue = *(unsigned short*)0xA4000114;
    *(unsigned short*)0xA4000114 = 0xFFFF;
    switch ( *(unsigned short*)0xA4000114 ){
        case 0x0FFF :
            mpu = 1;
            break;

        case 0x00FF :
            mpu = 2;
            break;

        default :
            switch ( *(unsigned int*)0xFF000030 & 0xFFFFFF00 ){
                case 0x10300B00 :
                    switch ( *(unsigned int*)0xFF000044 & 0xFFFFFFF0 ){
                        case 0x00002C00 :
                            mpu = 3;
                            break;

                        case 0x00002200 :
                            mpu = 4;    // just for reference
                            break;
            };
            break;
        };
        break;
    };
    *(unsigned short*)0xA4000114 = savevalue;

    return mpu;
}

int getCPUFamily()
{
    switch(GetMPU()){
        case 3 :
        case 4 :
            return 0;
            break;
        case 2 :
        case 1 :
        case 5 : // mpu7705 ?
            return 1;
            break;
        default :
            return 2;
    }
}

#define isEMU (GetMPU() == 2)
#define isSH3 (GetMPU() == 1)
#define isSH4 (GetMPU() == 0)

unsigned char CheckKeyRow(unsigned char code)
{
	unsigned char result=0;
	short*PORTB_CTRL=(void*)0xA4000102;
	short*PORTM_CTRL=(void*)0xA4000118;
	char*PORTB=(void*)0xA4000122;
	char*PORTM=(void*)0xA4000138;
	char*PORTA=(void*)0xA4000120;
	short smask;
	char cmask;
	unsigned char column, row;
	column = code>>4;
	row = code &0x0F;
	smask = 0x0003 << (( row %8)*2);
	cmask = ~( 1 << ( row %8) );
	if(row <8)
	{
		*PORTB_CTRL = 0xAAAA ^ smask;
		*PORTM_CTRL = (*PORTM_CTRL & 0xFF00 ) | 0x00AA;
		delay();
		*PORTB = cmask;
		*PORTM = (*PORTM & 0xF0 ) | 0x0F;
	}
	else
	{
		*PORTB_CTRL = 0xAAAA;
		*PORTM_CTRL = ((*PORTM_CTRL & 0xFF00 ) | 0x00AA)  ^ smask;
		delay();
		*PORTB = 0xFF;
		*PORTM = (*PORTM & 0xF0 ) | cmask;
	}

	delay();
	result = (~(*PORTA))>>column & 1;
	delay();
	*PORTB_CTRL = 0xAAAA;
	*PORTM_CTRL = (*PORTM_CTRL & 0xFF00 ) | 0x00AA;
	delay();
	*PORTB_CTRL = 0x5555;
	*PORTM_CTRL = (*PORTM_CTRL & 0xFF00 ) | 0x0055;
	delay();

	return result;
}

unsigned char KeyDown(unsigned char keycode)
{
	unsigned short key[8];
	const unsigned short* keyboardregister = (unsigned short*)0xA44B0000;
	unsigned char row;
		if(isSH4)
        {
		memcpy(&key, keyboardregister, sizeof(unsigned short) << 3);
		row = keycode%10;
		return (0 != (key[row >> 1] & 1 << keycode / 10 - 1 + ((row & 1) << 3)));
        }
	else
        {
        return CheckKeyRow((keycode % 10) + ((keycode / 10 - 1) << 4));
        }
}

#endif

#ifdef EASY_KEY_UP
unsigned char KeyUp(unsigned char code)
{
	return !(KeyDown(code));
}
#endif


#ifdef EASY_ANY_KEY
unsigned char AnyKey()
{
	return *((unsigned char*)0xA4000120)!=0xFF;
}
#endif



#ifdef EASY_INPUT
char* input(char* c, int x, int y, int longueur, char nb)
{
	int i, key, curseur=0;
	char lettre;
	locate(x, y);
	Print("[");
		locate(x+longueur+1, y);Print("]");
		while(1)
		{
			locate(x+1, y);
			Print(c);
			if(strlen(c)<longueur) Print(" ");
			Bdisp_DrawLineVRAM((x+curseur)*6, (y-1)*8, (x+curseur)*6, (y-1)*8+6);
			Bdisp_DrawLineVRAM((x+curseur)*6+1, (y-1)*8, (x+curseur)*6+1, (y-1)*8+6);
			GetKey(&key);
			lettre=0;
			switch(key)
			{
				case KEY_CTRL_LEFT: if(curseur) curseur--; break;
				case KEY_CTRL_RIGHT: if(c[curseur]) curseur++; break;
				case KEY_CTRL_DEL:
				if(curseur)
				{
					for(i=curseur ; i<longueur ; i++)
						c[i-1] = c[i];
					locate(x+curseur+1, y);Print(" ");
					curseur--;
				}
				else
				{
					for(i=0 ; c[i] ; i++)
						c[i] = c[i+1];
				}
				break;
				case KEY_CTRL_EXIT: c[0] = 0; return c;
				case KEY_CTRL_QUIT: c[0] = 0; return c;
				case KEY_CTRL_EXE: return c;
				case KEY_CHAR_PLUS: lettre='+'; break;
				case KEY_CHAR_MINUS: lettre='-'; break;
				case KEY_CHAR_POW: lettre='^'; break;
				case KEY_CTRL_XTT: lettre='X'; break;
				default:
				if(nb)
				{
					if(key>='0' && key<='9')
						lettre=key;
				}
				else if(key>0 && key<256)
					lettre=key;
			}
			if(lettre && curseur<longueur)
			{
				for(i=longueur-1 ; i>=curseur ; i--)
					c[i] = c[i-1];
				c[curseur] = lettre;
				curseur++;
			}
		}
	}
#endif

#ifdef EASY_NUMARRAY_CHAR
	int numArray_char(char* arr)
	{
		return sizeof(arr);
	}
#endif

#ifdef EASY_NUMARRAY_INT
	int numArray_int(char* arr)
	{
		return sizeof(arr)/4;
	}
#endif
