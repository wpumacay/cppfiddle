
from random import shuffle



def YaroslavskiyPartition( arr, lo, hi ) :

    p1 = arr[lo]
    p2 = arr[hi]

    if ( p1 > p2 ) :
        _tmp = arr[lo]
        arr[lo] = arr[hi]
        arr[hi] = _tmp
        p1 = arr[lo]
        p2 = arr[hi]

    l = lo + 1
    k = lo + 1
    g = hi - 1

    while k <= g :

        if ( arr[k] < p1 ) :
            _tmp = arr[l]
            arr[l] = arr[k]
            arr[k] = _tmp
            l += 1
            k += 1
        elif ( arr[k] > p2 ) :
            _tmp = arr[k]
            arr[k] = arr[g]
            arr[g] = _tmp
            g -= 1

        else :
            k += 1
        """
        while ( arr[l] < p1 ) :
            l += 1
            k += 1

        while ( arr[k] >= p1 and arr[k] <= p2 and k <= g ) :
            k +=1

        while ( arr[g] > p2 ) :
            g -= 1

        _range = range( k, g + 1 )

        s = k
        while s >= k and s <= g :
            if ( arr[s] < p1 ) :
                _tmp = arr[l]
                arr[l] = arr[s]
                arr[s] = _tmp
                l += 1
                k += 1

            elif ( arr[s] > p2 ) :
            
                _tmp = arr[g]
                arr[g] = arr[s]
                arr[s] = _tmp
                g -= 1
            
            else :
                k += 1
            
            s += 1
        """

    ## exchange lo and l
    _tmp = arr[lo]
    arr[lo] = arr[l - 1]
    arr[l - 1] = _tmp

    mid_1 = l - 1

    ## exchange hi and k
    _tmp = arr[hi]
    arr[hi] = arr[g + 1]
    arr[g + 1] = _tmp

    mid_2 = g + 1

    return mid_1, mid_2
	

def quicksort( arr, lo, hi ) :

    if ( hi <= lo ) :
        return

    mid_1, mid_2 = YaroslavskiyPartition( arr, lo, hi )
    quicksort( arr, lo, mid_1 - 1 )
    if ( arr[mid_1] < arr[mid_2] ) :
        quicksort( arr, mid_1 + 1, mid_2 - 1 )
    quicksort( arr, mid_2 + 1, hi )

#foo = range( 1, 11 )
#shuffle( foo )
#foo = [7, 6, 9, 3, 8, 2, 1, 5, 10, 4]
foo = [6, 8, 9, 4, 1, 5, 10, 2, 7, 3]
print foo
quicksort( foo, 0, len( foo ) - 1 )
print foo
## print YaroslavskiyPartition( foo, 0, len( foo ) - 1 )
