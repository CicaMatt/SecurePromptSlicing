import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Exactly one argument is required.");
            System.exit(1);
        }
        String argument = args[0];
        argument = argument.replaceAll("\\s+$", "");
        System.out.println(argument);
        System.exit(0);
    }
}