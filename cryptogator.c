#include<stdio.h>
#include<stdlib.h>
#include<gcrypt.h>
#include<string.h>
#include<time.h>
#include "sha1.h"
#include "md5.h"
#include "aes128.h"
#include "rsa.h"
#include "sha256.h"
#include "aes256.h"

//#define GCRYPT_VERSION "1.6.4"
#define loop(n) for(i = 0; i < n; ++ i)

/*funtion prototypes*/
void run_MD5(char *);
void run_SHA1(char *);
void run_SHA256(char *);
void run_AES128(char *);
void run_AES256(char *);
int i;

char ch;
double mean,median;


double Calculate_mean(double SHA1_time[], int len)
{
	double sum = 0.0;
	int i;
//	len = sizeof(SHA1_time)/sizeof(SHA1_time[0]);
	for(i=0; i<len; i++)
		sum += SHA1_time[i];

	return sum/len;
}

void swap(double *num1, double *num2)
{
    double temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
 
void bubbleSort(double arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}

int main(int argc, char *argv[])
{

	// check for argument numbers
	if( argc == 2)
		printf("Opening %s",argv[1]);
	else
	{
		printf("Please enter file as an argument. Exiting ... \n");
		exit(EXIT_FAILURE);
	}
	
	run_MD5(argv[1]);
	run_SHA1(argv[1]);
	run_SHA256(argv[1]);
	run_AES128(argv[1]);
	run_AES256(argv[1]);
	//rsaalgo(argv[1]);
	
return 0;
}

void run_MD5(char *filename)
{
	clock_t start_clock, end_clock;
	double MD5_time[100];
	char key[16]={0};

	printf("\n\n****************************\n\tMD5\n****************************\n\n");
	loop(100)
	{
		gcry_randomize(key,16,GCRY_STRONG_RANDOM); 
		start_clock = clock();
		MD5(key,filename);
		end_clock = clock();
		MD5_time[i] = (double)(end_clock - start_clock) / CLOCKS_PER_SEC; 
		printf("%d. Time : %lf \n", i+1, MD5_time[i]);	
	}
	printf("\n\nMD5\n---\nMean :: %lf \n", Calculate_mean(MD5_time,(int)(sizeof(MD5_time)/sizeof(MD5_time[0]))));
	bubbleSort(MD5_time, (int)(sizeof(MD5_time)/sizeof(MD5_time[0])));
	printf("Median :: %lf \n",(MD5_time[49] + MD5_time[50])/2);
	printf("\nPress ENTER to continue to SHA1...");
	scanf("%c",&ch);
}


void run_SHA1(char *filename)
{
	clock_t start_clock, end_clock;
	int n;
	double SHA1_time[100];
	char key[16]={0};
	//for(i=0; i<100; i++)
		printf("\n\n****************************\n\tSHA1\n****************************\n\n");
	loop(100)
	{
		//Fill buffer with length random bytes using a random quality as defined by GCRY_STRONG_RANDOM.
		gcry_randomize(key,16,GCRY_STRONG_RANDOM);
		start_clock = clock(); 
		SHA1(key, filename);
		end_clock = clock();
		SHA1_time[i] = (double)(end_clock - start_clock) / CLOCKS_PER_SEC; 
		printf("%d. Time : %lf \n", i+1, SHA1_time[i]);	
	}

	printf("\n\nSHA1\n----\nMean :: %lf \n", Calculate_mean(SHA1_time,(int)(sizeof(SHA1_time)/sizeof(SHA1_time[0]))));

	bubbleSort(SHA1_time, (int)(sizeof(SHA1_time)/sizeof(SHA1_time[0])));
	printf("Median :: %lf \n",(SHA1_time[49] + SHA1_time[50])/2);
	printf("\nPress ENTER to continue to SHA256 ...");
	scanf("%c",&ch);
	/*SHA1 ends */
}

void run_SHA256(char *filename)
{
	clock_t start_clock, end_clock;
	int n;
	double SHA256_time[100];
	char key[16]={0};
	//for(i=0; i<100; i++)
		printf("\n\n****************************\n\tSHA256\n****************************\n\n");
	loop(100)
	{
		gcry_randomize(key,16,GCRY_STRONG_RANDOM);
		start_clock = clock(); 
		SHA256(key, filename);
		end_clock = clock();
		SHA256_time[i] = (double)(end_clock - start_clock) / CLOCKS_PER_SEC; 
		printf("%d. Time : %lf \n\n", i+1, SHA256_time[i]);	
	}

	printf("\n\nSHA256\n------\nMean :: %lf \n", Calculate_mean(SHA256_time,(int)(sizeof(SHA256_time)/sizeof(SHA256_time[0]))));

	bubbleSort(SHA256_time, (int)(sizeof(SHA256_time)/sizeof(SHA256_time[0])));
	printf("Median :: %lf \n",(SHA256_time[49] + SHA256_time[50])/2);
	printf("\nPress ENTER to continue AES128 ...");
	scanf("%c",&ch);
	/*SHA256 ends */
}




