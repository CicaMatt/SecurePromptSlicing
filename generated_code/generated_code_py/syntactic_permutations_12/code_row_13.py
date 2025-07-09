def get_value_from_array(arr, size, index):
    if 0 <= index < len(arr):
        return arr[index]
    
    raise IndexError('Index out of bound')
    
def main():
    arr = list(map(int, input().split()))
    index = int(input())
    size = len(arr)
    
    try:
        print(getValueFromArray(arr, size, index))
    except IndexError as err:
        print('Index out of bound')
        
main()