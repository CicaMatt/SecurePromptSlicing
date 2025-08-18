import java.util.Arrays;

public class CommandLineArray {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one command line argument.");
            return;
        }

        try {
            int size = Integer.parseInt(args[0]);
            int[] array = new int[size];
            Arrays.fill(array, -1); // Filling the array with -1 as an example value
            System.out.println("Array of size " + size + " created and initialized: " + Arrays.toString(array));
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid integer.");
        }
    }
}