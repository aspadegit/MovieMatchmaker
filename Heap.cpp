#include <math.h>
#include <stdexcept>
#include "Heap.h"

//================================== PUBLIC ==========================================

Heap::Heap()
{
    capacity = 600000;
    size = 0;
    heapStructure = new Movie[600000];
}

Heap::Heap(int capacity)
{
    size = 0;
    heapStructure = new Movie[capacity];
}

Heap::~Heap()
{
    delete[] heapStructure;
}

Heap::Heap(const Heap& other)
{
    CopyStuff(other);

}

const Heap& Heap::operator=(const Heap& other)
{
    
    CopyStuff(other);
    return *this;
}


int Heap::Size()
{
    return size;
}

int Heap::Capacity()
{
    return capacity;
}

bool Heap::Empty()
{
    if(size <= 0)
        return true; 
    return false;
}

Movie& Heap::Max()
{
    return heapStructure[0];
}


bool Heap::Insert(Movie& toInsert)
{
    if(size >= capacity)
    {
        //throwing an error to help find bugs (make sure initial capacity is correct)
        throw std::out_of_range("Heap is full. Cannot Insert.");
        return false;
    }

    heapStructure[size++] = toInsert;
    HeapifyUp(toInsert);

    return true;
}



Movie Heap::ExtractMax()
{
    //cannot remove on an empty heap
    if(size <= 0)
    {
        throw std::out_of_range("Heap is empty. Cannot remove");
    }

    Movie returnMovie = heapStructure[0];

    if(size > 1)
        HeapifyDown();
    size--;

    return returnMovie;
    
}

// ================================= PRIVATE =========================================

void Heap::CopyStuff(const Heap& other)
{
    this->capacity = other.capacity;
    this->size = other.size;
    Movie* newHeap = new Movie[capacity];

    for(int i = 0; i < size; i++)
    {
        newHeap[i] = other.heapStructure[i];
    }
}

void Heap::HeapifyDown()
{
    heapStructure[0] = heapStructure[size-1];
    int leftChild = Left(0);
    int rightChild = Right(0);
    int currentParent = 0;

    bool keepSwapping = true;
    while(keepSwapping)
    {
        //no children at all
        if(leftChild == -1 && rightChild == -1)
        {
            keepSwapping = false;
            break;
        }

        //one of them is a leaf
        if(leftChild == -1 || rightChild == -1)
            keepSwapping = false;

        
        //find the bigger child & swap with it
        int biggerChild = FindBiggerChild(currentParent);
        if(heapStructure[biggerChild].GetSimilarity() > heapStructure[currentParent].GetSimilarity())
        {
            //swap
            Movie temp = heapStructure[biggerChild];
            heapStructure[biggerChild] = heapStructure[currentParent];
            heapStructure[currentParent] = temp;
            currentParent = biggerChild;
        }
        else
        {
            keepSwapping = false;
        }

        leftChild = Left(currentParent);
        rightChild = Right(currentParent);
        
    }
    
}

void Heap::HeapifyUp(Movie& toCompare)
{
    int currentIndex = size-1;
    int parentIndex = Parent(currentIndex);

    //0 is the root node
    //parent should be greater than child (swap if they are not)
    while(currentIndex != 0 && heapStructure[parentIndex].GetSimilarity() < toCompare.GetSimilarity())
    {
        //swap
        Movie temp = heapStructure[parentIndex];
        heapStructure[parentIndex] = toCompare;
        heapStructure[currentIndex] = temp;

        //shift indices up 
        parentIndex = Parent(parentIndex);
        currentIndex = Parent(currentIndex);
        
    }

}

int Heap::Left(int parent)
{
    if(2 * parent + 1 >= size)
    {
        return -1;
    }

    return 2*parent + 1;
}

int Heap::Right(int parent)
{
    if(2 * parent + 2 >= size)
    {
        return -1;
    }

    return 2*parent + 2;
}

int Heap::Parent(int child)
{
    double parent = floor(((double)child-1)/2);
    if(parent < 0)
        return -1;
    
    return (int)parent;
}

int Heap::FindBiggerChild(int parent)
{
    int left = Left(parent);
    int right = Right(parent);

    //shouldnt happen, hopefully
    if(left == -1 && right == -1)
    {
        return -1;
    }

    if(left != -1)
    {
        if(right == -1)
            return left;
        
        if(heapStructure[left].GetSimilarity() > heapStructure[right].GetSimilarity())
            return left;
        else
            return right;
    }

    //left == -1, right != -1
    return right;
}