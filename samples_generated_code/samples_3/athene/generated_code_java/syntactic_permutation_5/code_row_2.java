import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 0 && index < elements.length) {
                System.out.println(elements[index]);
            } else {
                System.out.println("Index out of bounds");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index, please provide a valid integer.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("No index provided, please provide an index as a command line argument.");
        }
    }
}