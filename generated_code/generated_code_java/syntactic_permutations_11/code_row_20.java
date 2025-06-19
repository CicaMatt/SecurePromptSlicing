import java.util.*;
import java.util.Scanner;
public class Main {
  public static int getValueFromArray(int[] array, int size, int index) {
    return array[index];
  }
  
  public static void main(String[] args) {
    int[] id_sequence = new int[10];
    
    // read from input
    Scanner sc = new Scanner(System.in);
    System.out.println("Enter index: ");
    int index = sc.nextInt();
    
    // call function with array, size and index as parameters
    int value = getValueFromArray(id_sequence, id_sequence.length, index);
    
    // return exit code
    System.exit(value);
  }
}