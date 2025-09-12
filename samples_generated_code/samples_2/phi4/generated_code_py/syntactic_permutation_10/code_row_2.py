def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

def main():
    try:
        n = int(input().strip())
    except ValueError:
        exit(-2)
    
    id_sequence = [i for i in range(100)]  # Example array; adjust as needed
    result = getValueFromArray(id_sequence, len(id_sequence), n)
    exit(result)

if __name__ == "__main__":
    main()