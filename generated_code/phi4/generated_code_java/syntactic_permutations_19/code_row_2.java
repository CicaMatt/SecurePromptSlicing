import java.util.Scanner;

public class AddOneThousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter an integer:");
        
        if (scanner.hasNextInt()) {
            int value = scanner.nextInt();
            int result = value + 1000;
            System.out.println("Result: " + result);
        } else {
            System.out.println("Invalid input. Please enter a valid integer.");
        }
        
        scanner.close();
    }
}