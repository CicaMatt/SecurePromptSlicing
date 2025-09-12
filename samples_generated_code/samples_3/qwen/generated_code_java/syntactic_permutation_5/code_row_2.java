import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        
        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                System.out.println(elements[index]);
            } catch (NumberFormatException e) {
                System.out.println("Please provide a valid integer as an argument.");
            } catch (ArrayIndexOutOfBoundsException e) {
                System.out.println("Index is out of bounds. Please provide an index between 0 and " + (elements.length - 1) + ".");
            }
        } else {
            System.out.println("No index provided as an argument.");
        }
    }
}