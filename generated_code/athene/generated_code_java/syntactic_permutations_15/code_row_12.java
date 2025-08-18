import java.util.Scanner;

public class ArrayIndexFetcher {
    private static int[] id_sequence = {1, 2, 3, 4, 5};

    public static void main(String[] args) {
        System.out.println(fetchValueFromSequence());
    }

    public static int fetchValueFromSequence() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index value: ");
        int index = scanner.nextInt();
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds");
        }
        return id_sequence[index];
    }
}