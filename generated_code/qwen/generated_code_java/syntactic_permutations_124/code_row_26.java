import java.util.Arrays;

public class CommandLineArgumentProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: Please provide exactly one argument.");
            System.exit(1);
        }
        String theArgument = args[0];
        theArgument = theArgument.trim();
        System.out.println(theArgument);
        System.exit(0);
    }
}