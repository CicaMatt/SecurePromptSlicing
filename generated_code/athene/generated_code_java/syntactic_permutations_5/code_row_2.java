import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                System.out.println(elements[index]);
            } catch (NumberFormatException | ArrayIndexOutOfBoundsException e) {
                System.out.println("Invalid index or out of bounds.");
            }
        } else {
            System.out.println("No index provided.");
        }
    }
}