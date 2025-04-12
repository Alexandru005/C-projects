#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct
{
  uint16_t semnatura;
  uint32_t dimensiune;
  uint16_t rezervat1;
  uint16_t rezervat2;
  uint32_t offset;
}header_t;


typedef struct
{
  uint32_t dimensiune_header_dib;
  uint32_t latime;
  uint32_t inaltime;
  uint16_t numar_planuri;
  uint16_t biti_pixel;
  uint32_t tip_compresie;
  uint32_t dimensiune_img;
  uint32_t rez_orizontala;
  uint32_t rez_verticala;
  uint32_t nr_culori_paleta;
  uint32_t nr_culori_importante;
} dibheader_t;

typedef struct{
  uint8_t r;
  uint8_t g;
  uint8_t b;
}RGB;
#pragma pack(pop)

int transformare_pixel(RGB *pixel)
{
  uint8_t gray = 0.299 * pixel->r + 0.587 * pixel->g + 0.114 * pixel->b;
  pixel->r = gray;
  pixel->g = gray;
  pixel->b = gray;
  return 1;
}

int main()
{
  FILE *fin;

  if((fin = fopen("poza1.bmp", "rb")) == NULL)
    {
      printf("eroare\n");
      exit(1);
    }

  //Verificare Header/DIBHeader & Scriere Header/DIBHeader

  header_t header;
  dibheader_t dibheader;

  fread(&header,sizeof(header_t),1,fin);
  fread(&dibheader,sizeof(dibheader_t),1,fin);
  
  if(header.semnatura != 0x4D42 || dibheader.biti_pixel != 24)
    {
      printf("eroare1\n");
      fclose(fin);
      exit(2);
    }

  FILE *fout;

  if((fout = fopen("Poza_alb_negru.bmp", "wb")) == NULL)
    {
      printf("eroare\n");
      exit(3);
    }

  //SCRIEM HEADER-UL SI DIBHEADER-UL
  fwrite(&header,sizeof(header_t),1,fout);
  fwrite(&dibheader,sizeof(dibheader_t),1,fout);

  int inal = dibheader.inaltime;
  int lat = dibheader.latime;
  RGB pixel;

  //PRELUCRAM PIXEL CU PIXEL
  for(int i = 0; i < inal; i++)
    {
      for(int j = 0; j < lat; j++)
	{
	  fread(&pixel,sizeof(RGB),1,fin);
	  transformare_pixel(&pixel);
	  fwrite(&pixel,sizeof(RGB),1,fout);
	}
    }
  
  fclose(fin);
  fclose(fout);
  
  return 0;
}
