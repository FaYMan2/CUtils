#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h>
#include<assert.h>

#define FNV_OFFSET 14695981039346656037 
#define FNV_PRIME 1099511628211 
#define INITIAL_CAPACITY 10000

typedef struct ht_entry{
    const char* key;
    void* value;
} entry;



typedef struct hashTablle {
    entry* ht_entries;
    size_t length;
    size_t capacity;
} ht;


ht* createHt(){
    ht* h_table = malloc(sizeof(ht));
    if(!h_table){
        return NULL;
    }

    h_table -> length = 0;
    h_table -> capacity = INITIAL_CAPACITY;
    h_table -> ht_entries = (entry*)calloc(INITIAL_CAPACITY,sizeof(entry));
    if(!h_table -> ht_entries){
        free(h_table);
        return NULL;
    }
    return h_table;
}

void deleteHt(ht* h_table){
    for(int i = 0;i<h_table->length;i++){
        free((void*)h_table->ht_entries[i].key);
    }

    free(h_table->ht_entries);
    free(h_table);
}


static uint64_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

void* getEntry(ht* h_table,const char* key){
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash % (uint64_t)(h_table->capacity-1));
    while(h_table->ht_entries[index].key != NULL){
        if(strcmp(h_table->ht_entries[index].key,key) == 0){
            return h_table->ht_entries[index].value;
        }
        index++;
        if(index >= h_table->capacity){
            index = 0;
        }
    }
    return NULL;
}

bool expandHt(ht* h_table){
    h_table->capacity = h_table->capacity * 2;
    entry* newEntries = (entry*)realloc(h_table->ht_entries,sizeof(entry)*h_table->capacity);
    if(newEntries == NULL){
        return false;
    }
    h_table->ht_entries = newEntries;
    return true;
}

static const char* addEntry(ht* h_table,const char* key,void* value){
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash % (uint64_t)(h_table->capacity-1));
    while(h_table->ht_entries[index].key != NULL){
        if(strcmp(key,h_table->ht_entries[index].key) == 0){
            h_table->ht_entries[index].value = value;
            return h_table->ht_entries[index].key;
        }
        index++;
        if(index >= h_table->capacity){
            index = 0;
        }
    }

    if(!h_table->length){
        key = strdup(key);
        if(key == NULL){
            return NULL;
        }
        h_table->length++;
    }
    h_table->ht_entries[index].key = key;
    h_table->ht_entries[index].value = value;
    return key;
}

const char* add(ht* h_table,const char* key,void* value){
    assert(value != NULL);
    if (h_table->length * 2 >= h_table->capacity){
        if(!expandHt(h_table)){
            return NULL;
        }
    }

    return addEntry(h_table,key,value);
}


int main(){
    ht* h_table = createHt();
    addEntry(h_table,(const char*)"hi",(void*)"world");
    const char* val = getEntry(h_table,(const char*)"hi");
    if(val){
        printf("value : %s",val);
    }
    else{
        printf("something went wrong");
    }
}

