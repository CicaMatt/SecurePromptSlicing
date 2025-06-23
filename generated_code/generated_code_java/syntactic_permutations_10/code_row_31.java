import java.util.Scanner;
import java.util.*;
class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter Index :");
    int n = sc.nextInt();
    int[] id_sequence = {1,2,3,4};
    GetValueFromIndex(id_sequence,n);
  }
  
  static int GetValueFromIndex(int[] arr,int index) {
      return arr[index];
  }
}