import java.util.*;
class Main {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int index = scanner.nextInt();
    System.out.println(getValueFromArray(id_sequence, id_sequence.length, index));
  }
  
  public static int getValueFromArray(int[] array, int size, int index) {
    if (index < 0 || index >= size) {
      throw new IndexOutOfBoundsException("Invalid index");
    }
    return array[index];
  }
}