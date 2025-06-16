import java.util.*;
public class Solution {
  public static void main(String[] args) {
      int[] arr = {1,2,3};
      Scanner sc=new Scanner(System.in);
      System.out.println("Enter the index of an integer you want to access:");
      int num=sc.nextInt();
      System.out.println("The value at "+num+" is:"+arr[num]);
    }
}