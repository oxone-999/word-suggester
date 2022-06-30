#include <bits/stdc++.h>
using namespace std;

struct Node {
  Node * links[26];
  bool flag = false;

  bool containsKey(char ch) {
    return (links[ch - 'a'] != NULL);
  }
  Node * get(char ch) {
    return links[ch - 'a'];
  }
  void put(char ch, Node * node) {
    links[ch - 'a'] = node;
  }
  void setEnd() {
    flag = true;
  }
  bool getEnd() {
    return flag;
  }
};
class Trie {
  private:
    Node * root;

  public:
    Trie() {
      root = new Node();
    }

  void insert(string word) {
    Node * node = root;
    Node* nn = root;
    for (int i = 0; i < word.length(); i++) {
      if (!node -> containsKey(word[i])) {
        node -> put(word[i], new Node());
      }
      nn = node;
      node = node->get(word[i]);
    }
    node->setEnd();
  }

  void dfs(Node* head,string str,vector<string> &vec){
    if(head->getEnd()){
        if(vec.size() >= 5) return;
        vec.push_back(str);
    } 
    
    // cout<<str<<endl;
    for(int i=0;i<26;i++)
    {
        Node* node = head;
        string s = str;
        if(node->containsKey(i+'a'))
        {
          s.push_back(i+'a');
          node = node->get(i+'a');
          dfs(node,s,vec);
        }
    }
  }

  vector<string> wordsStartingWith(string & word) {
    Node* node = root;
    vector<string> vec;
    string s;
    for (int i = 0; i < word.length(); i++) {
      if (node -> containsKey(word[i])) {
        node = node -> get(word[i]);
        s.push_back(word[i]);
      } else return {};
    } 

    if(!s.empty()) dfs(node,s,vec);

    return vec;
  }
};

int main(){
    Trie T;

    ifstream myfile;
    myfile.open(".\\dictionary.txt");
    
    string myline;
    int cnt = 0;

    if ( myfile.is_open() ) {
        while ( cnt < 10000 && myfile ) {
        getline (myfile, myline);
        transform(myline.begin(), myline.end(), myline.begin(), ::tolower);
        T.insert(myline);
        cnt++;
        }
    }
    else {
        cout << "Couldn't open file\n";
    }

    cout << "\nEnter word you want to search: ";
    string s;
    cin>>s;
    cout << endl;
    int n = s.size();

    string s1 = "";
    for(int j=0;j<n;j++){
        s1.push_back(s[j]);
        transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
        
        vector<string> vec;
        vec = T.wordsStartingWith(s1);

        string tmp(n-s1.length()+3, ' ');

        cout<<"["<<s1<<"]"<<":" << tmp;
        
        if(vec.empty()) cout<<"";
        for(auto it:vec){
            cout<<it<<" ";
        }
        cout<<endl;
    }

  return 0;
}