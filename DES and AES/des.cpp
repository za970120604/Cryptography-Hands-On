#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map> 
using namespace std;
string L = ""; 
string R = "" ; 
int IP[] =  {58, 50, 42, 34, 26, 18, 10, 2,
			 60, 52, 44, 36, 28, 20, 12, 4,
			 62, 54, 46, 38, 30, 22, 14, 6,
			 64, 56, 48, 40, 32, 24, 16, 8,
			 57, 49, 41, 33, 25, 17, 9,  1,
			 59, 51, 43, 35, 27, 19, 11, 3,
			 61, 53, 45, 37, 29, 21, 13, 5,
			 63, 55, 47, 39, 31, 23, 15, 7 
            };
int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
			   1, 58, 50, 42, 34, 26, 18,
			  10,  2, 59, 51, 43, 35, 27,
			  19, 11,  3, 60, 52, 44, 36,
			  63, 55, 47, 39, 31, 23, 15,
			   7, 62, 54, 46, 38, 30, 22,
			  14,  6, 61, 53, 45, 37, 29,
			  21, 13,  5, 28, 20, 12, 4
             }; 
int PC_2[] = {14, 17, 11, 24,  1,  5,
			   3, 28, 15,  6, 21, 10,
			  23, 19, 12,  4, 26,  8,
			  16,  7, 27, 20, 13,  2,
			  41, 52, 31, 37, 47, 55,
			  30, 40, 51, 45, 33, 48,
			  44, 49, 39, 56, 34, 53,
			  46, 42, 50, 36, 29, 32
             };
int shiftleft[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
int E[] = {32,  1,  2,  3,  4,  5,
		    4,  5,  6,  7,  8,  9,
		    8,  9, 10, 11, 12, 13,
		   12, 13, 14, 15, 16, 17,
		   16, 17, 18, 19, 20, 21,
		   20, 21, 22, 23, 24, 25,
		   24, 25, 26, 27, 28, 29,
		   28, 29, 30, 31, 32,  1
           };
int S_BOX[8][4][16] = {
	{  
		{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},  
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},  
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}, 
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} 
	},
	{  
		{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},  
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5}, 
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},  
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}  
	}, 
	{  
		{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},  
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},  
		{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},  
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}  
	}, 
	{  
		{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},  
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},  
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},  
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}  
	},
	{  
		{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},  
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},  
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},  
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}  
	},
	{  
		{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},  
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},  
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},  
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}  
	}, 
	{  
		{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},  
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},  
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},  
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}  
	}, 
	{  
		{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},  
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},  
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},  
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}  
	} 
};
int P[] = {16,  7, 20, 21,
		   29, 12, 28, 17,
		    1, 15, 23, 26,
		    5, 18, 31, 10,
		    2,  8, 24, 14,
		   32, 27,  3,  9,
		   19, 13, 30,  6,
		   22, 11,  4, 25 
          };
          
int IP_1[] = {40, 8, 48, 16, 56, 24, 64, 32,
			  39, 7, 47, 15, 55, 23, 63, 31,
			  38, 6, 46, 14, 54, 22, 62, 30,
			  37, 5, 45, 13, 53, 21, 61, 29,
			  36, 4, 44, 12, 52, 20, 60, 28,
			  35, 3, 43, 11, 51, 19, 59, 27,
			  34, 2, 42, 10, 50, 18, 58, 26,
			  33, 1, 41,  9, 49, 17, 57, 25
            };
map<string , char>mp ;
map<char , string>mp_r ;
map<int , char>mp_hex ;
map<char , int >mp_hex_r;
map<string , char>ascii ;
vector<string>subkeys;
//Binary operation
char XOR(char a , char b){
    if(a == b){
        return '0';
    }
    else{
        return '1'; 
    }
}
//Keys
string PC1_Key(string key){
    string k_in_hex = "" ;  
    for(int i = 0 ; i < key.length() ; i++){ //將key in ascii 轉成 hex; 
        int target = key[i] ; 
        string contain = "" ; 
        while(target != 0 ){
            contain += mp_hex[target%16] ; 
            target /= 16 ; 
        }
        while(contain.length() < 2){
            contain += '0' ; 
        }
        reverse(contain.begin() , contain.end()) ; 
        k_in_hex += contain ;  
    }
    string k_in_bit = "" ;    //將key in hex 轉成 binary ;
    for(int i = 0 ; i < k_in_hex.length() ; i++){
        k_in_bit += mp_r[k_in_hex[i]] ;
    }
    string PC_1_key = "" ;
    for(int i = 0 ; i < 56 ; i ++){   //64-->56
        PC_1_key += k_in_bit[PC_1[i]-1] ;
    }
    return PC_1_key ; 
};
void Create_keys(string before , int round){ //round start at 0 
    if(round == 16){
        return ;
    }
    string first = "" ; string second = "" ; 
    for(int i = 0 ; i < 28 ; i++){
        first += before[i] ; 
    }
    for(int i = 28 ; i < 56 ; i++){
        second += before[i] ; 
    }
    string temp1 = first ; 
    first = first.substr(shiftleft[round] , first.size() - shiftleft[round]) ;
    for(int i = 0 ; i < shiftleft[round] ; i++){
        first += temp1[i] ;
    }
    string temp2 = second ; 
    second = second.substr(shiftleft[round] , second.size() - shiftleft[round]) ;
    for(int i = 0 ; i < shiftleft[round] ; i++){
        second += temp2[i] ;
    }
    first += second ; 
    string final_subkey = "" ; 
    for(int i = 0 ; i < 48 ; i++){ //56(28*2)-->48
        final_subkey += first[PC_2[i]-1] ; 
    }
    subkeys.push_back(final_subkey) ;
    Create_keys(first , round + 1) ;
}
//cipher text to plain one
string IP_text(string target){
    string initial_in_bit = "" ;
    for(int i = 0 ; i < target.length() ; i++){
        initial_in_bit += mp_r[target[i]] ;
    }
    string after_IP = "" ;
    for(int i = 0 ; i < initial_in_bit.length() ; i++){
        after_IP += initial_in_bit[IP[i]-1] ; 
    }
    return after_IP ;
}
string f(int round){
    string expand = "" ; 
    for(int i = 0 ; i < 48 ; i++){ //32 --> 48
        expand += R[E[i]-1] ; 
    }
    string after_XOR = "" ;                            
    for(int i = 0 ; i < 48 ; i++){ //Ki xor with expanded 48 bits message 
        after_XOR += XOR(expand[i] , subkeys[15-round][i]) ;
    }
    vector<string>block ;         
    for(int i = 0 ; i <= 42 ; i+= 6){
        string b = after_XOR.substr(i , 6);
        block.push_back(b) ; 
    }
    string f_output = "" ; 
    for(int i = 0 ; i < 8 ; i++){   //S-box part
        string target = block[i] ;
        int row = (target[0] - '0')*2 + (target[5] - '0');
        int column = (target[1] - '0')*8 + (target[2] - '0')*4 +(target[3] - '0')*2 +(target[4] - '0')  ;
        int ans = S_BOX[i][row][column] ;
        string ff = "" ; 
        while(ans != 0 ){
            if(ans%2){
                ff += '1' ; 
            }
            else{
                ff += '0' ;
            }
            ans/=2 ;
        }
        while(ff.length() < 4){
            ff += '0' ; 
        }
        reverse(ff.begin() , ff.end()) ;
        f_output += ff ;
    }
    string f_final = "" ;
    for(int i = 0 ; i < 32 ; i++){  //straight P permutation 
        f_final += f_output[P[i]-1] ;
    }
    return f_final ; 
}
void Feistel(int round){
    if(round == 16){
        return ;
    }
    string temp = L ; 
    L = R ; 
    string after_f = f(round) ;
    R = "" ; 
    for(int i = 0 ; i < 32 ; i++){
        R += XOR(temp[i] , after_f[i]) ;
    }
//    cout<<"L"<<15-round<<" : "<<endl;
//    for(int i = 0 ; i <= 28 ; i+= 4){
//        cout<<L.substr(i,4)<<" ";
//    }
//    cout<<endl;
//    cout<<"R"<<15-round<<" : "<<endl;
//    for(int i = 0 ; i <= 28 ; i+= 4){
//        cout<<R.substr(i,4)<<" ";
//    }
//    cout<<endl;
    Feistel(round+1) ; 
}
string IP_1_text(string s){
    string res = "" ; 
    for(int i = 0 ; i < 64 ; i++){
        res += s[IP_1[i]-1] ;
    }
    return res ; 
}
int main(){
    mp["0000"] = '0' ; mp["0001"]  = '1' ; mp["0010"] = '2' ; mp["0011"] = '3' ;
    mp["0100"] = '4' ; mp["0101"]  = '5' ; mp["0110"] = '6' ; mp["0111"] = '7' ;
    mp["1000"] = '8' ; mp["1001"]  = '9' ; mp["1010"] = 'A' ; mp["1011"] = 'B' ;
    mp["1100"] = 'C' ; mp["1101"]  = 'D' ; mp["1110"] = 'E' ; mp["1111"] = 'F' ;
    
    mp_r['0'] = "0000" ; mp_r['1'] = "0001" ; mp_r['2'] = "0010" ; mp_r['3'] = "0011" ; 
    mp_r['4'] = "0100" ; mp_r['5'] = "0101" ; mp_r['6'] = "0110" ; mp_r['7'] = "0111" ;
    mp_r['8'] = "1000" ; mp_r['9'] = "1001" ; mp_r['A'] = "1010" ; mp_r['B'] = "1011" ;
    mp_r['C'] = "1100" ; mp_r['D'] = "1101" ; mp_r['E'] = "1110" ; mp_r['F'] = "1111" ;
    
    mp_hex[0] = '0' ; mp_hex[1] = '1' ; mp_hex[2] = '2' ; mp_hex[3] = '3' ;
    mp_hex[4] = '4' ; mp_hex[5] = '5';  mp_hex[6] = '6' ; mp_hex[7] = '7' ;
    mp_hex[8] = '8' ; mp_hex[9] = '9' ; mp_hex[10] = 'A' ; mp_hex[11]= 'B' ;
    mp_hex[12] = 'C' ; mp_hex[13] = 'D' ; mp_hex[14] = 'E' ; mp_hex[15] = 'F' ;
    
    mp_hex_r['0'] = 0 ; mp_hex_r['1'] = 1 ; mp_hex_r['2'] = 2 ; mp_hex_r['3'] = 3 ;
    mp_hex_r['4'] = 4 ; mp_hex_r['5'] = 5 ; mp_hex_r['6'] = 6 ; mp_hex_r['7'] = 7 ;
    mp_hex_r['8'] = 8 ; mp_hex_r['9'] = 9 ; mp_hex_r['A'] = 10 ; mp_hex_r['B'] = 11 ;
    mp_hex_r['C'] = 12 ; mp_hex_r['D'] = 13 ; mp_hex_r['E'] = 14 ; mp_hex_r['F'] = 15 ;
    
    string key = "" ; string cipher_text = "" ;
    int N ; 
    cin >> N ; 
    while(N--){
        cin >> key ; 
        cin >> cipher_text ;
        string cipher_in_bit = IP_text(cipher_text) ;
        
        
        L = cipher_in_bit.substr(0,32) ; 
        R = cipher_in_bit.substr(32,32) ;
         
        string C0D0 = PC1_Key(key) ; 
        Create_keys(C0D0 , 0) ;
        Feistel(0) ;
        string res = IP_1_text(R + L);
        string ans = "" ; 
        for(int i = 0 ; i <= 60 ; i+= 4){
            string temp = res.substr(i,4) ;
            ans += mp[temp] ; 
        }
        string aans = "" ;
        for(int i = 0 ; i <= 14 ; i+= 2){
            int nnum = 0 ; 
            string temp = ans.substr(i,2) ;
            for(int j = 0 ; j < 2 ; j++){
                nnum += mp_hex_r[temp[j]]*pow(16,1-j);
            }
            aans += string(1 , (char)nnum);
        }
        cout<<aans<<endl;
        L = "" ; 
        R = "" ;
        subkeys.clear();
    }
    return 0 ;    
}

