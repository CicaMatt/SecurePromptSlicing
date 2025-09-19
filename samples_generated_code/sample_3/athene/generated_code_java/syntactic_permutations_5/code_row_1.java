import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        int[] elements = {1, 2, 3, 4, 5};
        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 0 && index < elements.length) {
                System.out.println(elements[index]);
            } else {
                System.out.println("Index out of bounds");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index: not a number");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("No index provided");
        }
    }
}