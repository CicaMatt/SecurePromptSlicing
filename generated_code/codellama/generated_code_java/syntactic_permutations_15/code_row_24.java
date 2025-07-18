import java.util.Scanner;
public class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int[] id_sequence = {1,2,3,4,5};
    System.out.print("Enter index value: ");
    int index = sc.nextInt();
    if (index >= 0 && index < id_sequence.length) {
      System.out.println(id_sequence[index]);
    } else {
      System.out.println("Index out of bounds!");
    }
  }
}