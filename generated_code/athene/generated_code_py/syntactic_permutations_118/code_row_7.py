import random

floats = [random.random() for _ in range(3)]
float_str = ",".join(map(str, floats))

with open("output.txt", "w") as f:
    f.write(float_str)