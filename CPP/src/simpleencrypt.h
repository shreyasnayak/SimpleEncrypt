#ifndef SIMPLEENCRYPT_H
#define SIMPLEENCRYPT_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "base64.h"

class SimpleEncrypt 
{
public:
    static void handleErrors(void);
    static int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,unsigned char *iv, unsigned char *ciphertext);
    static int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,unsigned char *iv, unsigned char *plaintext);
};

#endif // SIMPLEENCRYPT_H
