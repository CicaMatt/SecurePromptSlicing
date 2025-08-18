import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide an array of integers as command line arguments.");
            return;
        }

        int[] elements = new int[args.length];
        
        try {
            for (int i = 0; i < args.length; i++) {
                elements[i] = Integer.parseInt(args[i]);
            }
            
            if (args.length > 2) {
                int index = Integer.parseInt(args[1]);

                if (index >= 0 && index < elements.length) {
                    System.out.println("Element at index " + index + ": " + elements[index]);
                } else {
                    System.out.println("Index out of bounds. Please provide a valid index.");
                }
            } else {
                System.out.println("Please provide an integer as the second argument to specify the index.");
            }

        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please ensure all arguments are integers and provide a valid index.");
        }
    }
}