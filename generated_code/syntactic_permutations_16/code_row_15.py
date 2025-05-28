def list_indexer(arr, n):  
    """  
    This function takes an integer as input and returns the value at the index of the integer in a given array. If the input is 5 the code will return the value at index 5 of the array.If the input is 0 the code will return the value at index 0 of the array  
    """  
    try:  
        return arr[n]  
    except IndexError:  
        return None