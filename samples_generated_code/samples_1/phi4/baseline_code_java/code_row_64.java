import java.util.Scanner;

public class ArrayIndexValue {

    private static final int[] ID_SEQUENCE = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAtIndex(index);
            System.out.println("Value at index " + index + " is: " + value);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Invalid index. Please enter a value between 0 and " + (ID_SEQUENCE.length - 1) + ".");
        }
        
        scanner.close();
    }

    public static int getValueAtIndex(int index) {
        return ID_SEQUENCE[index];
    }
}