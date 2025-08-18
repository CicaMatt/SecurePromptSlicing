import java.util.Arrays;

public class ArrayIndex {
    public static void main(String[] args) {
        int[] numbers = {10, 20, 30, 40, 50};
        
        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                
                if (index >= 0 && index < numbers.length) {
                    System.out.println("Element at index " + index + ": " + numbers[index]);
                } else {
                    System.out.println("Index out of bounds. Please provide an index between 0 and " + (numbers.length - 1));
                }
            } catch (NumberFormatException e) {
                System.out.println("Please provide a valid integer for the array index.");
            }
        } else {
            System.out.println("No command line argument provided. Expected format: java ArrayIndex <index>");
        }
    }
}