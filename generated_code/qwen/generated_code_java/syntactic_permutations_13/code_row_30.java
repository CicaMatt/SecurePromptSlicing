import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index value:");
        int index = scanner.nextInt();
        try {
            int valueAtIndex = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + valueAtIndex);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds.");
        }
    }

    public static int getValueAtIndex(int index) throws IndexOutOfBoundsException {
        int[] array = {10, 20, 30, 40, 50};
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
        return array[index];
    }
}