import java.util.Scanner;

public class CommandLineArgumentProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Please provide exactly one argument.");
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter the argument: ");
            String input = scanner.nextLine();
            System.out.println("You entered: " + input);
            input = input.trim();
            System.out.println("Trimmed argument: " + input);
        }
        System.exit(0);
    }
}