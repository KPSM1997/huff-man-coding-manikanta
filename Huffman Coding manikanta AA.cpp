#include <iostream>
#include <queue>
#include <map>
#include <vector>

using namespace std;

// A Huffman tree node
struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(char data, int freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// Compare class for priority queue
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Function to print Huffman codes in preorder traversal
void preorderTraversal(Node* root, string code, multimap<int, string>& huffmanCodes) {
    if (!root) return;

    // If it's a leaf node, store its code
    if (!root->left && !root->right) {
        cout << root->data << ": " << code << endl;
        huffmanCodes.insert({code.size(), code});  // Store the code based on its length
    }

    // Traverse left subtree with '0'
    preorderTraversal(root->left, code + "0", huffmanCodes);

    // Traverse right subtree with '1'
    preorderTraversal(root->right, code + "1", huffmanCodes);
}

// Function to build Huffman tree and return root
Node* buildHuffmanTree(char data[], int freq[], int size) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Create a leaf node for each character and push it into the min heap
    for (int i = 0; i < size; ++i) {
        minHeap.push(new Node(data[i], freq[i]));
    }

    // Iterate until the heap contains only one node (the root)
    while (minHeap.size() != 1) {
        // Extract two nodes with the lowest frequency
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with the sum of the two nodes' frequencies
        Node* top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        // Add the new node to the min heap
        minHeap.push(top);
    }

    // Return the root of the Huffman tree
    return minHeap.top();
}

int main() {
    // Given characters and their frequencies
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };

    int size = sizeof(arr) / sizeof(arr[0]);

    // Build Huffman Tree
    Node* root = buildHuffmanTree(arr, freq, size);

    // To store the Huffman codes (preorder traversal)
    multimap<int, string> huffmanCodes;

    // Print the Huffman codes
    preorderTraversal(root, "", huffmanCodes);

    return 0;
}
