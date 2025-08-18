def get_value_at_index(arr, idx):
    return arr[idx]

if __name__ == "__main__":
    sample_array = [10, 20, 30, 40, 50, 60, 70, 80]
    user_input = int(input("Enter an integer for the index: "))
    
    if 0 <= user_input < len(sample_array):
        print(get_value_at_index(sample_array, user_input))
    else:
        print(f"Index {user_input} is out of bounds for this array.")