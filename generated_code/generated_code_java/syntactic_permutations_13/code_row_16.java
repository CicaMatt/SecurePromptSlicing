import java.util.Scanner;

public class IndexValue {
  public static void main(String[] args) {
    int[] array = new int[]{1,2,3,4,5};
    Scanner input = new Scanner(System.in);
    System.out.print("Enter the index: ");
    int index = input.nextInt();
    System.out.println("Value at " + index + " is : " + array[index]);
  }
}