#include<iostream>
#include<stack>
#include<queue>
using namespace std;


// Class representing a node in the Binary Search Tree
class Node{
public:
    int data;           // Data stored in the node
    Node* leftptr;      // Pointer to the left child
    Node* rightptr;     // Pointer to the right child

    // Constructor to initialize a node with a given value
    Node(int val){
        data = val;
        leftptr = nullptr;
        rightptr = nullptr;
    }

    friend class BST;   // BST class is a friend, allowing access to private members
};

// Class representing the Binary Search Tree
class BST{
    Node* root;         // Pointer to the root of the BST

    // Private method for in-order traversal (left-root-right)
    void inorderE(Node* node){
        if(node != nullptr){
            inorderE(node->leftptr);   // Traverse left subtree
            cout << node->data << " "; // Visit node
            inorderE(node->rightptr);  // Traverse right subtree
        }
    }

    void preorderE(Node*node){
          if(node != nullptr){

            cout << node->data << " "; // Visit node
            inorderE(node->leftptr);   // Traverse left subtree
            
            inorderE(node->rightptr);  // Traverse right subtree
        }
    }
      void postorderE(Node*node){
          if(node != nullptr){

            inorderE(node->leftptr);   // Traverse left subtree
            
            inorderE(node->rightptr);  // Traverse right subtree
             cout << node->data << " "; // Visit node
        }
    }
      // Private method to insert a value into the BST
    //through recursion
    Node* insertE(Node* node, int val){
        if(node == nullptr){
            return new Node(val);      // Create a new node if current node is null
        }

        else if(node->data > val){
            node->leftptr = insertE(node->leftptr, val);   // Insert in left subtree
        }
        else if(node->data < val){
            node->rightptr = insertE(node->rightptr, val); // Insert in right subtree
        }
        else{
            cout << "Duplicate value ignored." << endl;    // Ignore duplicate values
        }

        return node;   // Return the node pointer
    }

  // Iterative search function for a binary search tree (BST)
void searchIE(Node* node, int x) {
    // Loop until the node is nullptr (i.e., we reach a leaf node)
    while (node != nullptr) {
        // If the current node's data matches the target, print "found" and exit
        if (node->data == x) {
            cout << "found" << endl;
            return;
        } 
        // If the target value is less than the current node's data, move to the left child
        else if (node->data > x) {
            node = node->leftptr;
        } 
        // If the target value is greater than the current node's data, move to the right child
        else {
            node = node->rightptr;
        }
    }
    // If the loop ends without finding the target, print that the data was not found
    cout << "the data is not found" << endl;
}

// Recursive search function for a binary search tree (BST)
void RecursiveE(Node* node, int x) {
    // Base case: if the node is nullptr, print that the value was not found
    if (node == nullptr) {
        cout << "the data is not found" << endl;
        return;
    }
    // If the current node's data matches the target, print "found" and exit
    if (node->data == x) {
        cout << "found " << x << endl;
        return;
    } 
    // If the target value is less than the current node's data, search the left subtree
    else if (node->data > x) {
        RecursiveE(node->leftptr, x);
    } 
    // If the target value is greater than the current node's data, search the right subtree
    else {
        RecursiveE(node->rightptr, x);
    }
}

   void InorderIterativeE(Node* node) {
    // Declare a stack to keep track of nodes
    stack<Node*> stk;
    
    // Check if the tree is empty
    if (node == nullptr) {
        cout << "empty tree" << endl;
        return;  // Exit the function as the tree is empty
    }
    
    // Iterate until the stack is empty or the current node is not null
    while (node != nullptr || !stk.empty()) {
        // Reach the leftmost node of the current node
        while (node != nullptr) {
            stk.push(node);  // Push the node to the stack
            node = node->leftptr;  // Move to the left child
        }
        
        // Current node must be null at this point
        node = stk.top();  // Retrieve the top node from the stack
        stk.pop();  // Remove the top node from the stack
        
        cout << node->data << " ";  // Print the node's data
        
        node = node->rightptr;  // Move to the right child
    }
   }
   
   // Function to calculate the height of a binary tree
int heightRec(Node* node) {
    // Base case: if the node is null, the height is 0
    if(node == nullptr){
        return 0;
    }
    
    // Recursively calculate the height of the left subtree
    int leftht = heightRec(node->leftptr);
    
    // Recursively calculate the height of the right subtree
    int rightht = heightRec(node->rightptr);
    
    // Determine the larger height between left and right subtrees
    int ht;
    if(leftht > rightht){
        ht = leftht;
    }
    else{
        ht = rightht;
    }

    // Return the height of the current node, which is the maximum height
    // of the left and right subtrees plus 1
    return ht + 1;
}

// Function to delete a node with a given value from a binary tree
Node* deleteE(Node* node, int val) {
    // Base case: if the node is null, return null
    if (node == NULL) {
        return node;
    }

    // If the value to be deleted is less than the current node's data,
    // then it lies in the left subtree
    if (val < node->data) {
        node->leftptr = deleteE(node->leftptr, val);
    }
    // If the value to be deleted is greater than the current node's data,
    // then it lies in the right subtree
    else if (val > node->data) {
        node->rightptr = deleteE(node->rightptr, val);
    }
    // If the value is the same as the current node's data, this is the node to be deleted
    else {
        // Node with only one child or no child
        if (node->leftptr == NULL) {
            Node* temp = node->rightptr; // Store the right child
            delete node;  // Delete the current node
            return temp;  // Return the right child to connect to the parent node
        } 
        else if (node->rightptr == NULL) {
            Node* temp = node->leftptr;  // Store the left child
            delete node;  // Delete the current node
            return temp;  // Return the left child to connect to the parent node
        }

        // Node with two children: get the inorder successor (smallest in the right subtree)
        Node* temp = node->rightptr;
        while (temp && temp->leftptr != NULL) {
            temp = temp->leftptr;
        }

        // Copy the inorder successor's data to this node
        node->data = temp->data;

        // Delete the inorder successor
        node->rightptr = deleteE(node->rightptr, temp->data);
    }

    // Return the node pointer to connect the modified tree
    return node;
}

// Function to perform level-order traversal of the binary tree
void levelorder(Node* node) {
    // Create an empty queue for level order traversal
    queue<Node*> q;

    // If the tree is empty, print a message and return
    if (node == nullptr) {
        cout << "empty tree";
        return;
    }

    // Enqueue the root node
    q.push(node);

    // Continue the traversal until the queue is empty
    while (!q.empty()) {
        // Get the number of nodes at the current level
        int size = q.size();

        // Process all nodes at the current level
        while (size > 0) {
            node = q.front();  // Get the front node from the queue
            cout << node->data << " ";  // Print the node's data
            q.pop();  // Remove the node from the queue

            // Enqueue the left child if it exists
            if (node->leftptr != nullptr) {
                q.push(node->leftptr);
            }

            // Enqueue the right child if it exists
            if (node->rightptr != nullptr) {
                q.push(node->rightptr);
            }

            size--;  // Decrement the size counter for the current level
        }
        // Print a newline after each level
        cout << endl;
    }
}

        
    
      


public:
    // Constructor to initialize an empty BST
    BST(){
        root = nullptr;
    }

    // Public method to insert a value into the BST
    void insert(int val){
        if(val <= 0){
            cout << "Invalid value. Please enter a positive integer." << endl;
            return ;
        }
        root = insertE(root, val);       // Call private insert method
    }

    // Public method to perform in-order traversal of the BST
    void Dinorder(){
        if(root == nullptr){
            cout << "Tree is empty." << endl;
            return;
        }

        inorderE(root);  // Call private in-order traversal method
    }
    void preorder(){
        preorderE(root);
        return;
    }
     void postorder(){
        postorderE(root);
        cout<<endl;
        return;
    }
    void search(int x){
        searchIE(root,x);
        return;
    }

    void searchR(int x){
        RecursiveE(root,x);
        return;
    }
    void inorderitrative(){
      InorderIterativeE(root);
    }
    void Delete(int val){
       root= deleteE(root,val);
    }
    void Height(){
         
         cout<<"the height of the tree is: "<<heightRec(root);
    }
    void Levelorder(){
        cout<<"the level order is: "<<endl;
        levelorder(root);
    }
};

int main(){
    BST bstree;         // Create an instance of BST
    int val[] = {10, 20, 40, 50,3,4,5,6,7,8,88};  // Array of values to be inserted
    for (int ival: val)
        bstree.insert(ival);   // Insert each value into the BST
    cout << "Inorder traversal: " ;
    bstree.Dinorder();         // Perform in-order traversal and print values
    cout << "\n preorder traversal: ";
    bstree.preorder();         
    cout << "\npostorder traversal: ";
    bstree.postorder(); 
    cout<<"searched the no. through iterative"<<endl;
    bstree.search(10); 
 
    cout<<"seached the no. through recursive"<<endl; 
    bstree.searchR(20); 
    cout<<endl;

    cout<<"Inorder Iterative :";
    bstree.inorderitrative();
    cout<<endl;

    // cout<<"Height of the tree is:"<<endl;
    bstree.Height();
    bstree.Delete(10);
    cout<<endl;
    bstree.Levelorder();

    return 0;
}
