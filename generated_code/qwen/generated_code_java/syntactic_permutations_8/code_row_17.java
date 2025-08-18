import java.util.Arrays;

public class CommandLineArgumentRetriever {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an array of strings and an index as command line arguments.");
            return;
        }

        int index;
        try {
            index = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be a valid integer representing the index.");
            return;
        }

        if (index < 0 || index >= args.length - 1) {
            System.out.println("Index is out of bounds for the provided array of strings.");
            return;
        }

        String result = args[index + 1];
        System.out.println("The value at the specified index is: " + result);
    }
}