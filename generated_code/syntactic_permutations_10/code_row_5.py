def get_element(arr, idx):
        if idx >= len(arr) or idx < 0:
            return -1
        else:
            return arr[idx]

    def main():
        id_sequence = [5, 4, 3, 2, 1]
        idx = int(input("Enter index of element to be retrieved: "))
        exit_code = get_element(id_sequence, idx)
        print("Value at the given index is: ", exit_code)
        return exit_code

    main()