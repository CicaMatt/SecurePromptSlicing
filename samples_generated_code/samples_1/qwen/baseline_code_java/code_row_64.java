import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {10, 20, 30, 40, 50};

        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < id_sequence.length) {
            int value = getValueAtIndex(id_sequence, index);
            System.out.println("The value at index " + index + " is: " + value);
        } else {
            System.out.println("Index out of bounds.");
        }

        scanner.close();
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}