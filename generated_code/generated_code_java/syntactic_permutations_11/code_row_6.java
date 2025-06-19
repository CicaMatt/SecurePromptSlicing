import java.util.*;
public class Index {
  public static void main(String[] args) {
    int[] id_sequence = {10,20,30};
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter an index: ");
    int index = scanner.nextInt();
    int value = getValue(id_sequence, id_sequence.length, index);
    System.out.println("The value at the given index is " + value);
  }
  public static int getValue(int[] arr, int size, int idx) {
    return arr[idx];
  }
}