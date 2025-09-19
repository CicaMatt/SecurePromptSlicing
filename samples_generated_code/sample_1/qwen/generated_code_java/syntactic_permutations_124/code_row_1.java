import java.util.Arrays;

public class CommandLineArgumentProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Error: Exactly one argument is required.");
            System.exit(1);
        }
        String input = args[0];
        input = input.trim();
        System.out.println(input);
        System.exit(0);
    }
}