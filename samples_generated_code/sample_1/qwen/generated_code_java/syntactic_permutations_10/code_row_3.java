import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {10, 20, 30, 40, 50};
        int size = id_sequence.length;
        int index = scanner.nextInt();
        try {
            int value = getValueFromArray(id_sequence, size, index);
            System.out.println(value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
        scanner.close();
    }
}