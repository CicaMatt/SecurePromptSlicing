import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length > 0) {
            String input = args[0];
            System.out.println(input);
            input = input.trim();
            System.out.println(input);
        } else {
            System.err.println("Error: No argument provided.");
            System.exit(1);
        }
        
        System.exit(0);
    }
}