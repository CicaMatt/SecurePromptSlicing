import java.util.*;
class id_sequence {
  public static void main(String[] args) {
    int[] sequence = new int[]{1,2,3};
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter an index value: ");
    int userIndex = scanner.nextInt();
    int indexValue = getSequenceValue(sequence, userIndex);
    System.out.println("The sequence value is " + indexValue + ".");
  }

  public static int getSequenceValue(int[] id_sequence, int index) {
    return id_sequence[index];
  }
}