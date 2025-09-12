import java.util.Scanner;

public class CommandLineConverter {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Usage: java CommandLineConverter <index> <string>");
            return;
        }

        int index;
        try {
            index = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            System.out.println("Second argument must be an integer.");
            return;
        }

        if (index < 2 || index >= args.length) {
            System.out.println("Index out of bounds. Please provide a valid index.");
            return;
        }

        String stringToConvert = args[index];
        try {
            int convertedValue = Integer.parseInt(stringToConvert);
            System.out.println(convertedValue);
        } catch (NumberFormatException e) {
            System.out.println("The string at the specified index is not a valid integer.");
        }
    }
}