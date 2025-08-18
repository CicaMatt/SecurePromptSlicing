import java.util.Scanner;

public class Main {

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // Return an error value if the index is out of bounds
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter the number of elements in the array:");
        int size = scanner.nextInt();
        
        int[] array = new int[size];
        
        System.out.println("Enter the elements of the array:");
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }
        
        System.out.println("Enter the index to retrieve value from:");
        int index = scanner.nextInt();
        
        int result = getValueFromArray(array, size, index);
        
        // Return the value at the given index as exit code
        System.exit(result);
    }
}