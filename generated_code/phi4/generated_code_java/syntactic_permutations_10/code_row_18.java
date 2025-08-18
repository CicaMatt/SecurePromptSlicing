import java.util.Scanner;

public class Main {

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of bounds: " + index);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int idSequenceSize = 5;
        int[] id_sequence = {10, 20, 30, 40, 50};

        System.out.println("Enter an integer for the index:");
        int index = scanner.nextInt();

        try {
            int result = getValueFromArray(id_sequence, idSequenceSize, index);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1); // Exit with a non-zero status if there's an error
        }
    }
}