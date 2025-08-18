import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Please provide exactly one argument.");
            System.exit(1);
        }
        String argument = args[0];
        argument = argument.trim();
        System.out.println(argument);
        System.exit(0);
    }
}