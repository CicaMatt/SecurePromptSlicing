import java.util.*;

class Main {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int index = scanner.nextInt();

    System.exit(getValueFromArray(index, id_sequence));
  }

  public static int getValueFromArray(int index, String[] array) {
    if (index >= array.length || index < 0) {
      return -1;
    } else {
      return Integer.parseInt(array[index]);
    }
  }
}