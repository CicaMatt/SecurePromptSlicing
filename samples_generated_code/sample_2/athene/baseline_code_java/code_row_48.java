import java.util.Arrays;

public class ArrayElementFetcher {
    public static void main(String[] args) {
        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        try {
            int index = Integer.parseInt(args[0]);
            System.out.println(elements[index]);
        } catch (ArrayIndexOutOfBoundsException | NumberFormatException e) {
            System.err.println("Invalid index or no argument provided.");
        }
    }
}