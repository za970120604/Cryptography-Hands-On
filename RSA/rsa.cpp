#include <iostream>
#include <fstream>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cassert>

using namespace std;
using namespace CryptoPP;

Integer enc(long e, string nstr, string message) {
	const Integer n(nstr.c_str());
	const Integer m((const byte*)message.data(), message.size());
	RSA::PublicKey pubKey;
	pubKey.Initialize(n, e);
	Integer ciphertext = pubKey.ApplyFunction(m);
	return ciphertext;
}
string dec(long e, string dstr, string nstr , string ciphertext) {
	const Integer n(nstr.c_str());
	const Integer d(dstr.c_str());
	const Integer c(ciphertext.c_str());
	AutoSeededRandomPool rng;
	string message;
	RSA::PrivateKey privKey;
	try {
		privKey.Initialize(n , e , d);
	}
	catch (InvalidArgument e) {
		return "";
	}
	const Integer m = privKey.CalculateInverse(rng, c);
	message.resize(m.MinEncodedSize());
	m.Encode((byte*)message.data(), message.size());
	return message;
}

int main() {
	ofstream out;
	out.open("out.txt");

	const Integer c1 = enc(0x11, "0x04823f9fe38141d93f1244be161b20f", "Hello World!");
	const Integer c2 = enc(0x10001, "0x9711ea5183d50d6a91114f1d7574cd52621b35499b4d3563ec95406a994099c9", "RSA is public key.");
	out << "Ciphertext 1 : " << hex << c1 << endl;
	out << "Ciphertext 2 : " << hex << c2 << endl;

	string arr[16]; 
	arr[0] = "0"; arr[1] = "1"; arr[2] = "2"; arr[3] = "3"; arr[4] = "4"; arr[5] = "5"; arr[6] = "6"; arr[7] = "7"; arr[8] = "8";
	arr[9] = "9"; arr[10] = "a"; arr[11] = "b"; arr[12] = "c"; arr[13] = "d"; arr[14] = "e"; arr[15] = "f"; 

	string to_append = "0x53a0a95b089cf23adb5cc73f07";
	int flag = 1; 
	for (int i = 0; i < 16 && flag; i++) {
		for (int j = 0; j < 16 && flag ; j++) {
			for (int k = 0; k < 16 && flag; k++) {
				for (int l = 0; l < 16 && flag; l++) {
					for (int m = 0; m < 16 && flag; m++) {
						string to_test = to_append + arr[i] + arr[j] + arr[k] + arr[l] + arr[m];
						string possible = dec(0x1d35, to_test, "0xc4b361851de35f080d3ca7352cbf372d", "0xa02d51d0e87efe1defc19f3ee899c31d");
						if (possible != "") {
							out << "Private key : "<< to_test << endl;
							out << "Message : " << possible << endl;
							flag = 0; 
						}	
					}
				}
			}
		}
	}

	return 0;
}
