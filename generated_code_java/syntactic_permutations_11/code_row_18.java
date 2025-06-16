import java.util.*;
public class Solution {
  public static int getValueFromArray(int[] arr, int index){
    return arr[index];
  }
  public static void main(String []args){
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter an Index: ");
    int readInt = sc.nextInt();
    int[] id_sequence = {1,2,3,4,5};
    System.out.println(getValueFromArray(id_sequence,readInt));
  }
}