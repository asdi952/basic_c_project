#ifndef SEGMENTALLOC_H_
#define SEGMENTALLOC_H_

typedef struct __SA_M{
    struct __SA_M* next;
    void* data[];
}SegmentAlloc_Mod;


//--------------------------------------------------------------------------------------------
typedef struct __SA{
    SegmentAlloc_Mod *head, *tail;
    size_t ptr;

    size_t segment_size;
    size_t segment_count;
}SegmentAlloc;

void init_SegmentAlloc(SegmentAlloc* alloc, size_t size);

void push_data_SegmentAlloc(SegmentAlloc* alloc, void* data, size_t size);

//--------------------------------------------------------------------------------------------
typedef struct __SA_I_S{
    SegmentAlloc* alloc;
    SegmentAlloc_Mod* mod;
}SegmentAlloc_It_Stream;

void init_SegmentAlloc_It_Stream(SegmentAlloc_It_Stream* it, SegmentAlloc* alloc);
int has_SegmentAlloc_It_Stream(SegmentAlloc_It_Stream* it);
void next_SegmentAlloc_It_Stream(SegmentAlloc_It_Stream* it);
void* data_SegmentAlloc_It_Stream(SegmentAlloc_It_Stream* it, size_t* size);



/* Test -- 

const char* a0 = "one\n";
    const char* a1 = "two\n";
    const char* a2 = "three\n";

    SegmentAlloc alloc;
    init_SegmentAlloc(&alloc, 2);
    push_data_SegmentAlloc(&alloc, a0, strlen(a0));
    push_data_SegmentAlloc(&alloc, a1, strlen(a1));
    push_data_SegmentAlloc(&alloc, a2, strlen(a2));


    SegmentAlloc_It_Stream it;
    init_SegmentAlloc_It_Stream(&it, &alloc);

    while( has_SegmentAlloc_It_Stream(&it)){
        size_t size;
        void* data = data_SegmentAlloc_It_Stream(&it, &size);
        printf("%.*s", (int)size, (char*)data);

        next_SegmentAlloc_It_Stream(&it);
    }

*/
#endif