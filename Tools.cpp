// Tools.cpp: implementation of the Tools class.
//
//////////////////////////////////////////////////////////////////////

#include "Tools.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// 平年与闰年每月天数列表
int months[2][13] = {{0,31,28,31,30,31,30,31,31,30,31,30,31},
					 {0,31,29,31,30,31,30,31,31,30,31,30,31}} ;

unsigned int crc_ta[256]={               /* CRC 余式表 */ 
        0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
        0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
        0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
        0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
        0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
        0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
        0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
        0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
        0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
        0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
        0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
        0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
        0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
        0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
        0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
        0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
        0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 
        0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067, 
        0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e, 
        0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256, 
        0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d, 
        0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 
        0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 
        0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 
        0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 
        0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 
        0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 
        0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
        0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
        0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
        0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
        0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0 
}; 

unsigned long crc32_table[256] = 
{
        0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
        0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
        0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
        0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
        0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
        0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
        0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
        0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
        0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
        0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
        0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
        0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
        0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
        0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
        0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
        0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
        0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
        0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
        0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
        0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
        0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
        0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
        0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
        0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
        0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
        0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
        0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
        0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
        0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
        0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
        0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
        0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
        0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
        0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
        0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
        0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
        0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
        0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
        0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
        0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
        0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
        0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
        0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
        0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
        0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
        0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
        0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
        0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
        0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
        0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
        0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
        0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
        0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
        0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
        0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
        0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
        0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
        0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
        0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
        0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
        0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
        0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
        0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
        0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};


/*******************************************************************************
*
*  函 数 名 : isLeap
*  功能描述 : 判断是否是闰年
*  参数列表 : year -- 年数
*  说    明 : 
*  返回结果 : 如果是闰年返回1、否则返回0
*
*******************************************************************************/
int isLeap(IN int year)
{
    if (year % 4 != 0 || (year %100 == 0 && year%400 != 0))
        return 0;
    return 1;
}

/*******************************************************************************
*
*  函 数 名 : isSuccDate
*  功能描述 : 判断日期是否合法
*  参数列表 : date -- 日期结构体
*  说    明 : 通过判断闰年与平年取出每月的天数,依次判断是否合法
*  返回结果 : 如果是合法返回1、否则返回0
*
*******************************************************************************/
int isSuccDate(IN date &pd)
{
    // 判断年是否合法
    // 我们不处理公元前的情况
    if (pd.year < 0)
    {
    #ifdef _DEBUG
        printf("对不起，公元前不在本程序计算之内\r\n") ;
    #endif
        return 0 ;
    }
    
    // 判断月是否合法
    if (pd.month < 1 || pd.month > 12)
    {
    #ifdef _DEBUG
        printf("对不起，您的月份输入不正确!\r\n") ;
    #endif
        return 0 ;
    }
    
    // 判断日是否合法
    if (pd.day < 0 || (pd.day > months[ isLeap( pd.year)][pd.month]))
    {
     #ifdef _DEBUG
        printf("对不起，您的天数输入不正确! \r\n") ;
     #endif
        return 0 ;
    }
    return 1;
}

/*******************************************************************************
*
*  函 数 名 : isSuccPhoto
*  功能描述 : 判断字符串是全是数字
*  参数列表 : szBuf -- 字符串
*  说    明 : 通过依次判断字符串的各个位，来判断整个字符串是不是全由数字组成
*  返回结果 : 如果是成功返回1、否则返回0
*
*******************************************************************************/
int isSuccPhoto(IN const char *szBuf)
{
    int i(0) ;
    for(;szBuf[i] != 0 && isdigit(szBuf[i]); ++i)
    {
        ;
    }

    if (szBuf[i] != 0)
    {
        return 0 ;
    }
    return 1 ;
}

/*******************************************************************************
*
*  函 数 名 : isXNumString
*  功能描述 : 检测字符串是否全为十六进制数
*  参数列表 : szbuf --  字符串
*  说    明 : 
*  返回结果 : 如果为16进制，返回1，否则返回0
*
*******************************************************************************/
int isXNumString(IN const char *szbuf)
{
        int nLen = strlen(szbuf) ;

        for (int i = 0; isxdigit(szbuf[i]); ++i)
                ;

        if (nLen == i)
        {
                return 1 ;
        }

        return 0 ;
}

/*******************************************************************************
*
*  函 数 名 : SafeInput
*  功能描述 : 对输入进行检测
*  参数列表 : szBuffer --  输入缓冲
*             nSize    --  缓冲区大小
*  说    明 : 防止溢出，输入回车结束
*  返回结果 : 如果成功，返回接收数据长度，否则返回0
*
*******************************************************************************/
int SafeInput(IN char *szBuffer, IN int nSize)
{
    int i ;
    char ch = ' ' ;
    
    if (szBuffer == NULL || nSize < 1)
    {
        return 0 ;
    }
    
    fflush(stdin) ;
    memset(szBuffer, 0, sizeof(char) * nSize );
    for (i = 0; i < nSize-1 && ch != '\n'; ++i)
    {
        ch = getc(stdin) ;
        if (ch != '\n')
        {
            szBuffer[i] = ch ;
        }
    }
    szBuffer[i] = 0 ;
    fflush(stdin) ;
    return i ;
}

/*******************************************************************************
*
*  函 数 名 : SafeHexInput
*  功能描述 : 安全输入十六进制
*  参数列表 : szBuffer --  输入缓冲
*             nSize    --  缓冲区大小
*  说    明 : 防止溢出，输入回车或者非十六进制数结束
*  返回结果 : 如果成功，返回接收数据长度，如果输入非16进制数否则返回0
*
*******************************************************************************/
int SafeHexInput(IN char *szBuffer, IN int nSize)
{
    int i ;
    char ch = ' ' ;
    
    if (szBuffer == NULL || nSize < 1)
    {
        return 0 ;
    }
    
    fflush(stdin) ;
    memset(szBuffer, 0, sizeof(char) * nSize );
    for (i = 0; i < nSize-1 && ch != '\n'; ++i)
    {
        ch = getc(stdin) ;
        if (ch != '\n' && isxdigit(ch))
        {
            szBuffer[i] = ch ;
        }
    }
    fflush(stdin) ;
    return i ;
}

/*******************************************************************************
*
*  函 数 名 : GetLine
*  功能描述 : 取得一行，遇到回车结束
*  参数列表 : szBuffer --  输入缓冲
*             nSize    --  缓冲区大小
*  说    明 : 
*  返回结果 : 如果成功，返回接收数据长度，失败返回0
*
*******************************************************************************/
int GetLine(IN FILE *fp, IN char *szBuffer, IN int nSize)
{
        if (NULL == szBuffer)
        {
                return 0 ;
        }

        if (feof(fp))
        {
                return 0 ;
        }

        char ch = 0 ;
        ch = fgetc(fp) ;
        for (int i = 0; i < nSize && !feof(fp) 
                         && ch != '\r' 
                         && ch != '\n'
                         && ch != 0; ++i)
        {
                szBuffer[i] = ch ;
                ch = fgetc(fp) ;
        }
        
        return i ;        
}

// RSHash 哈希函数
unsigned int RSHash(IN const char *str)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;

	while (*str)
	{
		hash = hash * a + (*str++);
		a *= b;
	}

	return (hash & 0x7FFFFFFF);
}

// JS Hash Function
unsigned int JSHash(IN const char *str)
{
	unsigned int hash = 1315423911;

	while (*str)
	{
		hash ^= ((hash << 5) + (*str++) + (hash >> 2));
	}
	
	return (hash & 0x7FFFFFFF);
}

// P. J. Weinberger Hash Function
unsigned int PJWHash(IN const char *str)
{
	unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
	unsigned int ThreeQuarters    = (unsigned int)((BitsInUnignedInt  * 3) / 4);
	unsigned int OneEighth        = (unsigned int)(BitsInUnignedInt / 8);
	unsigned int HighBits         = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
	unsigned int hash             = 0;
	unsigned int test             = 0;

	while (*str)
	{
		hash = (hash << OneEighth) + (*str++);
		if ((test = hash & HighBits) != 0)
		{
			hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
		}
	}

	return (hash & 0x7FFFFFFF);
}

// ELF Hash Function
unsigned int ELFHash(IN const char *str)
{
	unsigned int hash = 0;
	unsigned int x    = 0;

	while (*str)
	{
		hash = (hash << 4) + (*str++);
		if ((x = hash & 0xF0000000L) != 0)
		{
			hash ^= (x >> 24);
			hash &= ~x;
		}
	}

	return (hash & 0x7FFFFFFF);
}

// BKDR Hash Function
unsigned int BKDRHash(IN const char *str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;

	while (*str)
	{
		hash = hash * seed + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}

// SDBM Hash Function
unsigned int SDBMHash(IN const char *str)
{
	unsigned int hash = 0;

	while (*str)
	{
		hash = (*str++) + (hash << 6) + (hash << 16) - hash;
	}

	return (hash & 0x7FFFFFFF);
}

// DJB Hash Function
unsigned int DJBHash(IN const char *str)
{
	unsigned int hash = 5381;

	while (*str)
	{
		hash += (hash << 5) + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}

// AP Hash Function
unsigned int APHash(IN const char *str)
{
	unsigned int hash = 0;
	int i;

	for (i=0; *str; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
		}
	}

	return (hash & 0x7FFFFFFF);
}

// 计算CRC值
unsigned int cal_crc(IN const char *str)
{
    int len(0) ;
    unsigned int crc(0); 
    char da(0);

    if (str == NULL)
    {
        exit(EXIT_FAILURE) ;
    }
    len = strlen(str) ;

    while(len-- > 0)
    { 
        da = (crc / 256);    /* 以8 位二进制数的形式暂存CRC 的高 8 位 */ 
        crc <<= 8;              
        crc ^= crc_ta[da^*str];   /*  高8位和当前字节相加后再查表求CRC ，再加上以前的CRC */ 
        str++; 
    }

    return(crc); 
}

void init_crc32_table()
{
    for (int i = 0; i != 256; i++)
    {
        unsigned long crc = i;
        for (int j = 0; j != 8; j++)
        {
            if (crc & 1)  // 如果是奇数
                crc = (crc >> 1) ^ 0xEDB88320;
            else     // 如果是偶数
                crc >>= 1;
        }
        crc32_table[i] = crc;
    }
}

unsigned long crc32(IN const char* str)
{
    unsigned int len(strlen(str)) ;
    unsigned long crc = 0xFFFFFFFF;
    for(unsigned int i = 0;i < len; i++)
    {
        int temp = (crc ^ str[i]) & 0XFF;  // 计算出表格中的一个数值
        crc = ((crc>>8) & 0XFFFFFF ) ^ crc32_table[temp];
    }
    return ~crc;  // 最后再取反一下
}

/*******************************************************************************
*
*  函 数 名 : SkipSpace
*  功能描述 : 去除字符串前面和后面无意义的空白符
*  参数列表 : szBuffer --  输入缓冲
*  说    明 : 
*  返回结果 : 如果成功，返回长度，否则返回0
*
*******************************************************************************/
int SkipSpace(IN char *szBuf, IN int nSize)
{
    int i = 0,
        j  = 0;
    
    if (szBuf == NULL)
    {
        return 0 ;
    }
    i = j = 0 ;
    // 去除后面的空格
    //for (i = nSize - 1; i >= 0 && (isspace(szBuf[i]) || szBuf[i] == 0); --i)
    for (i = nSize - 1; i >= 0 && (szBuf[i] == 0x20 || szBuf[i] == 0); --i)
    {
        szBuf[i] = 0;
    }
    for (j = 0; szBuf[j] != 0 && szBuf[i] == 0x20; ++j)
    {
        ;
    }
    if (j != 0)
    {
        for (i = 0; szBuf[j] != 0; ++i, ++j)
        {
            szBuf[i] = szBuf[j] ;
        }
    }
    
    szBuf[i+1] = 0 ;
    return i;
}

/*******************************************************************************
*
*  函 数 名 : GetParamCount
*  功能描述 : 取得参数个数
*  参数列表 : pszBuffer         --       命令字符串
*  说    明 : 命令字符串参数必须是以空格分离的,否则无法处理
*  返回结果 : 成功返回参数个数,失败返回0
*
*******************************************************************************/
int GetParamCount(IN char *pszCmd)
{
        if (NULL == pszCmd)
        {
                return 0 ;
        }
        int nCount = 1 ;
        BOOL bIsHaving = FALSE ;
        for (; 0 != *pszCmd; ++pszCmd) 
        {
                if ((' ' == *pszCmd))
                {
                        if (FALSE == bIsHaving)
                        {
                                ++nCount;
                                bIsHaving = TRUE ;
                        }
                }
                else
                {
                        bIsHaving = FALSE ;
                }
        }
        return nCount ;
}




