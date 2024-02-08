#include <stdlib.h>
#include <memory.h>
#include "SegmentAlloc.h"

SegmentAlloc_Mod* create_SegmentAlloc_Mod(SegmentAlloc* alloc){
    SegmentAlloc_Mod* mod = (SegmentAlloc_Mod*) malloc(sizeof( SegmentAlloc_Mod) + alloc->segment_size);
    mod->next = NULL;
    return mod;
}

//--------------------------------------------------------------------------------------------

void init_SegmentAlloc(SegmentAlloc* alloc, size_t size){
    alloc->segment_size = size;
    alloc->ptr = 0;

    alloc->head = alloc->tail = create_SegmentAlloc_Mod(alloc);

    alloc->segment_count = 1;
}

void push_data_SegmentAlloc(SegmentAlloc* alloc, void* data, size_t size){

    size_t data_ptr = 0;
    while(size > 0){
        void* mem = alloc->tail->data;
        size_t mem_ptr = alloc->ptr;

        size_t left_mem = alloc->segment_size - alloc->ptr;
        size_t contained_size;
        if( size >= left_mem){
            SegmentAlloc_Mod* mod = create_SegmentAlloc_Mod(alloc);
            alloc->ptr = 0;
            alloc->segment_count += 1;
            alloc->tail->next = mod;
            alloc->tail = mod;

            contained_size = left_mem;
        }else{
            contained_size = size;
            alloc->ptr += size;
        }

        memcpy(mem + mem_ptr, data + data_ptr, contained_size);
        size -= contained_size;
        data_ptr += contained_size;
    }

}

//--------------------------------------------------------------------------------------------
void init_SegmentAlloc_It_Stream(SegmentAlloc_It_Stream* it, SegmentAlloc* alloc){
    it->mod = alloc->head;
    it->alloc = alloc;
}

int has_SegmentAlloc_It_Stream(SegmentAlloc_It_Stream* it){
    return it->mod != NULL;
}
void next_SegmentAlloc_It_Stream(SegmentAlloc_It_Stream* it){
    it->mod = it->mod->next;
}

void* data_SegmentAlloc_It_Stream(SegmentAlloc_It_Stream* it, size_t* size){
    if(it->mod->next == NULL){
        *size = it->alloc->ptr;
    }else{
        *size = it->alloc->segment_size;
    }
    return it->mod->data;
}


