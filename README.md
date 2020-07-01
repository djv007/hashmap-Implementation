# Hashmap-Implementation
Here i have made a hashmap in C++ language and OOP paradigm . 
Key of the hashmap is of type string and value stored is of type integer . 

i have used an array to implement hashmap . 
each element of the array is a linked list , where each element of the array is the head of the linked list stored at that index .
The linked list has a key of string type , an int value and address of next node .
let's call this bucketarray .


Steps :

 1 . I have converted key into a suitable hashcode using the process of hashing .
 
 2 . After hashing i have used a compression function % to make the hashcode in a suitable range so that they can be stored easily.
 
 3 . To avoid collision (when more than 1 keys want to go to same index in bucket array after coming from compression function) , i have used SEPARATE CHAINING process in which 
    each element of the bucket array will be a linked list i.e. if 2 key-value pairs want to get at same index then it will be possible .
 
 4 . Load factor determines how many nodes are there in one linked list where each node signifies a key-value pair in our hashmap , i have done rehashing after load factor reaches 0.7 , 
    so this means  on an average there are less than 1 node in a linked list to make search , insert , delete operations in my hashmap in O(1) time for one element .
    
Functions made : 
insert , delete , getValue of a key , update value of a key .
