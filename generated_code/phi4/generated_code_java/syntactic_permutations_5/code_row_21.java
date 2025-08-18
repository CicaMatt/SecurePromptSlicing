import java.util.Arrays;

public class ArrayFromCommandLine {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a command-line argument.");
            return;
        }

        try {
            int number = Integer.parseInt(args[0]);
            int[] array = new int[number];

            // Initialize the array with some values, for example, 1 to number
            for (int i = 0; i < array.length; i++) {
                array[i] = i + 1;
            }

            System.out.println("Array: " + Arrays.toString(array));
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer as the command-line argument.");
        }
    }
}