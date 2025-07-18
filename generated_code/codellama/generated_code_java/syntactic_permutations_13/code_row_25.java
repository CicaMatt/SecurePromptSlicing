import java.util.Scanner;
    
    public class Test {
        static String[] id_sequence = {"J", "K", "L", "M"};
    
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter an index value: ");
            int index = sc.nextInt();
    
            String result = id_sequence[index];
            System.out.println(result);
        }
    }