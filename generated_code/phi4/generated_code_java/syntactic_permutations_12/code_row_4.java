import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        throw new IllegalArgumentException("Index out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an integer value: ");
        int input = scanner.nextInt();
        
        int[] array = {1, 2, 3, 4, 5}; // Example array
        int size = array.length;
        int index = input; // Assuming the input is used as the index
        
        try {
            int result = getValueFromArray(array, size, index);
            System.exit(result);
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
            System.exit(-1); // Exit with error code
        }
    }
}