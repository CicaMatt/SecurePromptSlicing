import java.util.Arrays;

public class CommandLinePrinter {
    public static void main(String[] args) {
        if (args.length > 0) {
            System.out.println(args[0].trim());
        } else {
            System.err.println("No arguments provided.");
        }
    }
}