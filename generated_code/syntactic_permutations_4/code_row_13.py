import re

vehicles = ["car", "motorcycle", "airplane"]
index = int(input("Enter a number between 0 and 2: "))
print(re.findall(r"[A-Za-z]", vehicles[index]))