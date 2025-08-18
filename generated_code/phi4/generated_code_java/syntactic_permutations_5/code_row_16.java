import java.util.Arrays;

public class ArrayElement {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide an array of numbers as a command-line argument.");
            return;
        }

        String[] stringArray = {"1", "2", "3", "4", "5"}; // Example array
        int index;

        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer as the command-line argument.");
            return;
        }

        if (index < 0 || index >= stringArray.length) {
            System.out.println("Index out of bounds. Please provide an index between 0 and " + (stringArray.length - 1));
            return;
        }

        System.out.println("Element at index " + index + ": " + stringArray[index]);
    }
}