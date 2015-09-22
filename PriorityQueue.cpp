#include "PriorityQueue.hpp"
#include <cmath>
#include <iostream>

using namespace std;

PriorityQueue::PriorityQueue(unsigned int capacity)
{
                                      
capacity_ = capacity;
size_ = 0;
heap_ = new DataType [capacity_+1];                       
}
  
PriorityQueue::~PriorityQueue()
{
delete [] heap_;
} 

bool PriorityQueue::enqueue(DataType val)
{
if (size_ == capacity_) return false;
else if (size_==0) 
{
     heap_[1] = val;
     size_++;
     return true;
}              
else
{ 
     unsigned int i = size_+1;    
     heap_[i] = val;
     while (i>1 && val > heap_[i/2])
     { 
     DataType temp = val;
     heap_[i]=heap_[i/2];
     heap_[i/2] = temp;
     i=i/2;               
     }
     size_++;
     return true;
}
}
     
bool PriorityQueue::dequeue()
{
     if (size_ == 0) return false;
     else if (size_ == 1) 
     {
          size_--;
          return true;
     }
     else
     {
         unsigned int i =1;
         heap_[1] = heap_[size_];
         heap_[size_] = 0;
         size_--;
         while ((size_ >= 2*i || size_ >= 2*i+1)&&(heap_[i] < heap_[2*i] || heap_[i] < heap_[2*i+1]))
          {
               DataType temp;
               temp = heap_[i];
               if (heap_[2*i] > heap_[2*i+1])
               {
               heap_[i]= heap_[2*i];
               heap_[2*i] = temp;
               i=2*i;
               }
               else  
               {
               heap_[i]= heap_[2*i+1];
               heap_[2*i+1] = temp;
               i=2*i+1;
               }           
          }
          return true;          
     }  
}

PriorityQueue::DataType PriorityQueue::max() const
{
       if (size_ == 0) return -1;
       else return heap_[1];
}
 
bool PriorityQueue::empty() const
{
return !size_;
}
 
bool PriorityQueue::full() const
{
return (size_ == capacity_);
}
   
unsigned int PriorityQueue::size() const
{
return size_;         
}

void PriorityQueue::print() const
{
    if (size_==0) cout << "Can't print, son!\n";
    for (int i =0; i < size_; i++)
    {
        cout << heap_[i+1] << "_";
    }
}
  

  

 
  
