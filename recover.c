#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Recuperando imagens jpeg no cartão de cartão de mémoraia.
typedef  uint8_t  BYTE ;

int main(int argc, char *argv[])
{
    // Fundamenta o uso correto 
    if(argc!=2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // arquivo de entrada aberto (imagem forense)
    FILE*inptr=fopen(argv[1], "r");
    
     // Se o arquivo não conter valor/ falha
    if(inptr==NULL)
    {
        fprintf(stderr, "Não é possível abrir o arquivo %s.\n", argv[1]);
        return 2;
    }
    
    //// Não precisa apontar para nada.
    FILE* outptr = NULL;
    
   //criar um conjunto de 512 elementos para armazenar os 512 bytes do cartão de memória
    BYTE buffer[512];
 
    //counta os jpegs que foram encontrados
    int jpeg=0;
    
    // Arrray para armazenar os arquivos
    char filename[8]={0};
         
    //Ler o cartão de mémoria até o fim 
    while(fread(buffer, sizeof(BYTE)*512, 1, inptr)==1)
    {
        //verificação se encontrou um jpeg
        if(buffer[0]==0xFF&&buffer[1]==0xD8&&buffer[2]==0xFF&&(buffer[3]&0xF0)==0xE0)
        { 
            //fechar outptr se jpeg foi encontrado antes e esccreve em ###.jpg
            if(outptr != NULL)
            {
                fclose(outptr); 
            }
                sprintf(filename, "%03d.jpg", jpeg++); // A função sprintf serve para formatar uma string e guardar o resultado em um array (na realidade, ela aceita um ponteiro), e não mostrar nada na tela .
                
                // abrir um novo outptr para escrever um novo jpeg encontrado
                outptr = fopen(filename, "w");
        }
       
       // manter a escrita no arquivo jpeg se não for encontrado um novo jpeg    
       if(outptr != NULL)
       {
            fwrite(buffer, sizeof(BYTE)*512, 1, outptr);
       }
    }
  
    
    // fechar o último outptr aberto
     if (outptr != NULL)
     {
      fclose(outptr);
     }
    
    // fechar a imagem foresnse
      fclose(inptr);
    
    return 0;
    
}
