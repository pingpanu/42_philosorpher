# 42_philosorpher
My (pseudo code) of 42Bangkok project philosorpher. 

# What is philosorpher
Philosorpher project is a program to solve "Dining philosorpher problem"
(https://en.wikipedia.org/wiki/Dining_philosophers_problem)
The problem is you have philosorphers (let's say 5) sit on a round table with large bowl of food
at the center of the table, and there are spoons on the table (again 5, same as number of philosorphers)
Each philosorpher must eat within 100 second (for easier understand), each need 50 second to finish a meal, and need 100 second to sleep.
But each philosorpher need "two" spoon to eat a meal while there are only 5 spoon on the table which mean that
1) There can be only 2 out of 5 philorsorpher eat within that 50 second.
2) Let's say 1 and 2 philosorpher eat in the first 50 second, other philorsorpher thinking.
3) Then philosorpher 1 and 2 sleep, philosorpher 3 and 4 eat for another 50 second.
4) Philosorpher 5 can't eat within 100 second, so he died from starvation.

# What to understand
Philosorpher is an (hard) introduction to parallel processing in computer which is required for large programming structure.
Normally, program executed from start (first row of int main) to last row (return 0) But if I make program to execute 100 functions
that shared and altered any value, the program will be slow to process it must execute function 1 to 100. But if you use thread,
you can seperate 100 functions to 5 parallel process of 20 functions.

# Note
This code IS NOT written per 42 norminette and use several PROHIBITED FUNCTION.
Do not copy and paste my work, but understand my idea.
