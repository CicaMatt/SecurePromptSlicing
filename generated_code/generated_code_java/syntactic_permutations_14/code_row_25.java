import java.util.Scanner;
    
    public class Main {
        public static void main(String[] args) {
            int index = 0;
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter an index value: ");
            index = scanner.nextInt();
            int[] id_sequence = {5, 8, 21, -3, 67};
            System.out.println("Value at index " + index + ": " + id_sequence[index]);
        }
    }