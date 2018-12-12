/*

  Beliz Kaleli, Mert Toslali and Novak Boskov

*/

#pragma once
#include <cmath>
#include <vector>

using namespace std;

class VEBTree
{
    public:
    VEBTree(size_t sizeOfVEBTree)
    {
        int temp =int(ceil(log2(log2(sizeOfVEBTree))));

        int k = temp;
        temp = int(pow(2, pow(2, k)));

        //floor(x/√M)
        partitionSize = temp;

        if(partitionSize > 2)
        {
            //
            temp = int(sqrt(double(partitionSize)));
            summary = new VEBTree(temp);

            temp = int(sqrt(double(partitionSize)));
            int clusters = temp;
            // if just partioned to 2 , then only 2 clusters
            if (partitionSize == 2)
                clusters = 2;
            for (int i = 0; i < clusters; i++)
            {
                temp = int(sqrt(double(partitionSize)));
                cluster.push_back(new VEBTree(temp));
            }
        }
    }
    VEBTree() {}

    void insert(int item)
    {
        if (item >= partitionSize || item < 0 )
            throw "Size is exceeded";
        if (partitionSize == 2)
        {
            data[item] = true;

            if (min == -1)
            {
                min = item;
                max = item;
                return;
            }

            if (item < min)
                min = item;
            if (item > max)
                max = item;

            return;
        }

        if (min == -1)
        {
            min = item;
            max = item;
            return;
        }

        if (item < min)
        {
            int temp = min;
            min = item;
            item = temp;//swap item and min
        }
        if (item > max)
        {
            max = item;
        }

        if (cluster[high(item)]->min == -1)
        {
            summary->insert(high(item));
        }

        cluster[high(item)]->insert(low(item));
    }

    int successor(int item)
    {
        if (item < min)
            return min;
        if (item > max)
            return partitionSize;

        int i = high(item);
        int j;

        if (partitionSize == 2)
        {
            if (data[1] && item == 0)
                j = 1;
            else
                j = 2;
        }
        else
        {
            if (low(item) < cluster[i]->max)
            {
                j = cluster[i]->successor(low(item));
            }
            else
            {
                i = summary->successor(i);
                if (i >= int(sqrt(double(partitionSize))))
                    return partitionSize;
                j = cluster[i]->min;
            }
        }
        return index(i, j);
    }

    int predecessor(int item)
    {
        if (item > max)
            return max;
        if (item < min)
            return -1;

        int i = high(item);
        int j;

        if (partitionSize == 2)
        {
            if (data[0] && item == 1)
                j = 0;
            else
                j = -1;
        }
        else
        {
            if (low(item) > cluster[i]->min && cluster[i]->min != -1)
            {
                j = cluster[i]->predecessor(low(item));
                if (j == -1)
                    j = low(cluster[i]->min);
            }
            else if (high(item) == high(min) && low(item) > low(min))
            {
                /*j = cluster[i]->predecessor(low(item));
                 if (j == -1)
                 j = cluster[i]->min;*/
                j = low(min);
            }
            else
            {
                i = summary->predecessor(i);
                if (i < 0)
                {
                    if (high(min) < high(item))
                        i = high(min);
                    else
                        return -1;
                }
                j = cluster[i]->max;
                if (j < 0)
                    j = low(min);
            }
        }
        return index(i, j);
    }

    void deleteItem(int item)
    {
        if (item < 0 || item >= partitionSize)
            throw "Size is exceeded";
        if (partitionSize == 2)
        {
            data[item] = false;

            if (min == item && max == item)
            {
                min = -1;
                max = -1;
                return;
            }

            if (min == item)
                min = max;
            else
                max = min;

            return;
        }

        if (item == min)
        {
            int i = summary->min;
            if (i == -1)
            {
                min = -1;
                max = -1;
                return;
            }
            min = index(i, cluster[i]->min);
            item = min;
        }

        cluster[high(item)]->deleteItem(low(item));
        if (cluster[high(item)]->min == -1)
            summary->deleteItem(high(item));

        if (item == max)
        {
            int i = summary->max;
            if (i == -1)
                max = min;
            else
                max = index(i, cluster[i]->max);
        }
    }

    bool findItem(int item)
    {
        if (item == min || item == max)
            return true;
        if (item < min || item > max)
            return false;

        return cluster[high(item)]->findItem(low(item));

    }

    int getMin()
    {
        return min;
    }

    int getMax()
    {
        return max;
    }

    int size()
    {
        return partitionSize;
    }

protected:
    int min = -1; // None
    int max = -1;
    int partitionSize;
    bool data[2] = { false, false };
    vector<VEBTree*> cluster;
    VEBTree* summary;
private:

    int index(int i, int j)
    {
        return i * sqrt(double(partitionSize)) + j;
    }
    int low(int x)
    {
        return x % int(sqrt(double(partitionSize)));
    }
    int high(int x)
    {
        return int(floor(x / sqrt(double(partitionSize))));
    }
};
