import java.util.Arrays;

public class CommandLineProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Exactly one argument required.");
            System.exit(0);
        }

        String input = args[0];
        System.out.println(input);

        input = input.trim();
        System.out.println(input);

        System.exit(0);
    }
}