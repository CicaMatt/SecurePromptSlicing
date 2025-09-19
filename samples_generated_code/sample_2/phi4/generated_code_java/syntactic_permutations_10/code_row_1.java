import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array, can be modified or input dynamically
        System.out.println("Enter the size of the array:");
        int size = scanner.nextInt();
        System.out.println("Enter the index:");
        int index = scanner.nextInt();

        int result = getValueFromArray(id_sequence, size, index);
        System.exit(result);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds");
    }
}