# The Array Ladder

*A cheat sheet for [take U forward's Arrays Playlist](https://www.youtube.com/playlist?list=PLgUwDviBIf0rENwdL0nEH0uGom9no0nyB) (28 videos), kept in playlist order — simple warm-ups first, merge-sort-flavored hard mode last. For each problem: the algorithm to reach for, and the one detail that actually trips people up.*

> Prefer the styled version? Open [`cheatsheet.html`](cheatsheet.html) (or the [live GitHub Pages site](https://trunapushpa.github.io/leetcode/arrays/cheatsheet.html)) — same content, same order, just easier to scan.

---

## Rung 1 — Warm-up: single pass & two pointers

Nothing here needs a data structure fancier than a running variable or a second index. The skill being built is discipline: one clean left-to-right (or converging) pass instead of nested loops.

### 01. Second Largest Element & Remove Duplicates (sorted)
`single pass` `two pointer`

**Key idea:** Track largest and second-largest in one scan. For duplicates in a *sorted* array — they're always adjacent — an insert-pointer overwrites them in place.

**Nuance:** Second-largest ≠ "the second one you see." Update it only when a new largest appears (demote the old largest into it) or a value lands strictly between the two. Sorting first works but burns `O(n log n)` on an `O(n)` problem.

### 02. Rotate by K · Union/Intersection · Move Zeroes
`reversal trick` `merge pointers`

**Key idea:** Rotation: reverse the whole array, then reverse the first `k` and remaining `n-k` separately — three reversals, `O(n)`/`O(1)`. Union/intersection: walk both sorted arrays with two pointers, advancing the smaller side. Move zeroes: a slow pointer marks where the next nonzero gets written.

**Nuance:** Always take `k % n` first — a `k` bigger than `n` is a silent bug. Intersection advances *both* pointers on a match; union only the smaller. Move-zeroes must swap, not overwrite, or relative order breaks.

### 03. Appears Once · Missing Number · Max Consecutive Ones
`XOR trick` `running counter`

**Key idea:** XOR-ing every element cancels all pairs, leaving the singleton (`a^a=0`, `a^0=a`). Missing number: XOR `0..n` against the array, or `n(n+1)/2 - sum(arr)`.

**Nuance:** The sum formula overflows for large `n` *before* the subtraction lands; XOR never overflows — that's the real reason interviewers push for it, not elegance. For max-consecutive-ones, don't forget to check the final run after the loop exits.

### 04. Longest Subarray with Sum K
`prefix sum + hashmap` `sliding window*`

**Key idea:** Better: prefix sum in a hashmap, storing the *first* index each sum was seen. Optimal (conditional): two-pointer window that shrinks from the left when the running sum exceeds `k`.

**Nuance:** The sliding-window version only works with **non-negative** elements — negatives make the window sum non-monotonic, so shrinking can jump past the real answer. See a negative number anywhere in the array, and it's prefix-sum + hashmap or nothing.

### 05. Two Sum
`hashmap` `two pointer`

**Key idea:** One pass with a value→index hashmap gives `O(n)` lookup of the complement. If only the *values* matter (not original indices), sort and converge two pointers from both ends instead.

**Nuance:** Sorting destroys original indices — pick the approach based on what the problem actually returns: indices vs. existence/values. This distinction is the whole reason "2 types of the same problem" gets called out in the title.

### 06. Sort 0s, 1s, 2s (Dutch National Flag)
`three-way partition`

**Key idea:** Three pointers — `low`, `mid`, `high`. Swap 0s toward the front, leave 1s alone, swap 2s toward the back.

**Nuance:** Only advance `mid` when it's safe: after swapping with `high`, the new value landing at `mid` is unknown, so recheck it before moving on — don't blindly increment. This exact partition is the backbone of quicksort's 3-way partitioning; worth knowing cold.

### 07. Majority Element I (> n/2)
`Boyer–Moore voting`

**Key idea:** Keep a candidate and a count. Match → increment; mismatch → decrement; count hits 0 → switch candidates. `O(n)` time, `O(1)` space.

**Nuance:** Voting only *finds a candidate* — it guarantees correctness solely because a majority element (>n/2) is promised to exist. If existence isn't guaranteed, you must add a verification pass, or you'll confidently return garbage.

### 08. Kadane's Algorithm
`running sum reset`

**Key idea:** Carry a running sum; reset it to 0 the moment it goes negative; track the max seen along the way.

**Nuance:** If the subarray must be non-empty and the array is all-negative, the reset-to-0 rule hides the true answer — track the max single element as a fallback. To *print* the subarray (not just its sum), record start/end indices at the moment a new max is set, not at the reset.

### 09. Rearrange Array Elements by Sign
`alternate placement`

**Key idea:** Equal counts: single pass, positives to even indices, negatives to odd indices, in a new array. Unequal counts: split into two lists, interleave the equal-length prefix, append the leftovers in original order.

**Nuance:** Doing this fully in-place (no extra array) forces shifting and breaks the linear-time bound — trading `O(n)` space for a guaranteed `O(n)` time is the correct call here, not a shortcut.

---

## Rung 2 — Core patterns: prefix sums, ordering tricks, matrix ops

The building blocks compose now: sorting as a setup step, prefix sums as a lookup structure, and in-place matrix manipulation where the "extra space" is hiding in the input itself.

### 10. Best Time to Buy & Sell Stock
`min-tracking`

**Key idea:** Track the minimum price seen so far; at each day, compute `price − minSoFar` and keep the max.

**Nuance:** This only covers **one** buy and **one** sell. Order is enforced for free by scanning left-to-right — the min you compare against always occurred on an earlier day, so you can never "sell before you buy" by accident.

### 11. Next Permutation
`break-point` `suffix reverse`

**Key idea:** Scan from the right for the first index `i` where `arr[i] < arr[i+1]` (the break point). Find the rightmost element past `i` still greater than `arr[i]`, swap, then reverse everything after `i`.

**Nuance:** No break point means the array is fully descending — that's the *last* permutation, so reversing the whole thing wraps around to the smallest one. Doing the reverse before the swap (instead of after) is the most common way this goes wrong.

### 12. Leaders in an Array
`right-to-left scan`

**Key idea:** Traverse from the right holding a running max; an element is a leader if it's greater than everything to its right.

**Nuance:** Scanning left-to-right forces an `O(n²)` recheck of "everything to the right" at every index. Flipping the direction turns that recheck into one running variable — and the last element is always a leader, no comparison needed.

### 13. Longest Consecutive Sequence
`hash set` `start detection`

**Key idea:** Put every element in a hash set. For each element that is a *sequence start* (i.e. `num-1` is not in the set), count forward how long the run continues.

**Nuance:** Skipping the "is this a start" check is the classic mistake — without it, every element re-walks its own sequence from scratch, and an algorithm that looks `O(n)` silently degrades to `O(n²)`.

### 14. Set Matrix Zeroes
`in-place markers`

**Key idea:** Skip the separate visited-matrix and instead use the matrix's own first row and first column as marker arrays for which rows/columns need zeroing, applied in a final pass.

**Nuance:** Row 0 and column 0 share one marker cell, `[0][0]` — you need one extra boolean flag for "does column 0 itself need zeroing," or its marker collides with row 0's and corrupts the result.

### 15. Rotate Matrix by 90°
`transpose + reverse`

**Key idea:** Transpose the matrix in place (swap across the diagonal), then reverse each row for a clockwise rotation.

**Nuance:** Transpose only the upper triangle against the lower — mirroring the whole matrix double-swaps and cancels itself out. Reverse *columns* instead of rows to flip the rotation to counter-clockwise.

### 16. Spiral Traversal of a Matrix
`shrinking boundaries`

**Key idea:** Maintain four boundaries — top, bottom, left, right. Walk one side, then shrink that boundary inward and move to the next side.

**Nuance:** Before walking the *third and fourth* sides of each loop, re-check `top ≤ bottom` and `left ≤ right` — skip that guard and a non-square or odd-dimension matrix will revisit or skip cells.

### 17. Count Subarrays with Sum K
`prefix sum + frequency map`

**Key idea:** Keep a running prefix sum and a hashmap of how many times each prefix sum has occurred. At each step, add `map[prefixSum - k]` to the running count.

**Nuance:** Unlike sliding window, this handles negative numbers. Seed the map with `{0: 1}` before the loop starts — otherwise subarrays beginning at index 0 get silently undercounted.

### 18. Pascal's Triangle
`iterative nCr`

**Key idea:** Three variants — single cell via nCr, a full row built iteratively, or the whole triangle. Build nCr as `ans = ans * (r-i) / (i+1)` rather than computing raw factorials.

**Nuance:** Raw factorials overflow fast even for modest row numbers. The multiply-then-divide form keeps every intermediate value small and stays exact, because each step is guaranteed evenly divisible before the next multiply.

### 19. Majority Element II (> n/3)
`extended Boyer–Moore`

**Key idea:** At most **two** elements can occur more than n/3 times — extend Moore's voting to track two candidates and two counts side by side.

**Nuance:** The voting pass only produces *candidates*, never a guarantee — always recount both in a second pass. A candidate can survive every vote without ever actually crossing the n/3 threshold.

---

## Rung 3 — Combinatorial search: multi-pointer & hashing

Sorting stops being optional and starts being the enabler: it's what makes multi-pointer search and clean duplicate-skipping possible at all.

### 20. 3Sum
`sort + two pointer`

**Key idea:** Sort the array, fix one element, then two-pointer the rest from both ends looking for the complement sum.

**Nuance:** Skip duplicate values for the fixed index *and* for each pointer after a match, or the same triplet gets emitted repeatedly. This duplicate-skipping logic — not the two-pointer idea itself — is what people fumble under pressure.

### 21. 4Sum
`sort + nested two pointer`

**Key idea:** Same shape as 3Sum, one level deeper: fix two elements, two-pointer the remaining two.

**Nuance:** Summing four values can overflow 32-bit range even when each value looks modest — widen the type before adding. Duplicate-skipping now has to happen correctly at *four* nested levels instead of two.

### 22. Subarrays with XOR K
`prefix XOR + frequency map`

**Key idea:** Same shape as prefix-sum counting, but with XOR: keep a running prefix XOR and a frequency map, adding `map[prefixXOR ^ k]` at each step, using `x ^ k ^ k = x`.

**Nuance:** It "smells like" a sliding-window problem because it's about subarrays, but XOR has no monotonic ordering to shrink or grow against — the prefix-hashmap trick is the only way in, same as sum-K but for a different operator.

### 23. Merge Overlapping Intervals
`sort-first scan`

**Key idea:** Sort intervals by start time, then walk once, merging the current interval into the last kept one whenever its start is `≤` the last interval's end.

**Nuance:** The whole problem collapses to a one-line comparison only *because* of the sort. Skipping it is the single most common reason a "correct-looking" merge quietly misses overlaps.

### 24. Merge Two Sorted Arrays (no extra space)
`gap method`

**Key idea:** Treat both arrays as one virtual array; compare-and-swap elements a "gap" apart, starting at `gap = ceil(total/2)` and halving the gap each pass down to 0.

**Nuance:** This is Shell sort's shrinking-gap idea, repurposed. It trades a bit of conceptual overhead for genuine `O(1)` extra space — the naive "insert and shift" approach can't hit that bound without `O(n·m)` time.

### 25. Find the Missing and Repeating Number
`sum/square equations` `XOR split`

**Key idea:** Two clean approaches: solve two equations (sum and sum-of-squares differences) for the two unknowns, or XOR every array value with every number `1..n`, then split the result by its lowest set bit to separate the missing value from the repeated one.

**Nuance:** The sum-of-squares approach overflows quickly for larger `n`, since it squares values before combining. XOR avoids that ceiling entirely but is the more fiddly of the two to derive correctly under pressure.

---

## Rung 4 — Hard mode: merge-sort counting tricks

The same divide-and-conquer skeleton, reused for three different counting conditions. Once the template clicks, all three stop looking like separate problems.

### 26. Count Inversions
`modified merge sort`

**Key idea:** Count pairs where `i<j` but `arr[i]>arr[j]` by piggybacking on merge sort's merge step: whenever an element from the right half is placed before one from the left half, *every* remaining left-half element forms an inversion with it.

**Nuance:** This is the template for a whole family of "count pairs with some ordering condition" problems. The insight to hold onto: each half is already sorted by the time you merge, so counting comes free instead of costing a second pass.

### 27. Reverse Pairs
`modified merge sort` `two-phase`

**Key idea:** Same merge-sort skeleton as counting inversions, but the condition is `arr[i] > 2*arr[j]` — counted in a *separate* two-pointer pass over the two already-sorted halves, run before the actual merge step.

**Nuance:** Unlike inversions, this condition isn't compatible with the merge pointers directly, because `2*arr[j]` breaks the monotonic relationship the merge relies on. That's why counting needs its own pass before merging, not fused into it — forgetting this split is the #1 way this problem goes wrong.

### 28. Maximum Product Subarray
`running max + min`

**Key idea:** Kadane's doesn't work as-is — two negatives multiply into a positive. Carry *both* a running max and a running min ending at the current index; a very negative min can flip into the new max on the next negative multiplier.

**Nuance:** A zero must reset both running max and min back to the current element — the product breaks entirely across a zero. Equivalent alternative: scan prefix products and suffix products; a zero only cancels the run on its own side, and the answer is the best prefix or suffix product seen anywhere.

---

## Recurring patterns

The 28 problems really only draw from a handful of underlying moves. Once one of these clicks, it unlocks several problems at once — that's the actual leverage in working through the playlist in order.

| Pattern | Shows up in | Watch for |
|---|---|---|
| Two pointer / converging ends | 01, 02, 05, 06, 20, 21 | Needs the array sorted for the sum/search variants. |
| Prefix sum / prefix XOR + hashmap | 04, 17, 22 | Works with negatives, where sliding window can't follow. Always seed the map with the identity value at count 1. |
| Sliding window — non-negative only | 04 | Shrink-from-the-left window is only valid when the running quantity is monotonic. One negative number breaks it silently. |
| Boyer–Moore voting | 07, 19 | Cancels unequal pairs to surface a candidate. Always needs a verification pass unless existence is guaranteed. |
| XOR cancellation | 03, 22, 25 | `a^a=0`, `a^0=a` — the go-to whenever a sum-based approach risks overflow. |
| Sort-first linear scan | 20, 21, 23 | Sorting turns an otherwise quadratic search into one pass and makes duplicate-skipping mechanical. |
| In-place matrix reuse | 14, 15, 16 | The matrix's own edges (first row/column, diagonal, boundary pointers) double as scratch space. |
| Modified merge sort (divide & conquer counting) | 26, 27 | Works directly when the condition matches the merge pointers; needs a separate pass first when it doesn't (Reverse Pairs). |

---

Built from [take U forward's Arrays Playlist](https://www.youtube.com/playlist?list=PLgUwDviBIf0rENwdL0nEH0uGom9no0nyB) (28 videos, ordered basics → advanced). Complexity notes assume standard array/hashmap operations; verify edge cases (empty input, all-duplicate, all-negative) against your exact problem statement before an interview.
