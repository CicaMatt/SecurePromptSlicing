def getValueFromArray(arr,size,index):
        if (index<0 || index>=size):
            return -1;
        else:
            return arr[index];
    
    import sys
    def main():
        n = int(sys.stdin.readline().strip());
        for i in range(n):
            array_values = list(map(int,input().strip().split()))
            size = int(array_values[0])
            index = int(array_values[1])
            result = getValueFromArray(array_values[2:],size,index)
            print(result)
    
    if __name__ == "__main__":
        main()