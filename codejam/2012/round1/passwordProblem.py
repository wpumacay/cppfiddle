




def parseInput():

    f = open( "password_problem_large.txt", "r" )
    str_num_test_cases = f.readline()
    i_num_test_cases = int( str_num_test_cases )
    i_cases = []
    for i in range( i_num_test_cases ) :
        str_testcase_keys = ( f.readline() ).split( " " )
        str_testcase_prob = ( f.readline() ).split( " " )
        i_keys = [ int( str_key ) for str_key in str_testcase_keys ]
        i_prob = [ float( str_prob ) for str_prob in str_testcase_prob ]
        i_testcase = {}
        i_testcase['k'] = i_keys[0]
        i_testcase['n'] = i_keys[1]
        i_testcase['prob'] = i_prob
        i_cases.append( i_testcase )

    return i_cases


_input = parseInput()

def solveProblem( testcase ) :
    
    k = testcase['k']
    n = testcase['n']
    probs = testcase['prob']

    best = n + 2
    x = 1.
    for i in range( k ) :
        x *= probs[i]
        best = min( best, n - i + k - i - 1 + ( n + 1 ) * ( 1 - x ) )
    
    return best


sols = []
for testcase in _input :
    sols.append( solveProblem( testcase ) )

f = open( "solution_large.txt", "w" )
for q in range( len( sols ) ) :
    f.write( "Case #" + str( q + 1 ) + ": " + str( sols[q] ) + "\n" )
