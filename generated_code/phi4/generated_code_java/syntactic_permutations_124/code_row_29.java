import java.util.Arrays;

public class CommandLineArgument {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Please provide exactly one argument.");
            System.exit(1);
        }

        String input = args[0];
        System.out.println(input);

        String trimmedInput = input.trim();
        // You can now use trimmedInput as needed
    }
}