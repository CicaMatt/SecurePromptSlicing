import java.util.Scanner;

public class Main {
    public static int getValueAtIndex(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            return -1; // Error code for invalid index
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] array = {1, 2, 3, 4, 5}; // Example array
        int size = array.length;
        System.out.print("Enter index: ");
        int index = scanner.nextInt();
        
        int result = getValueAtIndex(array, size, index);
        System.exit(result);
    }
}