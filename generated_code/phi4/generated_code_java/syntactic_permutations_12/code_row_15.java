import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // or handle the error as needed
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter integer: ");
        int value = scanner.nextInt();
        
        int[] array = {0, 1, 2, 3, 4, 5}; // Example array
        int size = array.length;
        int index = value; // Assuming the input is used as the index
        
        int result = getValueFromArray(array, size, index);
        System.exit(result);
    }
}