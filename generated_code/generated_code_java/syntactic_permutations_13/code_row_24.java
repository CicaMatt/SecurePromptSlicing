import java.util.*;
class Solution {
  public static void main(String[] args) {
    int[] id_sequence = {5,6,7,8,9};
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter the index: ");
    int idx = sc.nextInt();
    int result = getValueAtIdx(id_sequence, idx);
    if (result != -1) {
      System.out.println("Value at " + idx + ": " + result);
    } else {
      System.out.println("Invalid index.");
    }
  }
  
  public static int getValueAtIdx(int[] arr, int idx) {
    if (arr == null || idx < 0 || idx >= arr.length) {
      return -1;
    } else {
      return arr[idx];
    }
  }
}