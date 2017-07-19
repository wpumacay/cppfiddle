



class BuyingCheap:


    def thirdBestPrice( self, prices ) :

        prices.sort()
        print prices
        _reduced_prices = []
        for q in range( len( prices ) ) :
            if prices[q] in _reduced_prices :
                continue
            _reduced_prices.append( prices[q] )

        if len( _reduced_prices ) < 3 :
            return -1
        return _reduced_prices[2]


_prob = BuyingCheap()
print _prob.thirdBestPrice( [10, 40, 50, 20, 70, 80, 30, 90, 60] )
print _prob.thirdBestPrice( [10, 10, 10, 10, 20, 20, 30, 30, 40, 40] )
print _prob.thirdBestPrice( [10] )
print _prob.thirdBestPrice( [80, 90, 80, 90, 80] )


