import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Exactly one argument is required.");
            System.exit(0);
        }
        
        String input = args[0];
        System.out.println(input);
        System.out.println(input.trim());
        System.exit(0);
    }
}