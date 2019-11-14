#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha2.h"

void print_sha256(char* plaintext, size_t size) {
	unsigned char digest[SHA256_DIGEST_LENGTH];

	SHA256_CTX sha_ctx;
	SHA256_Init(&sha_ctx); // コンテキストを初期化
	SHA256_Update(&sha_ctx, plaintext, size);
	SHA256_Final(digest, &sha_ctx); // digest に出力


	printf("plaintext:\n%s\n", plaintext);
	printf("strlen(plaintext) = %d\n", strlen(plaintext));
	printf("             size = %d\n", size);
	
	printf("SHA256: ");
	for (int i = 0; i < sizeof(digest); ++i) {
		printf("%02x", digest[i]);
	}
	printf("\n");
}

void print_sha256_rawbyte(char* plaintext, size_t size) {
	unsigned char digest[SHA256_DIGEST_LENGTH];

	SHA256_CTX sha_ctx;
	SHA256_Init(&sha_ctx); // コンテキストを初期化
	SHA256_Update(&sha_ctx, plaintext, size);
	SHA256_Final(digest, &sha_ctx); // digest に出力

	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
		printf("%c", (char)digest[i]);
		//putchar(digest[i]);
	}
}

int main(int argc, char const *argv[])
{
	if(argc < 2) {
		fprintf(stderr, "Error: missing argument.\n");
		exit(1);
	}

	FILE* fp = fopen(argv[1], "rb");
	if(fp == NULL) {
		fprintf(stderr, "Error: failed to open file (%s).\n", argv[1]);
		exit(1);
	}

	fseek(fp, 0L, SEEK_END);
	size_t filesize = ftell(fp);
	fclose(fp);

	fp = fopen(argv[1], "rb");
	char* plaintext = (char *)malloc(filesize);
	fread(plaintext, sizeof(char), filesize, fp);

	print_sha256_rawbyte(plaintext, filesize);

	return 0;
}
