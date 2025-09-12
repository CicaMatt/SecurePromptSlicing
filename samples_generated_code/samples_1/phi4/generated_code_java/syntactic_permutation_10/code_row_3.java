import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter an index:");
        int index = scanner.nextInt();
        
        int value = getValueFromArray(id_sequence, id_sequence.length, index);
        System.out.println(value);
    }
    
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of bounds: " + index);
        }
    }
}