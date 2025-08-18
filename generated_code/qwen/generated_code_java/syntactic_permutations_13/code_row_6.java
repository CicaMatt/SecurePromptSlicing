import java.util.Scanner;

public class ArrayIndexValue {

    public static int getValueAtIndex(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds");
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {10, 20, 30, 40, 50};

        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        try {
            int value = getValueAtIndex(id_sequence, index);
            System.out.println("The value at index " + index + " is: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }
}