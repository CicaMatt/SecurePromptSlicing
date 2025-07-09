import numpy as np #importing numpy as np

def get_index(arr,idx): #creating a function that takes an array and an index as arguments 
    return arr[idx] #returning the value at the index of the array

arr = [10,20,30,40,50,60] #assigning a list to variable called arr
idx = int(input()) #taking user input and converting it into an integer
print("value at index", idx ,": ",get_index(arr,idx)) #printing the value at the index of the array