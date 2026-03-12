# quicksort-pivot-exploration

A C++ implementation of **QuickSort with an adaptive pivot selection strategy**.

Instead of choosing a fixed pivot (first, last, or random element), this project introduces a **sampling-based pivot selection algorithm** that analyzes a subset of the array before deciding the pivot.

The goal is to **reduce the chances of worst-case partitioning** and make QuickSort more robust across different input patterns.

---

# Motivation

QuickSort performance strongly depends on **pivot selection**.

Poor pivot choices can lead to:

- Highly unbalanced partitions
- Increased recursion depth
- Worst-case time complexity **O(n²)**

Common pivot strategies include:

- First element
- Last element
- Random element
- Median-of-three

This project explores a more **adaptive pivot strategy** that analyzes a small sample of the data before choosing the pivot.

---

# Key Idea

Instead of blindly selecting a pivot, the algorithm:

1. Samples several elements from the array.
2. Detects patterns such as:
   - sorted sequences
   - reverse sorted sequences
   - duplicate-heavy samples
3. Chooses a pivot based on these observations.

This makes the pivot selection **data-aware** rather than fixed.

---

# Pivot Selection Strategy

The pivot is selected using the function:

```
choosePivotIndex(A, l, r)
```

### Step 1 — Determine Sample Size

The number of sampled elements grows logarithmically.

```
if n < 50
    k = 3
else
    k = min(9, floor(log2(n)))
```

This keeps the sampling cost very small.

---

### Step 2 — Select Evenly Spaced Samples

Samples are taken across the entire range of the array.

Example:

```
[l, mid, r]
```

or

```
l + i*(r-l)/(k-1)
```

This ensures the sample represents the **whole subarray**.

---

### Step 3 — Detect Monotonic Patterns

If the sample appears **sorted or reverse sorted**, the algorithm selects:

```
pivot = middle element
```

This prevents QuickSort’s classic worst case for already sorted arrays.

---

### Step 4 — Detect Duplicate Dominance

If a value appears frequently in the sample:

```
frequency ≥ k/2
```

That value is selected as the pivot.

This improves performance on **duplicate-heavy datasets**.

---

### Step 5 — Median-of-Sample Fallback

If no pattern is detected, the algorithm falls back to:

```
pivot = median(sample)
```

This approximates the **true median** and produces balanced partitions in general cases.

---

# Algorithm Complexity

| Operation | Complexity |
|----------|-----------|
Pivot Sampling | O(log n) |
Partition | O(n) |
Average QuickSort | O(n log n) |
Worst Case | O(n²) |

The adaptive pivot strategy reduces the likelihood of encountering the worst-case scenario.

---

# Project Structure

```
.
├── quickSort.cpp
├── pivot.hpp
└── README.md
```

### quickSort.cpp
Contains the QuickSort implementation and the partition logic.

### pivot.hpp
Contains the adaptive pivot selection algorithm.

---

# Compilation

Compile using any C++17 compatible compiler.

Example using g++:

```
g++ quickSort.cpp -o quicksort
```

---

# Running the Program

Run the compiled executable:

```
./quicksort
```

Example input:

```
Enter number of elements: 5
Enter elements:
5 3 1 4 2
```

Example output:

```
Sorted array:
1 2 3 4 5
```

---

# Limitations

This implementation uses **2-way partitioning**.

If the array contains many duplicate elements, performance may degrade.

A possible improvement would be implementing **3-way partitioning (Dutch National Flag algorithm)**.

---

# Future Improvements

Possible extensions for this project:

- Implement **3-way partition QuickSort**
- Add **benchmark comparisons** with:
  - Random pivot QuickSort
  - Median-of-three QuickSort
- Add **large dataset testing**
- Visualize pivot selection and recursion depth

---

# Learning Objectives

This project explores:

- QuickSort algorithm design
- Pivot selection strategies
- Sampling techniques in algorithms
- Defensive algorithm design
- Performance considerations in divide-and-conquer algorithms
