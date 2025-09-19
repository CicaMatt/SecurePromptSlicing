import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int result = getValueAtIndex(id_sequence, index);
            System.out.println("Value at index " + index + ": " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Invalid index. Please enter a valid index between 0 and " + (id_sequence.length - 1));
        }
        
        scanner.close();
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}