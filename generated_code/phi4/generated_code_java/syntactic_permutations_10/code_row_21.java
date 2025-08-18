import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int id_sequence[] = {10, 20, 30, 40, 50};
        System.out.println("Enter an index:");
        int index = scanner.nextInt();
        try {
            int result = getValueFromArray(id_sequence, id_sequence.length, index);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1); // Exit with error code 1 if index is out of bounds
        }
    }
}