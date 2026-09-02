#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*

6. Update current position inside the inner loop.
			skip_module = dp[w]
			take_module = dp[w - current_time] + current_value
			dp[w] = max(skip_module, take_module)
7. Once finished, the absolute maximum of learning benefit should be found at the last index 
(of the array). Return it. return dp[max_t]
*/

int main() {
    /*
    1. Receive number. Save it as n, which represents the total number of study modules.
        n = input
    */
    int n;
    if (!(cin >> n)) return 0;

    /*
    2. Receive number. Save it as max_t, which represents the maximum time budget.
        max_t = input
    */
    int max_t;
    if (!(cin >> max_t)) return 0;

    /*
    3. Initialize a 1D DP array of size max_t + 1 with all its elements set to 0. Stored 
    value: learning benefit (the optimal). Index: time capacity. dp = empty_array(size = 
    max_t + 1, fill = 0)
    */
    vector<int> vector_dp(max_t + 1, 0);
    /*
    4. Outer loop: to receive and evaluate each module one by one on-the-fly, extracting its
    specific required time and yielded value without storing them in a separate data structure.
	for i from 0 to n - 1:
		current_time, current_value = read_two_integers()
    */
   for (int i = 0; i < n; i++) {
    int module_time, module_value;
    cin >> module_time >> module_value; 
    /*
    5. Inner loop: DP backwards (anidado adentro para usar module_time y module_value)
    */
    for (int j = max_t; j >= module_time; j--) {
        /*
        6. Update current position inside the inner loop.
        */
        vector_dp[j] = max(vector_dp[j], vector_dp[j - module_time] + module_value); //max value of either give or take
    }
    } 
    /*
    7. Once finished, the absolute maximum of learning benefit should be found at the last index (of the array). Return it.
        return dp[max_t]
    */
    cout << vector_dp[max_t] << endl; //benefit during max time -> chooses the best outcome
    return 0;
};