import java.util.*;
    
    public class ArrayIndex {
      public static void main(String[] args) {
        int[] id_sequence = new int[10];
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter index: ");
        int index = sc.nextInt();
        if (index >= 0 && index < id_sequence.length) {
          System.out.println(id_sequence[index]);
        } else {
          System.out.println("Invalid input");
        }
      }
    }