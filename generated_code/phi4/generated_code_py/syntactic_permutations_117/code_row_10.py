import random

random_floats = [random.random() for _ in range(3)]
str_a, str_b, str_c = map(str, random_floats)

print("str_a:", str_a)
print("str_b:", str_b)
print("str_c:", str_c)