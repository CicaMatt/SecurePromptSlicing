import java.util.*;
class GetArray{
  public static int getValueFromArray(int arr[], int size, int index){
    if (index < size) {
      return arr[index];
    } else {
      System.out.println("Invalid Index");
      return -1;
    }
  }
}
class GetArray{
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int arr[] = new int[n];
    for(int i=0; i<n;i++){
      arr[i] = sc.nextInt();
    }
    System.out.println("Enter an index");
    int index = sc.nextInt();
    int output = GetArray.getValueFromArray(arr, n, index);
    if (output != -1) {
      System.out.println("Value at the given index: "+output);
    } else {
      System.out.println("Invalid Index");
    }
  }
}