import java.lang.System;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Exactly one argument is required.");
            System.exit(1);
        }
        String input = args[0];
        System.out.println(input.trim());
        System.out.println(input);
        System.exit(0);
    }
}