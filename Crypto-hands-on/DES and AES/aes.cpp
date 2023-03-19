#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"
#include <string>

#include <iostream>
#include <string>
#include <fstream>

int main()
{
    using namespace CryptoPP;

    HexEncoder encoder(new FileSink(std::cout));

    std::ofstream out;
    out.open("aes-out.txt");

    std::string plain = "AES is the US block cipher standard.";
    std::string cipher;


    byte k[16];
    std::string s = "keyis84932731830";
    for (int i = 0; i < 16; i++)    k[i] = s[i];

    byte IV_0[16];
    s = "0000000000000000";
    for (int i = 0; i < 16; i++)    IV_0[i] = s[i];

    byte IV_9[16];
    s = "9999999999999999";
    for (int i = 0; i < 16; i++)    IV_9[i] = s[i];

    SecByteBlock tmp_1(k, sizeof(k));
    SecByteBlock key((const byte*)tmp_1.data(), tmp_1.size());
    SecByteBlock tmp_2(IV_0, sizeof(IV_0));
    SecByteBlock iv_0((const byte*)tmp_2.data(), tmp_2.size());
    SecByteBlock tmp_3(IV_9, sizeof(IV_9));
    SecByteBlock iv_9((const byte*)tmp_3.data(), tmp_3.size());

    AESEncryption aese(key, key.size());
    CFB_Mode_ExternalCipher::Encryption cfb(aese, IV_0, 4);
    StringSource CFB(plain, true, new StreamTransformationFilter(cfb, new StringSink(cipher)));
    std::cout << "cipher text: ";
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    std::cout << std::endl;
    cipher.clear();

    CBC_Mode< AES >::Encryption e_0;
    e_0.SetKeyWithIV(key, key.size(), iv_0);
    StringSource cbc_0(plain, true, new StreamTransformationFilter(e_0, new StringSink(cipher), StreamTransformationFilter::ZEROS_PADDING));
    std::cout << "cipher text: ";
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    std::cout << std::endl;
    cipher.clear();

    CBC_Mode< AES >::Encryption e_9;
    e_9.SetKeyWithIV(key, key.size(), iv_9);
    StringSource cbc_9(plain, true, new StreamTransformationFilter(e_9, new StringSink(cipher)));
    std::cout << "cipher text: ";
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    std::cout << std::endl;
    cipher.clear();

    ECB_Mode< AES >::Encryption e;
    e.SetKey(key, key.size());
    StringSource ecb(plain, true, new StreamTransformationFilter(e, new StringSink(cipher)));
    std::cout << "cipher text: ";
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    std::cout << std::endl;
    cipher.clear();


    return 0;
}