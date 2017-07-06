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
inline void HeapSort( RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan ) 
{
    // Adicione el código de Heap Sort, use std::make_heap y std::pop_heap.
    std::make_heap( start, end );
    int N = end - start;
    
    int q = 0;
    while ( q < N )
    {
        std::pop_heap( start, end - q );
        q++;
    }
    
}

template<typename RandomAccessIterator, typename LessThan>
void MergeSort_merge( RandomAccessIterator start, RandomAccessIterator end, 
                      std::vector<typename RandomAccessIterator::value_type> &pAux, 
                      int pLo, int pHi, int pMid,
                      LessThan &lessThan )
{
    int q;
    for ( q = pLo; q <= pHi; q++ )
    {
        pAux[q] = *( start + q );
    }

    int p1 = pLo;
    int p2 = pMid + 1;

    for ( q = pLo; q <= pHi; q++ )
    {
        if ( p1 > pMid )
        {
            *( start + q ) = pAux[p2];
            p2++;
        }
        else if ( p2 > pHi )
        {
            *( start + q ) = pAux[p1];
            p1++;
        }
        else if ( lessThan( pAux[p2], pAux[p1] ) )
        {
            *( start + q ) = pAux[p2];
            p2++;
        }
        else
        {
            *( start + q ) = pAux[p1];
            p1++;
        }
    }

}

template<typename RandomAccessIterator, typename LessThan>
void MergeSort_sort( RandomAccessIterator start, RandomAccessIterator end, 
                     std::vector<typename RandomAccessIterator::value_type> &pAux, 
                     int pLo, int pHi,
                     LessThan &lessThan )
{
    if ( pLo >= pHi )
    {
        return;
    }

    int _mid = ( pLo + pHi ) / 2;

    MergeSort_sort<RandomAccessIterator,LessThan>( start, end, pAux, pLo, _mid, lessThan );
    MergeSort_sort<RandomAccessIterator,LessThan>( start, end, pAux, _mid + 1, pHi, lessThan );
    MergeSort_merge<RandomAccessIterator,LessThan>( start, end, pAux, pLo, pHi, _mid, lessThan );
}

template <typename RandomAccessIterator, typename LessThan>
inline void MergeSort( RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan ) 
{
    std::vector<typename RandomAccessIterator::value_type> _aux( start, end );

    int lo = 0;
    int hi = end - start - 1;
    int mid = ( lo + hi ) / 2;

    MergeSort_sort<RandomAccessIterator, LessThan>( start, end, _aux, lo, mid, lessThan );
    MergeSort_sort<RandomAccessIterator, LessThan>( start, end, _aux, mid + 1, hi, lessThan );
    MergeSort_merge<RandomAccessIterator, LessThan>( start, end, _aux, lo, hi, mid, lessThan );
}

template <typename RandomAccessIterator, typename LessThan>
inline void IterativeMergeSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) {
    int _curr_size;
    int _left_start;
    int N = end - start;

    std::vector<typename RandomAccessIterator::value_type> _aux( start, end );

    for ( _curr_size = 1; _curr_size <= N - 1; _curr_size = 2 * _curr_size )
    {
        for ( _left_start = 0; _left_start < N - 1; _left_start += 2 * _curr_size )
        {
            int _mid = _left_start + _curr_size - 1;

            int _right_end = std::min( _left_start + 2 * _curr_size - 1, N - 1 );
            MergeSort_merge<RandomAccessIterator, LessThan>( start, end, _aux, _left_start, _right_end, _mid, lessThan );
        }
    }
}

template<typename RandomAccessIterator, typename LessThan>
int LomutoPartition( RandomAccessIterator start, RandomAccessIterator end, int lo, int hi, LessThan &lessThan )
{
    int i = lo - 1;
    for ( int j = lo; j <= hi - 1; j++ )
    {
        if ( lessThan( *( start + j ), *( start + hi ) ) ||
             ( *( start + j ) == *( start + hi ) ) )
        {
            i++;
            typename RandomAccessIterator::value_type _tmp = *( start + i );
            *( start + i ) = *( start + j );
            *( start + j ) = _tmp;
        }
    }

    typename RandomAccessIterator::value_type _tmp = *( start + i + 1 );
    *( start + i + 1 ) = *( start + hi );
    *( start + hi ) = _tmp;

    return i + 1;
}

template <typename RandomAccessIterator, typename LessThan>
void LomutoSort( RandomAccessIterator start, RandomAccessIterator end, int lo, int hi, LessThan &lessThan )
{
    if ( hi <= lo )
    {
        return;
    }

    int _mid = LomutoPartition<RandomAccessIterator, LessThan>( start, end, lo, hi, lessThan );
    LomutoSort<RandomAccessIterator, LessThan>( start, end, lo, _mid - 1, lessThan );
    LomutoSort<RandomAccessIterator, LessThan>( start, end, _mid + 1, hi, lessThan );
}

template <typename RandomAccessIterator, typename LessThan>
inline void LomutoQuickSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) 
{
    std::random_shuffle( start, end );
    int N = end - start;
    LomutoSort<RandomAccessIterator, LessThan>( start, end, 0, N - 1, lessThan );
}

template<typename RandomAccessIterator, typename LessThan>
int HoarePartition( RandomAccessIterator start, RandomAccessIterator end, int lo, int hi, LessThan &lessThan )
{
    int i = lo + 1, j = hi;
    while ( true )
    {
        while ( lessThan( *( start + i ), *( start + lo )  ) )
        {
            i++;
            if ( i == hi )
            {
                break;
            }
        }

        while ( lessThan( *( start + lo ) , *( start + j ) ) )
        {
            j--;
            if ( j == lo )
            {
                break;
            }
        }

        if ( i >= j )
        {
            break;
        }

        // exchange i and j
        typename RandomAccessIterator::value_type _tmp = *( start + i );
        *( start + i ) = *( start + j );
        *( start + j ) = _tmp;
    }

    // exchange lo and j
    typename RandomAccessIterator::value_type _tmp = *( start + lo );
    *( start + lo ) = *( start + j );
    *( start + j ) = _tmp;

    return j;
}

template <typename RandomAccessIterator, typename LessThan>
void HoareSort( RandomAccessIterator start, RandomAccessIterator end, int lo, int hi, LessThan &lessThan )
{
    if ( hi <= lo )
    {
        return;
    }

    int _mid = HoarePartition<RandomAccessIterator, LessThan>( start, end, lo, hi, lessThan );
    HoareSort<RandomAccessIterator, LessThan>( start, end, lo, _mid - 1, lessThan );
    HoareSort<RandomAccessIterator, LessThan>( start, end, _mid + 1, hi, lessThan );
}

template <typename RandomAccessIterator, typename LessThan>
inline void HoareQuickSort(RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan) 
{
    std::shuffle( start, end, std::default_random_engine(std::time(0)) );
    int N = end - start;
    HoareSort<RandomAccessIterator, LessThan>( start, end, 0, N - 1, lessThan );
}


template<typename RandomAccessIterator, typename LessThan>
int YaroslavskiyPartition( RandomAccessIterator start, RandomAccessIterator end, int lo, int hi, LessThan &lessThan )
{
    int i = lo + 1, j = hi;
    while ( true )
    {
        while ( lessThan( *( start + i ), *( start + lo )  ) )
        {
            i++;
            if ( i == hi )
            {
                break;
            }
        }

        while ( lessThan( *( start + lo ) , *( start + j ) ) )
        {
            j--;
            if ( j == lo )
            {
                break;
            }
        }

        if ( i >= j )
        {
            break;
        }

        // exchange i and j
        typename RandomAccessIterator::value_type _tmp = *( start + i );
        *( start + i ) = *( start + j );
        *( start + j ) = _tmp;
    }

    // exchange lo and j
    typename RandomAccessIterator::value_type _tmp = *( start + lo );
    *( start + lo ) = *( start + j );
    *( start + j ) = _tmp;

    return j;
}

template <typename RandomAccessIterator, typename LessThan>
void YaroslavskiySort( RandomAccessIterator start, RandomAccessIterator end, int lo, int hi, LessThan &lessThan )
{
    if ( hi <= lo )
    {
        return;
    }

    int _mid = YaroslavskiyPartition<RandomAccessIterator, LessThan>( start, end, lo, hi, lessThan );
    YaroslavskiySort<RandomAccessIterator, LessThan>( start, end, lo, _mid - 1, lessThan );
    YaroslavskiySort<RandomAccessIterator, LessThan>( start, end, _mid + 1, hi, lessThan );
}


template <typename RandomAccessIterator, typename LessThan>
inline void YaroslavskiyQuickSort( RandomAccessIterator start, RandomAccessIterator end, LessThan &lessThan ) 
{
    std::shuffle( start, end, std::default_random_engine( std::time( 0 ) ) );
    int N = end - start;
    YaroslavskiySort<RandomAccessIterator, LessThan>( start, end, 0, N - 1, lessThan );
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
        std::vector<SORT_ALGORITHM> sort_algorithms = {InsertSort, SelectSort, StableSelectSort, HeapSort, MergeSort, IterativeMergeSort, HoareQuickSort, LomutoQuickSort, YaroslavskiyQuickSort };
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
