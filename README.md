# SimpleDataStructures
Data structures that are mainly used in the Flight Controller program.
They are designed to achieve basic functionality that I need for my libraries, to be fast and robust, moreover very simple in use.
The goal for this library is also to be scalable, so I used base abstract classes as interfaces (concrete classes basically don't contain virtual methods to avoid dynamic dispatch.

Currently tested data structures are:
* LinkedList
* GrowingArray
