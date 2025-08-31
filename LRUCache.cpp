// Doubly linked list node structure
class Node {
public:
    int key;
    int val;
    Node* prev;
    Node* next;
    // Constructor to initialize a node with key and value
    Node(int key, int val) : key(key), val(val), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    // Helper function to remove a node from the doubly linked list
    void deleteNode(Node* node) {
        if (node == nullptr) return;
        // Bypass the current node
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    // Helper function to insert a node right after the dummy head
    void insertAtHead(Node* node) {
        if (node == nullptr) return;

        // Inserting after head and before head->next
        node->next = head->next;
        head->next = node;
        node->prev = head;
        node->next->prev = node;
    }

    // Dummy head and tail nodes to simplify insertion/removal logic
    Node* head = new Node(-1, -1);
    Node* tail = new Node(-1, -1);

public:
    int capacity = 0;  // Maximum capacity of the cache
    unordered_map<int, Node*> mp; // Maps key to its corresponding node in the list

    // Constructor to initialize LRUCache
    LRUCache(int capacity) {
        // Connect dummy head and tail
        head->next = tail;
        tail->prev = head;
        this->capacity = capacity;
        mp.clear(); // Just for safety
    }

    // Get value for the given key, update its position as most recently used
    int get(int key) {
        if (mp.find(key) != mp.end()) {
            // Key found in cache
            Node* node = mp[key];

            // Move this node to the front (most recently used)
            deleteNode(node);
            insertAtHead(node);

            return node->val;
        } else {
            // Key not found
            return -1;
        }
    }
    // Insert or update key-value pair
    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            // Key already exists → update value and move it to front
            Node* node = mp[key];
            node->val = value;
            deleteNode(node);     // Remove from current position
            insertAtHead(node);   // Move to front (most recently used)
        } else {
            // Key does not exist → create new node
            Node* node = new Node(key, value);

            if (mp.size() == capacity) {
                // Cache is full → remove least recently used (LRU)
                Node* lru = tail->prev;

                deleteNode(lru);         // Remove from list
                mp.erase(lru->key);      // Remove from map
            }

            // Insert the new node at front
            insertAtHead(node);

            // Update map with the node
            mp[key] = head->next;  // head->next is always the most recent node
        }
    }
};