## Step 1: Navigate to the Source Directory
#### cd /path/to/lfu-cache/src

## Step 2: Compile Source Files into Object Files
#### g++ -c LFUCache.cpp -o ../build/LFUCache.o
#### g++ -c NodeList.cpp -o ../build/NodeList.o
#### g++ -c FrequencyNode.cpp -o ../build/FrequencyNode.o
#### g++ -c MapItem.cpp -o ../build/MapItem.o
#### g++ -c main.cpp -o ../build/main.o

## Step 3: Link Object Files to Create Executable Binary
#### g++ ../build/LFUCache.o ../build/NodeList.o ../build/FrequencyNode.o ../build/MapItem.o ../build/main.o -o ../build/lru_cache

## Step 4: Run the Program
#### cd ../build
#### ./lru_cache

