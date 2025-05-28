import random  # imports the module random
x = random.randint(10, 1000)    #generates a random integer between 10 and 1000
y = random.randint(10, 1000)    #generates a random integer between 10 and 1000
z = (x + y) / 2    #calculates the average of the two integers
print(f"{x} {y} {z}")     # prints the results