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

Today I am beginning with the very basics of Data Structures and Algorithms: Vectors and Linked Lists.

I have implemented a dynamic array which is a collection that can be accessed by index in O(1) time and have elements inserted
in O(n) time. I have implemented an `expand()` function which grows the array capacity if the number of elements reaches the actual
capacity. The vector uses operator overloading for console logging and index access.

I have implemented the linked list as a doubly-linked list that can be accessed by index in O(1) time and have elements inserted to
either end in O(1) time. Insertions in between require traversal through a pointer starting forwards from the head or backwards from
the tail, depending on which requires less steps. Operator overloading is also used for index access, but undergoes more computationally
expensive traversals underneath.