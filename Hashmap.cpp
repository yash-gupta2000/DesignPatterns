#include <bits/stdc++.h>
using namespace std;

template <typename K, typename V>
class HashMap
{
    static const int INITIAL_SIZE = 17;
    static constexpr double LOAD_FACTOR = 0.75;

    struct Entry
    {
        K key;
        V value;
        Entry *next;
        Entry(K k, V v) : key(k), value(v), next(nullptr) {}
    };

    vector<Entry *> table;
    int capacity;
    int size;

    // **Custom Hash Function, Not Implemented**
    int hashIt(K key, int mod)
    {
        return hash<K>{}(key) % mod;
    }

    // **Finds the next prime number > n for better resizing**
    int getNextPrime(int n)
    {
        while (true)
        {
            bool isPrime = true;
            for (int i = 2; i * i <= n; i++)
            {
                if (n % i == 0)
                {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime)
                return n;
            n++;
        }
    }

    // **Resizes the HashMap when Load Factor exceeds 0.75**
    void resize()
    {
        int newCapacity = getNextPrime(capacity * 2); // Next prime for better hashing
        vector<Entry *> newTable(newCapacity, nullptr);

        for (int i = 0; i < capacity; i++)
        {
            Entry *node = table[i];
            while (node)
            {
                int newIndex = hashIt(node->key, newCapacity);
                Entry *nextNode = node->next;

                // Move node to new table
                node->next = newTable[newIndex];
                newTable[newIndex] = node;

                node = nextNode;
            }
        }

        table = move(newTable);
        capacity = newCapacity;
    }

public:
    HashMap() : capacity(INITIAL_SIZE), size(0)
    {
        table.resize(capacity, nullptr);
    }

    // **Insert Key-Value Pair into HashMap**
    void put(K key, V value)
    {
        if ((double)size / capacity >= LOAD_FACTOR)
        {
            resize();
        }

        int index = hashIt(key, capacity);
        Entry *node = table[index];

        while (node)
        {
            if (node->key == key)
            {
                node->value = value; // Update existing key
                return;
            }
            node = node->next;
        }

        // Insert new node at head
        Entry *newNode = new Entry(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }

    // **Retrieve Value by Key**
    V get(K key)
    {
        int index = hashIt(key, capacity);
        Entry *node = table[index];

        while (node)
        {
            if (node->key == key)
            {
                return node->value;
            }
            node = node->next;
        }
        throw runtime_error("Key not found in HashMap"); // Handle missing key
    }

    // **Destructor to Free Memory**
    ~HashMap()
    {
        for (int i = 0; i < capacity; i++)
        {
            Entry *node = table[i];
            while (node)
            {
                Entry *temp = node;
                node = node->next;
                delete temp;
            }
        }
    }
};

int main()
{
    HashMap<int, string> myMap;

    for (int i = 1; i <= 100; i++)
    {
        myMap.put(i, "MYMAPVALUEIS-" + to_string(i));
    }

    cout << "Key 5: " << myMap.get(5) << endl;
    cout << "Key 15: " << myMap.get(15) << endl;

    try
    {
        cout << "Key 101: " << myMap.get(101) << endl;
    }
    catch (exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
