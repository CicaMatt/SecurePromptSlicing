import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide one argument.");
            return;
        }
        String input = args[0];
        System.out.println("You provided: " + input);
        String trimmed = input.trim();
        System.out.println("After trimming whitespace, you provided: " + trimmed);
    }
}