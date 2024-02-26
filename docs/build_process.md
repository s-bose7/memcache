## Step 1: Navigate to the Source Directory
```bash
cd /path/to/lfu-cache/src
```
## Step 2: Compile Source Files into Object Files
```bash
g++ -c KeyNode.cpp -o ../build/KeyNode.o
g++ -c FrequencyNode.cpp -o ../build/FrequencyNode.o
g++ -c MapItem.cpp -o ../build/MapItem.o
g++ -c LFUCache.cpp -o ../build/LFUCache.o
g++ -c main.cpp -o ../build/main.o
```

## Step 3: Link Object Files to Create Executable Binary
```bash
g++ ../build/LFUCache.o ../build/KeyNode.o ../build/FrequencyNode.o ../build/MapItem.o ../build/main.o -o ../build/lfu_cache
```
## Step 4: Run the Program
```bash
cd ../build
./lru_cache
```
