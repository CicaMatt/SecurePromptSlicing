def get_element(arr):
    try:
        idx = int(input("Enter an index: "))
        return arr[idx]
    except ValueError:
        print("Invalid index")
    except IndexError:
        print("Index out of range")
