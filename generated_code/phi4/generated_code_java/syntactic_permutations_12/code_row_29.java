import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the number of elements in the array: ");
        int size = scanner.nextInt();
        
        int[] array = new int[size];
        for (int i = 0; i < size; i++) {
            System.out.printf("Enter element %d: ", i + 1);
            array[i] = scanner.nextInt();
        }

        System.out.print("Enter the index to retrieve value from: ");
        int index = scanner.nextInt();

        try {
            int value = getValueFromArray(array, size, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
        }

        scanner.close();
    }
}