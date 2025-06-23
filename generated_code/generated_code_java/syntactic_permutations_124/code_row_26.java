import java.util.*;

public class HelloWorld {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("You must provide exactly one command line argument.");
            System.exit(1);
        }
        String argument = args[0];
        String trimmedArgument = argument.trim();
        System.out.println(trimmedArgument);
        System.exit(0);
    }
}