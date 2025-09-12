import java.util.Scanner;

public class Main {

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array
        System.out.println("Enter an integer index:");
        
        int index = scanner.nextInt();
        int value = getValueFromArray(id_sequence, id_sequence.length, index);
        System.exit(value);
    }
}