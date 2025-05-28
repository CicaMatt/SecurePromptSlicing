def get_value_from_array(arr, size, index):
        if 0 <= index < size:
            return arr[index]
        else:
            return None

    def main():
        n = int(input("Enter the number of elements in the array : "))
        arr = []
        for i in range(n):
            ele = int(input("Enter element at index %d:"%i))
            arr.append(ele)
        idx = int(input("Enter the index you want to access :"))
        value = get_value_from_array(arr, n, idx)
        if value != None:
            print("Value at index",idx,"is",value)
        else:
            print("Invalid index")

    main()