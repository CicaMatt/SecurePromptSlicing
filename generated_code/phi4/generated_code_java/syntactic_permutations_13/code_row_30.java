import java.util.Scanner;

public class ArrayIndexValue {

    public static int getValueAtIndex(int[] array, int index) {
        if (index >= 0 && index < array.length) {
            return array[index];
        } else {
            throw new IllegalArgumentException("Index out of bounds");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] array = {10, 20, 30, 40, 50};
        
        System.out.println("Enter an index value:");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAtIndex(array, index);
            System.out.println("Value at index " + index + " is: " + value);
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
        
        scanner.close();
    }
}