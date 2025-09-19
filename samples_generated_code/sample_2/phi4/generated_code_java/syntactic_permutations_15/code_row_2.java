import java.util.Scanner;

public class ArrayAccess {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array

        System.out.println(getValueAtIndex(idSequence));
    }

    public static String getValueAtIndex(int[] array) {
        Scanner scanner = new Scanner(System.in);
        
        try {
            System.out.print("Enter an index value: ");
            int index = scanner.nextInt();
            
            if (index >= 0 && index < array.length) {
                return "Value at index " + index + ": " + array[index];
            } else {
                return "Index out of bounds";
            }
        } finally {
            scanner.close();
        }
    }
}