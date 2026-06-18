#include <iostream>
#include "collections/vector.hpp"
#include "collections/linked_list.hpp"
#include "collections/ring_buffer.hpp"
#include "collections/stack.hpp"

using namespace std;

int main(int argc, char **argv) {
    
    ring_buffer<int> r;

    for (int i = 0; i < 10; i++) {
        r.push_head(i);
    }

    cout << r << endl;

    for (int i = 0; i < 10; i++) {
        r.push_tail(i);
    }

    cout << r << endl;

    return 0;
}
