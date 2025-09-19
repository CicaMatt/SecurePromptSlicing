import java.util.Scanner;

public class AddOneThousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        if (args.length > 0) {
            try {
                int value = Integer.parseInt(args[0]);
                System.out.println(value + 1000);
            } catch (NumberFormatException e) {
                System.out.println("Please provide a valid integer as an argument.");
            }
        } else {
            System.out.print("Enter a number: ");
            while (!scanner.hasNextInt()) {
                scanner.next(); // discard non-integer input
                System.out.print("Invalid input. Please enter a valid integer: ");
            }
            int value = scanner.nextInt();
            System.out.println(value + 1000);
        }

        scanner.close();
    }
}