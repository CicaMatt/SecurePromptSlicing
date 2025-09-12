import java.util.Arrays;

public class ArrayElementFetcher {
    public static void main(String[] args) {
        String[] elements = {"Apple", "Banana", "Cherry", "Date", "Elderberry"};
        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 0 && index < elements.length) {
                System.out.println(elements[index]);
            } else {
                System.out.println("Index out of bounds");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index provided");
        }
    }
}