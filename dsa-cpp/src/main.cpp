#include <iostream>
#include "collections/vector.hpp"
#include "collections/linked_list.hpp"
#include "collections/stack.hpp"

using namespace std;

int main(int argc, char **argv) {
    
    stack<int>* s = new vector<int>();
    queue<int>* q = new linked_list<int>();

    for (size_t i = 0; i < 10; i++) {
        s->push(i);
        q->offer(i);
    }

    while (!s->is_empty()) {
        cout << "[" << s->pop() << ", " << q->poll() << "]" << endl;
    }

    return 0;
}
