import java.util.Arrays;

public class ArrayElementFetcher {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No index provided.");
            return;
        }
        int[] elements = {1, 2, 3, 4, 5};
        try {
            int index = Integer.parseInt(args[0]);
            if (index < 0 || index >= elements.length) {
                System.out.println("Index out of bounds.");
            } else {
                System.out.println(elements[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index provided.");
        }
    }
}