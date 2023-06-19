#include <iostream>
#include <cstring>

enum WayFromParent{
    left = 0,
    right = 1,
    NOWAY = -1
};

struct TreeNode{
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    WayFromParent way;
    int char_value;
    int weight;
    int view=0;
};

TreeNode* SortedNodes[256] = {NULL};

void bubblesort(TreeNode* (&sorts)[256], int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size-1; j++){
            if(sorts[j]->weight<sorts[j+1]->weight){
                TreeNode* a = sorts[j];
                sorts[j] = sorts[j+1];
                sorts[j+1] = a;
            }
        }
    }
}

TreeNode* CreateNode(int value, int weight){
    TreeNode* NewNode = new TreeNode();
    NewNode->left = NULL;
    NewNode->right = NULL;
    NewNode->parent = NULL;
    NewNode->way = NOWAY;
    NewNode->char_value = value;
    NewNode->weight = weight;
    return NewNode;
}

TreeNode* MergeNodes(TreeNode* more, TreeNode* less){
    TreeNode* parent = CreateNode('\0', more->weight+less->weight);
    parent->left = more;
    parent->right = less;
    more->parent = parent;
    more->way = left;
    less->parent = parent;
    less->way = right;
    return parent;
}

TreeNode* CreateTreeNot(TreeNode* (&sorts)[256], int size){
    if(size==1){
        return sorts[0];
    }else{
        TreeNode* a = sorts[size-2];
        TreeNode* b = sorts[size-1];
        TreeNode* c = MergeNodes(a, b);
        sorts[size-2] = c;
        sorts[size-1] = nullptr;
        bubblesort(sorts, size-1);
        size = size-1;
        return CreateTreeNot(sorts, size);
    }
}

TreeNode* CreateTree(TreeNode* (&sorts)[256], int size){
    TreeNode* root = CreateTreeNot(sorts, size);
    TreeNode* a = root->left;
    root->left = root->right;
    root->right = a;
}

int GetView(TreeNode* node){
    if(node->char_value == '\0'){
        return -1;
    }else{
        int view=0;
        int degree=0;
        TreeNode* currentnode = node;
        while(currentnode->parent!=nullptr){
            view = view + 10^degree*(currentnode->way);
            currentnode = currentnode->parent;
            degree++;
        }
        return view;
    }
}

void SettingViewPreOrder(TreeNode *node){
    if (node == NULL) return;
    node->view = GetView(node);
    SettingViewPreOrder(node->left);
    SettingViewPreOrder(node->right);
}

void PrintPreOrder(TreeNode *node){
    if (node == NULL) return;
    std::cout << static_cast<char>(node->char_value) << " = " << node->view << std::endl;
    SettingViewPreOrder(node->left);
    SettingViewPreOrder(node->right);
}


int GetStringSize(std::string s){
    int i=0;
    while(s[i]!='\0'){
        i++;
    }
    return i;
}

void CharFrequency(std::string s, int (&chars)[256]){
    int n = GetStringSize(s);
    for(int i=0; i<n; i++){
        int a = static_cast<int>(s[i]);
        chars[a]++;
    }
}

int chars[256] = {0};

int main(){
    std::string s = "aaddacddecaaeebbebbaacecabaddaccaabaaab";
    // std::getline(std::cin, s);
    CharFrequency(s, chars);
    int counter = 0;
    for(int i=0; i<256; i++){
        if(chars[i]!=0){
            SortedNodes[counter] = CreateNode(i, chars[i]);
            counter++;
        }
    }
    int size = counter;
    bubblesort(SortedNodes, size);

    TreeNode* root = CreateTree(SortedNodes, size);
    SettingViewPreOrder(root);
    PrintPreOrder(root);
    std::cout << "\n\n" << root->right->weight << std::endl;
}