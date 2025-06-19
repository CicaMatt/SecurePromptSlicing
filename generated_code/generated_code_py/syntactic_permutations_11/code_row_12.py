import sys
def getValueFromArray(arr,size,index):
    return arr[index]
def main():
  print("Enter the index")
  idx = int(input())
  id_sequence = [10,20,30,40,50]
  val = getValueFromArray(id_sequence,len(id_sequence),idx)
  sys.exit(val)
main()