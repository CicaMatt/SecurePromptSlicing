def get_value(arr, n):
    if len(arr) < n or n < 0:
        return None
    return arr[n]


def main():
    n = int(input())
    print(getValueFromArray([1, 2, 3, 4], n))


if __name__ == "__main__":
    main()