#include <iostream>
#include <vector>
#include <algorithm>

void compare_with_the_beginning(std::string &s, std::vector <int> &z, int start_pos, int cur_pos, int &l, int &r){
    for(int j = start_pos; j < s.size() && s[j] == s[j - cur_pos]; j++){
        z[cur_pos]++;
    }

    if(z[cur_pos] > start_pos - cur_pos){
        l = cur_pos;
        r = cur_pos + z[cur_pos] - 1;
    }
}

void Z (std::string &s, std::vector<int> &z){
    z[0] = s.size();
    int l = 0, r = 0;
    for(int i = 1; i < s.size(); i++){
        if(i > r){
            z[i] = 0;
            compare_with_the_beginning(s, z, i, i, l, r);
        }else{
            if(i + z[i - l] - 1 < r){
                z[i] = z[i - l];
            }else{
                z[i] = r - i + 1;
                compare_with_the_beginning(s, z, r + 1, i, l ,r);
            }
        }
    }
}

void Prefix (std::string &str, std::vector<int> &prefix){
    prefix[0] = 0;
    for(int i = 1; i < prefix.size(); i++){
        int l = prefix[i - 1];
        while(str[l] != str[i] && l > 0){
            l = prefix[l - 1];
        }
        if(str[l] == str[i]){
            prefix[i] = l + 1;

        }else{
            prefix[i] = 0;
        }
    }
}

void prefix_to_str(std::string &str, const std::vector <int> &prefix){
    int k = 0;
    for(int i = 0; i < prefix.size(); i++){
        if(prefix[i] == 0){
            str.push_back('a' + k);
            k++;
        }else{
            str.push_back(str[prefix[i] - 1]);
        }
    }
}

void z_to_str(std::string &str, const std::vector <int> &z){
    int k = 0;
    for(int i = 0; i < str.size(); i++){
        if(z[i] == 0){
            str.push_back('a' + k);
            k++;
        }else{
            for(int j = 0; j < z[i]; j++){
                str.push_back(str[j]);
            }
            i += z[i] - 1;
        }
    }
}

void Z_to_Prefix(std::vector<int> &z){
    std::string s(z.size(), 'a');
    z_to_str(s, z);
    Prefix(s, z);
}

void Prefix_to_Z(std::vector<int> &prefix){
    std::string s(prefix.size(), 'a');
    prefix_to_str(s, prefix);
    Z(s, prefix);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int N, x;
    std::cin >> N;
    std::vector<int> z;
    for(int i = 0; i < N; ++i){
        std::cin >> x;
        z.push_back(x);
    }

    return 0;
}

void prefix_to_str(string &str, const vector <int> &prefix)
{
    str.push_back('a');
    int k = 1;
    for(int i = 1; i < prefix.size(); i++)
    {
        if(prefix[i] == 0)
        {
            str.push_back('a' + k);
            k++;
        }
        else
        {
            str.push_back(str[prefix[i] - 1]);
        }
    }
}

void z_to_str(string &str, const vector <int> &z)
{
    str.push_back('a');
    int k = 1;

    for(int i = 0; i < str.size(); i++)
    {
        if(z[i] == 0)
        {
            str.push_back('a' + k);
            k++;
        }
        else
        {
            for(int j = 0; j < z[i]; j++)
            {
                str.push_back(str[j]);
            }
            i += z[i] - 1;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> Prefix (std::string &str, std::vector<int> &prefix){
    prefix[0] = 0;
    for(int i = 1; i < prefix.size(); i++){
        int l = prefix[i - 1];
        while(str[l] != str[i] && l > 0){
            l = prefix[l - 1];
        }
        if(str[l] == str[i]){
            prefix[i] = l + 1;

        }else{
            prefix[i] = 0;
        }
    }
    return prefix;
}

void z_to_str(std::string &str, const std::vector <int> &z){
    str.push_back('a');
    int k = 1;
    for(int i = 1; i < z.size(); i++){
        if(z[i] == 0){
            str.push_back('a' + k);
            k++;
        }else{
            for(int j = 0; j < z[i]; j++){
                str.push_back(str[j]);
            }
            i += z[i] - 1;
        }
    }
}

std::vector<int> z2p(std::vector<int> &z){
    std::string s;
    z_to_str(s, z);
    for(int i = 0; i < s.size(); ++i){
        std::cout << s[i] << " ";
    }
    std::cout << "\n";
    return Prefix(s, z);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int N, x;
    std::cin >> N;
    std::vector<int> z;
    for(int i = 0; i < N; ++i){
        std::cin >> x;
        z.push_back(x);
    }
    std::vector<int> res = z2p(z);
    for(int i = 0; i < res.size(); ++i){
        std::cout << res[i] << " ";
    }
    return 0;
}



