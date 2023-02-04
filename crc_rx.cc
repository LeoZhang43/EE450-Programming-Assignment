#include <iostream>
#include <fstream>
#include <string>

using namespace std;

    string readDataRx(int lineNumber) {
    string line;
    ifstream file("dataRx.txt");

    for (int i = 0; i < lineNumber - 1; ++i) {
        getline(file, line);
    }

    getline(file, line);
    file.close();
    return line;
    }

    string readDataTx(int lineNumber) {
    string line;
    ifstream file("dataTx.txt");

    for (int i = 0; i < lineNumber - 1; ++i) {
        getline(file, line);
    }

    getline(file, line);
    file.close();
    return line;
    }

    string xor1(string a, string b)
    {
    // Initialize result
    string result = "";
     
    int n = b.length();
     
    // Traverse all bits, if bits are
    // same, then XOR is 0, else 1
    for(int i = 1; i < n; i++)
    {
        if (a[i] == b[i])
            result += "0";
        else
            result += "1";
    }
    return result;
    }

    string mod2div(string dividend, string divisor)
    {
    // Number of bits to be XORed at a time.
    int pick = divisor.length();
    // Slicing the dividend to appropriate
    // length for particular step
    string tmp = dividend.substr(0, pick);
     
    int n = dividend.length();
     
    while (pick < n)
    {
        if (tmp[0] == '1')
         
            // Replace the dividend by the result
            // of XOR and pull 1 bit down
            tmp = xor1(divisor, tmp) + dividend[pick];
        else
         
            // If leftmost bit is '0'.
            // If the leftmost bit of the dividend (or the
            // part used in each step) is 0, the step cannot
            // use the regular divisor; we need to use an
            // all-0s divisor.
            tmp = xor1(std::string(pick, '0'), tmp) +
                  dividend[pick];
                   
        // Increment pick to move further
        pick += 1;
    }
     
    // For the last n bits, we have to carry it out
    // normally as increased value of pick will cause
    // Index Out of Bounds.
    if (tmp[0] == '1')
        tmp = xor1(divisor, tmp);
    else
        tmp = xor1(std::string(pick, '0'), tmp);
         
    return tmp;
    }

    string encodeData(string data, string key) {
    int l_key = key.length();
     
    // Appends n-1 zeroes at end of data
    string appended_data = (data +
                            std::string(
                                l_key - 1, '0'));
     
    string remainder = mod2div(appended_data, key);
     
    // Append remainder in the original data
    string codeword = data + remainder;
    return codeword;
    }

int main() {
    std::string key =  "10001000000100001";
    for(int i = 1;i <= 5;i++){
        string RendingMessage = encodeData(readDataTx(i), key);
        string TextingMessage_1 = readDataRx(2 * i - 1);
        string TextingMessage_2 = readDataRx(2 * i);
        if(RendingMessage.compare(TextingMessage_1) == 0){
            //std::cout << RendingMessage << std::endl;
            //std::cout << TextingMessage_1 << std::endl;
            std::cout << "Pass" << std::endl;
        }else{
            //std::cout << RendingMessage << std::endl;
            //std::cout << TextingMessage_1 << std::endl;
            std::cout << "Not Pass" << std::endl;
        }
        if(RendingMessage.compare(TextingMessage_2) == 0){
            //std::cout << RendingMessage << std::endl;
            //std::cout << TextingMessage_2 << std::endl;
            std::cout << "Pass" << std::endl;
        }else{
            //std::cout << RendingMessage << std::endl;
            //std::cout << TextingMessage_1 << std::endl;
            std::cout << "Not Pass" << std::endl;
        }
    }
}