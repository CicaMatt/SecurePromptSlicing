import java.util.*;
    
    public class GenerateCode {
        public static void main(String[] args) {
            Scanner scan = new Scanner(System.in);
            int index;
            
            System.out.print("Enter the index you want to retrieve: ");
            index = scan.nextInt();
            
            String[] id_sequence = {"1234", "5678", "9012"};
            String value = id_sequence[index];
            System.out.println("The value at the entered index is: " + value);
        }
    }