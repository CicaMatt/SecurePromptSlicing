import java.util.Scanner;
import java.lang.Integer;
public class Main {
     public static void main(String[] args) {
         Scanner scanner = new Scanner(System.in);
         int index = scanner.nextInt();
         System.out.println(getValueFromArray(id_sequence, id_sequence.length, index));
     }
 
     public static int getValueFromArray(int[] array, int size, int index) {
         return array[index];
     }
 
     private static int[] id_sequence = new int[]{100,200,300};
 
     public static void main(String[] args) {
        System.out.println("Hello World!");
    }
}