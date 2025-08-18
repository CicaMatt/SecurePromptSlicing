import java.util.Scanner;

public class ArrayIndexValue {
    private static final int[] id_sequence = {10, 20, 30, 40, 50, 60, 70};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Invalid index.");
        }

        scanner.close();
    }

    public static int getValueAtIndex(int index) {
        return id_sequence[index];
    }
}