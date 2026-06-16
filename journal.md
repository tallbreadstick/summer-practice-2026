SUMMER PRACTICE ARC 2026

# Introduction

While AI has made software development much easier in the last few years, I must not forget to polish my fundamentals. This era
is not much different from the industrial revolution that shook the scene of artisanal industries. AI-generated code ships fast,
but quality degrades as projects scale. I will keep my talent sharp and maintain my traditional coding ability. I have taken short
'pilgrimages' every now and then through the fundamentals whenever time permitted. Here begins the summer practice arc of 2026.

# Rules

- Complete 1 journal entry per day for 14 days.
- No direct interaction between AI and source code; No copilot, cursor, or similar.
- As much as possible limit AI to search engine functionality, like a doc tool.

## Day 1 : 06/15/2026

### Activity 1 - Vector and Linked List

Today I am beginning with the very basics of Data Structures and Algorithms: Vectors and Linked Lists.

I have implemented a dynamic array which is a collection that can be accessed by index in O(1) time and have elements inserted
in O(n) time. I have implemented an `expand()` function which grows the array capacity if the number of elements reaches the actual
capacity. The vector uses operator overloading for console logging and index access.

I have implemented the linked list as a doubly-linked list that can be accessed by index in O(1) time and have elements inserted to
either end in O(1) time. Insertions in between require traversal through a pointer starting forwards from the head or backwards from
the tail, depending on which requires less steps. Operator overloading is also used for index access, but undergoes more computationally
expensive traversals underneath.

### Activity 2 - WC Command Line Tool

I asked GPT for some quick project suggestions for an AI dependency detox, and it suggested the `wc` shell tool. I will implement it in
C++ just for fun.

## Day 2 : 06/16/2026

### Activity 1 - Stack and Queue Abstract Classes

I have implemented some abstract classes for the Stack and Queue data structures. Using intermediate abstract model classes, both Vector
and Linked List are now polymorphic objects that can match into Stacks or Queues. From this activity, I learned the differences between OOP
in classic languages like Java and more bare metal ones like C++. I now further appreciate the straightforward nature of Java's OOP, and
am further amazed by Rust's clean approach at polymorphism while managing to be a low-level language.