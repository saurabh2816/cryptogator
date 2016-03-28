#include<gcrypt.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>



#define bSize 16					// Block Size for AES
#define blckLength 16
#define key_len 32
#define loop(n) for(i = 0; i < n; ++ i)

//#define GCRYPT_VERSION "1.6.4"

void bubbleSort(double [], int );
void swap(double *, double *);
//Function to generate Random Key



void run_AES256(char *fileName)
{


FILE *fin, *fout;                                       
                                    
int  j,k,bytes,i; 
char counter[16];                                   
char *key="";                        
char *buf = malloc(bSize),ch;                          //buffer to store the file

int mode = GCRY_CIPHER_MODE_CTR;

double AES256_Encryption_Time[100], AES256_Decryption_Time[100], total_E=0, total_D=0; 


clock_t start_clock_E, end_clock_E, start_clock_D, end_clock_D;  

//AES256_CBC Encryption Starts

gcry_cipher_hd_t aes_encrypt;

int additional;       //additional blocks for padding purposes


for(j=0; j<100;j++)
{
key = generate_random_key(32);
printf("\n%d. Key : %s\n",j+1,key);



start_clock_E = clock();                                      //starts clock

memset(counter, 0, 16);

fin = fopen(fileName, "rb");
fout = fopen("AES256_Encryption", "wb");

gcry_cipher_open(&aes_encrypt, GCRY_CIPHER_AES256, GCRY_CIPHER_MODE_CTR, 0);
gcry_cipher_setkey(aes_encrypt, key, key_len);
gcry_cipher_setiv(aes_encrypt, counter, blckLength);


while(!feof(fin))
    {
    additional = 0;
    bytes = fread(buf, 1, bSize, fin); 
        if(!bytes){break;}
   additional = bytes;
    while(additional<bSize)
         additional++;

    while(bytes < bSize)
        buf[bytes++] = additional;

    gcry_cipher_encrypt(aes_encrypt, buf, bSize, NULL, 0);
    bytes = fwrite(buf, 1, bSize, fout);
    }
end_clock_E = clock();

double total_EA256 = (double)(end_clock_E-start_clock_E)/CLOCKS_PER_SEC;
printf("Encrypption Time : %lf \n", total_EA256);
AES256_Encryption_Time[j] = total_EA256;

total_E += AES256_Encryption_Time[j];

gcry_cipher_close(aes_encrypt);
fclose(fin);
fclose(fout);



    //AES256_CBC Decryption Starts

//for(j=1; j<=100;j++){
//printf("Decryption : \n Key : %s\n",key);


start_clock_D = clock();
//printf("Started Decrypption Iteration No. %d using AES256 CBC Mode at : %ld \n ", j,start_clock_D);

gcry_cipher_open(&aes_encrypt, GCRY_CIPHER_AES256, GCRY_CIPHER_MODE_CTR, 0);
gcry_cipher_setkey(aes_encrypt, key, key_len);
gcry_cipher_setiv(aes_encrypt, counter, blckLength);

fin = fopen("AES256_Encryption", "rb") ;
fout = fopen("AES256_Decryption", "wb");
        

    gcry_cipher_decrypt(aes_encrypt, buf, blckLength, NULL, 0);
    bytes = fwrite(buf, 1, bSize, fout);
        

end_clock_D = clock();
double total_DA256 = (double)(end_clock_D-start_clock_D)/CLOCKS_PER_SEC;
printf("Decrypption Time : %lf\n",total_DA256);

AES256_Decryption_Time[j] = total_DA256;

total_D += AES256_Decryption_Time[j];
}
gcry_cipher_close(aes_encrypt);


free(buf);
buf = NULL;

printf("\n\nAES256\n------\nMean Encryption Time : %lf\nMean Decryption Time : %lf\n", total_E/100, total_D/100);

bubbleSort(AES256_Encryption_Time, (int)(sizeof(AES256_Encryption_Time)/sizeof(AES256_Encryption_Time[0])));
bubbleSort(AES256_Decryption_Time, (int)(sizeof(AES256_Decryption_Time)/sizeof(AES256_Decryption_Time[0])));

printf("Median Encryption Time : %lf\nMedian Decryption Time : %lf\n", (AES256_Encryption_Time[49] + AES256_Encryption_Time[50])/2, (AES256_Decryption_Time[49] + AES256_Decryption_Time[50])/2);

	printf("\nPress ENTER to continue ...");
	scanf("%c",&ch);

}
