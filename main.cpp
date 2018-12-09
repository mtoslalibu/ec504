#include <vector>
#include <math.h>
#include <time.h>
#include "vEB.hpp"
#include "XFastTrie.hpp"

int main(int argc, char* argv[]) {
    FILE* f = fopen("stat.txt", "a+");

    XFastTrie xft8 = XFastTrie(8);
    XFastTrie xft16 = XFastTrie(16);

    // allocate space for the data in XFastTrie
    vector<Entry*> entries;
    for (unsigned long i = 0; i < pow(2, 16); i++) {
        Entry* e = new Entry{i};
        entries.push_back(e);
    }

    // --------------------------------------------------------------------------------
    // XFastTrie(8)
    // --------------------------------------------------------------------------------

    cout << "inserts for XFastTrie(8)" << endl;
    fprintf(f, "XFastTrie(8) insert\n");
    for (int i = 0; i < pow(2, 8); i += 2) {
        time_t t = clock();
        xft8.insert(entries[i]);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "lookup from XFastTrie(8)" << endl;
    fprintf(f, "\nXFastTrie(8) lookup\n");
    for (int i = 0; i < pow(2, 8); i += 2) {
        time_t t = clock();
        xft8.lookup((uint64_t) i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "predecessor for XFastTrie(8)" << endl;
    fprintf(f, "\nXFastTrie(8) predecessor\n");
    for (int i = 1; i < pow(2, 8) - 1; i += 2) {
        time_t t = clock();
        xft8.getPredecessor((uint64_t) i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "successor for XFastTrie(8)" << endl;
    fprintf(f, "\nXFastTrie(8) successor\n");
    for (int i = 1; i < pow(2, 8) - 1; i += 2) {
        time_t t = clock();
        xft8.getSuccessor((uint64_t) i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "deletes from XFastTrie(8)" << endl;
    fprintf(f, "\nXFastTrie(8) delete\n");
    for (int i = 0; i < pow(2, 8); i += 2) {
        time_t t = clock();
        xft8.del(i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    // --------------------------------------------------------------------------------
    // XFastTrie(16)
    // --------------------------------------------------------------------------------

    cout << "inserts for XFastTrie(16)" << endl;
    fprintf(f, "\nXFastTrie(16) insert\n");
    for (int i = 0; i < pow(2, 16) / 8; i += 2) {
        time_t t = clock();
        xft16.insert(entries[i]);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "lookup from XFastTrie(16)" << endl;
    fprintf(f, "\nXFastTrie(16) lookup\n");
    for (int i = 0; i < pow(2, 16); i += 2) {
        time_t t = clock();
        xft16.lookup((uint64_t) i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "predecessor for XFastTrie(16)" << endl;
    fprintf(f, "\nXFastTrie(16) predecessor\n");
    for (int i = 1; i < (pow(2, 16) - 1) / 8; i += 2) {
        time_t t = clock();
        xft16.getPredecessor((uint64_t) i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "successor for XFastTrie(16)" << endl;
    fprintf(f, "\nXFastTrie(16) successor\n");
    for (int i = 1; i < (pow(2, 16) - 1) / 8; i += 2) {
        time_t t = clock();
        xft16.getSuccessor((uint64_t) i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "deletes from XFastTrie(16)" << endl;
    fprintf(f, "\nXFastTrie(16) delete\n");
    for (int i = 0; i < pow(2, 16) / 8; i += 2) {
        time_t t = clock();
        xft16.del((uint64_t) i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    // --------------------------------------------------------------------------------
    // vEB(256)
    // --------------------------------------------------------------------------------

    VEBTree *v256 = new VEBTree(256);

    cout << "inserts for vEB(256)" << endl;
    fprintf(f, "\nvEB(256) insert\n");
    for (int i = 0; i < pow(2, 8); i += 2) {
        time_t t = clock();
        v256->insert(i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "lookup from vEB(256)" << endl;
    fprintf(f, "\nvEB(256) lookup\n");
    for (int i = 0; i < pow(2, 8); i += 2) {
        time_t t = clock();
        v256->findItem(i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "predecessor for vEB(256)" << endl;
    fprintf(f, "\nvEB(256) predecessor\n");
    for (int i = 1; i < pow(2, 8) - 1; i += 2) {
        time_t t = clock();
        v256->predecessor(i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "successor for vEB(256)" << endl;
    fprintf(f, "\nvEB(256) successor\n");
    for (int i = 1; i < pow(2, 8) - 1; i += 2) {
        time_t t = clock();
        v256->successor(i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "deletes from vEB(256))" << endl;
    fprintf(f, "\nvEB(256) delete\n");
    for (int i = 0; i < pow(2, 8); i += 2) {
        time_t t = clock();
        v256->deleteItem(i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    delete(v256);

    // --------------------------------------------------------------------------------
    // vEB(512)
    // --------------------------------------------------------------------------------

    VEBTree* v512 = new VEBTree(512);

    cout << "inserts for vEB(512)" << endl;
    fprintf(f, "\nvEB(512) insert\n");
    for (int i = 0; i < pow(2, 16) / 8; i += 2) {
        time_t t = clock();
        v512->insert(i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "lookup from vEB(512)" << endl;
    fprintf(f, "\nvEB(512) lookup\n");
    for (int i = 0; i < pow(2, 16); i += 2) {
        time_t t = clock();
        v512->findItem(i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "predecessor for vEB(512)" << endl;
    fprintf(f, "\nvEB(512) predecessor\n");
    for (int i = 1; i < (pow(2, 16) - 1) / 8; i += 2) {
        time_t t = clock();
        v512->predecessor(i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "successor for vEB(512)" << endl;
    fprintf(f, "\nvEB(512) successor\n");
    for (int i = 1; i < (pow(2, 16) - 1) / 8; i += 2) {
        time_t t = clock();
        v512->successor(i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    cout << "deletes from vEB(512)" << endl;
    fprintf(f, "\nvEB(512) delete\n");
    for (int i = 0; i < pow(2, 16) / 8; i += 2) {
        time_t t = clock();
        v512->deleteItem(i);
        fprintf(f, "%f ", (double) (clock() - t) / CLOCKS_PER_SEC);
    }

    delete(v512);

    fclose(f);

    return 0;
}
