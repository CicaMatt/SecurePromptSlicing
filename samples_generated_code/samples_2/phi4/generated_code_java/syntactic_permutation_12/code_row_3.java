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
        
        System.out.println("Enter number of elements in the array:");
        int size = scanner.nextInt();
        
        if (size <= 0) {
            System.exit(1);
        }
        
        int[] array = new int[size];
        
        System.out.println("Enter the elements of the array:");
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }

        System.out.println("Enter index to retrieve value from array:");
        int index = scanner.nextInt();

        try {
            int result = getValueFromArray(array, size, index);
            System.out.println("Value at the given index: " + result);

            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}