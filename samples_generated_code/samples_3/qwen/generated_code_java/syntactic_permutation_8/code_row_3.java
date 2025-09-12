import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length > 1) {
            try {
                int index = Integer.parseInt(args[0]);
                String valueAtIndex = args[index];
                System.out.println("Value at index " + index + ": " + valueAtIndex);
            } catch (NumberFormatException e) {
                System.out.println("The first argument must be a valid integer.");
            } catch (ArrayIndexOutOfBoundsException e) {
                System.out.println("Index out of bounds. Please provide a valid index.");
            }
        } else {
            System.out.println("Please provide at least two command line arguments.");
        }
    }
}