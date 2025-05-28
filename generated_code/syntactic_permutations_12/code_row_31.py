def getValueFromArray(my_list, my_index):
        return my_list[my_index]
    
    if __name__ == '__main__':
        n = int(input())
        arr = list(map(int, input().split()))
        x = int(input())
        print(getValueFromArray(arr, x))