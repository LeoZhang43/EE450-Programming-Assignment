#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string add_digit(string input) {
    string output = "";
    for (int i = 0; i < input.length(); i += 8) {
        int count = 0;
        for (int j = i; j < i + 8; j++) {
            if (input[j] == '1') count++;
        }
        if (count % 2 == 0) {
            output += input.substr(i, 8) + "0";
        } else {
            output += input.substr(i, 8) + "1";
        }
    }
    return output;
}

//get the first string in dataVs.txt file
string getFirstString(string line) {
    int spaceIndex = line.find(" ");
    return add_digit(line.substr(0, spaceIndex));
}

//calculate first and second data with XOR
string XOR(string first, string second){
	string answer = "";
	for(int i = 0;i < 72;i++){
		int p1 = first.at(i) - '0';
		int p2 = second.at(i) - '0';
		answer += p1 ^ p2 + '0';
	}
	return answer;
}

//get second string in dataVs.txt
string getSecondString(string line) {
    int spaceIndex = line.find(" ");
    string first = line.substr(0, spaceIndex);
    string second = line.substr(spaceIndex + 1);
    string modified = add_digit(first);
    // cout << modified.length() << endl;
    // cout << second.length() << endl;
    string result = XOR(modified, second);
    // cout << result.length() << endl;
    return result;
}

//do 2D parity check and get col, row in return
vector<string> convertString(string s) {
    char arr[8][9];
    int index = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 9; j++) {
            arr[i][j] = s[index];
            index++;
        }
    }

    string row = "";
    string col = "";
    int num = 0;
    for (int i = 0; i < 8; i++) {
        row += arr[i][8];
        if(arr[i][8] == '1') num++;
    }
    for (int j = 0; j < 8; j++) {
        int count = 0;
        for (int i = 0; i < 8; i++) {
            if (arr[i][j] == '1') count++;
        }
        col += (count % 2 == 0 ? '0' : '1');
    }
    row += (num % 2 == 0 ? '0' : '1');
    vector<string> ans;
    ans.push_back(row);
    ans.push_back(col);
    // cout << "Row: " << row << endl;
    // cout << "Col: " << col << endl;
    return ans;
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
 
// Performs Modulo-2 division
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
 
// Function used at the sender side to encode
// data by appending remainder of modular division
// at the end of data.
string encodeData(string data, string key)
{
    int l_key = key.length();
     
    // Appends n-1 zeroes at end of data
    string appended_data = (data +
                            std::string(
                                l_key - 1, '0'));
     
    string remainder = mod2div(appended_data, key);
     
    // Append remainder in the original data
    string codeword = data + remainder;
    return remainder;
}
 // checking if the message received by receiver is correct or not. If the remainder is all 0 then it is correct, else wrong.
void receiver(string data, string key)
{
    string currxor = mod2div(data.substr(0, key.size()), key);
    int curr = key.size();
    while (curr != data.size())
    {
        if (currxor.size() != key.size())
        {
            currxor.push_back(data[curr++]);
        }
        else
        {
            currxor = mod2div(currxor, key);
        }
    }
    if (currxor.size() == key.size())
    {
        currxor = mod2div(currxor, key);
    }
    if (currxor.find('1') != string::npos)
    {
        cout << "there is some error in data" << endl;
    }
    else
    {
        cout << "correct message received" << endl;
    }
}

int main() {
    ifstream file("dataVs.txt");
    string line;
    string key =  "10001000000100001";
    while (getline(file, line)) {
        string First = getFirstString(line);
        string Second = getSecondString(line);
        // cout << First << endl;
        // cout << Second << endl;
        string remainder = encodeData(First, key);
        string ans = mod2div(Second + remainder, key);
        //cout << ans << endl;
        vector<string> firstAnswer = convertString(First);
        vector<string> secondAnswer = convertString(Second);
        cout << "2D parity:" << "Col: " << firstAnswer[1] << "; Row: " << firstAnswer[0] << " ;";
        if(firstAnswer[0].compare(secondAnswer[0]) == 0 && 
            firstAnswer[1].compare(secondAnswer[1]) == 0){
            // std::cout << firstAnswer[0] << std::endl;
            // std::cout << secondAnswer[0] << std::endl;
            // std::cout << firstAnswer[1] << std::endl;
            // std::cout << secondAnswer[1] << std::endl;
            std::cout << "        Reuslt: Pass" << std::endl;
        }else{
            // cout << firstAnswer[0] << endl;
            // cout << secondAnswer[0] << endl;
            // cout << firstAnswer[1] << endl;
            // cout << secondAnswer[1] << endl;
            cout << "        Reuslt: Not Pass" << std::endl;
        }
        cout << "CRC :" << remainder << ";";
        if(ans.compare("0000000000000000") == 0){
            std::cout << "                           Reuslt: Pass" << std::endl;
        }else{
            std::cout << "                           Reuslt: Not Pass" << std::endl;
        }
        cout << "=======================================" << endl;
    }

    return 0;
}

