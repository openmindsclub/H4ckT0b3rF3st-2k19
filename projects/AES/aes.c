#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes.h"

void xor(int a[],int b[],int *c,int len)
{

}

void MC(int col[],int *r,int begin)
{

}

void invMC(int col[],int *r,int begin)
{

}

void expandKey(int key[],int *subKeys)
{
}

void encrypt(char plainText[],char key[],char *ciphertext,int *subKeys)
{

}

void decrypt(char plainText[],char key[],char *ciphertext,int *subKeys)
{
    int cipherText[16],tmp[16];
    int *t = malloc(16 * sizeof(int));

    for(size_t _=0;_<16;_++) cipherText[_] = (__uint8_t)plainText[_];

    for(size_t _=0;_<16;_++) tmp[_] = *(subKeys + 160 + _);
    xor(cipherText,tmp,t,16);
    for(size_t _=0;_<16;_++) cipherText[_] = *(t + _);

    for (size_t rnd=9;rnd>=1;rnd--)
    {
        for(size_t _=0;_<16;_++) tmp[_] =  cipherText[SRi[_]];//invShiftRows/invSubBytes
        for(size_t _=0;_<16;_++) cipherText[_] = Si[tmp[_]];
        

        for(size_t _=0;_<16;_++) tmp[_] = *(subKeys + rnd * 16 + _);//addRoundKey
        xor(cipherText,tmp,t,16);
        for(size_t _=0;_<16;_++) cipherText[_] = *(t + _);

        for (size_t i=0;i<4;i++)//invMixColumns
        {
            for(size_t _=0;_<4;_++) tmp[_] = cipherText[4*i+_];
            
            invMC(tmp,cipherText,4*i);
        }
        
    }

    for(size_t _=0;_<16;_++) tmp[_] =  cipherText[SRi[_]];//invShiftRows/invSubBytes
    for(size_t _=0;_<16;_++) cipherText[_] = Si[tmp[_]];

    for(size_t _=0;_<16;_++) tmp[_] = *(subKeys + _);//addRoundKey
    xor(cipherText,tmp,t,16);
    for(size_t _=0;_<16;_++) ciphertext[_] = *(t + _);

    ciphertext[16] = '\0';
    free(t);
}

char * toHex(char *msg,int len)// encodes a message in hex
{
    static char * msgHex;
    char *tmp;

    msgHex = malloc(2 * len + 1);
    tmp = malloc(3 * sizeof(char));
    
    for (size_t i=0;i<len;i++)
    {
        snprintf(tmp,3,"%02x",(__uint8_t)*(msg+i));
        msgHex = strcat(msgHex,tmp);
    }
    return msgHex;
}
void main(int argc,char **argv)
{
    char *file,*cipherText,*plainText,tmp[16];
    int len = 0,Key[16],*subKeys = malloc(176 * sizeof(int)+1);

    if (argc != 3)
    {
        printf("[+] Usage: %s <plaintext> <key>\n",argv[0]);
        exit(0);
    }

    if (strlen(argv[2]) != 16)
    {
        printf("[+] the key length must be 16 bytes\n");
        exit(0);
    }

    if (strlen(argv[1]) % 16) len = 16 - (strlen(argv[1]) % 16);
    plainText = malloc(strlen(argv[1]) + len + 1);
    cipherText = malloc(strlen(argv[1]) + len + 1);
    for(size_t _=0;_<16;_++) Key[_] = (__uint8_t)argv[2][_];
    expandKey(Key,subKeys);

    for (size_t i=0;i<strlen(argv[1]);i++) *(plainText+i) = argv[1][i];
    
    for (size_t i=0;i<len;i++)//PKCS1.5 Padding
    {
        *(plainText + strlen(argv[1]) + i) = (char)len;
    }

    for (size_t i=0;i<strlen(plainText)/16;i++)//encrypt each block seperetaly and add it output of the encryption to the ciphertext
    {
        for (size_t _=0;_<16;_++) tmp[_] = *(plainText + 16*i + _);
        encrypt(tmp,argv[2],cipherText,subKeys);
    }
    printf("[+] key: %s\n[+] plaintext: %s\n[+] ciphertext: %s\n",argv[2],argv[1],toHex(cipherText,(strlen(plainText)/16)*16));
   
}