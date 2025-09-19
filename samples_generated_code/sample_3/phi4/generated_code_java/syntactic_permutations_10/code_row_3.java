import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array; modify as needed
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer index: ");
        int index = scanner.nextInt();
        
        int result = getValueFromArray(id_sequence, id_sequence.length, index);
        System.out.println(result);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
    }
}