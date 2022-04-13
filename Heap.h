#include "Movie.h"
class Heap
{
    public:
        //constructors
        Heap();             //default capacity of 5
        Heap(int capacity);

        //big three
        ~Heap();
        Heap(const Heap& other);
        const Heap& operator=(const Heap& other);

        //accesssors
        int Size();
        int Capacity();
        Movie& Max();

        //behaviors
        bool Empty();
        bool Insert(Movie& toInsert);  // returns true on successful insert
        Movie ExtractMax();


    private:
        int capacity;
        int size;
        Movie* heapStructure;  //an array of movie pointers
        void CopyStuff(const Heap& other);
        void HeapifyDown();
        void HeapifyUp(Movie& toCompare);

        //returns the index based on the passed in one, -1 if doesn't exist
        int Left(int parent);
        int Right(int parent);
        int Parent(int child);

        int FindBiggerChild(int parent);


};