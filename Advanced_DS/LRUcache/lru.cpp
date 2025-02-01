#include<bits/stdc++.h>
using namespace std;

// question source: Leetcode 146. LRU Cache

class LRUCache {
private:
    struct Node{
        int key;
        int val;
        Node* next;
        Node* prev;

        Node(int _key, int _val){
            key = _key;
            val = _val;
        }
    };

    int capacity;
    Node *head;
    Node *tail;

    unordered_map<int,Node*> map; // key to node*

    // method to insert node in front of head
    void insertNodeInfontHead(Node* node){
        Node* temp = head->next;

        // update the pointers on the new node.
        node->next = head->next;
        node->prev = head;

        // update the head of existing node.
        temp->prev = node;
        head->next = node;
    }

    // method to remove a given node (Note: it will just updated the next & prev pointers)
    void removeNode(Node* node){
        Node* prevNode = node->prev;
        Node* nextNode = node->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        head = new Node(-1,-1);
        tail = new Node(-1,-1);
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {

        // check if key is present or not
        if(map.find(key) == map.end()){
            return -1;
        }

        // get the value and bring in fornt of the head
        Node* node = map[key];
        int val = node->val;
        removeNode(node);
        insertNodeInfontHead(node);

        return val;
    }
    
    void put(int key, int value) {
        // if the key is already present, update the value and position in DLL
        if(map.find(key) != map.end()){
            Node* node = map[key];
            removeNode(node);

            node->val = value;

            insertNodeInfontHead(node);

            return;
        }

        // if size of cache has reached its maximum capacity
        if(map.size() == capacity){
            /* delete the node present just before tail*/
            int deleteKey;
            Node* node = tail->prev;

            deleteKey = node->key;
            map.erase(deleteKey);

            // delete node for DLL
            removeNode(node);
            delete(node);
        }

        // create new node and insert into DLL
        Node *node = new Node(key,value);
        insertNodeInfontHead(node);
        map[key] = node;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */