#include <iostream>
#include "collections/vector.hpp"
#include "collections/linked_list.hpp"

using namespace std;

int main(int argc, char **argv) {
    
    linked_list<int> l;

    for (int i = 0; i < 10; i++) {
        l.push_tail(i);
    }

    cout << l << endl;

    for (size_t i = 0; i < 10; i++) {
        cout << l[i] << endl;
    }

    return 0;
}
