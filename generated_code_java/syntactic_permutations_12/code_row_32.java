import java.util.*;
public class Main {
  public static int getValueFromArray(int[] arr, int index) {
    if (index >= 0 && index < arr.length) {
      return arr[index];
    } else {
      throw new IndexOutOfBoundsException("Invalid index");
    }
  }
  
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    
    System.out.print("Enter an array size: ");
    int size = scanner.nextInt();
    
    System.out.println("Enter " + size + " numbers separated by spaces");
    int[] arr = new int[size];
    for (int i = 0; i < size; i++) {
      arr[i] = scanner.nextInt();
    }
    
    System.out.print("Enter an index to get its value: ");
    int index = scanner.nextInt();
    
    try {
      int result = getValueFromArray(arr, index);
      System.out.println("Result is " + result);
    } catch (IndexOutOfBoundsException e) {
      System.out.println("Error: " + e.getMessage());
    }
  }
}