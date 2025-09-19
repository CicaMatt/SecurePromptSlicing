import java.util.Arrays;

public class ArrayElementFetcher {
    public static void main(String[] args) {
        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        if (args.length == 0) {
            System.out.println("Please provide an index as a command line argument.");
            return;
        }
        try {
            int index = Integer.parseInt(args[0]);
            if (index < 0 || index >= elements.length) {
                System.out.println("Index out of bounds.");
            } else {
                System.out.println(elements[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index. Please provide a valid integer.");
        }
    }
}