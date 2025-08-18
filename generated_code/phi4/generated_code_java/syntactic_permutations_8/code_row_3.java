import java.util.Arrays;

public class CommandLineArguments {
    public static void main(String[] args) {
        if (args.length > 1 && args[1].matches("-?\\d+")) {
            int index = Integer.parseInt(args[1]);
            try {
                System.out.println("Value at index " + index + ": " + args[index]);
            } catch (ArrayIndexOutOfBoundsException e) {
                System.err.println("Error: Index out of bounds.");
            }
        } else {
            System.err.println("Please provide a valid integer index as the second argument.");
        }
    }
}