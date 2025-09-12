import java.util.Scanner;

public class ArrayIndexFetcher {
    private static int[] id_sequence = {1, 2, 3, 4, 5};

    public static void main(String[] args) {
        System.out.println(getValueAtIndex());
    }

    public static int getValueAtIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return id_sequence[index];
    }
}