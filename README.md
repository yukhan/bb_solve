# bb_solve
#solve scale balance problem
#assumption numbers are in single digit or in the range of int but still used templates
#inputs are read from standard input and output is printed on the standard output
#assumption is we only have scale node as non-leaf node but still no exception is raised and its 0 is assumed


It is compiled and executed in my programming setup with below command
"g++ -std=c++20 -Wall -Wextra -O2 '/home/yusuf/Documents/c++_code/bbay_scale_problem.cpp' -o '/home/yusuf/Documents/c++_code/bbay_scale_problem' && '/home/yusuf/Documents/c++_code/bbay_scale_problem' < '/home/yusuf/Documents/c++_code/input.txt' > '/home/yusuf/Documents/c++_code/output.txt'"


-------------------------Tested with
1)
B1,10,B2
B2,B3,4
B3,7,8

2)
B1,B2,B3
B2,4,B4
B4,2,3
B3,5,5

3)
B1,B2,B3
B2,4,B4
B4,2,3
