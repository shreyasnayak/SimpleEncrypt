#include <stdio.h>
#include <iostream>
#include <string.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "src/base64.h"

using namespace std;

void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv))
        handleErrors();

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,unsigned char *iv, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;
    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv))
        handleErrors();

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

extern "C" {

    char* decryptMessage(char* ciphertext,char* ckey,char* civ)
    {
        unsigned char* key = (unsigned char *)ckey;
        unsigned char* iv = (unsigned char *)civ;
        unsigned char decryptedtext[128];
        int decryptedtext_len;

        size_t len = static_cast<size_t>(strlen(ciphertext));
        ciphertext[len] = '\0';

        /* Decode from Base64 */
        string decoded = base64_decode(ciphertext);

        /* Decrypt the Data */
        decryptedtext_len = decrypt((unsigned char *)decoded.c_str(), decoded.length(), key, iv,decryptedtext);
        decryptedtext[decryptedtext_len] = '\0';

        /* Allocate memory in heap & Return the value */
        char *decrypted_message = strdup((char * )decryptedtext);
        return decrypted_message;
    }

    char* encryptMessage(char* message,char* ckey,char* civ)
    {
        unsigned char* key = (unsigned char *)ckey;
        unsigned char* iv = (unsigned char *)civ;
        unsigned char ciphertext[128];
        int ciphertext_len;

        /* Encrypt the data */
        ciphertext_len = encrypt ((unsigned char *)message, static_cast<int>(strlen(message)),key, iv,ciphertext);
        ciphertext[ciphertext_len]= '\0';

        /* Encode to Base64 */
        size_t len = static_cast<size_t>(ciphertext_len);
        string encoded = base64_encode((uint8_t*)ciphertext, len);

        /* Allocate memory in heap & Return the value */
        char *encrypt_message = strdup(encoded.c_str());
        return  encrypt_message;
    }


    void freeme(char *ptr)
    {
        free(ptr);
    }
}
