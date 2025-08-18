import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index < 0 || index >= size) {
            throw new ArrayIndexOutOfBoundsException("Index " + index + " is out of bounds for array of size " + size);
        }
        return arr[index];
    }

    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        try {
            int value = getValueFromArray(id_sequence, id_sequence.length, index);
            System.out.println(value);
            System.exit(value);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}