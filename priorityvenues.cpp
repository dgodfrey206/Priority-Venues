#include <iostream>
#include <map>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;

class PriorityVenues {
public:
    PriorityVenues()=default;
    PriorityVenues(size_t s){a.reserve(s);}
    void offer(unsigned char,int);
    int size() const;
    unsigned char pop();
    void heapifyUp();
    void heapifyDown(int);
    unsigned char top() const { return a[0]; }
    int Left(int i) const { return i*2+1; }
    int Right(int i) const { return i*2+2; }
    int Parent(int i) const { return (i - 1)/2; }
    auto find(unsigned char) const;
    bool empty()const{return a.empty();}
private:
    void push(unsigned char, int);
    vector<unsigned char> a; // heap structure
    int priority[256] = {}; // cache of priorities
};

void PriorityVenues::heapifyUp() {
    int smallest = size()-1;
    while (Parent(smallest) >= 0 && priority[a[smallest]] > priority[a[Parent(smallest)]]) {
        swap(a[smallest], a[Parent(smallest)]);
        smallest = Parent(smallest);
    }
}

void PriorityVenues::heapifyDown(int i) {
    int largest = i;
    int left    = Left(i);
    int right   = Right(i);

    if( left < size() && priority[a[largest]] < priority[a[ left ]])
        largest = left;
    if( right < size()  && priority[a[largest]] < priority[a[right]])
        largest = right;
    if( largest != i ){
        swap( a[i], a[largest] );
        heapifyDown( largest );
    }
}

void PriorityVenues::push(unsigned char c, int p) {
    a.push_back(c);
    priority[c] = p;
    heapifyUp();
}

auto PriorityVenues::find(unsigned char c) const {
    return std::find(begin(a),end(a),c);
}

unsigned char PriorityVenues::pop() {
    unsigned char old = a[0];
    swap(a[0], a.back());
    a.pop_back();
    heapifyDown(0);
    return old;
}

void PriorityVenues::offer(unsigned char c, int p) {
    auto it = find(c);
    if (it != end(a) && priority[*it] != p) {
        // if the character is found, then the priority is being changed
        // remove all elements until c becomes the root
        // then remove c, repush the elements, and push the newly changed c
        string cache;
        while (top() != c) {
            cache += pop();
        }
        pop(); // pop root which is now c
        // add the other elements
        for (char x : cache) {
            push(x, priority[x]);
        }
    }
    // push new element (0 means delete)
    if (p != 0)
        push(c, p);
}

int PriorityVenues::size() const {
    return a.size();
}

int main()
{
    PriorityVenues pv(4);
    pv.offer('a', 10);
    pv.offer('T', 11);
    pv.offer('z', 20);
    pv.offer('a', 15);
    while(!pv.empty()){
        cout<<pv.pop();
    }
    /* output
        zaT
    */
}
