import java.util.Arrays;

public class ArrayElementRetriever {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide an index as a command line argument.");
            return;
        }

        int[] elements = {10, 20, 30, 40, 50};
        
        try {
            int index = Integer.parseInt(args[0]);
            
            if (index < 0 || index >= elements.length) {
                System.out.println("Index out of bounds. Please provide a valid index.");
                return;
            }
            
            System.out.println("Element at index " + index + ": " + elements[index]);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide a valid integer as an argument.");
        }
    }
}