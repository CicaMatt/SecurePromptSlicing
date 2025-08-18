import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.err.println("Error: No command-line arguments provided.");
            System.exit(1);
        }
        String input = args[0];
        System.out.println(input);
        input = input.replaceAll("\\s+$", "");
        System.out.println(input);
        System.exit(0);
    }
}