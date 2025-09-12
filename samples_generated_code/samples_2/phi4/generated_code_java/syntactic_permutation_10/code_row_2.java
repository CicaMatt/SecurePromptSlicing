import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds");
    }

    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        scanner.close();

        try {
            int result = getValueFromArray(id_sequence, id_sequence.length, index);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}