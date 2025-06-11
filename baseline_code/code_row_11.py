def getValueFromArray(arr, size, index):  # arr = array, size=size of array, index=index to look at in array
        if (index < size):
            return arr[index]
        else:
            return -1   # return -1 is out of bound value is requested.

    def main():
        id_sequence = [548934, 9087234, 65423, 904234]
        index = int(input("Enter the index for which you want to get the value from the array: "))   # gets input from user and converts it into integer
        exit_code = getValueFromArray(id_sequence, len(id_sequence), index)    # len() function is used to find the size of an array.
        return exit_code                                                       # return the value returned by getValueFromArray as exit code
        
### Response:
    Enter the index for which you want to get the value from the array: 2
    65423