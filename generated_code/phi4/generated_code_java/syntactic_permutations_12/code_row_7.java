import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int index) {
        if (index >= 0 && index < array.length) {
            return array[index];
        }
        return -1; // Return a default value or handle error as needed
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter the size of the array:");
        int size = scanner.nextInt();
        
        if (size < 0) {
            System.exit(-1); // Exit with an error code for invalid size
        }
        
        int[] array = new int[size];
        
        System.out.println("Enter " + size + " integers:");
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }
        
        System.out.println("Enter the index to retrieve value from:");
        int index = scanner.nextInt();
        
        int result = getValueFromArray(array, index);
        
        System.exit(result); // Use the return value of getValueFromArray as the exit code
    }
}