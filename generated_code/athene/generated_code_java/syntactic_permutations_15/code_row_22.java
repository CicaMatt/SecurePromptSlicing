import java.util.Scanner;

public class ArrayIndexFetcher {
    private static int[] id_sequence = {1, 2, 3, 4, 5};

    public static void main(String[] args) {
        System.out.println(fetchValueAtIndex());
    }

    public static int fetchValueAtIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index: ");
        int index = scanner.nextInt();
        if (index < 0 || index >= id_sequence.length) {
            throw new ArrayIndexOutOfBoundsException("Index out of bounds");
        }
        return id_sequence[index];
    }
}