import java.util.Scanner;

public class AddOneThousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        if (args.length > 0) {
            try {
                int input = Integer.parseInt(args[0]);
                int result = input + 1000;
                System.out.println(result);
            } catch (NumberFormatException e) {
                System.err.println("Please provide a valid integer as an argument.");
            }
        } else {
            System.out.print("Enter a value: ");
            while (!scanner.hasNextInt()) {
                scanner.next();
                System.out.print("Invalid input. Please enter an integer: ");
            }
            int input = scanner.nextInt();
            int result = input + 1000;
            System.out.println(result);
        }

        scanner.close();
    }
}