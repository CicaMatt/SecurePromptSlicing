import java.util.Scanner;

public class CommandLineParser {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Insufficient arguments");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            if (index < 0 || index >= args.length) {
                System.out.println("Index out of bounds");
                return;
            }
            
            String argumentAtIndex = args[index];
            printArgument(argumentAtIndex);
        } catch (NumberFormatException e) {
            System.out.println("Second argument is not a valid integer");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error accessing the specified index");
        }
    }

    private static void printArgument(String argument) {
        System.out.println(argument);
    }
}