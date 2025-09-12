import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array; replace with actual values if needed.
        int size = id_sequence.length;
        
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        
        int result = getValueFromArray(id_sequence, size, index);
        System.exit(result);
    }
    
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            throw new IllegalArgumentException("Index out of bounds");
        }
    }
}