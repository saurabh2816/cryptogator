#include <stdio.h>
#include <gpg-error.h>
#include<time.h>
#define GCRYPT_NO_DEPRECATED
#include <gcrypt.h>
#include<string.h>

gcry_sexp_t sexp_new(const char *str) {
	gcry_error_t error;

	gcry_sexp_t sexp;
	size_t len = strlen(str);
	if ((error = gcry_sexp_new(&sexp, str, len, 1))) {
		printf("Error in sexp_new(%s): %s\nSource: %s\n", str, gcry_strerror(error), gcry_strsource(error));
		exit(1);
	}

	return sexp;
}

char* sexp_string(gcry_sexp_t sexp) {
	size_t buf_len = gcry_sexp_sprint(sexp, GCRYSEXP_FMT_ADVANCED, NULL, 0);
	char *buffer = (char*)gcry_malloc(buf_len);
	if (buffer == NULL) {
		printf("gcry_malloc(%ld) returned NULL in sexp_string()!\n", buf_len);
		exit(1);
	}
	if (0 == gcry_sexp_sprint(sexp, GCRYSEXP_FMT_ADVANCED, buffer, buf_len)) {
		printf("gcry_sexp_sprint() lies!\n");
		exit(1);
	}
	return buffer;

	// This should be freed with gcry_free(buffer);
}



char* encrypt(char *public_key, char *plaintext){
	gcry_error_t error;

	gcry_mpi_t r_mpi;
	if ((error = gcry_mpi_scan(&r_mpi, GCRYMPI_FMT_USG, plaintext, strlen(plaintext), NULL))) {
		printf("Error in gcry_mpi_scan() in encrypt(): %s\nSource: %s\n", gcry_strerror(error), gcry_strsource(error));
		exit(1);
	}

	gcry_sexp_t data;
	size_t erroff;
	if ((error = gcry_sexp_build(&data, &erroff, "(data (flags raw) (value %m))", r_mpi))) {
		printf("Error in gcry_sexp_build() in encrypt() at %ld: %s\nSource: %s\n", erroff, gcry_strerror(error), gcry_strsource(error));
		exit(1);
	}

	gcry_sexp_t public_sexp = sexp_new(public_key);
	gcry_sexp_t r_ciph;
	if ((error = gcry_pk_encrypt(&r_ciph, data, public_sexp))) {
		printf("Error in gcry_pk_encrypt(): %s\nSource: %s\n", gcry_strerror(error), gcry_strsource(error));
		exit(1);
	}

	return sexp_string(r_ciph);
}

char* decrypt(char *private_key, char *ciphertext){
	gcry_error_t error;
	gcry_sexp_t data = sexp_new(ciphertext);

	gcry_sexp_t private_sexp = sexp_new(private_key);
	gcry_sexp_t r_plain;
	if ((error = gcry_pk_decrypt(&r_plain, data, private_sexp))) {
		printf("Error in gcry_pk_decrypt(): %s\nSource: %s\n", gcry_strerror(error), gcry_strsource(error));
		exit(1);
	}

	gcry_mpi_t r_mpi = gcry_sexp_nth_mpi(r_plain, 0, GCRYMPI_FMT_USG);

	unsigned char *plaintext;
	size_t plaintext_size;
	if ((error = gcry_mpi_aprint(GCRYMPI_FMT_USG, &plaintext, &plaintext_size, r_mpi))) {
		printf("Error in gcry_mpi_aprint(): %s\nSource: %s\n", gcry_strerror(error), gcry_strsource(error));
		exit(1);
	}

	return plaintext;
}

char* sign(char *private_key, char *document){
	gcry_error_t error;

	gcry_mpi_t r_mpi;
	if ((error = gcry_mpi_scan(&r_mpi, GCRYMPI_FMT_USG, document, 16, NULL))) {
		printf("Error in gcry_mpi_scan() in encrypt(): %s\nSource: %s\n", gcry_strerror(error), gcry_strsource(error));
		exit(1);
	}

	gcry_sexp_t data;
	size_t erroff;
	if ((error = gcry_sexp_build(&data, &erroff, "(data (flags raw) (value %m))", r_mpi))) {
		printf("Error in gcry_sexp_build() in sign() at %ld: %s\nSource: %s\n", erroff, gcry_strerror(error), gcry_strsource(error));
		exit(1);
	}

	gcry_sexp_t private_sexp = sexp_new(private_key);
	gcry_sexp_t r_sig;
	if ((error = gcry_pk_sign(&r_sig, data, private_sexp))) {
		printf("Error in gcry_pk_sign(): %s\nSource: %s\n", gcry_strerror(error), gcry_strsource(error));
		exit(1);
	}

	return sexp_string(r_sig);
}


void rsaalgo(char *filen)
 {
clock_t begin,enend,deend;
 //double time_spent,time;
 begin = clock();
 FILE * pFile;
 int lSize=16,k;
pFile = fopen ( filen , "r" );
  if (pFile==NULL) {fputs ("File error",stderr); exit (1);}
  char *buffer;
size_t result;
	char *public_key, *private_key;


FILE *f = fopen("rsaEncrypt.txt", "w");
if (f == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}
FILE *f1 = fopen("rsaDecrypt.txt", "w");
if (f1 == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}




	gcry_error_t error;

	// Generate a reduced strength (to save time) RSA key, 2048 bits long
	gcry_sexp_t params = sexp_new("(genkey (rsa (transient-key) (nbits 4:1024)))");
	gcry_sexp_t r_key;
	if ((error = gcry_pk_genkey(&r_key, params))) {
		printf("Error in generating keys");
		exit(1);
		}


		gcry_sexp_t public_sexp  = gcry_sexp_nth(r_key, 1);
	gcry_sexp_t private_sexp = gcry_sexp_nth(r_key, 2);

	public_key = sexp_string(public_sexp);
	private_key = sexp_string(private_sexp);
char *plaintext = "DEADBEEF01234567";

	printf("Public Key:\n%s\n", public_key);
	printf("Private Key:\n%s\n", private_key);

while(!feof(pFile))
{
buffer= (char*) malloc (sizeof(char)*lSize);

    result = fread (buffer,1,lSize,pFile);
  if (result != 16) {
	  for(k=0;k<16-result;k++)
	  strcat(buffer,"0");
	  //fputs ("Reading error",stderr); exit (3);
	  }
  if(!result)
       break;
     printf(" The Bytes Read %d \n", (int)result);

plaintext= buffer;



	printf("Plain Text:\n%s\n\n", plaintext);

	char *ciphertext;//=(char*) malloc (sizeof(char)*lSize);;
	ciphertext = encrypt(public_key, plaintext);
	printf("Ciper Text:\n%s\n", ciphertext);

	char *decrypted;
	decrypted = decrypt(private_key, ciphertext);
	printf("Decrypted Plain Text:\n%s\n\n", decrypted);

	char *signature;
	signature = sign(private_key, plaintext);
	printf("Signature:\n%s\n", signature);
int index;
int length2=strlen(ciphertext);
  for (index = 0; index<length2-1; index++)
    fprintf(f,"%c", ciphertext[index]);

	int length1=strlen(decrypted);
  for (index = 0; index<length1-3; index++)
    fprintf(f1,"%c", decrypted[index]);
//free(plaintext);

free(ciphertext);//free(decrypted);
}

 fclose(f1);fclose(f);
 fclose (pFile);
 //free(ciphertext);free(decrypted);



//	return 0;
}

