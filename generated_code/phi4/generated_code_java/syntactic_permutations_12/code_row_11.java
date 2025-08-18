import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // Return -1 for invalid index
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the value: ");
        int inputValue = scanner.nextInt();
        
        int[] exampleArray = {10, 20, 30, 40, 50}; // Example array
        int size = exampleArray.length;
        int index = 2; // Example index
        
        int result = getValueFromArray(exampleArray, size, index);
        System.exit(result);
    }
}