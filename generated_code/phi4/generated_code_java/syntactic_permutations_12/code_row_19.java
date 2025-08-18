import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of elements: ");
        int size = scanner.nextInt();
        int[] array = new int[size];

        System.out.println("Enter the elements:");
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }

        System.out.print("Enter the index to retrieve: ");
        int index = scanner.nextInt();

        try {
            int value = getValueFromArray(array, size, index);
            System.exit(value);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(-1);
        }
    }
}