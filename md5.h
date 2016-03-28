#include <gcrypt.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define GCRYPT_VERSION "1.6.4"
void MD5( const char *, char *);

void MD5( const char *key, char *filename)
{
	//function for HMAC
	size_t key_l = sizeof(key);
	FILE *fin;
	char *input;

	int i;

	
	fin = fopen(filename, "rb");
	
	
	fseek(fin, 0, SEEK_END);								// get to the end and point the pointer to get the file length

	long int fileLength = ftell(fin);						// gets current pointer position and stores as file length
	rewind(fin);											// sets file pointer at the beginning 
	input = (char *)malloc((fileLength+1)*sizeof(char));	// creates buffer of file size
	fread(input, fileLength, 1, fin);						// take the file in a buffer name 'input'


	gcry_md_hd_t md5;
	size_t hashlen = gcry_md_get_algo_dlen(GCRY_MD_MD5);	 // Retrieve the length in bytes of the digest yielded by SHA1
	unsigned char *hash; 									// variable to store the hash


	/*
	The gcry_error_t type is an alias for the libgpg-error type gpg_error_t. An
	error value like this has always two components, an error code and an error source.
	Both together form the error value.
	*/
	
	gpg_error_t error;
	

	   gcry_md_open (&md5, GCRY_MD_MD5, GCRY_MD_FLAG_HMAC); 	// Create a message digest object for SHA1
	   gcry_md_setkey (md5, key, key_l);						// Set the key for the MAC
	   gcry_md_write (md5, input, fileLength);					
	   hash = gcry_md_read (md5, GCRY_MD_MD5);
	   
	   char *output = (char*)malloc(sizeof(char) * ((hashlen*2)+1));
	   char *copy_out = output;
	   
	for(i =0; i<hashlen; i++, copy_out+=2)
	snprintf (copy_out, 3, "%02x", hash[i] );
	
	printf("%s\n", output);
	free(output);
	
	gcry_md_close(md5);
	fclose(fin);
}

