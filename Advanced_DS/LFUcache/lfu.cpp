#include<bits/stdc++.h>
using namespace std;

// question source: Leetcode 460. LFU Cache

class LFUCache {
private:
    struct Node{
        int key;
        int val;
        int freq;
        Node* next;
        Node* prev;

        Node(int _key, int _val){
            key = _key;
            val = _val;
            freq = 1;
        }
    };

    struct List{
        int size;
        Node *head;
        Node *tail;

        List(){
            head = new Node(-1,-1);
            tail = new Node(-1,-1);
            head->next = tail;
            tail->prev = head;
            size = 0;
        }

        // insert a node into the list
        void insertNode(Node* node){
            Node *temp = head->next;
            head->next = node;
            node->prev = head;
            node->next = temp;
            temp->prev = node;
            size++;
        }

        // remove a node from the list
        void removeNode(Node* node){
            // update the pointers of the given nodes and its neighbour
            Node *prevNode = node->prev;
            Node *nextNode = node->next;
            prevNode->next = nextNode;
            nextNode->prev = prevNode;
            size--;
        }
    };

    int capacity;
    int minFreq;
    unordered_map<int,Node*> map; // key to node;
    unordered_map<int, List*> freqList; // freq to list

    // method to update the frequency list map
    void updateFreqList(Node* node){
        int freq = node->freq;

        // remove the node from the current list
        List *currList = freqList[freq];
        currList->removeNode(node);

        // if the current freq was minFreq & currList's size == 0, increment minFreq to next, i.e +1;
        if(minFreq == freq && currList->size == 0){
            minFreq++;
        }

        // node's frequency
        node->freq += 1;
        freq += 1;

        // add the node to the next freqList, create one if doesn't exist
        List *newFreqList;
        if(freqList.find(freq) == freqList.end()){
            newFreqList = new List();
        }
        else{
            newFreqList = freqList[freq];
        }
        newFreqList->insertNode(node);
        freqList[freq] = newFreqList;
    }
    
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        this->minFreq = 0;
    }
    
    int get(int key) {

        // if key not present
        if(map.find(key) == map.end()){
            return -1;
        }

        // get the node
        Node *node = map[key];
        int retVal = node->val;
        updateFreqList(node);

        return retVal;

    }
    
    void put(int key, int value) {
        /* if node is already present */
        if(map.find(key) != map.end()){
            // update the value and its frequency
            Node *node = map[key];
            node->val = value;
            updateFreqList(node);

            return;
        }

        /* if the map size has reached its maximum capacity */
        if(map.size() == capacity){
            // remove the node from the minFreq list
            List *list = freqList[minFreq];
            Node *removedNode = list->tail->prev;
            list->removeNode(removedNode);
            map.erase(removedNode->key);
            delete(removedNode);
        }

        /* create and insert a new node */
        Node *newNode = new Node(key, value);
        minFreq = 1;
        List *newList;
        if(freqList.find(1) == freqList.end()){
            newList = new List();
        }
        else{
            newList = freqList[1];
        }

        newList->insertNode(newNode);
        map[key] = newNode;
        freqList[minFreq] = newList;

    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */