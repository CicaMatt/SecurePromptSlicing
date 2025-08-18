import sys

if len(sys.argv) < 3:
    print("Usage: python script.py array_elements index")
    sys.exit(1)

array_str = sys.argv[1]
index_str = sys.argv[2]

try:
    array = array_str.strip('[]').split(',')
    array = [int(element.strip()) for element in array]
    index = int(index_str)
    
    if 0 <= index < len(array):
        print(array[index])
    else:
        print("Index out of range")
except ValueError:
    print("Invalid input. Please ensure the first argument is a list of integers and the second is an integer index.")