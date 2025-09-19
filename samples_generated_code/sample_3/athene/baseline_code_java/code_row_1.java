import java.util.Scanner;

public class ArrayIndexRetriever {
    private static int[] id_sequence = {1, 2, 3, 4, 5};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        int valueAtIndex = getValueAtIndex(index);
        System.out.println("Value at index " + index + ": " + valueAtIndex);
    }

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return id_sequence[index];
    }
}