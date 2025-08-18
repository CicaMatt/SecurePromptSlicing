import java.util.Arrays;

public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide at least two arguments.");
            return;
        }
        
        try {
            int index = Integer.parseInt(args[1]);
            String valueAtIndex = args[index];
            System.out.println("Value at index " + index + ": " + valueAtIndex);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be a valid integer.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please provide a valid index.");
        }
    }
}