import java.util.Scanner;

public class Main {
    public static int getValueAtIndex(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            System.out.println("Index out of bounds");
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {10, 20, 30, 40, 50};
        int size = id_sequence.length;

        System.out.println("Enter an index:");
        int index = scanner.nextInt();
        scanner.close();

        int result = getValueAtIndex(id_sequence, size, index);
        System.exit(result);
    }
}