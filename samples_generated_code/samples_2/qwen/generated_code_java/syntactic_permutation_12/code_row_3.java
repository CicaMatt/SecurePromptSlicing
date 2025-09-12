import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        throw new IndexOutOfBoundsException("Index is out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int value = scanner.nextInt();
        int[] array = {1, 2, 3, 4, 5}; // Example array
        int size = array.length;
        int index = value;

        try {
            int result = getValueFromArray(array, size, index);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}