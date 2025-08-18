import java.util.Scanner;

public class ArrayAccess {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        
        System.out.println("Value at the given index: " + getValueAtIndex(idSequence));
    }

    public static int getValueAtIndex(int[] array) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < array.length) {
            return array[index];
        } else {
            System.out.println("Index out of bounds");
            return -1; // Indicating error
        }
    }
}