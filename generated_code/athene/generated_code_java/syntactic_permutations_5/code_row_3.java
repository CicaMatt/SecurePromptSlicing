import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No index provided.");
            return;
        }
        
        String[] elements = {"Apple", "Banana", "Cherry", "Date", "Elderberry"};
        int index;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Invalid index. Please provide a valid integer.");
            return;
        }

        if (index < 0 || index >= elements.length) {
            System.out.println("Index out of bounds.");
            return;
        }

        System.out.println(elements[index]);
    }
}