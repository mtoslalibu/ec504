/*

  Beliz Kaleli, Mert Toslali and Novak Boskov

*/

#include <iostream>
#include <vector>
#include <math.h>
#include <sstream>
#include "vEB.hpp"
#include "XFastTrie.hpp"

using namespace std;

// Returns vector of numbers. Handles comma separated string inputs.
vector<int> getNums() {
    vector<int> ret;
    string input;
    int c;

    cin.ignore();
    getline(cin, input);
    stringstream ss(input);
    while (ss >> c) {
        ret.push_back(c);

        if (ss.peek() == ',' || ss.peek() == ' ')
            ss.ignore();
    }

    return ret;
}

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
            cout << "Veb Tree is created: [Upper limit is 65535 && Plz don't use negative values!]"<< endl;
            cout << "If no predecessor or successor found: return values are -1 and 65536 respectively.."<< endl;

            veb = new VEBTree(512);

            while (1) {
                cout << endl << "Please choose the operation:" << endl;
                cout << "1) for insert" << endl;
                cout << "2) for lookup" << endl;
                cout << "3) for delete" << endl;
                cout << "4) for predecessor" << endl;
                cout << "5) for successor" << endl;
                cout << "6) for minimum" << endl;
                cout << "7) for maximum" << endl;
                cout << "8) construct new data structure" << endl;
                cout << ">> ";
                int operation;
                cin >> operation;

                vector<int> input_nums;

                switch (operation) {
                case 1:
                    cout << "Insert numbers [in format: 1,2,3]: ";
                    input_nums = getNums();

                    for (int n : input_nums)
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
                    cout << "Successor is: " << veb->successor(s_key)<< endl;
                    continue;
                case 6:
                    cout << "Minimum is: " << veb->getMin() << endl;
                    continue;
                case 7:
                    cout << "Maximum is: " << veb->getMax() << endl;
                    continue;
                case 8:
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
                cout << endl << "Please choose the operation:" << endl;
                cout << "1) for insert" << endl;
                cout << "2) for lookup" << endl;
                cout << "3) for delete" << endl;
                cout << "4) for predecessor" << endl;
                cout << "5) for successor" << endl;
                cout << "6) for minimum" << endl;
                cout << "7) for maximum" << endl;
                cout << "8) construct new data structure" << endl;
                cout << ">> ";
                int operation;
                cin >> operation;

                Entry* e = NULL;
                Entry* predecessor = NULL;
                Entry* successor = NULL;
                vector<int> input_nums;

                switch (operation) {
                case 1:
                    cout << "Insert numbers [in format: 1,2,3]: ";
                    input_nums = getNums();

                    for (int n : input_nums) {
                        e = new Entry{(uint64_t) n};
                        entries.push_back(e);
                        xft.insert(e);
                    }

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
                    e = xft.getMin();
                    if (e)
                        cout << "Minimum is: " << e->key << endl;
                    else
                        cout << "There is no minimum." << endl;

                    continue;
                case 7:
                    e = xft.getMax();
                    if (e)
                        cout << "Maximum is: " << e->key << endl;
                    else
                        cout << "There is no maximum." << endl;

                    continue;
                case 8:
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
