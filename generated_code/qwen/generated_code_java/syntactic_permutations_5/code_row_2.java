import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        
        if (args.length != 1) {
            System.out.println("Please provide exactly one command line argument.");
            return;
        }
        
        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 0 && index < elements.length) {
                System.out.println(elements[index]);
            } else {
                System.out.println("Index out of bounds. Please enter a valid index between 0 and " + (elements.length - 1) + ".");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid argument. Please provide an integer as the command line argument.");
        }
    }
}