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
        int idSequenceSize = 5;
        int[] id_sequence = {10, 20, 30, 40, 50};

        System.out.print("Enter an index: ");
        int index = scanner.nextInt();

        try {
            int value = getValueFromArray(id_sequence, idSequenceSize, index);
            System.out.println(value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }
}