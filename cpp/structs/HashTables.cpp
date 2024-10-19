#include <iostream>
#define displayKey(table, k) {if (table.get(k) == nullptr) {cout << "Não há valor associado à chave " << k << endl;} else {cout << "[" << k << "]: " <<  table.get(k)->value << endl;};}

using namespace std;

typedef struct HashTableNode HTNode;
struct HashTableNode {
    unsigned key;
    int value;
    HTNode* next;
    HTNode* previous;
};

class HashTable {
    private:
        HTNode** m_table; //An array with the respective lists for each hash
        int m_size; //The size of the hash function image set;

        unsigned hash(unsigned key) {
            return key % m_size;
        }

    public:
        HashTable(int iM): m_table(nullptr), m_size(iM) { //iM is hash image size
                m_table = new HTNode*[iM]; //initializes as an array (before initialized as nullptr)
                for (int i = 0; i < m_size; i++) { //will set all the values to nullptr since no insertion has been made
                    m_table[i] = nullptr;
                }
            }

        ~HashTable() {
            for (int i = 0; i < m_size; i++) { //Will delete every hash stored values
                HTNode * node = m_table[i];
                while (node != nullptr) { //Delete the entire linked list of that hash value
                    HTNode* nextNode = node->next;
                    delete node;
                    node = nextNode;
                }
            }
            delete[] m_table; //Delete hashes array
        }

        void set(unsigned key, int value){ //For seting a pair of key, value
            unsigned hashed = hash(key); //Gets the hash for the key
            HTNode* ptrNode = m_table[hashed]; //Gets the linked list of that hash
            while (ptrNode != nullptr and ptrNode->key != key){ //And runs till find the node repecting to the key
                ptrNode = ptrNode->next;
            }
            if (ptrNode == nullptr){ //The key has never been used, so creates the node
                ptrNode = new HTNode;
                ptrNode->key = key;
                ptrNode->previous = nullptr;
                ptrNode->next = m_table[hashed];
                if (m_table[hashed] != nullptr){
                    m_table[hashed]->previous = ptrNode;
                } //Inserts before the list (doesn't need to add in the end)
                m_table[hashed] = ptrNode;
            }
            ptrNode->value = value; //in either cases, update the value
        }

        HTNode* get(unsigned key){
            unsigned hashed = hash(key);
            HTNode* ptrNode = m_table[hashed];
            while (ptrNode != nullptr and ptrNode->key != key){ //And runs till find the node repecting to the key
                ptrNode = ptrNode->next;
            }
            return ptrNode;
        }

        void remove(unsigned key){
            unsigned hashed = hash(key);
            HTNode* ptrNode = m_table[hashed];
            while (ptrNode != nullptr and ptrNode->key != key){ //And runs till find the node repecting to the key
                ptrNode = ptrNode->next;
            }
            if (ptrNode != nullptr){
                HTNode* nextNode = ptrNode->next;
                if (nextNode != nullptr) {
                    nextNode->previous = ptrNode->previous;
                }
                HTNode* previousNode = ptrNode->previous;
                if (previousNode != nullptr) {
                    ptrNode->previous->next = ptrNode->next;
                } else {
                    m_table[hashed] = ptrNode->next;
                }
                delete ptrNode;
            } //if reaches here, then the key didn't exist anyway
        }
};

//TODO: adicionar algortimos de resize da hashtable

/*int main(){
    HashTable hashnew = HashTable(20);

    cout << "Acessando chave inválida" << endl;
    displayKey(hashnew, 20);

    cout << endl << "Atribuindo e acessando valor" << endl;
    hashnew.set(20, 12);
    displayKey(hashnew, 20);
    hashnew.set(3, 4);
    displayKey(hashnew, 3);

    cout << endl << "Sobreescrevendo valor" << endl;
    hashnew.set(20, 14);
    displayKey(hashnew, 20);

    cout << endl << "Escrevendo em chaves com mesma hash" << endl;
    hashnew.set(40, 99);
    displayKey(hashnew, 40);
    hashnew.set(60, 199);
    displayKey(hashnew, 60);
    hashnew.set(20, 12);
    displayKey(hashnew, 20);
    displayKey(hashnew, 40);
    displayKey(hashnew, 60);

    cout << endl << "Removendo chave" << endl;
    hashnew.remove(3);
    displayKey(hashnew, 3);

    cout << endl << "Removendo chaves com mesma hash" << endl;
    hashnew.remove(20);
    displayKey(hashnew, 20);
    displayKey(hashnew, 40);
    displayKey(hashnew, 60);
    hashnew.remove(40);
    displayKey(hashnew, 20);
    displayKey(hashnew, 40);
    displayKey(hashnew, 60);
    hashnew.remove(60);
    displayKey(hashnew, 20);
    displayKey(hashnew, 40);
    displayKey(hashnew, 60);

    cout << endl << "Atribuindo valores novamente para chaves deletadas" << endl;
    hashnew.set(60, 99);
    displayKey(hashnew, 60);
    displayKey(hashnew, 40);
}*/
