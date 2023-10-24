#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"
#include <map>
#include <stack>
#include "catch.hpp"

class HuffmanTree: public HuffmanTreeBase{
public:
    std::string compress(const std::string inputStr);
    std::string serializeTree() const;
    std::string decompress(const std::string inputCode, const std::string serializedTree);
    void assign(HuffmanNode* node, std::map<char,std::string>& weights, std::string code);
    void serialize(HuffmanNode* node, std::string& outStr) const;
    HuffmanNode* makeTree(const std::string inputStr);
private:
    HuffmanNode* __root;
};