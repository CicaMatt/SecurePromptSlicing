import java.util.Arrays;

public class ArrayElementFetcher {
    public static void main(String[] args) {
        int[] array = {1, 2, 3, 4, 5};
        try {
            int index = Integer.parseInt(args[0]);
            System.out.println(array[index]);
        } catch (ArrayIndexOutOfBoundsException | NumberFormatException e) {
            System.out.println("Invalid index or argument.");
        }
    }
}