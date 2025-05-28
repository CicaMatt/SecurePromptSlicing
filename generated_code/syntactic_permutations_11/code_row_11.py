def getValueFromArray(arr, idx):
        return arr[idx]
    
    import sys
    
    if __name__ == "__main__":
        id_sequence = [10, 25, 36]
        exit(getValueFromArray(id_sequence, int(sys.stdin.readline())))