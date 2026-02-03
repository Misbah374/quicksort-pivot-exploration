#ifndef PIVOT_HPP
#define PIVOT_HPP

#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <unordered_map>

namespace pivot {

/* ---------- Utility ---------- */

// check if sample is monotonic (sorted or reverse sorted)
inline bool isMonotonic(const std::vector<int>& s) {
    bool inc = true, dec = true;
    for (size_t i = 1; i < s.size(); ++i) {
        if (s[i] < s[i - 1]) inc = false;
        if (s[i] > s[i - 1]) dec = false;
    }
    return inc || dec;
}

// find median of small vector (k <= 9)
inline int medianOfSample(std::vector<int>& s) {
    std::sort(s.begin(), s.end());
    return s[s.size() / 2];
}

/* ---------- Core Function ---------- */

inline int choosePivotIndex(int* A, int l, int r) {
    int n = r - l + 1;
    int mid = l + (r - l) / 2;

    // Step 1: decide sample size
    int k = (n < 50) ? 3 : std::min(9, (int)std::log2(n));

    // Step 2: collect evenly spaced samples
    std::vector<int> sample;
    std::vector<int> indices;

    if (k == 3) {
        indices = {l, mid, r};
    } else {
        for (int i = 0; i < k; i++) {
            indices.push_back(l + i * (r - l) / (k - 1));
        }
    }

    for (int idx : indices)
        sample.push_back(A[idx]);         // Collect actual values from array.

    std::cout << "Sample values: ";
    for (int x : sample) std::cout << x << " ";
    std::cout << "\n";
    
    // Step 3: monotonic check (sorted / reverse)
    if (isMonotonic(sample)) {
        return mid;
    }

    // Step 4: duplicate-heavy check
    std::unordered_map<int, int> freq;
    for (int x : sample)
        freq[x]++;

    for (auto& it : freq) {
        if (it.second >= k / 2) {
            std::cout << "Duplicate-heavy sample -> pivot value "
                      << it.first << "\n";

            for (int idx : indices)
                if (A[idx] == it.first)
                    return idx;
        }
    }


    // Step 5: median-of-sample fallback
    int pivotValue = medianOfSample(sample);
    std::cout << "Median-of-sample pivot value: "
              << pivotValue << "\n";

    for (int idx : indices)
        if (A[idx] == pivotValue)
            return idx;

    return mid; // safety fallback
}

} // namespace pivot

#endif


/*
--------------------------------------------------------------------------------
Algorithm: ChoosePivotIndex(A, l, r)

Step 1: Start
    - Input: array A[l..r]
    - Output: index of pivot element

Step 2: Compute size and middle
    - n = r - l + 1
    - mid = l + (r - l) / 2

Step 3: Decide sample size k
    - if n < 50, then k = 3
    - else k = min(9, floor(log2(n)))

Step 4: Select k evenly spaced indices
    - if k = 3, indices = {l, mid, r}
    - else for i = 0 to k-1:
        idx = l + i * (r - l) / (k - 1)
        append idx to indices

Step 5: Collect sample values
    - for each idx in indices:
        sample.append(A[idx])

Step 6: Check if sample is monotonic
    - if sample is strictly increasing or decreasing:
        return mid as pivot

Step 7: Check for duplicate dominance
    - count frequency of each value in sample
    - if any value occurs >= k/2 times:
        return index of that value in A

Step 8: Median-of-sample fallback
    - sort the sample
    - pivotValue = sample[k/2]
    - return index of pivotValue in A

Step 9: Safety fallback
    - if no pivot chosen (should not happen):
        return mid

Step 10: End
--------------------------------------------------------------------------------
Notes:
1. Sampling is logarithmic in subarray size → O(log n) cost
2. Monotonic check prevents worst-case for sorted/reverse arrays
3. Duplicate detection improves pivot choice for repeated values
4. Median-of-sample ensures general case robustness
5. Always returns a valid index inside [l, r]
*/


/*
ChoosePivotIndex(A, l, r):

    n ← r − l + 1
    mid ← l + (r − l) / 2

    // Step 1: decide sample size (logarithmic growth)
    if n < 50 then
        k ← 3
    else
        k ← min(9, ⌊log2(n)⌋)

    // Step 2: pick k evenly spaced sample indices
    if k = 3 then
        indices ← { l, mid, r }
    else
        indices ← empty list
        for i from 0 to k − 1 do
            idx ← l + i × (r − l) / (k − 1)
            append idx to indices

    // Step 3: collect sample values
    sample ← empty list
    for each idx in indices do
        append A[idx] to sample

    // Step 4: check if sample is monotonic
    if IsMonotonic(sample) then
        return mid

    // Step 5: detect duplicate dominance
    freq ← empty map
    for each value x in sample do
        freq[x] ← freq[x] + 1

    for each (value, count) in freq do
        if count ≥ k / 2 then
            for each idx in indices do
                if A[idx] = value then
                    return idx

    // Step 6: median-of-sample fallback
    sort(sample)
    pivotValue ← sample[⌊k / 2⌋]

    for each idx in indices do
        if A[idx] = pivotValue then
            return idx

    // Step 7: safety fallback
    return mid



IsMonotonic(sample):

    increasing ← true
    decreasing ← true

    for i from 1 to length(sample) − 1 do
        if sample[i] < sample[i−1] then
            increasing ← false
        if sample[i] > sample[i−1] then
            decreasing ← false

    return increasing OR decreasing

*/

/*
    Choose a pivot by sampling the data logarithmically, 
    rejecting extremes, detecting duplicate dominance, and 
    falling back to the median of a representative subset.
*/