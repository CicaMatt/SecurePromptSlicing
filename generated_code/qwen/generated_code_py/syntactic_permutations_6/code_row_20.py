import sys

vehicles = ["car", "bike", "truck", "motorcycle"]

try:
    index = int(input("Enter the index of the vehicle you want: "))
    print(vehicles[index])
except IndexError:
    print("Index out of range. Please enter a valid index.")
except ValueError:
    print("Invalid input. Please enter an integer.")