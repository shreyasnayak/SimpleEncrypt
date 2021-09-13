# About SimpleEncrypt

[SimpleEncrypt](https://github.com/shreyasnayak/SimpleEncrypt) is a Cross-Language Encryption Library that provides the ability to encrypt and decrypt data in C++ and Python 3

## Build and install C++ shared library

- Install dependencies `sudo apt-get install libssl-dev openssl`
- Download or clone simple encrypt [C++ shared library](https://github.com/shreyasnayak/SimpleEncrypt/tree/main/CPP)
- Compile and install

```
git clone https://github.com/shreyasnayak/SimpleEncrypt
mkdir CPP/Build && cd CPP/Build
cmake ..
make
sudo make install
```

### Usage

```cpp
#include <stdio.h>
#include <iostream>
#include <simpleencrypt.h>

int main(int argc, char *argv[])
{
    unsigned char* key = (unsigned char *)"171A065A7675A09AECEC118DBC008A822A041FC2EBF2B3E4CF7A4C966E5D5897";
    unsigned char* iv = (unsigned char *)"2B5442AD8739992F";
    unsigned char* message = (unsigned char *)"Hello World";
    unsigned char decryptedtext[128];
    unsigned char ciphertext[128];
    int decryptedtext_len,ciphertext_len;

    /* Encrypt the data */
    ciphertext_len = SimpleEncrypt::encrypt((unsigned char *)message, static_cast<int>(strlen((char *)message)),key, iv,ciphertext);
    ciphertext[ciphertext_len]= '\0';

    /* Encrypt the data */
    ciphertext_len = SimpleEncrypt::encrypt((unsigned char *)message, static_cast<int>(strlen((char *) message)),key, iv,ciphertext);
    ciphertext[ciphertext_len]= '\0';

    /* Encode to Base64 */
    size_t len = static_cast<size_t>(ciphertext_len);
    std::string encoded = base64_encode((uint8_t*)ciphertext, len);


    /* Decode from Base64 */
    std::string decoded = base64_decode(encoded.c_str());

    /* Decrypt the Data */
    decryptedtext_len = SimpleEncrypt::decrypt((unsigned char *)decoded.c_str(), decoded.length(), key, iv,decryptedtext);
    decryptedtext[decryptedtext_len] = '\0';

    /* Allocate memory in heap & Return the value */
    char *decrypted_message = strdup((char * )decryptedtext);

    std::cout << "Encoded Message : "<< encoded.c_str() << std::endl;
    std::cout << "Decoded Message : "<< decrypted_message << std::endl;
    return 0;
}
```
