#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <stdexcept>
#include <nlohmann/json.hpp>  

long long int decode_value(const std::string& value, int base) {
    long long int result = 0;
    for (size_t i = 0; i < value.size(); ++i) {
        char ch = value[i];
        int digit = 0;
        if (ch >= '0' && ch <= '9') {
            digit = ch - '0';
        } else if (ch >= 'a' && ch <= 'f') {
            digit = ch - 'a' + 10;
        } else if (ch >= 'A' && ch <= 'F') {
            digit = ch - 'A' + 10;
        } else {
            throw std::invalid_argument("Invalid character in value.");
        }
        result = result * base + digit;
    }
    return result;
}


long long int lagrange_interpolation_at_zero(const std::vector<std::pair<int, long long int>>& roots) {
    long long int c = 0;
    size_t n = roots.size();
    
   
    for (size_t i = 0; i < n; ++i) {
        int xi = roots[i].first;
        long long int yi = roots[i].second;
        long long int term = yi;  
        
     
        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                int xj = roots[j].first;
                term *= (0 - xj);
                term /= (xi - xj);  
            }
        }
        
        c += term;
    }
    
    return c;
}


long long int process_json_file(const std::string& file_name) {
   
    std::ifstream input_file(file_name);
    if (!input_file.is_open()) {
        std::cerr << "Error opening input file: " << file_name << std::endl;
        return -1;
    }
    
    nlohmann::json input_json;
    input_file >> input_json;  
    input_file.close();
    
    
    int n = input_json["keys"]["n"];
    int k = input_json["keys"]["k"];
    
    std::vector<std::pair<int, long long int>> roots;
    
   
    for (auto& item : input_json.items()) {
        if (item.key() == "keys") continue;  
        
        int x = std::stoi(item.key());  
        int base = item.value()["base"];
        std::string value = item.value()["value"];
        
       
        long long int y = decode_value(value, base);
        
        
        roots.push_back({x, y});
    }

   
    return lagrange_interpolation_at_zero(roots);
}

int main() {
  
    long long int c1 = process_json_file("input1.json");
    if (c1 == -1) return 1;  
    
   
    long long int c2 = process_json_file("input2.json");
    if (c2 == -1) return 1;  
    
    
    std::cout << "Test Case 1 - Secret constant term (c): " << c1 << std::endl;
    std::cout << "Test Case 2 - Secret constant term (c): " << c2 << std::endl;
    
    return 0;
}
