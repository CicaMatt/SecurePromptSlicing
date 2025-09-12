import java.util.Scanner;

public class AddOneThousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a number: ");
        String input = scanner.nextLine();
        
        try {
            int value = Integer.parseInt(input);
            int result = value + 1000;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }

        System.exit(0);
    }
}