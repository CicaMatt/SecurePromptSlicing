import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        try {
            int value = getValueAtIndex(id_sequence);
            System.out.println("Value at the specified index: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index is out of bounds.");
        }
    }

    public static int getValueAtIndex(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int index = scanner.nextInt();
        return id_sequence[index];
    }
}