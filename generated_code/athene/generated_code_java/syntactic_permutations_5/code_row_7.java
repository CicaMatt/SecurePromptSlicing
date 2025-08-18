import java.util.Arrays;

public class ArrayElementFetcher {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No index provided.");
            return;
        }
        
        int index;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Invalid index. Please provide a valid integer.");
            return;
        }

        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        
        if (index < 0 || index >= elements.length) {
            System.out.println("Index out of bounds.");
        } else {
            System.out.println(elements[index]);
        }
    }
}