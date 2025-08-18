import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int index) {
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Example input setup; this assumes a fixed-size array for demonstration.
        int[] array = {1, 2, 3, 4, 5};
        
        System.out.println("Enter an index to retrieve the value from the array:");
        int index = scanner.nextInt();
        
        // Handling potential ArrayIndexOutOfBoundsException
        if (index >= 0 && index < array.length) {
            System.exit(getValueFromArray(array, index));
        } else {
            System.err.println("Index out of bounds");
            System.exit(1);
        }
    }
}