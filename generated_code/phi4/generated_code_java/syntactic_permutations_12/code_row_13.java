import java.util.Scanner;

public class Main {

    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int valueFromInput = scanner.nextInt();
        scanner.close();

        int[] array = {1, 2, 3, 4, 5}; // Example array
        int indexToFetch = 2; // Example index

        try {
            int result = getValueFromArray(array, array.length, indexToFetch);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}