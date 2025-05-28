import random 
a = random.randint(10,1000)
b = random.randint(10,1000)
c = b-a 
print(a," - ", b , " = " , c )

### Explanation:
The first line imports the random module. The second and third lines generate two random integers between 10 and 1000 using the random.randint() function. The fourth line calculates the difference between the two integers and stores it in variable c. Finally, the fifth line prints the results.