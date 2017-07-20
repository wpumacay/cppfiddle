



class CrazyLine :


    def maxCrazyness( self, heights ) :
        # sort the heights
        heights.sort()

        p1 = 0
        p2 = len( heights ) - 1
        mid = ( p1 + p2 + 1 ) / 2 
        
        _line = [ heights[q] for q in range( len( heights ) )]
        
        #print heights
        _line[mid] = heights[p2]
        p2 -= 1
        # fill left and right parts
        _count = 0
        _indx_left = mid - 1
        _indx_right = mid + 1
        while True :
            _count += 1
            if p1 > p2 :
                break
            if ( _count % 4 == 1 ) :
                if _indx_left >= 0 :
                    _line[_indx_left] = heights[p1]
                    #print '-> ', heights[p1]
                    p1 += 1
                _indx_left -= 1
            elif ( _count % 4 == 2 ) :
                if _indx_right < len( heights ) :
                    _line[_indx_right] = heights[p1]
                    #print '-> ', heights[p1]
                    p1 += 1
                _indx_right += 1
            elif ( _count % 4 == 3 ) :
                if _indx_left >= 0 :
                    _line[_indx_left] = heights[p2]
                    p2 -= 1
                _indx_left -= 1
            else :
                if _indx_right < len( heights ) :
                    _line[_indx_right] = heights[p2]
                    p2 -= 1
                _indx_right += 1

        _res = 0
        for q in range( 0, len( _line ) - 1 ) :
            _res += abs( _line[q] - _line[q + 1] )
        print _line
        return _res

_prob = CrazyLine()
print _prob.maxCrazyness( [5,10,25,40,25] )
print _prob.maxCrazyness( [2,3,5,7,11,13,17,19] )
print _prob.maxCrazyness( [1,1,1,1,1,1,501] )
print _prob.maxCrazyness( [1000,1000,1000,1000,1000,1000,1000,1000,1000] )
