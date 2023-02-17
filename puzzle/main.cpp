#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int count = 0;

int puzzle (long long int N) {

    count++;

    if (N==1)
        return (1);
    if ((N%2) == 0)
        return puzzle(N/2);
    else
        return puzzle(3*N+1);
}

int main() {
    long long int N=0;
    int answer;

    do {
        count = -1;
        cout << "Enter an N: ", cin >> N, cout << N << "\t";
        auto start = high_resolution_clock::now();
        answer=puzzle(N);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << count << " , " << answer << endl;
        cout << "Running time: " << duration.count() << " microseconds" << endl;
    } while(cin);

    return(0);
}
/***************************************************************************************
 * Question answers:
 *
 * 1. What does the variable count do?
 *
 * The variable count keeps track of how many times the puzzle function recursively
 *  calls itself. This variable starts at -1 because the first pass through puzzle
 *  is not a recursive call.
 *
 *  2. What are the run times for all of the test cases in longest.txt?
 *
 * 9: 1 microsecond
 * 97: 4 microseconds
 * 871: 5 microseconds
 * 6171: 32 microseconds
 * 77031: 28 microseconds
 * 837799: 60 microseconds
 * 8400511: 52 microseconds
 * 63728127: 83 microseconds
 * 670617279: 26 microseconds
 * 9780657630: 68 microseconds
 * 75128138247: 52 microseconds
 * 989345275647: 62 microseconds
 *
 *  3. Is it possible to say anything about the order (Big-Oh) of the puzzle function?
 *
 *  When points are plotted, the order of the puzzle function resembles a O(logn), or
 *  O(Clogn), where C is a constant where the curve can be scaled up to actually fit
 *  the points, or at least most of them. The curious thing is that the numbers are
 *  volatile, and they don't necessarily go through the loop more the bigger the
 *  number. It is dependent on how many even numbers there are in a row, once it
 *  starts being divided by two. They always make their way back to one, but it is
 *  inconsistent how long it takes to get there. O(logn) or O(Clogn) is a rough
 *  guess, but it is the closest I can come to making sense of the volatile algorithm.
 **************************************************************************************/