import java.util.Scanner;

    public class IndexedArray {
      public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        
        System.out.print("Enter an index from 0 to 9: ");
        int index = Integer.parseInt(reader.nextLine());
        
        int id_sequence[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        System.out.println("Value at index " + index + ": " + id_sequence[index]);
      }
    }