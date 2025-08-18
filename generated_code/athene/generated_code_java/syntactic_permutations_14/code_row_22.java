import java.util.Scanner;

public class IndexFinder {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        if (index >= 0 && index < id_sequence.length) {
            System.out.println("Value at index " + index + ": " + getValueAtIndex(id_sequence, index));
        } else {
            System.out.println("Index out of bounds.");
        }
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}