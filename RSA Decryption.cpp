#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <Wincrypt.h>

int main()
{
	HCRYPTPROV hCryptProv;
	FILE *keyFile = fopen(
		"rsa_key.bin",
		"rb"
	);
	if (keyFile == NULL) {
		printf("Failed to open rsa_key.bin.\n");
		return -1;
	}
	DWORD dataLen = 0x494;
	char keyData[0x494];
	int f = fread(keyData, dataLen, 1, keyFile);
	if (f != 1) {
		printf("Failed to read key.\n");
		printf("%d\n", f);
		return -1;
	}

	if (CryptAcquireContext(
		&hCryptProv,
		NULL,
		MS_ENH_RSA_AES_PROV,
		0x18,
		0xF0000000)) {
		printf("Acquired crypto context.\n");
	}
	else {
		printf("Failed to acquire crypto context.\n");
		return -1;
	}

	HCRYPTKEY decryptKey;

	if (CryptImportKey(hCryptProv, (BYTE*)keyData, dataLen, 0, 0, &decryptKey)) {
		printf("Imported key.\n");
	}
	else {
		printf("Failed to import key.\n");
		return -1;
	}

	FILE *encryptedFile = fopen("encrypted_aes_key", "rb");
	if (encryptedFile == NULL) {
		printf("Failed to open encrypted_aes_key.\n");
		return -1;
	}

	char fileData[256];
	if (fread(fileData, 256, 1, encryptedFile) != 1) {
		printf("Failed to read encrypted_aes_key.\n");
		return -1;
	}

	dataLen = 256;
	if (CryptDecrypt(decryptKey, 0, 1, 0, (BYTE*)fileData, &dataLen)) {
		printf("Decryption successful.\n");
	}
	else {
		printf("Decryption failed.\n");
		return -1;
	}

	for (int i = 0; i < 256; i++) {
		if (i && i % 16 == 0) {
			printf("\n");
		}
		printf("%02x ", fileData[i] & 0xFF);
		
	}

	return 0;
}

