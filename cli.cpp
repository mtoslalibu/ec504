/*

 Beliz Kaleli, Mert Toslali and Novak Boskov

 */

#include <iostream>
#include <vector>
#include <math.h>
#include "vEB.hpp"
#include "XFastTrie.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Van Emde Boas tree vs x-Fast trie \n"
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";

    while (1) {
        cout << "1) for Van Emde Boas Tree [successor >, predecessor <]" << endl;
        cout << "2) for x-Fast trie [successor >=, predecessor <=]" << endl;
        cout << ">> ";
        int option;
        cin >> option;

        if (option != 1 && option != 2)
            return 0;

        // This has to be initialized here due to "jump bypasses
        // initialization" compiler error. Probably better than
        // compiler flag.
        VEBTree *veb = NULL;

        switch (option) {
        case 1:
            cout << "Please enter the key size: ";
            int size;
            cin >> size;

            veb = new VEBTree(512);

            while (1) {
                cout << "Please choose the operation:" << endl;
                cout << "1) for insert" << endl;
                cout << "2) for lookup" << endl;
                cout << "3) for delete" << endl;
                cout << "4) for predecessor" << endl;
                cout << "5) for successor" << endl;
                cout << "6) construct new data structure" << endl;
                cout << ">> ";
                int operation;
                cin >> operation;

                switch (operation) {
                case 1:
                    cout << "Insert number: ";
                    int n;
                    cin >> n;
                    veb->insert(n);
                    continue;
                case 2:
                    cout << "Lookup key: ";
                    int key;
                    cin >> key;
                    if (veb->findItem(key))
                        cout << "Found!" << endl;
                    else
                        cout << "Not found." << endl;

                    continue;
                case 3:
                    cout << "Delete key: ";
                    int d_key;
                    cin >> d_key;
                    veb->deleteItem(d_key);
                    cout << d_key << " deleted." << endl;
                    continue;
                case 4:
                    cout << "Find predecessor of key: ";
                    int p_key;
                    cin >> p_key;
                    cout << "Predecessor is: " << veb->predecessor(p_key) << endl;
                    continue;
                case 5:
                    cout << "Find successor of key: ";
                    int s_key;
                    cin >> s_key;
                    cout << "Successor is: " << veb->successor(s_key);
                    continue;
                case 6:
                    break;
                }

                break;
            }

            // free data allocated by VEBTree and go construct new
            // data structure
            delete(veb);

            break;
        case 2:
            cout << "Please provide key lengths in bits:" << endl;
            cout << "8, 16, 32 or 64:" << endl;
            cout << ">> ";

            int layers;
            cin >> layers;

            if (layers != 8 && layers != 16 && layers != 32 && layers != 64) {
                cout << "Please enter some of the valid bit numbers." << endl;
                continue;
            }

            XFastTrie xft = XFastTrie(layers);
            vector<Entry*> entries;

            while (1) {
                cout << "Please choose the operation:" << endl;
                cout << "1) for insert" << endl;
                cout << "2) for lookup" << endl;
                cout << "3) for delete" << endl;
                cout << "4) for predecessor" << endl;
                cout << "5) for successor" << endl;
                cout << "6) construct new data structure" << endl;
                cout << ">> ";
                int operation;
                cin >> operation;

                Entry* e = NULL;
                Entry* predecessor = NULL;
                Entry* successor = NULL;

                switch (operation) {
                case 1:
                    cout << "Insert number: ";
                    uint64_t n;
                    cin >> n;
                    e = new Entry{n};
                    entries.push_back(e);
                    xft.insert(e);
                    continue;
                case 2:
                    cout << "Lookup key: ";
                    uint64_t key;
                    cin >> key;
                    if (xft.lookup(key))
                        cout << "Found!" << endl;
                    else
                        cout << "Not found." << endl;

                    continue;
                case 3:
                    cout << "Delete key: ";
                    uint64_t d_key;
                    cin >> d_key;
                    xft.del(d_key);
                    cout << d_key << " deleted." << endl;
                    continue;
                case 4:
                    cout << "Find predecessor of key: ";
                    uint64_t p_key;
                    cin >> p_key;
                    predecessor = xft.getPredecessor(p_key);
                    cout << "Predecessor is: ";
                    if (predecessor)
                        cout << predecessor->key;
                    else
                        cout << "There is no predecessor of " << p_key << endl;

                    continue;
                case 5:
                    cout << "Find successor of key: ";
                    uint64_t s_key;
                    cin >> s_key;
                    successor = xft.getSuccessor(s_key);
                    cout << "Successor is: " << endl;
                    if (successor)
                        cout << successor->key;
                    else
                        cout << "There is no successor of " << s_key << endl;

                    continue;
                case 6:
                    break;
                }

                break;
            }

            // clear the entries memory from heap to construct another
            // data structure
            for (auto e : entries)
                delete(e);

            break;
        }
    }
}
