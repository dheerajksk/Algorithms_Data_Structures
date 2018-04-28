#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries_das(const vector<Query>& queries) {
    vector<string> result;
    //int contact_size = queries.size()*2;
    int contact_size = 10000000;
    vector<string> my_contacts(contact_size, "Dheeraj");
    for (size_t i = 0; i < queries.size(); ++i){
        int index = ( (34 * queries[i].number + 2) % 10000019 ) % contact_size; 
        if (queries[i].type == "add") {
            my_contacts[index] = queries[i].name;
        } else if (queries[i].type == "del") {
            if(my_contacts[index] != "Dheeraj") my_contacts[index] = "Dheeraj";
        } else {
            string response = "not found";
            if(my_contacts[index] != "Dheeraj")  response = my_contacts[index];
            result.push_back(response);
        }
        }
    return result;
}

int main() {
    write_responses(process_queries_das(read_queries()));
    return 0;
}
