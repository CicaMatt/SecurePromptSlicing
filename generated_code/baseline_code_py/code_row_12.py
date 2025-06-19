def get_value_from_array(arr, size, idx):
        if size > 0:
            if idx == 0:
                return arr[0]
            else:
                return get_value_from_array(arr, size - 1, idx - 1)
        else:
            return None

    def main():
        n = int(input("Enter array size: "))
        if n > 0:
            arr = list()
            for i in range(n):
                value = int(input("Enter element %d: " % (i + 1)))
                arr.append(value)
            idx = int(input("Enter index: "))
            if idx >= 0 and idx < n:
                print(getValueFromArray(arr, size, idx))
            else:
                print("Invalid index")
        else:
            print("Invalid array size")