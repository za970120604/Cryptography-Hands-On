#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <iostream>
#include <fstream>
#include <ostream>

using namespace std;
using namespace CryptoPP;
const string toHex(const string str);

int main() {
	string digestHex, digest(32, 0);
	string msg, prev, nonce(4, 0);\
	int count = 0;
	ofstream out;
	SHA256 hash;

	out.open("out_1.txt", ios_base::app);
	
	msg = "Bitcoin";
	hash.Update((const byte*)msg.data(), msg.size());
	hash.Final((byte*)&digest[0]);
	/*digestHex = toHex(digest);
	cout << digestHex << endl;*/
	
	for (int leading0 = 0; leading0 < 8 ; leading0++) {
		int nonceInt = 0;
		prev = digest;

		do {
			nonce[0] = (nonceInt >> 24) & 0xFF;
			nonce[1] = (nonceInt >> 16) & 0xFF;
			nonce[2] = (nonceInt >> 8) & 0xFF;
			nonce[3] = (nonceInt >> 0) & 0xFF;

			msg = prev + nonce;
			hash.Update((const byte*)msg.data(), 36);
			hash.Final((byte*)&digest[0]);
			digestHex = toHex(digest);

			for (count = 0; digestHex.c_str()[count] == '0'; count++);
		} while (leading0 > count && ++nonceInt);

		out << leading0 << '\n' << toHex(prev) << '\n';
		out << toHex(nonce) << '\n' << digestHex << endl;
	}

	int nonceInt1 = 0;
	prev = digest;

	do {
		nonce[0] = (nonceInt1 >> 24) & 0xFF;
		nonce[1] = (nonceInt1 >> 16) & 0xFF;
		nonce[2] = (nonceInt1 >> 8) & 0xFF;
		nonce[3] = (nonceInt1 >> 0) & 0xFF;

		msg = prev + nonce;
		hash.Update((const byte*)msg.data(), 36);
		hash.Final((byte*)&digest[0]);
		digestHex = toHex(digest);

		for (count = 0; digestHex.c_str()[count] == '0'; count++);
	} while (7 > count && ++nonceInt1);

	out << 7 << '\n' << toHex(prev) << '\n';
	out << toHex(nonce) << '\n' << digestHex << endl;

	for (int leading0 = 8 ; leading0 < 16; leading0++) {
		int nonceInt = 0;
		prev = digest;

		do {
			nonce[0] = (nonceInt >> 24) & 0xFF;
			nonce[1] = (nonceInt >> 16) & 0xFF;
			nonce[2] = (nonceInt >> 8) & 0xFF;
			nonce[3] = (nonceInt >> 0) & 0xFF;

			msg = prev + nonce;
			hash.Update((const byte*)msg.data(), 36);
			hash.Final((byte*)&digest[0]);
			digestHex = toHex(digest);

			for (count = 0; digestHex.c_str()[count] == '0'; count++);
		} while (leading0 > count && ++nonceInt);

		out << leading0 << '\n' << toHex(prev) << '\n';
		out << toHex(nonce) << '\n' << digestHex << endl;
	}


	return 0;
}

const string toHex(const string str) {
	string hex;
	StringSource ss((const byte*)str.c_str(), str.size(), true,
		new HexEncoder(new StringSink(hex)));

	return hex;
}
