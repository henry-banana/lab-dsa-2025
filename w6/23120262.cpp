#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct Company {
    std::string name;
    std::string profit_tax;
    std::string address;
};

const long long P_HASH = 31;
const long long M_HASH = 2000;

struct HashTable {
    std::vector<std::vector<Company>> table;

    HashTable() {
        table.resize(M_HASH);
    }
};

std::vector<Company> readCompanyList(std::string file_name) {
    std::vector<Company> companies;
    std::ifstream inFile(file_name);

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file " << file_name << "\n";
        return companies;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        Company c;
        getline(ss, c.name, '|');
        getline(ss, c.profit_tax, '|');
        getline(ss, c.address);
        companies.push_back(c);
    }

    inFile.close();
    return companies;
}

long long hashString(std::string company_name) {
    std::string s_to_hash = company_name;
    if (s_to_hash.length() > 20) {
        s_to_hash = s_to_hash.substr(s_to_hash.length() - 20);
    }

    long long hash_value = 0;
    long long power = 1;

    for (int i = 0; i < s_to_hash.length(); ++i) {
        long long temp = (long long)((s_to_hash[i]) * power) % M_HASH;
        hash_value = (hash_value + temp) % M_HASH;
        power = (power * P_HASH) % M_HASH; 
    }
    
    if (hash_value < 0) {
        hash_value += M_HASH;
    }

    return hash_value;
}

void insert(HashTable* hash_table, const Company& company) {
    if (!hash_table) return;
    long long index = hashString(company.name);
    hash_table->table[index].push_back(company);
}

HashTable* createHashTable(const std::vector<Company>& list_company) {
    HashTable* ht = new HashTable(); 
    
    for (const Company& c : list_company) {
        insert(ht, c);
    }
    return ht;
}


Company* search(HashTable* hash_table, std::string company_name) {
    if (!hash_table) return nullptr;

    long long index = hashString(company_name);

    for (Company& c : hash_table->table[index]) {
        if (c.name == company_name) {
            return &c;
        }
    }
    return nullptr;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./main <MST_file_path> <input_file_path> <output_file_path>" << "\n";
        return 1;
    }

    std::string mst_file_path = argv[1];
    std::string input_file_path = argv[2];
    std::string output_file_path = argv[3];

    std::vector<Company> all_companies = readCompanyList(mst_file_path);

    HashTable* company_ht = createHashTable(all_companies);

    std::ifstream inputFile(input_file_path);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file " << input_file_path << "\n";
        delete company_ht;
        return 1;
    }

    std::ofstream outputFile(output_file_path);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file " << output_file_path << "\n";
        inputFile.close();
        delete company_ht;
        return 1;
    }

    std::string company_name_to_search;
    while (std::getline(inputFile, company_name_to_search)) {
        if (company_name_to_search.empty()) continue;

        Company* found_company = search(company_ht, company_name_to_search);

        if (found_company) {
            outputFile << found_company->name << "|"
                       << found_company->profit_tax << "|"
                       << found_company->address << "\n";
        }
    }

    inputFile.close();
    outputFile.close();

    delete company_ht;

    return 0;
}