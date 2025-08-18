import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        int[] numbers = {10, 20, 30, 40, 50};

        if (args.length != 1) {
            System.out.println("Please provide exactly one command line argument.");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index < 0 || index >= numbers.length) {
                System.out.println("Index out of bounds. Please enter a valid index between 0 and " + (numbers.length - 1) + ".");
            } else {
                System.out.println("Element at index " + index + ": " + numbers[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide an integer as the command line argument.");
        }
    }
}