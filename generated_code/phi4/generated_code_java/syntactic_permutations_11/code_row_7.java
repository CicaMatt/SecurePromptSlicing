import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter an index:");
        int index = scanner.nextInt();
        
        System.exit(getValueFromArray(id_sequence, id_sequence.length, index));
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            System.out.println("Index out of bounds");
            return -1; // or any error code
        }
    }
}