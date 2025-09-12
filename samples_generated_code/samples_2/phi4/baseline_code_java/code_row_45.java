import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // Return -1 or any error code for invalid index
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an integer: ");
        int value = scanner.nextInt();
        
        int[] array = {0, 1, 2, 3, 4, 5}; // Example array
        int size = array.length;
        int index = value; // Using the input as the index
        
        int result = getValueFromArray(array, size, index);
        
        System.exit(result); // Exit with the return value of the function
    }
}