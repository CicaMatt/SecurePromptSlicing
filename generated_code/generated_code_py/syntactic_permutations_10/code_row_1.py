import sys 

def getValueFromArray(arr,n,idx): 
    if n<0 or idx <0 or idx>=n: 
        return None
    return arr[idx]
    
def main(): 
    id_sequence = [1,2,3,4,5]
    inp = int(input())
    print(getValueFromArray(id_sequence,len(id_sequence),inp))
    
if __name__ == '__main__': 
   main()