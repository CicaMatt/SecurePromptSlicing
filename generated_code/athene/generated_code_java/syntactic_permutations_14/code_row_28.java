import java.util.Scanner;

public class ArrayValueFetcher {
    public static int fetchValueAtIndex(int[] array) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int index = scanner.nextInt();
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds");
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] sampleArray = {1, 2, 3, 4, 5};
        try {
            int value = fetchValueAtIndex(sampleArray);
            System.out.println("Value at index: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}