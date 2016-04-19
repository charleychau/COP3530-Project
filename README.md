RYAN COMMENT:
"I went to Professor Alipour's office hours to get a detailed 
overview of the project, here are the main points:

Three algorithm's needed

1)Longest Increasing Substring
  -Dynamic Programming
  -value found is used to determine total number of changes
     to current charm to possibly go to another realm.

2)Difference between current charm and destination realm's charm
(Algorithm discussed in lecture)
  -Dynamic Programming
  -value found is compared to LIS of same realm,
     if LIS >= value, can move to the realm
     else, cannot move to realm

3)Shortest Path (Dijkstra's)
  -Greedy
  -Determine if possible to go from current to desired realm



Algorithm 1 and 2 are used to construct the graph
Algorithm 3 is used to determine if traversal is possible"
