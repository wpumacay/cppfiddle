#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>

template <typename T>
struct cmpLess 
{ 
    inline bool operator() ( const T &t1, const T &t2 ) const 
    { 
        return (t1 < t2); 
    }
};

template <typename T>
struct cmpGreater 
{ 
    inline bool operator() ( const T &t1, const T &t2 ) const 
    { 
        return (t2 < t1); 
    } 
};


template <typename RandomAccessIterator>
inline void InsertSort( RandomAccessIterator start, RandomAccessIterator end ) 
{
    cmpLess < typename RandomAccessIterator::value_type > lessThan;
    InsertSort( start, end, lessThan );
}

template <typename RandomAccessIterator>
inline void SelectSort( RandomAccessIterator start, RandomAccessIterator end ) 
{
    cmpLess < typename RandomAccessIterator::value_type > lessThan;
    SelectSort( start, end, lessThan );
}

template <typename RandomAccessIterator>
inline void StableSelectSort( RandomAccessIterator start, RandomAccessIterator end ) 
{
    cmpLess < typename RandomAccessIterator::value_type > lessThan;
    StableSelectSort( start, end, lessThan );
}

template <typename RandomAccessIterator>
inline void HeapSort( RandomAccessIterator start, RandomAccessIterator end ) 
{
    cmpLess < typename RandomAccessIterator::value_type > lessThan;
    HeapSort( start, end, lessThan );
}

template <typename RandomAccessIterator>
inline void MergeSort( RandomAccessIterator start, RandomAccessIterator end ) 
{
    cmpLess < typename RandomAccessIterator::value_type > lessThan;
    MergeSort( start, end, lessThan );
}

template <typename RandomAccessIterator>
inline void IterativeMergeSort( RandomAccessIterator start, RandomAccessIterator end ) 
{
    cmpLess < typename RandomAccessIterator::value_type > lessThan;
    IterativeMergeSort( start, end, lessThan );
}

template <typename RandomAccessIterator>
inline void LomutoQuickSort( RandomAccessIterator start, RandomAccessIterator end ) 
{
    cmpLess < typename RandomAccessIterator::value_type > lessThan;
    LomutoQuickSort( start, end, lessThan );
}

template <typename RandomAccessIterator>
inline void HoareQuickSort( RandomAccessIterator start, RandomAccessIterator end ) 
{
    cmpLess < typename RandomAccessIterator::value_type > lessThan;
    HoareQuickSort( start, end, lessThan );
}

template <typename RandomAccessIterator>
inline void YaroslavskiyQuickSort( RandomAccessIterator start, RandomAccessIterator end ) 
{
    cmpLess < typename RandomAccessIterator::value_type > lessThan;
    YaroslavskiyQuickSort( start, end, lessThan );
}


// SORTING IMPLEMENTATIONS *************************************************************************************************


template <typename RandomAccessIterator, typename LessThan>
inline void InsertSort( RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan ) 
{
    RandomAccessIterator _it,_it_sw;
    for ( _it = start; _it != end; _it++ )
    {
        for ( _it_sw = _it; _it_sw > start; _it_sw-- )
        {
            if ( lessThan( *( _it_sw ), *( _it_sw - 1 ) ) )
            {
                //  Swap
                typename RandomAccessIterator::value_type _tmp = *( _it_sw );
                *( _it_sw ) = *( _it_sw - 1 );
                *( _it_sw - 1 ) = _tmp;
            }
            else
            {
                break;
            }
        }
    }
}

template <typename RandomAccessIterator, typename LessThan>
inline void SelectSort( RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan ) 
{
    RandomAccessIterator _it, _it_min, _min;
    for ( _it = start; _it != end; _it++ )
    {
        _min = _it;
        // find smallest element in remaining region
        int q = 0;
        for ( _it_min = _it + 1; _it_min < end; _it_min++ )
        {
            if ( lessThan( *( _it_min ), *( _min ) ) )
            {
                _min = _it_min;
            }
        }
        // exchange to keep the invariant
        typename RandomAccessIterator::value_type _tmp = *( _min );
        *( _min ) = *( _it );
        *( _it ) = _tmp;
    }

}

template <typename RandomAccessIterator, typename LessThan>
inline void StableSelectSort( RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan ) 
{
    RandomAccessIterator _it, _it_min, _min;
    for ( _it = start; _it != end; _it++ )
    {
        _min = _it;
        // find smallest element in remaining region
        int q = 0;
        for ( _it_min = _it + 1; _it_min < end; _it_min++ )
        {
            if ( lessThan( *( _it_min ), *( _min ) ) )
            {
                _min = _it_min;
            }
        }
        // Rellocate by shifting all elements to the right
        typename RandomAccessIterator::value_type _tmp = *( _min );
        RandomAccessIterator _it_shift;
        for ( _it_shift = _min; _it_shift > _it; _it_shift-- )
        {
            *( _it_shift ) = *( _it_shift - 1 );
        }
        *( _it ) = _tmp;
    }
}

template <typename RandomAccessIterator, typename LessThan>
void HeapSort_min_heapify( RandomAccessIterator start, RandomAccessIterator, end, RandomAccessIterator pos )
{
    
}

template <typename RandomAccessIterator, typename LessThan>
void HeapSort_build_min_heap( RandomAccessIterator start, RandomAccessIterator end )
{

}

template <typename RandomAccessIterator, typename LessThan>
inline void HeapSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Heap Sort, use std::make_heap y std::pop_heap.
}

template <typename RandomAccessIterator, typename LessThan>
inline void MergeSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Merge Sort.
}

template <typename RandomAccessIterator, typename LessThan>
inline void IterativeMergeSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Merge Sort.
}

template <typename RandomAccessIterator, typename LessThan>
inline void LomutoQuickSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Quick Sort de Lomuto.
}

template <typename RandomAccessIterator, typename LessThan>
inline void HoareQuickSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Quick Sort de Hoare.
}

template <typename RandomAccessIterator, typename LessThan>
inline void YaroslavskiyQuickSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
  // Adicione el código de Quick Sort con doble pivot y corte a insertion sort con pocos elementos.
}

void print( std::vector<int> vect )
{
    std::cout << "[ ";
    for ( int q = 0; q < vect.size(); q++ )
    {
        std::cout << vect[q] << " ";
    }
    std::cout << "]" << std::endl;
}

// *************************************************************************************************************************

int main( int argc, char** argv ) 
{
    typedef void ( *SORT_ALGORITHM )( std::vector<int>::iterator, std::vector<int>::iterator );
    for ( auto & i : { 100/*,1000,10000,100000,1000000,10000000,100000000*/ } )
    {
        std::vector<int> w(i), v;
        std::iota( w.begin(), w.end(), 1 );
        for( auto a = w.begin(), _a = w.begin() + i/100; a < w.end(); _a += i/100 )
        {
            std::shuffle (a, _a, std::default_random_engine(std::time(0)));
            a = _a;
        }
        // retire el comentario para estudiar datos completamente desordenados:
        std::shuffle (w.begin(), w.end(), std::default_random_engine(std::time(0)));
        std::vector<SORT_ALGORITHM> sort_algorithms = {InsertSort, SelectSort, StableSelectSort/*, HeapSort, MergeSort, IterativeMergeSort, LomutoQuickSort, HoareQuickSort*/ };
        if ( i > 100000 && i < 100000000)
        {
            sort_algorithms = {HeapSort, MergeSort, IterativeMergeSort, LomutoQuickSort, HoareQuickSort };
            std::cout << "-, -, -, ";
        }
        if (i == 100000000)
        {
            sort_algorithms = {IterativeMergeSort, LomutoQuickSort, HoareQuickSort };
            std::cout << "-, -, -, -, -, ";
        }
        for ( auto & sort_algorithm : sort_algorithms){
            v=w;
            std::clock_t inicio = std::clock();
            print( v );
            sort_algorithm(v.begin(),v.end());
            print( v );
            std::cout << 1000.0 * (double)(std::clock()-inicio)/(double)CLOCKS_PER_SEC << ", " << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}
