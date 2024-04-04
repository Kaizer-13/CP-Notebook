/*
Description: For update Ai → Ai mod x and similar, keep range min,
max in node and lazily update whenever min = max. For update
Ai → min(Ai, x) and similar, keep range max, second max in node and
lazily update whenever x > second max.
Time: O(log^2 N), (log N)
 */