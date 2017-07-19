

class FloatingMedian:


    def sumOfMedians( self, seed, mul, add, N, K ) :
        _k = 0
        _tk = seed
        # generate the temperatures
        _temps = [ _tk ]
        for q in range( 1, N ) :
            _tk = ( _tk * mul + add ) % 65536
            _temps.append( _tk )
        # print _temps
        # take the median of each slice of size k
        _sum = 0
        _slice = None
        for i in range( 0, N - K + 1 ) :
            if i == 0 : ## just in the first case sort
                _sub = _temps[i:i + K]
                _sub.sort()
                _slice = _sub
                # find the median in slice [i - i+k-1]
            else :
                _left = _temps[i - 1]
                _right = _temps[i + K - 1]
                ## sort by removing the left most and adding the rightmost
                #_slice.remove( _left )
                #_slice.append( _right )
                q = K - 1
                while ( q > 0 ) :
                    if ( _slice[q] < _slice[q - 1] ) :
                        _tmp = _slice[q]
                        _slice[q] = _slice[q - 1]
                        _slice[q - 1] = _tmp
                    q -= 1

            _median = _slice[ ( len( _slice ) - 1 ) / 2 ]
            _sum += _median
            # print _median
        return _sum


_prob = FloatingMedian()

print _prob.sumOfMedians( 3, 1, 1, 10, 3 )
print _prob.sumOfMedians( 10, 0, 13, 5, 2 )
print _prob.sumOfMedians( 4123, 2341, 1231, 7, 3 )
print _prob.sumOfMedians( 47, 5621, 1, 125000, 1700 )
print _prob.sumOfMedians( 32321, 46543, 32552, 17, 17 )








        
