## Advanced Encryption Cipher(AES)
this is an implementation of the AES-128 cipher in ECB mode in C language

## Usage

``` bash
$ gcc aes.c -o aes
$ ./aes <plaintext> <key>
[+] key: <key>
[+] plaintext: <plaintext>
[+] ciphertext: <hex-encoded ciphertext>
```

## Tasks

complete each one of the functions stated below:
1. xor
2. Mix Columns(MC)
3. inverse Mix Columns(invMc)
4. expand Key
5. encrypt

## Resources
[FIPS 197, Advanced Encryption Standard (AES)](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf)
