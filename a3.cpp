#include "a3.h"
#include <string>
using namespace std;


SpellCheck::SpellCheck(string data[],int sz){
    root_=new Node();
    for(int i =0; i<sz; i++){
       addWord(data[i]);
    }
}
bool SpellCheck::lastLetter(const string& newWord, int currChar){
    //checks if currChar is the last letter of the word
    return (currChar == newWord.length()-1) ? true:false;
}
void SpellCheck::addWord(const string& newWord){
    //recursively
    addWord(newWord, 0, root_);
 }
void SpellCheck::addWord(const string& newWord, int currChar, Node* rt){
    
    //Check if the current character index is still the word
    if(currChar < newWord.length()){
        
        //Take the current character and find the index position
        char currLetter=newWord[currChar];
        int index = rt->getIndex(currLetter);
        
        //If there is no letter at that position, create a new node
        if(!rt->children_[index]){
            rt->children_[index] = new Node (currLetter);
            //checks if the word is done
            if(lastLetter(newWord, currChar)){
                rt->children_[index]->isTerminal_ = true;
                return;
            }
            //if word is not done, continue to add
            addWord(newWord, currChar+1, rt->children_[index]);
        }
        
        //The letter exists, checks if word is terminal
        if(lastLetter(newWord, currChar)){
            rt->children_[index]->isTerminal_ = true;
            return;
        }
        //Otherwise continue to add
        addWord(newWord, currChar+1, rt->children_[index]);
    }
    //If the currChar is equal to the length of the word, the word is finished
    //Make the previous node a terminating node
    return;
}


 bool SpellCheck::lookup(const string& word) const{
     //recursively
     return find(root_, word, 0);
 }

//  find checks if the string passed is a word in the SpellCheck (recursively)
 bool SpellCheck::find(Node* rt, const string& word, int currChar)const {
 
     //Check if the current character index is still the word
     if(currChar < word.length()){
 
         //Finds the index of next character
         int index = rt->getIndex(word[currChar]);
     
         //Keeps going
         if(rt->children_[index])
            return find(rt->children_[index], word, currChar+1);
         else{
            return false;//if nullptr, not there
         }
     }//close if word.length()
     else{
         return (rt->isTerminal_);
     }
     
     return rt->isTerminal_;//true means word in dictionary
 }
 //


//Finds and returns a node if the string exists
SpellCheck::Node* SpellCheck::search( Node* rt, const string& word, int currChar) const{
    Node* tmp = rt;
    
    //Check if the current character index is still the word
    if(currChar < word.length()){
        
        //Finds the index of character
        int index = rt->getIndex(word[currChar]);
        
        //Finds the node at end of word recursively
        if(rt->children_[index])
            tmp = search(rt->children_[index], word, currChar+1);
        else
            return nullptr;//If index doesn't exist, word doesn't exist
    }
    return tmp;//Last node in search
}


int SpellCheck::suggest(const string& partialWord, string suggestions[]) const{
   
    //Find the node that you start at
    Node* partialRoot = search(root_, partialWord, 0);
    
    int numSug=0;
    
    //for(int i=0; i<25; i++){
        //try to scan
    
        //Recursively add words to suggestions
        traverse(partialRoot/*->children_[i]*/, partialWord, numSug, suggestions);
        
   // }
    
    return numSug;
}

void SpellCheck::traverse(Node* partialRoot, const string& partialWord, int& numSug, string suggestions[]) const{
    
    if(partialRoot){
        if(partialRoot->isTerminal_){
             suggestions[numSug++] = partialWord;
        }
       
        for(int i=0; i<26; i++){
            if(partialRoot->children_[i] != nullptr)
                traverse(partialRoot->children_[i], partialWord+partialRoot->children_[i]->ch_, numSug, suggestions);
        }
    }
    return;
}
void SpellCheck::remove(Node* node){
   
    for(int i=0; i<26; i++){
        if(node->children_[i] != nullptr){
            remove(node->children_[i]);
        }
    }
    if(node){
        delete node;
    }
    
    return;
}
    
SpellCheck::~SpellCheck(){
	//this is a post order traversal
    remove(root_);
}
