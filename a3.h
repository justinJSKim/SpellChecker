#ifndef A3_H
#define A3_H
#include <string>
#include <iostream>
using namespace std;


class SpellCheck{
    
    struct Node{
        bool isTerminal_;
        char ch_;
        Node* children_[26];
        Node(char c='\0'){
            isTerminal_ = false;
            ch_=c;
            for(int i = 0 ; i < 26; i++){
                children_[i]=nullptr;
            }
        }
        
        //given a lower case alphabetic character ch, returns the associated index 'a'-> 0, 'b'->1....
        int getIndex(char c){
            if(c=='\0'){
                return 0;
            }
            return c -'a';
        }
    };
    Node* root_;
    
    bool lastLetter(const string& newWord, int currChar);
   
    void addWord(const string& newWord, int currChar, Node* rt);
    bool find(Node* rt, const string& word, int currChar) const;
    Node* search( Node* rt, const string& word, int currChar) const;
    void traverse(Node* partialRoot, const string& partialWord, int& numSug, string suggestions[]) const;
    void remove(Node* node);
    
public:
    SpellCheck(string data[],int sz);
    void addWord(const string& newWord);
    bool lookup(const string& word) const;
    int suggest(const string& partialWord, string suggestions[]) const;
    ~SpellCheck();
};
#endif