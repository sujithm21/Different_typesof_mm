// #include<iostream>
// #include<vector>

// using namespace std;

// int value_of_x(int n, int k, vector<int> &arr){
//     int max1 = 0;

//     for(int i = 0; i < n; i++){
//         int sum = 0; // Reset sum for each element in arr
//         if(k != 0){
//             for(int j = 0; j < k; j++){
//                 sum += j ^ arr[i];
//             }
//         } else {
//             sum = arr[i];
//         }
//         max1 = max(max1, sum);
//     }

//     return max1;
// }

// int main(){
//     vector<int> arr1 = {1, 6, 3};

//     int a = value_of_x(3, 7, arr1);

//     cout << a;
// }
#include <bits/stdc++.h>
using namespace std;

unordered_map<int, int> L;

int main() {
    int n, k, m;
    cin >> n >> k;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> m;
        v[i] = m;
        int j = 0;
        while (m) {
            L[j] += (m & 1);
            m >>= 1;
            j++;
        }
    }

    int j = 0, K = k, ans = 0, ans2 = 0;
    while (K) {
        j++;
        K >>= 1;
    }

    ans = 1;
    for (int i = j; i > 0; i--) {
        if (L[i - 1] < n - L[i - 1]) {
            ans <<= 1;
        }
    }
    ans >>= 1;

    for (auto i : v)
        ans2 += ans ^ i;

    cout << ans2 << endl;

    return 0;
}
