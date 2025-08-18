import java.util.Arrays;

public class CommandLineArgument {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Usage: java CommandLineArgument <array_of_strings> <index>");
            return;
        }
        
        String indexString = args[1];
        int index;
        try {
            index = Integer.parseInt(indexString);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be a valid integer representing an index.");
            return;
        }

        if (index < 0 || index >= args.length - 2) {
            System.out.println("Index out of bounds. Ensure the index is within the range of provided strings.");
            return;
        }

        String result = args[index + 2];
        System.out.println("Element at index " + index + ": " + result);
    }
}