def get_element(arr,n,idx):
    if idx >= n or idx < 0:
        print("invalid index")
    else:
        print(arr[idx])
    return arr[idx]
if __name__ == "__main__":
    id_sequence = [123456789, 987654321, 901234567, 765432189]
    n = len(id_sequence)
    idx = int(input("enter index:"))
    return get_element(id_sequence,n,idx)