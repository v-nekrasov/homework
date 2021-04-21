#pragma pack(1)
typedef struct BMPHEAD_

  {                                                              

    unsigned short int Signature ;              // Must be 0x4d42 == ”BM”               //0

    unsigned int FileLength ;                  // в байтах                                                          //2

    unsigned int Zero ;                           // Must be 0                                                          //6

    unsigned int Ptr ;                              // смещение к области данных          //10

    unsigned int Version ;// длина оставшейся части заголовка=0x28          //14

    unsigned int Width ;          // ширина изображения в пикселах                 //18

    unsigned int Height ;         // высота изображения в пикселах                  //22

    unsigned short int   Planes ;                // к-во битовых плоскостей                             //26

    unsigned short int   BitsPerPixel ;       // к-во бит на папиксел       //28

    unsigned int Compression ;              // сжатие: 0 или 1 или 2                    //30

    unsigned int SizeImage ;                   // размер блока данных в байтах      //34

    unsigned int XPelsPerMeter ;           // в ширину: пикселов на метр          //38

    unsigned int YPelsPerMeter ;           // в высчоту: пикселов на метр        //42

    unsigned int ClrUsed ;      // к-во цветов в палитре                   //46

    unsigned int ClrImportant ; // к-во используемых цветов в палитре //50

	unsigned char pal[256][4];

	unsigned char (**v)[4];// true color

	int **g; // grayscale 0<=g[][]<=255 || bitmap
	
  } BMPHEAD;
#pragma pack()

