import java.util.Arrays;

public class ArrayElementFetcher {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No index provided.");
            return;
        }
        
        int[] numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 0 && index < numbers.length) {
                System.out.println(numbers[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index format.");
        }
    }
}