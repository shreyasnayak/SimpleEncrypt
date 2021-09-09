# CPP_Library

CPP_Library will have code for SimpleEncrypt shared library for python package, this will be wrapper library between CPP code and python.

Install dependencies

```
sudo apt-get install libssl-dev openssl
```

## Building SimpleEncrypt Python shared library

```
mkdir SimpleEncrypt_Python/CPP_Library/Build
cd SimpleEncrypt_Python/CPP_Library/Build
cmake ..
make
sudo make install
```

# Python_Package
