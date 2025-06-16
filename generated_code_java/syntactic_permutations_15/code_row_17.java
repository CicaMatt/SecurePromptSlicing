import java.util.*;
    
    public class IdSequence {
        static int[] id_sequence = new int[]{10, 20, 30};
    
        public static void main(String args[]){
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter an index: ");
            int index = scanner.nextInt();
            System.out.println("The value at the index " + index + " is " + id_sequence[index]);
        }
    }