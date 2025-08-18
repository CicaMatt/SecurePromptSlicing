import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Please provide exactly one argument.");
            Scanner scanner = new Scanner(System.in);
            String input = scanner.nextLine();
            scanner.close();
        } else {
            String input = args[0];
            System.out.println(input);
            input = input.trim();
            System.out.println(input);
        }
        System.exit(0);
    }
}