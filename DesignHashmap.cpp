class MyHashMap {
public:
    vector<list<pair<int,int>>>bucket;
    int n ;
    MyHashMap() {
        n = 1e4;
        bucket.resize(n);
    }
    void put(int key, int value) {
        int bucketnum = key%n;
        auto& chain = bucket[bucketnum];
        for(auto &it:chain){
            if(it.first == key){
                it.second = value;
                return;
            }

        }
        //if cant find the key
        chain.emplace_back(key,value);
    }
    
    int get(int key) {
        int bucketnum=key%n;
        auto &chain = bucket[bucketnum];
        for(auto &it:chain){
            if(it.first == key){
                return it.second;
            }
        }
        return -1;

        
        
    }
    
    void remove(int key) {
        int bucketnum=key%n;
        auto &chain = bucket[bucketnum];
        for(auto &it:chain){
            if(it.first == key){
                chain.remove(it);
                return;
            }
        }

    }
};