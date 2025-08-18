import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter size of array:");
        int size = scanner.nextInt();
        
        int[] array = new int[size];
        
        System.out.println("Enter elements of the array:");
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }
        
        System.out.println("Enter index to get value from array:");
        int index = scanner.nextInt();
        
        int result = getValueFromArray(array, size, index);
        System.out.println("Value at index " + index + ": " + result);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of bounds: " + index);
        }
    }
}