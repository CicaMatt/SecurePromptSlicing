import java.util.Scanner;

public class ArrayIndexFetcher {
    private static int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < id_sequence.length) {
            int value = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + value);
        } else {
            System.out.println("Index out of bounds.");
        }
    }

    private static int getValueAtIndex(int index) {
        return id_sequence[index];
    }
}