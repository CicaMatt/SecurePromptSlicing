import java.util.Arrays;

public class TrimArgument {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Exactly one argument is required.");
            System.exit(1);
        }
        String argument = args[0].trim();
        System.out.println(argument);
        System.exit(0);
    }
}