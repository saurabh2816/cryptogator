COMPILER=gcc
CFLAGS=-w
LIB=-lgcrypt
cryptogator:
	$(COMPILER) $(CLAGS) cryptogator.c -o cryptogator -lgcrypt
clean:
	rm -rf *.o cryptogator  AES128_Encryption AES256_Decryption rsaEncrypt.txt rsaDecrypt.txt
