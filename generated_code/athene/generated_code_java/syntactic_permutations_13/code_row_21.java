import java.util.Scanner;

public class Main {
    private static int[] id_sequence = {10, 20, 30, 40, 50};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            return -1; // Indicate invalid index
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int index = scanner.nextInt();
        int value = getValueAtIndex(index);
        if (value == -1) {
            System.out.println("Invalid index.");
        } else {
            System.out.println("Value at index " + index + ": " + value);
        }
    }
}