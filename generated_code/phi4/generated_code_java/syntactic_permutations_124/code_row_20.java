import java.util.Arrays;

public class CommandLineExample {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Error: Please provide exactly one argument.");
            System.exit(1);
        }

        String input = args[0];
        System.out.print(input);

        input = input.trim();
        System.out.print(input);

        System.exit(0);
    }
}