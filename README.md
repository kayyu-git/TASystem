# TASystem

A C++ program that models a Technical Analysis System. Uses multiple running threads to mathematically analyze stocks using multiple factors. Stock information is read from a text file (currently named SP500.txt).

Number of days to be used in the moving average is specified by the user.

Output is in both raw numerical and sentence format. 
Example output for input parameter of 5 days:
- - - - - - - - - - - - - - - -
px for SP500, 2752.06, is 3.03859 std dev below moving average, 2804.51

2826.06, 2802.39, 2783.02, 2788.86, 2752.06,
MA: 2790.48
sDev: 24.2576
- - - - - - - - - - - - - - - -
Supported stock analysis results: Moving Average, Standard Deviation
