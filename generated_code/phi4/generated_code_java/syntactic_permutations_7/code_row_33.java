import java.util.Scanner;

public class CommandLineIntegerConverter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Insufficient arguments provided.");
            return;
        }

        int index;
        try {
            index = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be an integer.");
            return;
        }

        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds.");
            return;
        }

        String valueToConvert = args[index];
        
        try {
            int convertedValue = Integer.parseInt(valueToConvert);
            System.out.println(convertedValue);
        } catch (NumberFormatException e) {
            System.out.println("The argument at the specified index is not a valid integer.");
        }
    }
}