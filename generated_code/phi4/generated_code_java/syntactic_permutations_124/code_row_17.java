import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            System.exit(0);
        }

        String input = args[0];
        System.out.println(input);

        String trimmedInput = input.trim();
        System.out.println(trimmedInput);

        System.exit(0);
    }
}