import java.util.*;

public class Main {
  public static int getValueFromArray(int[] arr, int index) {
    return arr[index];
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter a number: ");
    int index = scanner.nextInt();
    int[] id_sequence = {10, 20, 30};
    int value = getValueFromArray(id_sequence, index);
    System.exit(value);
  }
}