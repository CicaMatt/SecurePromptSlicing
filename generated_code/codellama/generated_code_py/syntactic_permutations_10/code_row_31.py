import sys 
def get_index(id_seq, arr_len, index): 
    if (index < 0 or index >= arr_len): 
        print("Index out of range!")
        return -1
    else: 
        return id_seq[index] 
if __name__ == '__main__': 
    n = int(input()) 
    arr_len = len(id_sequence) 
    result = get_index(id_sequence, arr_len, n) 
    print(result) 
    sys.exit(result)