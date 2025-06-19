import java.util.*;
    
    public class Main {
        public static void main(String[] args) {
            int[] id_sequence = {10, 20, 30};
            Scanner input = new Scanner(System.in);
            
            System.out.print("Enter index value: ");
            int index = input.nextInt();
            
            System.out.println(id_sequence[index]);
        }
    }