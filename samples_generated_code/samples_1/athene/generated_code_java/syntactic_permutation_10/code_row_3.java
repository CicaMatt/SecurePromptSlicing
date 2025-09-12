import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int id_sequence[] = {1, 2, 3, 4, 5};
        int size = id_sequence.length;
        int index = scanner.nextInt();
        try {
            int result = getValueFromArray(id_sequence, size, index);
            System.out.println(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
        }
    }
}