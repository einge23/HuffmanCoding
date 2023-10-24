#include "HuffmanTree.hpp"
#include <string>
void HuffmanTree::assign(HuffmanNode* __root, std::map<char,std::string>& weights, std::string code){
        HuffmanNode* temp = __root;
        if(temp == NULL)
            return;
        

        if(temp->isLeaf()){
            weights[temp->getCharacter()] = code;
        }
        assign(temp->left, weights, code + "0");
        assign(temp->right, weights, code + "1");
}
HuffmanNode* HuffmanTree::makeTree(const std::string inputStr){
    //first add all chars and frequency to map


std::map<char, int> m;
std::map<char,int>::iterator itr;
std::string str = inputStr;


for(int i = 0;i<(int)str.length();i++){
    m[str[i]]++;
}

//make one node tree with char and frequency as priority
//heapqueue insert


HeapQueue<HuffmanNode*,HuffmanNode::Compare> Q;
for(itr = m.begin(); itr!= m.end();itr++){

    HuffmanNode* N = new HuffmanNode(itr->first,itr->second); //node made with name (first), and frequency(second)
        //VectorCompleteTree<HuffmanNode*> V;//Tree of new node
        //V.addLast(N);
    //insert in ascending priority
    Q.insert(N);
}
while(Q.size() > 1){
    //dequeue two trees t1 and t2 //tree t's priority is sum of lowest 2

    HuffmanNode* t1 = Q.min();
    size_t t1freq = t1->getFrequency();
    Q.removeMin();
    HuffmanNode* t2 = Q.min();
    size_t t2freq = t2->getFrequency();
    Q.removeMin();
    size_t tfreq = t1freq + t2freq;
    HuffmanNode* _root = new HuffmanNode(' ', tfreq); // root node with no char but combined priority
    _root->left = t1;
    _root->right = t2;
    t1->parent = _root;
    t2->parent = _root;
    Q.insert(_root); //tree constructed and put into queue
}
 //assign 0 and 1 weights to tree, left nodes will have 0 and right will have 1
    __root = Q.min();
    return __root;
}

std::string HuffmanTree::compress(const std::string inputStr){

    __root = makeTree(inputStr);
    std::string str = inputStr;
    std::map<char,std::string> weights;
    std::map<char,std::string>::iterator witr;
    std::string code; std::string comb_code;
    assign(__root, weights, code);
    int c;
    for(int i = 0;i<(int)str.size();i++){
        c = str[i];
        comb_code += weights[c];
    }
    return comb_code;

}
void HuffmanTree::serialize(HuffmanNode* node, std::string& serial) const{
    if(node == NULL){
        return;
    }
        serialize(node->left,serial);
        serialize(node->right,serial);

        if (node->left == NULL && node->right == NULL) {
        serial += "L";
        serial += node->getCharacter();
        }
    // If it's an internal node (branch), add "B"
        else {
        serial += "B";
        }
}

std::string HuffmanTree::serializeTree() const{
    HuffmanNode* temp = __root;
    if(temp == NULL){
        return "";
    }
    std::string o = "";
    serialize(temp,o);
    
    return o;
}
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){
       // Rebuild the Huffman tree from the serialized tree string
    std::stack<HuffmanNode*> s;
    HuffmanNode* root = NULL;
    std::string decode = "";

    //first rebuild tree
  for (int i = 0; i < (int)serializedTree.length(); i++) {
    char c = serializedTree[i];
        if(c == 'L'){
            if (i + 1 < (int)serializedTree.length()) {
                char ch = serializedTree[i + 1]; // Read the character 'ch'
                HuffmanNode* leaf = new HuffmanNode(ch,0);
                s.push(leaf);
                i++;
            }
            else{
                return "";
            }

        }
        else if(c == 'B'){
            HuffmanNode* right = s.top();
            s.pop();
            HuffmanNode* left = s.top();
            s.pop();
            HuffmanNode* branch = new HuffmanNode(' ',0);
            branch->left = left;
            branch->right = right;
            left->parent = branch;
            right->parent = branch;
            s.push(branch);
            if(s.size() == 1){
                root = branch;
            }
        }
    }
    if(s.size() != 1 || root == NULL){
        return "";
    }
    HuffmanNode* cur = root;
    for(char c: inputCode){
        if(c == '0'){
            cur = cur->left;
        }
        else if(c == '1'){
            cur = cur->right;
        }
        if(cur->isLeaf()){
            decode+= cur->getCharacter();
            cur = root;
        }
    }
    return decode;
  }


/*int main(){

    HuffmanTree t;
    std::string test = "It is time to unmask the computing community as a Secret Society for the Creation and Preservation of Artificial Complexity";
    std::string code = t.compress(test);
    std::cout<<code<<std::endl;
    std::string tree = t.serializeTree();
    std::cout<<tree<<std::endl;
    std::string orig = t.decompress(code, tree);
    std::cout<<orig;
    return 0;

}*/
