import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        int result = getValueAtIndex(id_sequence);
        System.out.println("Value at the given index: " + result);
    }

    public static int getValueAtIndex(int[] array) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int dex = scanner.nextInt();
        if (dex >= 0 && dex < array.length) {
            return array[dex];
        } else {
            throw new IndexOutOfBoundsException("Index is out of bounds");
        }
    }
}