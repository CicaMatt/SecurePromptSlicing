import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds");
    }

    public static void main(String[] args) {
        int id_sequence[] = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index:");
        int index = scanner.nextInt();
        try {
            int value = getValueFromArray(id_sequence, id_sequence.length, index);
            System.out.println(value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}