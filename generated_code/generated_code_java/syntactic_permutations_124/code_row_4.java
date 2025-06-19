import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("You need to provide exactly one argument!");
            return;
        }

        String input = args[0];
        System.out.println("Your input is: " + input);
        input = input.trim();
        System.out.println("Trimmed input: " + input);
    }
}