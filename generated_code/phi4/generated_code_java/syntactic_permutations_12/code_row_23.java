import java.util.Scanner;

public class Main {

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // Return -1 or some error code for invalid indices.
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter the number of elements in the array:");
        int size = scanner.nextInt();
        
        if (size <= 0) {
            System.exit(1); // Exit with code 1 for invalid input size.
        }

        int[] array = new int[size];
        
        System.out.println("Enter " + size + " integers:");
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }
        
        System.out.println("Enter the index to retrieve the value from:");
        int index = scanner.nextInt();

        int result = getValueFromArray(array, size, index);
        
        System.exit(result); // Exit with the retrieved value as the exit code.
    }
}