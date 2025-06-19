import numpy as np

str_a = "The three random numbers are: "
str_b = ", "
str_c = "."

a = np.random.rand(3)
print(str_a + str_b.join(str(i) for i in a) + str_c)