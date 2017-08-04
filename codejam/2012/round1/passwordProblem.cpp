
#include <string>
#include <fstream>
#include <iostream>

using namespace std;










int main()
{

    ifstream _f( "password_problem_small.txt" );

    if ( !_f.is_open() )
    {
        return -1;
    }

    string _line;

    

    

    _f.close();


    return 0;
}
